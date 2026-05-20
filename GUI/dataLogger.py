import random
import  serial, csv, re, time
import serial.tools.list_ports
import eCVTGUI
import json

baud_rate = 115200
log_filename = 'sensor_data.csv'
uc_connected = False

# Function to find the serial port connected to the STM microcontroller 
def find_serial_port(keyword="STLink", exclude_com= ""):
    # List all available serial ports and check for the one that matches the keyword in its description and does not match the excluded COM port
    ports = serial.tools.list_ports.comports()
    for port in ports :
        if keyword.lower() in port.description.lower() and exclude_com.lower() not in port.device.lower():
            return port.device
    return None

#TODO: Switch when finished developing
#serial_port = find_serial_port("STLink", "XXXX") 
serial_port = None

# Check if the serial port was found and establish connection
# If no serial port is found, gui will not run
if serial_port is None:
    #TODO: Remove when finished developing
    uc_connected = True
    print("STM microcontroller not found. Please check the connection in the device manager and try again.")
else:
    uc_connected = True
    print(f"Using port: {serial_port}")
    ser = serial.Serial(serial_port, baud_rate, timeout=1)

# Function to log sensor data to a CSV file
def log_sensor_data(times, engine_rpms, box_rpms):
    # Configure serial port parameters
    with open(log_filename, mode='w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["Timestamp", "Engine RPM", "Box RPM"]) # Write header
        for time, engine_rpm, box_rpm in zip(times, engine_rpms, box_rpms):
            writer.writerow([time, engine_rpm, box_rpm]) # Write data row
    csvfile.close()

# Function to request log download from microcontroller and log the data to a CSV file
# Used when RF code is implemented 
def download_log_request():
    # Send command to microcontroller to request log download and read incoming data until "COMPLETE" is received, then log the data to a CSV file
    ser.write(f'DOWNLOAD_LOG\n'.encode()) # Send command to request log download
    time.sleep(1) # Small delay to ensure microcontroller processes the command
    start_time = time.time()
    times = []
    engine_rpms = []
    box_rpms = []
    while True:
        if ser.in_waiting > 0:
            # Read line from serial port and decode it
            line = ser.readline().decode('utf-8', errors='ignore').strip()
            
            # Optional: If you still want to exit early when a specific message arrives
            if "COMPLETE" in line:
                print("Received completion signal.")
                break
            else:
                log_line = line.split(",")
                if len(log_line) == 3: # Check if the line has the expected number of values
                    times.append(log_line[0])
                    engine_rpms.append(log_line[1])
                    box_rpms.append(log_line[2])
    
    log_sensor_data(times, engine_rpms, box_rpms) # Log data to CSV file
    return time.time() - start_time

# Function to request log download from microcontroller via USB and log the data to a CSV file, then update the dropdown menu with the new log files
def receive_logs_from_usb_request(gui_app):
    # Establish connection to eCVT microcontroller via USB
    eCVT_ser_port = None
    if(serial_port is None):
        eCVT_ser_port = find_serial_port(keyword="STLink", exclude_com="XXXX")
    else:
        eCVT_ser_port = find_serial_port(keyword="STLink", exclude_com=serial_port)
        
    # If no serial port is found, print an error message and update the GUI status label
    if(eCVT_ser_port is None):
        print("eCVT microcontroller not found.")
        gui_app.status_label.config(text="eCVT microcontroller not found. Check connection in the device manager.", bg="#e0e0e0")
        return 0
    else:
        # If a serial port is found, establish a connection and send the command to request log download
        print(f"Using port: {eCVT_ser_port} for eCVT log download.")
        eCVT_ser = serial.Serial(eCVT_ser_port, baud_rate, timeout=1)
        # Send request to eCVT microcontroller to send log files over USB
        eCVT_ser.write(f'DOWNLOAD_LOG\n'.encode()) # Send command to request log download        

        total_logs_received = 0
        line = "LOG0.txt"
        wait_for_first_line = 0
        LOG_PID_DICT = {}
        LOG_PIDs = []
        # Wait until "COMPLETE" is received meaning all log files have been sent
        while True:
            # Wait to receive log line
            line = eCVT_ser.readline().decode('utf-8', errors='ignore').strip()
            if line and line != "DOWNLOAD_LOG\n":
                # Create new log file if the log file name is received
                if("LOG" in line):
                    log_filename = line.split(".")[0] + "_eCVT.csv"
                    print("New log " + log_filename)
                    total_logs_received += 1
                    if(log_filename != "LOG0_eCVT.csv"):
                        LOG_PIDs = []
                        csvLogFile.close() # Close previous log file if it exists
                    csvLogFile = open(log_filename, mode='w', newline='')
                    writer = csv.writer(csvLogFile)
                    wait_for_first_line = 0
                # All log files have been sent
                elif("COMPLETE" in line):
                    print("Received completion signal.")
                    break
                # Log the log data point into the current log file
                else:
                    log_data = line.split(" ") # Assuming data is space-separated
                    # If the line contains 4 values it is a PID line and needs to be stored to be saved in the JSON file
                    if(len(log_data) == 4):
                        LOG_PIDs.append(line)
                    # If the line contains 3 values it is a data line and needs to be logged into the current log file
                    if len(log_data) == 3: # Check if the line has the expected number of values
                        if wait_for_first_line == 0:
                            writer.writerow(["Timestamp", "Engine RPM", "Box RPM"]) # Write header
                            LOG_PID_DICT[log_filename] = LOG_PIDs
                            wait_for_first_line = 1
                        writer.writerow(log_data) # Write data row
        # Create list of log file options for the drop down selection
        log_file_options = []
        for i in range(total_logs_received):
            log_file_options.append(f"LOG {i}")
        # Update the GUI dropdown log selection menu with the new log files that were received
        update_log_selection_dropdown(gui_app, log_file_options) # Update the dropdown menu
        # Save the log PID dictionary to a JSON file
        with open("log_PIDs.json","w") as f:
            json.dump(LOG_PID_DICT, f, indent=4)
            f.close()
        # close serial connection
        eCVT_ser.close()

# Function to send a request to the microcontroller to delete a log file from the USB storage, then update the dropdown menu with the new log files
def delete_log_from_usb_request(gui_app, log_filename):
    # Ensure the eCVT microcontroller is plugged in
    eCVT_ser_port = None
    if(serial_port is None):
        eCVT_ser_port = find_serial_port(keyword="STLink", exclude_com="XXXX")
    else:
        eCVT_ser_port = find_serial_port(keyword="STLink", exclude_com=serial_port)
    # If no serial port is found, print an error message and update the GUI status label
    if(eCVT_ser_port is None):
        print("eCVT microcontroller not found.")
        gui_app.status_label.config(text="eCVT microcontroller not found. Check connection in the device manager.", bg="#e0e0e0")
        return 0
    else:
        print(f"Using port: {eCVT_ser_port} for eCVT log download.")
        eCVT_ser = serial.Serial(eCVT_ser_port, baud_rate, timeout=1)
        # Send command to eCVT microcontroller to delete log file from USB storage
        eCVT_ser.write(f'DELETE {log_filename}\n'.encode()) # Send command to request log download
        # close serial connection
        eCVT_ser.close()

# Function to update the log selection dropdown menu in the GUI with new log file options
def update_log_selection_dropdown(gui_app, options):
    # 1. Update your data list
    gui_app.logFileoptions = options # Or your logic to get files
    # 2. Access the internal menu widget
    menu = gui_app.selection_menu["menu"]
    # 3. Clear the existing menu options
    menu.delete(0, "end")
    # 4. Rebuild the menu with new options
    for option in gui_app.logFileoptions:
        menu.add_command(
            label=option,
            command=lambda value=option: [
                gui_app.logfile_selection_dropdown.set(value), # Sets the variable
                gui_app.update_graph_with_selected_log(value)  # Triggers the logic
            ]
        )

    # Optional: Automatically select the first new option
    if gui_app.logFileoptions:
        gui_app.logfile_selection_dropdown.set(gui_app.logFileoptions[0])
    
# Function to send a request to the microcontroller to change the PID values, then wait for a completion signal from the microcontroller
def change_PID_request(PID_values):
    ser.reset_input_buffer()
    for entry in PID_values:
        ser.write(f'PID {entry}\n'.encode())
        time.sleep(0.5)
    return wait_for_completion()
# Function to send a request to the microcontroller to change the logging rate, then wait for a completion signal from the microcontroller
def change_logging_rate_request(rate):
    ser.write(f'CHANGE_RATE {rate}\n'.encode())
    time.sleep(1) # Small delay to ensure microcontroller processes the command
    return wait_for_completion()

# Function to send a request to the microcontroller to test the RF connection, then wait for a completion signal from the microcontroller
def test_rf_connection_request():
    ser.reset_input_buffer()
    ser.reset_output_buffer()
    # Send command to USER side microcontroller to send a message to the eCVT microcontroller and wait for a response
    ser.write(b'TEST_RF\n')
    return wait_for_completion()

# Function to wait for a completion signal from the microcontroller, returns 1 if "COMPLETE" is received, 0 if "RF_ERROR" is received, and 2 if timeout occurs
def wait_for_completion():
    start_time = time.time()
    timeout_duration = 3 # seconds

    while time.time() - start_time < timeout_duration:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8', errors='ignore').strip()
            if line == "COMPLETE":
                return 1
            elif line == "RF_ERROR":
                return 0
    return 2


if __name__ == "__main__":
    pass