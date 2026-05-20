import sys
import tkinter as tk
from tkinter import ttk, messagebox
import random, json
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt 
import dataLogger
import time
from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg, NavigationToolbar2Tk)

# TODO
# Find why saved PID values are only 2 decimal places instead of 3
# Ensure log files are being deleted

# Global Hex codes
BG_color = "#e57c3a"
connected_color = "#00a925"
disconnected_color = "#b70000" 
FR_color = "#ffffff"
BOX_color = "#363636"
# Fonts
global_font = "Arial"
global_font_size = 14

#Global variables
# P1, I1, D1 = Low RPM
# P2, I2, D2 = Low Gear
# P3, I3, D3 = High RPM
# P4, I4, D4 = High Gear
PID_VALUES = {"P1":0.0,"I1":0.0,"D1":0.0, 
              "P2":0.0,"I2":0.0,"D2":0.0,
              "P3":0.0,"I3":0.0,"D3":0.0, 
              "P4":0.0,"I4":0.0,"D4":0.0,
              "SetPoint1":0,"SetPoint2":0,"SetPoint3":0,"SetPoint4":0}
# Presets are arrays with Index 0 -> P1, Index 1 -> I1, Index 2 -> D1, etc.
PRESET1_PID_VALUES = [0.0] *16
PRESET2_PID_VALUES = [0.0] *16
PRESET3_PID_VALUES = [0.0] *16
PIDHistory = [0.0]*48  # 4 sets of 12 PID values
LOG_RATE = 0

class App(tk.Tk):
    def __init__(self):
        super().__init__()
        # --- Window Setup ---
        self.title("eCVT GUI Control")
        self.state('zoomed')
        self.configure(bg= BG_color)
        self.resizable(True, True)
        self.load_config()
        self.init_GUI()
        self.load_current_logs()
        

    def init_GUI(self):
        # Main frame
        mainFrame = tk.Frame(self)
        mainFrame.pack(fill="both", expand=True, padx=10, pady=10)
        # Left column
        leftCol = tk.Frame(mainFrame,bg=BG_color)
        leftCol.pack(side="left", fill="both", expand=True)
        # Right column
        rightCol = tk.Frame(mainFrame,bg=BG_color)
        rightCol.pack(side="right", fill="both")

        # RF Frame
        frameRF  = tk.Frame(leftCol, bg=FR_color, bd=2, relief="solid", height=40, width=400)
        frameRF.pack(fill="both", pady=10)
        # Status indicator
        self.rf_status_label = tk.Label(frameRF, text= "Current RF Status: Untested", bg="#e0e0e0", font=(global_font,global_font_size))
        self.rf_status_label.pack(side="left", pady=5,padx=5)
        # Test button
        ttk.Button(frameRF, text="Test", command=self.test_rf_connection).pack(side="left", padx=10, pady=10)
        # Status message area
        self.status_label = tk.Label(frameRF, text="", bg="#e0e0e0", font=(global_font,global_font_size), width=60)
        self.status_label.pack(side="right", pady=5,padx=5)
        status_colors_text = tk.Label(frameRF, text="Status: ", bg="#e0e0e0", font=(global_font,global_font_size))
        status_colors_text.pack(side="right", pady=5)


        # Logging Frame
        frameLOG = tk.Frame(leftCol, bg=FR_color, bd=2, relief="solid", height=800, width=600)
        frameLOG.pack(fill="both", expand=True, pady=10)
        # Logging rate
        frameLOGRATE = tk.Frame(frameLOG, bg=FR_color, bd=2, relief="solid", height=100, width=40)
        frameLOGRATE.pack(fill="both", pady=10, padx=10, side="left")
        tk.Label(frameLOGRATE, text="Configure Logging Rate", bg=BG_color, font=(global_font,global_font_size)).pack(side="top", pady=5,padx=10)
        tk.Label(frameLOGRATE, text="(Number of readings before log point)", bg=BG_color, font=(global_font,global_font_size)).pack(side="top", pady=5,padx=10)
        self.logging_rate_label = tk.Label(frameLOGRATE, text=str(LOG_RATE), bg=BG_color, font=(global_font,global_font_size))
        self.logging_rate_label.pack(side="bottom", pady=10,padx=10)
        self.logging_rate_scale = ttk.Scale(frameLOGRATE, from_=5, to=1, orient="vertical", length=550, command=self.update_logging_rate_label)
        self.logging_rate_scale.pack(side="top", padx=10, pady=10, expand=True)
        self.logging_rate_scale.set(LOG_RATE)
        logging_rate_set_button = ttk.Button(frameLOGRATE, text="Set Logging Rate", command=self.set_logging_rate)
        logging_rate_set_button.pack(side="bottom", pady=10)

        # Frame for log buttons and graph
        frameLOGRIGHTCOL = tk.Frame(frameLOG, bg=FR_color, height=100, width=100)
        frameLOGRIGHTCOL.pack(fill="both", expand=True, pady=10, side="right")
        # Log buttons frame
        frameLOGBUTTONS = tk.Frame(frameLOGRIGHTCOL, bg=FR_color, height=20, width=100)
        frameLOGBUTTONS.pack(fill="both", pady=5, side="top")
        # Log download button
        tk.Button(frameLOGBUTTONS, text="Download Log Files", command=self.download_log_file_usb, width=25, height=5).pack(side="left", padx=10, pady=10)
        #Logo
        logo = tk.PhotoImage(file="logo.png")
        logo_label = tk.Label(frameLOGBUTTONS, image=logo)
        logo_label.image = logo  # keep reference
        logo_label.place(relx=0.5, rely=0.5, anchor="e")
        # Log file selection dropdown
        self.logfile_selection_dropdown = tk.StringVar(value="")
        self.logFileoptions = []
        self.selection_menu = tk.OptionMenu(frameLOGBUTTONS, self.logfile_selection_dropdown, "", command=self.update_graph_with_selected_log)
        self.selection_menu.pack(pady=5, padx=5, side="right")
        # Delete log button
        tk.Button(frameLOGBUTTONS, text="Delete Log File", command=self.delete_log_file_usb, width=25, height=5).pack(side="right", padx=10, pady=10)

        # PID value label
        self.log_pid_value_label = tk.Label(frameLOGBUTTONS, text="Log PID Values:", bg=BG_color, font=(global_font,global_font_size))
        self.log_pid_value_label.pack(side="right", pady=5)
        # Graph frame placeholder
        frameLOGGRAPH = tk.Frame(frameLOGRIGHTCOL, bg=BOX_color, bd=2, relief="solid", height=100, width=200)
        frameLOGGRAPH.pack(fill="both", pady=10, padx=10, side="bottom")
        # MPH vs RPM Graph
        figMPHvsRPM, self.ax1 = plt.subplots()
        self.canvas = FigureCanvasTkAgg(figMPHvsRPM, master=frameLOGGRAPH)
        self.canvas.get_tk_widget().pack(fill="both", expand=True, side="top")
        self.ax1.set_title("Shift Curve")
        self.ax1.set_xlabel("Rear wheel speed (MPH)")
        self.ax1.set_ylabel("Engine RPM")
        toolbar1 = NavigationToolbar2Tk(self.canvas, frameLOGGRAPH, pack_toolbar=False)
        toolbar1.update()
        toolbar1.pack(anchor="w", fill = tk.X, side="top")
        
        # TIME vs RPM Graph
        figTIMEvsRPM, self.ax2 = plt.subplots()
        self.ax2.set_title("Shift RPM")
        self.ax2.set_xlabel("Time (Sec)")
        self.ax2.set_ylabel("Engine RPM")
        self.canvas2 = FigureCanvasTkAgg(figTIMEvsRPM, master=frameLOGGRAPH)
        self.canvas2.get_tk_widget().pack(fill="both", expand=True, side="bottom")
        toolbar2 = NavigationToolbar2Tk(self.canvas2, frameLOGGRAPH, pack_toolbar=False)
        toolbar2.update()
        toolbar2.pack(anchor="w", fill = tk.X, side="bottom")


        # PID Frame
        framePID = tk.Frame(rightCol, bg=FR_color, bd=2, relief="solid", height=800, width=400)
        framePID.pack(fill="both",expand=True, padx=10)
        tk.Label(framePID, text="Control Loop Tuning", bg=BG_color, font=(global_font,global_font_size)).pack(side="top", pady=5,padx=10)
        # Individual Entries
        pidframes = tk.Frame(framePID, bg=FR_color)
        pidframes.pack(fill="both", expand=True, pady=10, side="top")
        tk.Label(pidframes, text="Current PID Values:", bg=FR_color, font=(global_font, 11, "bold")).pack(side="top", pady=5)
        
        # PID vert columns for current values and entry boxes
        # P column
        colP = tk.Frame(pidframes, bg=FR_color)
        colP.pack(side="left", expand=True, padx=5)
        tk.Label(colP, text="P", bg=FR_color, font=(global_font, 11, "bold")).pack()
        self.PID_P1_label = tk.Label(colP, text=PID_VALUES["P1"], bg=FR_color)
        self.PID_P1_label.pack()
        self.PID_P2_label = tk.Label(colP, text=PID_VALUES["P2"], bg=FR_color)
        self.PID_P2_label.pack()
        self.PID_P3_label = tk.Label(colP, text=PID_VALUES["P3"], bg=FR_color)
        self.PID_P3_label.pack()
        self.PID_P4_label = tk.Label(colP, text=PID_VALUES["P4"], bg=FR_color)
        self.PID_P4_label.pack()
        tk.Label(colP, text="", bg=FR_color).pack()
        self.PID_P1_entry = tk.Entry(colP, bg=BG_color, width=10)
        self.PID_P1_entry.pack()
        self.PID_P2_entry = tk.Entry(colP, bg=BG_color, width=10)
        self.PID_P2_entry.pack()
        self.PID_P3_entry = tk.Entry(colP, bg=BG_color, width=10)
        self.PID_P3_entry.pack()
        self.PID_P4_entry = tk.Entry(colP, bg=BG_color, width=10)
        self.PID_P4_entry.pack()
        # I column
        colI = tk.Frame(pidframes, bg=FR_color)
        colI.pack(side="left", expand=True, padx=5)
        tk.Label(colI, text="I", bg=FR_color, font=(global_font, 11, "bold")).pack()
        self.PID_I1_label = tk.Label(colI, text=PID_VALUES["I1"], bg=FR_color)
        self.PID_I1_label.pack()
        self.PID_I2_label = tk.Label(colI, text=PID_VALUES["I2"], bg=FR_color)
        self.PID_I2_label.pack()
        self.PID_I3_label = tk.Label(colI, text=PID_VALUES["I3"], bg=FR_color)
        self.PID_I3_label.pack()
        self.PID_I4_label = tk.Label(colI, text=PID_VALUES["I4"], bg=FR_color)
        self.PID_I4_label.pack()
        tk.Label(colI, text="", bg=FR_color).pack()
        self.PID_I1_entry = tk.Entry(colI, bg=BG_color, width=10)
        self.PID_I1_entry.pack()
        self.PID_I2_entry = tk.Entry(colI, bg=BG_color, width=10)
        self.PID_I2_entry.pack()
        self.PID_I3_entry = tk.Entry(colI, bg=BG_color, width=10)
        self.PID_I3_entry.pack()
        self.PID_I4_entry = tk.Entry(colI, bg=BG_color, width=10)
        self.PID_I4_entry.pack()
        # D column
        colD = tk.Frame(pidframes, bg=FR_color)
        colD.pack(side="left", expand=True, padx=5)
        tk.Label(colD, text="D", bg=FR_color, font=(global_font, 11, "bold")).pack()
        self.PID_D1_label = tk.Label(colD, text=PID_VALUES["D1"], bg=FR_color)
        self.PID_D1_label.pack()
        self.PID_D2_label = tk.Label(colD, text=PID_VALUES["D2"], bg=FR_color)
        self.PID_D2_label.pack()
        self.PID_D3_label = tk.Label(colD, text=PID_VALUES["D3"], bg=FR_color)
        self.PID_D3_label.pack()
        self.PID_D4_label = tk.Label(colD, text=PID_VALUES["D4"], bg=FR_color)
        self.PID_D4_label.pack()
        tk.Label(colD, text="", bg=FR_color).pack()
        self.PID_D1_entry = tk.Entry(colD, bg=BG_color, width=10)
        self.PID_D1_entry.pack()
        self.PID_D2_entry = tk.Entry(colD, bg=BG_color, width=10)
        self.PID_D2_entry.pack()
        self.PID_D3_entry = tk.Entry(colD, bg=BG_color, width=10)
        self.PID_D3_entry.pack()
        self.PID_D4_entry = tk.Entry(colD, bg=BG_color, width=10)
        self.PID_D4_entry.pack()
        # Set Point column
        colSetPoint = tk.Frame(pidframes, bg=FR_color)
        colSetPoint.pack(side="left", expand=True, padx=5)
        tk.Label(colSetPoint, text="Set Point", bg=FR_color, font=(global_font, 11, "bold")).pack()
        self.PID_SetPoint1_label = tk.Label(colSetPoint, text=PID_VALUES["SetPoint1"], bg=FR_color)
        self.PID_SetPoint1_label.pack()
        self.PID_SetPoint2_label = tk.Label(colSetPoint, text=PID_VALUES["SetPoint2"], bg=FR_color)
        self.PID_SetPoint2_label.pack()
        self.PID_SetPoint3_label = tk.Label(colSetPoint, text=PID_VALUES["SetPoint3"], bg=FR_color)
        self.PID_SetPoint3_label.pack()
        self.PID_SetPoint4_label = tk.Label(colSetPoint, text=PID_VALUES["SetPoint4"], bg=FR_color)
        self.PID_SetPoint4_label.pack()
        tk.Label(colSetPoint, text="", bg=FR_color).pack()
        self.PID_SetPoint1_entry = tk.Entry(colSetPoint, bg=BG_color, width=10)
        self.PID_SetPoint1_entry.pack()
        self.PID_SetPoint2_entry = tk.Entry(colSetPoint, bg=BG_color, width=10)
        self.PID_SetPoint2_entry.pack()
        self.PID_SetPoint3_entry = tk.Entry(colSetPoint, bg=BG_color, width=10)
        self.PID_SetPoint3_entry.pack()
        self.PID_SetPoint4_entry = tk.Entry(colSetPoint, bg=BG_color, width=10)
        self.PID_SetPoint4_entry.pack()

        # RPM and Gear Labels for user clarity
        colLabels = tk.Frame(pidframes, bg=FR_color)
        colLabels.pack(side="left", expand=True, padx=10)
        tk.Label(colLabels, text="", bg=FR_color).pack()
        tk.Label(colLabels, text="RPM Low", bg=FR_color).pack()
        tk.Label(colLabels, text="Low Gear", bg=FR_color).pack()
        tk.Label(colLabels, text="RPM High", bg=FR_color).pack()
        tk.Label(colLabels, text="High Gear", bg=FR_color).pack()
        tk.Label(colLabels, text="", bg=FR_color).pack()
        tk.Label(colLabels, text="RPM Low", bg=FR_color).pack()
        tk.Label(colLabels, text="Low Gear", bg=FR_color).pack()
        tk.Label(colLabels, text="RPM High", bg=FR_color).pack()
        tk.Label(colLabels, text="High Gear", bg=FR_color).pack()
        
        # PID Send Button and Preset Save
        # Change PID values button
        framePIDButtons = tk.Frame(framePID, bg=FR_color, relief="solid", height=200, width=200)
        framePIDButtons.pack(fill="both", expand=True, padx=2, pady=5)
        ttk.Button(framePIDButtons, text="Send Tuning Values", command=self.config_PID_tuning).pack(pady=10, side="left")
        # Preset dropdown
        preset_options = ["1","2","3"]
        self.preset_text = tk.StringVar(value="1")
        self.preset_option_menu = tk.OptionMenu(framePIDButtons, self.preset_text, *preset_options)
        self.preset_option_menu.pack(pady=5, padx=2, side="right")
        # Save preset button
        ttk.Button(framePIDButtons, text="Save to preset:", command=self.save_preset).pack(pady=5, padx=5, side="right")

        # PID history frame
        framePIDHistory = tk.Frame(framePID, bg=FR_color, relief="solid", bd=2)
        framePIDHistory.pack(fill="x", side="top", pady=(0,10))
        # PID history title
        tk.Label(
            framePIDHistory,
            text="Previous 3 PID Entries:",
            bg=FR_color,
            font=(global_font, 11, "bold")
        ).pack(side="top", pady=(0,5))
        # Container for the 3 sets of previous PID values
        history_container = tk.Frame(framePIDHistory, bg=FR_color)
        history_container.pack(side="top", fill="x")
        # Store all label references here so we can update them later
        self.history_labels = [ [ [None]*4 for _ in range(4) ] for _ in range(3) ]
        # Offsets inside each 12-value block
        pid_offsets = {
            0: (0, 3, 6, 9),   # P offsets
            1: (1, 4, 7, 10),  # I offsets
            2: (2, 5, 8, 11),  # D offsets
            3: (12, 13, 14, 15) # Set Point offsets
        }
        row_names = ["RPM Low", "Low Gear", "RPM High", "High Gear"]
        # Create the 3 sets of previous PID values
        for set_idx in range(3):  # left, middle, right sets
            set_frame = tk.Frame(history_container, bg=FR_color)
            set_frame.pack(side="left", padx=2, pady=5)

            tk.Label(set_frame, text=f"Past Entry {set_idx+1}", bg=FR_color,
                    font=(global_font,10,"bold")).pack(pady=5)

            col_frame = tk.Frame(set_frame, bg=FR_color, relief="solid", bd=1)
            col_frame.pack()
            # Create columns for P, I, D, and Set Point
            for col in range(4):  # P, I, D, Set Point
                col_block = tk.Frame(col_frame, bg=FR_color)
                col_block.pack(side="left", padx=2, pady=5)

                heading = ["P","I","D","SP"][col]
                tk.Label(col_block, text=heading, bg=FR_color,
                        font=(global_font,10,"bold")).pack(pady=5)
                # Fill in the 4 rows of this column with the appropriate PID values from PIDHistory using the offsets
                for row in range(4):
                    hist_index = set_idx*16 + pid_offsets[col][row]
                    value = PIDHistory[hist_index]

                    label = tk.Label(col_block, text=str(value), bg=FR_color, width=8)
                    label.pack(pady=5, padx=2)

                    self.history_labels[set_idx][row][col] = label


        # PID Preset Frame
        pidpresetframe = tk.Frame(framePID, bg=FR_color, relief="solid", bd=2)
        pidpresetframe.pack(fill="both", expand=True, pady=10, side="bottom")
        # PID Preset title
        tk.Label(pidpresetframe, text="PID Presets", bg=FR_color, font=(global_font, 11, "bold")).pack(side="top", pady=5)
        # Preset column for P
        presetsCOLP = tk.Frame(pidpresetframe, bg=FR_color)
        presetsCOLP.pack(side="left", expand=True, padx=5)
        tk.Label(presetsCOLP, text="P", bg=FR_color, font=(global_font, 11, "bold")).pack()
        tk.Label(presetsCOLP, text="Preset 1", bg=FR_color, font=(global_font, 11, "bold")).pack()
        self.preset1_P1_label = tk.Label(presetsCOLP, text=PRESET1_PID_VALUES[0], bg=FR_color)
        self.preset1_P1_label.pack(pady=2)
        self.preset1_P2_label = tk.Label(presetsCOLP, text=PRESET1_PID_VALUES[3], bg=FR_color)
        self.preset1_P2_label.pack(pady=2)
        self.preset1_P3_label = tk.Label(presetsCOLP, text=PRESET1_PID_VALUES[6], bg=FR_color)
        self.preset1_P3_label.pack(pady=2)
        self.preset1_P4_label = tk.Label(presetsCOLP, text=PRESET1_PID_VALUES[9], bg=FR_color)
        self.preset1_P4_label.pack(pady=2)
        tk.Label(presetsCOLP, text="Preset 2", bg=FR_color, font=(global_font, 11, "bold")).pack()
        self.preset2_P1_label = tk.Label(presetsCOLP, text=PRESET2_PID_VALUES[0], bg=FR_color)
        self.preset2_P1_label.pack(pady=2)
        self.preset2_P2_label = tk.Label(presetsCOLP, text=PRESET2_PID_VALUES[3], bg=FR_color)
        self.preset2_P2_label.pack(pady=2)
        self.preset2_P3_label = tk.Label(presetsCOLP, text=PRESET2_PID_VALUES[6], bg=FR_color)
        self.preset2_P3_label.pack(pady=2)
        self.preset2_P4_label = tk.Label(presetsCOLP, text=PRESET2_PID_VALUES[9], bg=FR_color)
        self.preset2_P4_label.pack(pady=2)
        tk.Label(presetsCOLP, text="Preset 3", bg=FR_color, font=(global_font, 11, "bold")).pack()
        self.preset3_P1_label = tk.Label(presetsCOLP, text=PRESET3_PID_VALUES[0], bg=FR_color)
        self.preset3_P1_label.pack(pady=2)
        self.preset3_P2_label = tk.Label(presetsCOLP, text=PRESET3_PID_VALUES[3], bg=FR_color)
        self.preset3_P2_label.pack(pady=2)
        self.preset3_P3_label = tk.Label(presetsCOLP, text=PRESET3_PID_VALUES[6], bg=FR_color)
        self.preset3_P3_label.pack(pady=2)
        self.preset3_P4_label = tk.Label(presetsCOLP, text=PRESET3_PID_VALUES[9], bg=FR_color)
        self.preset3_P4_label.pack(pady=2)
        # Preset column for I
        presetsCOLI = tk.Frame(pidpresetframe, bg=FR_color)
        presetsCOLI.pack(side="left", expand=True, padx=5)
        tk.Label(presetsCOLI, text="I", bg=FR_color, font=(global_font, 11, "bold")).pack()
        tk.Label(presetsCOLI, text="", bg=FR_color).pack()
        self.preset1_I1_label = tk.Label(presetsCOLI, text=PRESET1_PID_VALUES[1], bg=FR_color)
        self.preset1_I1_label.pack(pady=2)
        self.preset1_I2_label = tk.Label(presetsCOLI, text=PRESET1_PID_VALUES[4], bg=FR_color)
        self.preset1_I2_label.pack(pady=2)
        self.preset1_I3_label = tk.Label(presetsCOLI, text=PRESET1_PID_VALUES[7], bg=FR_color)
        self.preset1_I3_label.pack(pady=2)
        self.preset1_I4_label = tk.Label(presetsCOLI, text=PRESET1_PID_VALUES[10], bg=FR_color)
        self.preset1_I4_label.pack(pady=2)
        tk.Label(presetsCOLI, text="", bg=FR_color).pack()
        self.preset2_I1_label = tk.Label(presetsCOLI, text=PRESET2_PID_VALUES[1], bg=FR_color)
        self.preset2_I1_label.pack(pady=2)
        self.preset2_I2_label = tk.Label(presetsCOLI, text=PRESET2_PID_VALUES[4], bg=FR_color)
        self.preset2_I2_label.pack(pady=2)
        self.preset2_I3_label = tk.Label(presetsCOLI, text=PRESET2_PID_VALUES[7], bg=FR_color)
        self.preset2_I3_label.pack(pady=2)
        self.preset2_I4_label = tk.Label(presetsCOLI, text=PRESET2_PID_VALUES[10], bg=FR_color)
        self.preset2_I4_label.pack(pady=2)
        tk.Label(presetsCOLI, text="", bg=FR_color).pack()
        self.preset3_I1_label = tk.Label(presetsCOLI, text=PRESET3_PID_VALUES[1], bg=FR_color)
        self.preset3_I1_label.pack(pady=2)
        self.preset3_I2_label = tk.Label(presetsCOLI, text=PRESET3_PID_VALUES[4], bg=FR_color)
        self.preset3_I2_label.pack(pady=2)
        self.preset3_I3_label = tk.Label(presetsCOLI, text=PRESET3_PID_VALUES[7], bg=FR_color)
        self.preset3_I3_label.pack(pady=2)
        self.preset3_I4_label = tk.Label(presetsCOLI, text=PRESET3_PID_VALUES[10], bg=FR_color)
        self.preset3_I4_label.pack(pady=2)
        # Preset column for D
        presetsCOLD = tk.Frame(pidpresetframe, bg=FR_color)
        presetsCOLD.pack(side="left", expand=True, padx=5)
        tk.Label(presetsCOLD, text="D", bg=FR_color, font=(global_font, 11, "bold")).pack()
        tk.Label(presetsCOLD, text="", bg=FR_color).pack()
        self.preset1_D1_label = tk.Label(presetsCOLD, text=PRESET1_PID_VALUES[2], bg=FR_color)
        self.preset1_D1_label.pack(pady=2)
        self.preset1_D2_label = tk.Label(presetsCOLD, text=PRESET1_PID_VALUES[5], bg=FR_color)
        self.preset1_D2_label.pack(pady=2)
        self.preset1_D3_label = tk.Label(presetsCOLD, text=PRESET1_PID_VALUES[8], bg=FR_color)
        self.preset1_D3_label.pack(pady=2)
        self.preset1_D4_label = tk.Label(presetsCOLD, text=PRESET1_PID_VALUES[11], bg=FR_color)
        self.preset1_D4_label.pack(pady=2)
        tk.Label(presetsCOLD, text="", bg=FR_color).pack()
        self.preset2_D1_label = tk.Label(presetsCOLD, text=PRESET2_PID_VALUES[2], bg=FR_color)
        self.preset2_D1_label.pack(pady=2)
        self.preset2_D2_label = tk.Label(presetsCOLD, text=PRESET2_PID_VALUES[5], bg=FR_color)
        self.preset2_D2_label.pack(pady=2)
        self.preset2_D3_label = tk.Label(presetsCOLD, text=PRESET2_PID_VALUES[8], bg=FR_color)
        self.preset2_D3_label.pack(pady=2)
        self.preset2_D4_label = tk.Label(presetsCOLD, text=PRESET2_PID_VALUES[11], bg=FR_color)
        self.preset2_D4_label.pack(pady=2)
        tk.Label(presetsCOLD, text="", bg=FR_color).pack()
        self.preset3_D1_label = tk.Label(presetsCOLD, text=PRESET3_PID_VALUES[2], bg=FR_color)
        self.preset3_D1_label.pack(pady=2)
        self.preset3_D2_label = tk.Label(presetsCOLD, text=PRESET3_PID_VALUES[5], bg=FR_color)
        self.preset3_D2_label.pack(pady=2)
        self.preset3_D3_label = tk.Label(presetsCOLD, text=PRESET3_PID_VALUES[8], bg=FR_color)
        self.preset3_D3_label.pack(pady=2)
        self.preset3_D4_label = tk.Label(presetsCOLD, text=PRESET3_PID_VALUES[11], bg=FR_color)
        self.preset3_D4_label.pack(pady=2)
        # Preset column for Set Point
        presetsCOLSetPoint = tk.Frame(pidpresetframe, bg=FR_color)
        presetsCOLSetPoint.pack(side="left", expand=True, padx=5)
        tk.Label(presetsCOLSetPoint, text="Set Point", bg=FR_color, font=(global_font, 11, "bold")).pack()
        tk.Label(presetsCOLSetPoint, text="", bg=FR_color).pack()
        self.preset1_SetPoint1_label = tk.Label(presetsCOLSetPoint, text=PRESET1_PID_VALUES[12], bg=FR_color)
        self.preset1_SetPoint1_label.pack(pady=2)
        self.preset1_SetPoint2_label = tk.Label(presetsCOLSetPoint, text=PRESET1_PID_VALUES[13], bg=FR_color)
        self.preset1_SetPoint2_label.pack(pady=2)
        self.preset1_SetPoint3_label = tk.Label(presetsCOLSetPoint, text=PRESET1_PID_VALUES[14], bg=FR_color)
        self.preset1_SetPoint3_label.pack(pady=2)
        self.preset1_SetPoint4_label = tk.Label(presetsCOLSetPoint, text=PRESET1_PID_VALUES[15], bg=FR_color)
        self.preset1_SetPoint4_label.pack(pady=2)
        tk.Label(presetsCOLSetPoint, text="", bg=FR_color).pack()
        self.preset2_SetPoint1_label = tk.Label(presetsCOLSetPoint, text=PRESET2_PID_VALUES[12], bg=FR_color)
        self.preset2_SetPoint1_label.pack(pady=2)
        self.preset2_SetPoint2_label = tk.Label(presetsCOLSetPoint, text=PRESET2_PID_VALUES[13], bg=FR_color)
        self.preset2_SetPoint2_label.pack(pady=2)
        self.preset2_SetPoint3_label = tk.Label(presetsCOLSetPoint, text=PRESET2_PID_VALUES[14], bg=FR_color)
        self.preset2_SetPoint3_label.pack(pady=2)
        self.preset2_SetPoint4_label = tk.Label(presetsCOLSetPoint, text=PRESET2_PID_VALUES[15], bg=FR_color)
        self.preset2_SetPoint4_label.pack(pady=2)
        tk.Label(presetsCOLSetPoint, text="", bg=FR_color).pack()
        self.preset3_SetPoint1_label = tk.Label(presetsCOLSetPoint, text=PRESET3_PID_VALUES[12], bg=FR_color)
        self.preset3_SetPoint1_label.pack(pady=2)
        self.preset3_SetPoint2_label = tk.Label(presetsCOLSetPoint, text=PRESET3_PID_VALUES[13], bg=FR_color)
        self.preset3_SetPoint2_label.pack(pady=2)
        self.preset3_SetPoint3_label = tk.Label(presetsCOLSetPoint, text=PRESET3_PID_VALUES[14], bg=FR_color)
        self.preset3_SetPoint3_label.pack(pady=2)
        self.preset3_SetPoint4_label = tk.Label(presetsCOLSetPoint, text=PRESET3_PID_VALUES[15], bg=FR_color)
        self.preset3_SetPoint4_label.pack(pady=2)
        # Column for labeling presets and assigning preset buttons
        presetsCOLSet = tk.Frame(pidpresetframe, bg=FR_color)
        presetsCOLSet.pack(side="left", expand=True, padx=5)
        tk.Label(presetsCOLSet, text="", bg=FR_color).pack()
        ttk.Button(presetsCOLSet, text="Assign Preset 1", command=self.assign_preset1).pack()
        tk.Label(presetsCOLSet, text="RPM Low", bg=FR_color).pack(pady=2)
        tk.Label(presetsCOLSet, text="Low Gear", bg=FR_color).pack(pady=2)
        tk.Label(presetsCOLSet, text="RPM High", bg=FR_color).pack(pady=2)
        tk.Label(presetsCOLSet, text="High Gear", bg=FR_color).pack(pady=2)
        ttk.Button(presetsCOLSet, text="Assign Preset 2", command=self.assign_preset2).pack()
        tk.Label(presetsCOLSet, text="RPM Low", bg=FR_color).pack(pady=2)
        tk.Label(presetsCOLSet, text="Low Gear", bg=FR_color).pack(pady=2)
        tk.Label(presetsCOLSet, text="RPM High", bg=FR_color).pack(pady=2)
        tk.Label(presetsCOLSet, text="High Gear", bg=FR_color).pack(pady=2)
        ttk.Button(presetsCOLSet, text="Assign Preset 3", command=self.assign_preset3).pack()
        tk.Label(presetsCOLSet, text="RPM Low", bg=FR_color).pack(pady=2)
        tk.Label(presetsCOLSet, text="Low Gear", bg=FR_color).pack(pady=2)
        tk.Label(presetsCOLSet, text="RPM High", bg=FR_color).pack(pady=2)
        tk.Label(presetsCOLSet, text="High Gear", bg=FR_color).pack(pady=2)


    # Send a request to the micro controller to see if it is within RF range to communicate 
    def test_rf_connection(self):
        self.status_label.config(text="Beginning RF Connection Test", bg="#e0e0e0")
        # Send request to user microcontroller to test RF connection
        result = dataLogger.test_rf_connection_request()
        # Update RF status label based on result
        if(result == 1):
            self.rf_status_label.config(text="Current RF Status: In Range", bg=connected_color) 
        elif(result == 0):
            self.rf_status_label.config(text="Current RF Status: Out of Range", bg=disconnected_color)
        self.status_label.config(text="RF Connection Test Complete", bg="#e0e0e0")
    
    def download_log_file_usb(self):
        self.status_label.config(text="Downloading Log File via USB", bg="#e0e0e0")
        # Send request to user microcontroller to download log file
        if (dataLogger.receive_logs_from_usb_request(self) != 0):
            self.status_label.config(text=f"Log Files Downloaded via USB", bg="#e0e0e0")

    # Graph the log file data using matplotlib into the 2 graphs
    # This is where you can chanhe how data is visualized, add more graphs, etc. The data is extracted from the CSV file into pandas dataframes for easy manipulation
    def graph_log_file(self, file_name):
        # Open the CSV file and extract the relevant columns (time, engine RPM, box RPM)
        df = pd.read_csv(file_name)
        # Convert milliseconds → seconds
        time_csv = df["Timestamp"] * 1e-3
        engine_rpm = df["Engine RPM"]
        box_rpm = df["Box RPM"]
        time_csv -= time_csv.iloc[1] # Set time 0 to first data point

        # ---------- Smooth data ----------
        engine_step = 50
        engine_rpm_filtered = engine_rpm.rolling(
            window=engine_step,
            center=True
        ).median()

        box_step = 50
        box_filtered = box_rpm.rolling(
            window=box_step,
            center=True
        ).median()
        wheel_rad = 10.67            # inches
        wheel_circ = 2 * np.pi * wheel_rad  # inches

        # RPM → mph
        box_speed_mph = (
            box_filtered
            * wheel_circ    # inches / rev
            / 12            # inches → feet
            / 5280          # feet → miles
            * 60            # minutes → hours
        )

        # ---------- Plot 1: Shift Curve (Box RPM vs Time) ----------
        self.ax1.clear()
        self.ax1.plot(box_filtered, engine_rpm_filtered, linewidth=3)
        self.ax1.set_title("Shift Curve")
        self.ax1.set_xlabel("Engine RPM")
        self.ax1.set_ylabel("Rear Wheel Speed (MPH)")
        self.ax1.grid(True)
        self.canvas.draw()

        # ---------- Plot 2: Shift RPM (Engine RPM vs Time) ----------
        self.ax2.clear()
        self.ax2.plot(time_csv, engine_rpm_filtered, linewidth=3)
        self.ax2.set_title("Shift RPM")
        self.ax2.set_xlabel("Time (Sec)")
        self.ax2.set_ylabel("Engine RPM")
        self.ax2.grid(True)
        self.ax2.set_ylim(1250, 3500)
        self.canvas2.draw() 
    
    # Send a request to download 
    # Used when using RF connections 
    def download_log_file(self):
        self.status_label.config(text="Downloading Log File", bg="#e0e0e0")
        # Send request to STM32 to download log file
        total_time = dataLogger.download_log_request()
        self.status_label.config(text="Log File Downloaded", bg="#e0e0e0")
        self.graph_log_file("RPM3.csv")

    # Update the logging rate variable so the slider value can be visualized
    def update_logging_rate_label(self, value):
        # Change the logging rate label to reflect the slider value (convert from string to float to int)
        self.logging_rate_label.config(text=str(int(float(value))) + " readings/log point")

    # Update the PID history display by moving the old values to the new position and inserting the new values at the beginning of the history list
    def update_history(self, PID_VALUES):
        # 1. Shift history: Moving 32 old values to make room for 16 new ones
        # Using a slice is cleaner: PIDHistory[16:48] = PIDHistory[0:32]
        for i in range(48 - 16):
            PIDHistory[47 - i] = PIDHistory[31 - i]
        
        # 2. Insert the 16 new variables
        keys = list(PID_VALUES.keys())
        for i in range(16):
            PIDHistory[i] = float(PID_VALUES[keys[i]])

        # 3. Transposed Mapping
        # If your grid is 4x4, we calculate the index based on the column first
        for set_idx in range(3):
            for row in range(4):
                for col in range(4):
                    # TRANSPOSED LOGIC: 
                    # We multiply the COLUMN by 4 instead of the row (or offsets)
                    # to change the direction the data fills the grid.
                    hist_index = (set_idx * 16) + (col * 4) + row

                    value = PIDHistory[hist_index]
                    label = self.history_labels[set_idx][row][col]
                    label.config(text=f"{value:.2f}")

    # Validate and send the new PID values to the microcontroller, then update the PID labels and history on the GUI
    def config_PID_tuning(self):
        # Iterates through P, I, D for stages 1 through 4
        self.status_label.config(text="Sending PID Values", bg="#e0e0e0")
        
        stages = [1, 2, 3, 4]
        parameters = ["P", "I", "D"]
        temp_PID = PID_VALUES.copy()
        badEntryFlag = False
        emptyEntries = 0
        changedValues = []
        for stage in stages:
            for param in parameters:
                key = f"{param}{stage}"
                
                # Use getattr to retrieve the specific entry and label objects
                entry_widget = getattr(self, f"PID_{key}_entry")
                label_widget = getattr(self, f"PID_{key}_label")
                
                new_value_str = entry_widget.get().strip()

                # 1. Check if the entry is empty (if empty, ignore and move to the next parameter)
                if not new_value_str:
                    emptyEntries += 1
                    continue

                # 2. Check and Validate the Value
                try:
                    new_value_float = float(new_value_str)
        
                    if not (0 <= new_value_float < 1):
                        badEntryFlag = True
                        # Error: Value is outside the bounds (<= 0 or >= 1)
                        tk.messagebox.showerror(
                            "Validation Error",
                            f"The value for {key} must be a number strictly between 0 and 1. Received: {new_value_str}"
                        )
                        entry_widget.focus_set() # Focus on the problematic entry
                    else:
                        changedValues.append(str(key)[0:2] + " " + new_value_str)
                # Handle the case where the input is not a valid float
                except ValueError:
                    # Error: Input is not a valid number
                    badEntryFlag = True
                    tk.messagebox.showerror(
                        "Input Error",
                        f"Invalid input for {key}. Please enter a numerical value. Received: '{new_value_str}'"
                    )
                    entry_widget.focus_set() # Focus on the problematic entry
        # Now validate the Set Point values
        for stage in stages:
            key = f"SetPoint{stage}"
            entry_widget = getattr(self, f"PID_{key}_entry")
            label_widget = getattr(self, f"PID_{key}_label")
            new_value_str = entry_widget.get().strip()

            if not new_value_str:
                emptyEntries += 1
                continue
            try:
                if(stage == 2 or stage == 4):
                    new_value_float = float(new_value_str)
                else:
                    new_value_int = int(new_value_str)
                
                match stage:
                    case 1:
                        # For stage 1, we expect an integer value between 150 and 330
                        if not (150 <= new_value_int <= 330):
                            badEntryFlag = True
                            tk.messagebox.showerror(
                                "Validation Error",
                                f"The value for {key} must be an integer between 150 and 330. Received: {new_value_str}"
                            )
                            entry_widget.focus_set() # Focus on the problematic entry
                        else:
                            changedValues.append(f"SP{stage}" + " " + new_value_str)
                    # For stage 2, we expect a float value between 0 and 4
                    case 2:
                        if not (0 <= new_value_float <= 4):
                            badEntryFlag = True
                            tk.messagebox.showerror(
                                "Validation Error",
                                f"The value for {key} must be a float between 0 and 4. Received: {new_value_str}"
                            )
                            entry_widget.focus_set() # Focus on the problematic entry
                        else:
                            changedValues.append(f"SP{stage}" + " " + new_value_str)
                    # For stage 3, we expect an integer value between 270 and 330
                    case 3:
                        if not (270 <= new_value_int <= 330):
                            badEntryFlag = True
                            tk.messagebox.showerror(
                                "Validation Error",
                                f"The value for {key} must be an integer between 270 and 330. Received: {new_value_str}"
                            )
                            entry_widget.focus_set() # Focus on the problematic entry
                        else:
                            changedValues.append(f"SP{stage}" + " " + new_value_str)
                    # For stage 4, we expect a float value between 0 and 3
                    case 4:
                        if not (0 <= new_value_float <= 3):
                            badEntryFlag = True
                            tk.messagebox.showerror(
                                "Validation Error",
                                f"The value for {key} must be a float between 0 and 3. Received: {new_value_str}"
                            )
                            entry_widget.focus_set() # Focus on the problematic entry   
                        else:
                            changedValues.append(f"SP{stage}" + " " + new_value_str)
            # Handle the case where the input is not a valid number
            except ValueError:
                    # Error: Input is not a valid number
                    badEntryFlag = True
                    tk.messagebox.showerror(
                        "Input Error",
                        f"Invalid input for {key}. Please enter a numerical value. (Integer for stages 1 and 3, Float for stages 2 and 4) Received: '{new_value_str}'"
                    )
                    entry_widget.focus_set() # Focus on the problematic entry
                
        # Final Check: If there were no bad entries and at least one entry was filled, proceed to update values and send the request
        if ((not badEntryFlag) and emptyEntries < 16):
            # update values and labels
            for stage in stages:
                for param in parameters:
                    key = f"{param}{stage}"
                    # Use getattr to retrieve the specific entry and label objects
                    entry_widget = getattr(self, f"PID_{key}_entry")
                    label_widget = getattr(self, f"PID_{key}_label")
                    new_value_str = entry_widget.get().strip()
                    if new_value_str:
                        #Update global state and UI label
                        PID_VALUES[key] = new_value_str
                        label_widget.config(text=new_value_str)
                        # Optionally clear the entry field after successful update
                        entry_widget.delete(0, tk.END) 
            # Handle the Set Point values
            for stage in stages:
                key = f"SetPoint{stage}"
                entry_widget = getattr(self, f"PID_{key}_entry")
                label_widget = getattr(self, f"PID_{key}_label")
                new_value_str = entry_widget.get().strip()
                if new_value_str:
                    PID_VALUES[key] = new_value_str
                    label_widget.config(text=new_value_str)
                    entry_widget.delete(0, tk.END)
            # Send the request to the microcontroller to update the PID values based on user input if no validation errors were found
            result = dataLogger.change_PID_request(changedValues) # Send request to STM32 to change PID values based on user input
            # Update the status label based on the result of the request
            if result == 1:
                self.status_label.config(text="PID Values Changed Successfully", bg="#e0e0e0")
            else:         
                self.status_label.config(text="Error sending PID Values over RF", bg="#e0e0e0")
            # Finally, update the PID history on the GUI with the new values 
            self.update_history(temp_PID)
        # If there were validation errors or if all entries were empty, do not send the request and update the status label accordingly
        else:
            if(emptyEntries ==  16):
                self.status_label.config(text="No PID Values Updated (All Entries Empty)", bg="#e0e0e0")
            else:
                self.status_label.config(text="PID Update Aborted Due to Input Errors", bg="#e0e0e0")

    # Save the current PID values to the selected preset (1, 2, or 3) and update the preset display labels on the GUI
    def save_preset(self):
        if self.preset_text.get() == "1":
            PRESET1_PID_VALUES[0] = PID_VALUES["P1"]
            PRESET1_PID_VALUES[1] = PID_VALUES["I1"]
            PRESET1_PID_VALUES[2] = PID_VALUES["D1"]
            PRESET1_PID_VALUES[3] = PID_VALUES["P2"]
            PRESET1_PID_VALUES[4] = PID_VALUES["I2"]
            PRESET1_PID_VALUES[5] = PID_VALUES["D2"]
            PRESET1_PID_VALUES[6] = PID_VALUES["P3"]
            PRESET1_PID_VALUES[7] = PID_VALUES["I3"]
            PRESET1_PID_VALUES[8] = PID_VALUES["D3"]
            PRESET1_PID_VALUES[9] = PID_VALUES["P4"]
            PRESET1_PID_VALUES[10] = PID_VALUES["I4"]
            PRESET1_PID_VALUES[11] = PID_VALUES["D4"]
            PRESET1_PID_VALUES[12] = PID_VALUES["SetPoint1"]
            PRESET1_PID_VALUES[13] = PID_VALUES["SetPoint2"]
            PRESET1_PID_VALUES[14] = PID_VALUES["SetPoint3"]
            PRESET1_PID_VALUES[15] = PID_VALUES["SetPoint4"]
            self.preset1_P1_label.config(text=PRESET1_PID_VALUES[0])
            self.preset1_I1_label.config(text=PRESET1_PID_VALUES[1])
            self.preset1_D1_label.config(text=PRESET1_PID_VALUES[2])
            self.preset1_P2_label.config(text=PRESET1_PID_VALUES[3])
            self.preset1_I2_label.config(text=PRESET1_PID_VALUES[4])
            self.preset1_D2_label.config(text=PRESET1_PID_VALUES[5])
            self.preset1_P3_label.config(text=PRESET1_PID_VALUES[6])
            self.preset1_I3_label.config(text=PRESET1_PID_VALUES[7])
            self.preset1_D3_label.config(text=PRESET1_PID_VALUES[8])
            self.preset1_P4_label.config(text=PRESET1_PID_VALUES[9])
            self.preset1_I4_label.config(text=PRESET1_PID_VALUES[10])
            self.preset1_D4_label.config(text=PRESET1_PID_VALUES[11])
            self.preset1_SetPoint1_label.config(text=PRESET1_PID_VALUES[12])
            self.preset1_SetPoint2_label.config(text=PRESET1_PID_VALUES[13])
            self.preset1_SetPoint3_label.config(text=PRESET1_PID_VALUES[14])
            self.preset1_SetPoint4_label.config(text=PRESET1_PID_VALUES[15])
        elif self.preset_text.get() == "2":
            PRESET2_PID_VALUES[0] = PID_VALUES["P1"]
            PRESET2_PID_VALUES[1] = PID_VALUES["I1"]
            PRESET2_PID_VALUES[2] = PID_VALUES["D1"]
            PRESET2_PID_VALUES[3] = PID_VALUES["P2"]
            PRESET2_PID_VALUES[4] = PID_VALUES["I2"]
            PRESET2_PID_VALUES[5] = PID_VALUES["D2"]
            PRESET2_PID_VALUES[6] = PID_VALUES["P3"]
            PRESET2_PID_VALUES[7] = PID_VALUES["I3"]
            PRESET2_PID_VALUES[8] = PID_VALUES["D3"]
            PRESET2_PID_VALUES[9] = PID_VALUES["P4"]
            PRESET2_PID_VALUES[10] = PID_VALUES["I4"]
            PRESET2_PID_VALUES[11] = PID_VALUES["D4"]
            PRESET2_PID_VALUES[12] = PID_VALUES["SetPoint1"]
            PRESET2_PID_VALUES[13] = PID_VALUES["SetPoint2"]
            PRESET2_PID_VALUES[14] = PID_VALUES["SetPoint3"]
            PRESET2_PID_VALUES[15] = PID_VALUES["SetPoint4"]
            self.preset2_P1_label.config(text=PRESET2_PID_VALUES[0])
            self.preset2_I1_label.config(text=PRESET2_PID_VALUES[1])
            self.preset2_D1_label.config(text=PRESET2_PID_VALUES[2])
            self.preset2_P2_label.config(text=PRESET2_PID_VALUES[3])
            self.preset2_I2_label.config(text=PRESET2_PID_VALUES[4])
            self.preset2_D2_label.config(text=PRESET2_PID_VALUES[5])
            self.preset2_P3_label.config(text=PRESET2_PID_VALUES[6])
            self.preset2_I3_label.config(text=PRESET2_PID_VALUES[7])
            self.preset2_D3_label.config(text=PRESET2_PID_VALUES[8])
            self.preset2_P4_label.config(text=PRESET2_PID_VALUES[9])
            self.preset2_I4_label.config(text=PRESET2_PID_VALUES[10])
            self.preset2_D4_label.config(text=PRESET2_PID_VALUES[11])
            self.preset2_SetPoint1_label.config(text=PRESET2_PID_VALUES[12])
            self.preset2_SetPoint2_label.config(text=PRESET2_PID_VALUES[13])
            self.preset2_SetPoint3_label.config(text=PRESET2_PID_VALUES[14])
            self.preset2_SetPoint4_label.config(text=PRESET2_PID_VALUES[15])
        elif self.preset_text.get() == "3":
            PRESET3_PID_VALUES[0] = PID_VALUES["P1"]
            PRESET3_PID_VALUES[1] = PID_VALUES["I1"]
            PRESET3_PID_VALUES[2] = PID_VALUES["D1"]
            PRESET3_PID_VALUES[3] = PID_VALUES["P2"]
            PRESET3_PID_VALUES[4] = PID_VALUES["I2"]
            PRESET3_PID_VALUES[5] = PID_VALUES["D2"]
            PRESET3_PID_VALUES[6] = PID_VALUES["P3"]
            PRESET3_PID_VALUES[7] = PID_VALUES["I3"]
            PRESET3_PID_VALUES[8] = PID_VALUES["D3"]
            PRESET3_PID_VALUES[9] = PID_VALUES["P4"]
            PRESET3_PID_VALUES[10] = PID_VALUES["I4"]
            PRESET3_PID_VALUES[11] = PID_VALUES["D4"]
            PRESET3_PID_VALUES[12] = PID_VALUES["SetPoint1"]
            PRESET3_PID_VALUES[13] = PID_VALUES["SetPoint2"]
            PRESET3_PID_VALUES[14] = PID_VALUES["SetPoint3"]
            PRESET3_PID_VALUES[15] = PID_VALUES["SetPoint4"]
            self.preset3_P1_label.config(text=PRESET3_PID_VALUES[0])
            self.preset3_I1_label.config(text=PRESET3_PID_VALUES[1])
            self.preset3_D1_label.config(text=PRESET3_PID_VALUES[2])
            self.preset3_P2_label.config(text=PRESET3_PID_VALUES[3])
            self.preset3_I2_label.config(text=PRESET3_PID_VALUES[4])
            self.preset3_D2_label.config(text=PRESET3_PID_VALUES[5])
            self.preset3_P3_label.config(text=PRESET3_PID_VALUES[6])
            self.preset3_I3_label.config(text=PRESET3_PID_VALUES[7])
            self.preset3_D3_label.config(text=PRESET3_PID_VALUES[8])
            self.preset3_P4_label.config(text=PRESET3_PID_VALUES[9])
            self.preset3_I4_label.config(text=PRESET3_PID_VALUES[10])
            self.preset3_D4_label.config(text=PRESET3_PID_VALUES[11])
            self.preset3_SetPoint1_label.config(text=PRESET3_PID_VALUES[12])
            self.preset3_SetPoint2_label.config(text=PRESET3_PID_VALUES[13])
            self.preset3_SetPoint3_label.config(text=PRESET3_PID_VALUES[14])
            self.preset3_SetPoint4_label.config(text=PRESET3_PID_VALUES[15])

    # Load the PID values from preset 1 into the current PID values and update the PID labels and history on the GUI accordingly, then send a request to the microcontroller to update the PID values based on the selected preset
    def assign_preset1(self):
        self.update_history(PID_VALUES)
        PID_VALUES["P1"] = PRESET1_PID_VALUES[0]
        PID_VALUES["I1"] = PRESET1_PID_VALUES[1]
        PID_VALUES["D1"] = PRESET1_PID_VALUES[2]
        PID_VALUES["P2"] = PRESET1_PID_VALUES[3]
        PID_VALUES["I2"] = PRESET1_PID_VALUES[4]
        PID_VALUES["D2"] = PRESET1_PID_VALUES[5]
        PID_VALUES["P3"] = PRESET1_PID_VALUES[6]
        PID_VALUES["I3"] = PRESET1_PID_VALUES[7]
        PID_VALUES["D3"] = PRESET1_PID_VALUES[8]
        PID_VALUES["P4"] = PRESET1_PID_VALUES[9]
        PID_VALUES["I4"] = PRESET1_PID_VALUES[10]
        PID_VALUES["D4"] = PRESET1_PID_VALUES[11]
        PID_VALUES["SetPoint1"] = PRESET1_PID_VALUES[12]
        PID_VALUES["SetPoint2"] = PRESET1_PID_VALUES[13]
        PID_VALUES["SetPoint3"] = PRESET1_PID_VALUES[14]
        PID_VALUES["SetPoint4"] = PRESET1_PID_VALUES[15]

        self.PID_P1_label.config(text=str(PID_VALUES["P1"]))
        self.PID_P2_label.config(text=str(PID_VALUES["P2"]))
        self.PID_P3_label.config(text=str(PID_VALUES["P3"]))
        self.PID_P4_label.config(text=str(PID_VALUES["P4"]))
        self.PID_I1_label.config(text=str(PID_VALUES["I1"])) 
        self.PID_I2_label.config(text=str(PID_VALUES["I2"]))  
        self.PID_I3_label.config(text=str(PID_VALUES["I3"]))
        self.PID_I4_label.config(text=str(PID_VALUES["I4"]))
        self.PID_D1_label.config(text=str(PID_VALUES["D1"]))
        self.PID_D2_label.config(text=str(PID_VALUES["D2"]))
        self.PID_D3_label.config(text=str(PID_VALUES["D3"]))
        self.PID_D4_label.config(text=str(PID_VALUES["D4"]))
        self.PID_SetPoint1_label.config(text=str(PID_VALUES["SetPoint1"]))
        self.PID_SetPoint2_label.config(text=str(PID_VALUES["SetPoint2"]))
        self.PID_SetPoint3_label.config(text=str(PID_VALUES["SetPoint3"]))
        self.PID_SetPoint4_label.config(text=str(PID_VALUES["SetPoint4"]))

        dataLogger.change_PID_request([ "P1" + " " + str(PID_VALUES["P1"]),
                                        "I1" + " " + str(PID_VALUES["I1"]),
                                        "D1" + " " + str(PID_VALUES["D1"]),
                                        "P2" + " " + str(PID_VALUES["P2"]),
                                        "I2" + " " + str(PID_VALUES["I2"]),
                                        "D2" + " " + str(PID_VALUES["D2"]),
                                        "P3" + " " + str(PID_VALUES["P3"]),
                                        "I3" + " " + str(PID_VALUES["I3"]),
                                        "D3" + " " + str(PID_VALUES["D3"]),
                                        "P4" + " " + str(PID_VALUES["P4"]),
                                        "I4" + " " + str(PID_VALUES["I4"]),
                                        "D4" + " " + str(PID_VALUES["D4"]),
                                        "SP1" + " " + str(PID_VALUES["SetPoint1"]),
                                        "SP2" + " " + str(PID_VALUES["SetPoint2"]),
                                        "SP3" + " " + str(PID_VALUES["SetPoint3"]),
                                        "SP4" + " " + str(PID_VALUES["SetPoint4"])])
    # Load the PID values from preset 2 into the current PID values and update the PID labels and history on the GUI accordingly, then send a request to the microcontroller to update the PID values based on the selected preset
    def assign_preset2(self):
        self.update_history(PID_VALUES)
        PID_VALUES["P1"] = PRESET2_PID_VALUES[0]
        PID_VALUES["I1"] = PRESET2_PID_VALUES[1]
        PID_VALUES["D1"] = PRESET2_PID_VALUES[2]
        PID_VALUES["P2"] = PRESET2_PID_VALUES[3]
        PID_VALUES["I2"] = PRESET2_PID_VALUES[4]
        PID_VALUES["D2"] = PRESET2_PID_VALUES[5]
        PID_VALUES["P3"] = PRESET2_PID_VALUES[6]
        PID_VALUES["I3"] = PRESET2_PID_VALUES[7]
        PID_VALUES["D3"] = PRESET2_PID_VALUES[8]
        PID_VALUES["P4"] = PRESET2_PID_VALUES[9]
        PID_VALUES["I4"] = PRESET2_PID_VALUES[10]
        PID_VALUES["D4"] = PRESET2_PID_VALUES[11]
        PID_VALUES["SetPoint1"] = PRESET2_PID_VALUES[12]
        PID_VALUES["SetPoint2"] = PRESET2_PID_VALUES[13]
        PID_VALUES["SetPoint3"] = PRESET2_PID_VALUES[14]
        PID_VALUES["SetPoint4"] = PRESET2_PID_VALUES[15]
        self.PID_P1_label.config(text=str(PID_VALUES["P1"]))
        self.PID_P2_label.config(text=str(PID_VALUES["P2"]))
        self.PID_P3_label.config(text=str(PID_VALUES["P3"]))
        self.PID_P4_label.config(text=str(PID_VALUES["P4"]))
        self.PID_I1_label.config(text=str(PID_VALUES["I1"]))
        self.PID_I2_label.config(text=str(PID_VALUES["I2"]))
        self.PID_I3_label.config(text=str(PID_VALUES["I3"]))
        self.PID_I4_label.config(text=str(PID_VALUES["I4"]))   
        self.PID_D1_label.config(text=str(PID_VALUES["D1"]))
        self.PID_D2_label.config(text=str(PID_VALUES["D2"]))
        self.PID_D3_label.config(text=str(PID_VALUES["D3"]))
        self.PID_D4_label.config(text=str(PID_VALUES["D4"]))
        self.PID_SetPoint1_label.config(text=str(PID_VALUES["SetPoint1"]))
        self.PID_SetPoint2_label.config(text=str(PID_VALUES["SetPoint2"]))
        self.PID_SetPoint3_label.config(text=str(PID_VALUES["SetPoint3"]))
        self.PID_SetPoint4_label.config(text=str(PID_VALUES["SetPoint4"]))
        dataLogger.change_PID_request([ "P1" + " " + str(PID_VALUES["P1"]),
                                        "I1" + " " + str(PID_VALUES["I1"]),
                                        "D1" + " " + str(PID_VALUES["D1"]),
                                        "P2" + " " + str(PID_VALUES["P2"]),
                                        "I2" + " " + str(PID_VALUES["I2"]),
                                        "D2" + " " + str(PID_VALUES["D2"]),
                                        "P3" + " " + str(PID_VALUES["P3"]),
                                        "I3" + " " + str(PID_VALUES["I3"]),
                                        "D3" + " " + str(PID_VALUES["D3"]),
                                        "P4" + " " + str(PID_VALUES["P4"]),
                                        "I4" + " " + str(PID_VALUES["I4"]),
                                        "D4" + " " + str(PID_VALUES["D4"]),
                                        "SP1" + " " + str(PID_VALUES["SetPoint1"]),
                                        "SP2" + " " + str(PID_VALUES["SetPoint2"]),
                                        "SP3" + " " + str(PID_VALUES["SetPoint3"]),
                                        "SP4" + " " + str(PID_VALUES["SetPoint4"])])
    # Load the PID values from preset 3 into the current PID values and update the PID labels and history on the GUI accordingly, then send a request to the microcontroller to update the PID values based on the selected preset
    def assign_preset3(self):
        self.update_history(PID_VALUES)
        PID_VALUES["P1"] = PRESET3_PID_VALUES[0]
        PID_VALUES["I1"] = PRESET3_PID_VALUES[1]
        PID_VALUES["D1"] = PRESET3_PID_VALUES[2]
        PID_VALUES["P2"] = PRESET3_PID_VALUES[3]
        PID_VALUES["I2"] = PRESET3_PID_VALUES[4]
        PID_VALUES["D2"] = PRESET3_PID_VALUES[5]
        PID_VALUES["P3"] = PRESET3_PID_VALUES[6]
        PID_VALUES["I3"] = PRESET3_PID_VALUES[7]
        PID_VALUES["D3"] = PRESET3_PID_VALUES[8]
        PID_VALUES["P4"] = PRESET3_PID_VALUES[9]
        PID_VALUES["I4"] = PRESET3_PID_VALUES[10]
        PID_VALUES["D4"] = PRESET3_PID_VALUES[11]
        PID_VALUES["SetPoint1"] = PRESET3_PID_VALUES[12]
        PID_VALUES["SetPoint2"] = PRESET3_PID_VALUES[13]
        PID_VALUES["SetPoint3"] = PRESET3_PID_VALUES[14]
        PID_VALUES["SetPoint4"] = PRESET3_PID_VALUES[15]
        self.PID_P1_label.config(text=str(PID_VALUES["P1"]))
        self.PID_P2_label.config(text=str(PID_VALUES["P2"]))
        self.PID_P3_label.config(text=str(PID_VALUES["P3"]))
        self.PID_P4_label.config(text=str(PID_VALUES["P4"]))
        self.PID_I1_label.config(text=str(PID_VALUES["I1"]))  
        self.PID_I2_label.config(text=str(PID_VALUES["I2"]))
        self.PID_I3_label.config(text=str(PID_VALUES["I3"]))
        self.PID_I4_label.config(text=str(PID_VALUES["I4"])) 
        self.PID_D1_label.config(text=str(PID_VALUES["D1"]))
        self.PID_D2_label.config(text=str(PID_VALUES["D2"]))
        self.PID_D3_label.config(text=str(PID_VALUES["D3"]))
        self.PID_D4_label.config(text=str(PID_VALUES["D4"]))
        self.PID_SetPoint1_label.config(text=str(PID_VALUES["SetPoint1"]))
        self.PID_SetPoint2_label.config(text=str(PID_VALUES["SetPoint2"]))
        self.PID_SetPoint3_label.config(text=str(PID_VALUES["SetPoint3"]))
        self.PID_SetPoint4_label.config(text=str(PID_VALUES["SetPoint4"]))
        dataLogger.change_PID_request([ "P1" + " " + str(PID_VALUES["P1"]),
                                        "I1" + " " + str(PID_VALUES["I1"]),
                                        "D1" + " " + str(PID_VALUES["D1"]),
                                        "P2" + " " + str(PID_VALUES["P2"]),
                                        "I2" + " " + str(PID_VALUES["I2"]),
                                        "D2" + " " + str(PID_VALUES["D2"]),
                                        "P3" + " " + str(PID_VALUES["P3"]),
                                        "I3" + " " + str(PID_VALUES["I3"]),
                                        "D3" + " " + str(PID_VALUES["D3"]),
                                        "P4" + " " + str(PID_VALUES["P4"]),
                                        "I4" + " " + str(PID_VALUES["I4"]),
                                        "D4" + " " + str(PID_VALUES["D4"]),
                                        "SP1" + " " + str(PID_VALUES["SetPoint1"]),
                                        "SP2" + " " + str(PID_VALUES["SetPoint2"]),
                                        "SP3" + " " + str(PID_VALUES["SetPoint3"]),
                                        "SP4" + " " + str(PID_VALUES["SetPoint4"])])

    # Load the saved presets from the JSON config file 
    def load_config(self):
        # Open the JSON config file
        with open("config.json","r") as f:
            # Tell python to use global variables
            global LOG_RATE
            global PRESET1_PID_VALUES
            global PRESET2_PID_VALUES
            global PRESET3_PID_VALUES
            global PID_VALUES
            global PIDHistory
            #Read in the JSON Data
            json_data = json.load(f)
            # Set the global variables
            LOG_RATE = json_data["LOG_RATE"]
            temp_PID = json_data["0"]
            PIDHistory = json_data["HIST"]
            PID_VALUES["P1"] = temp_PID[0]
            PID_VALUES["I1"] = temp_PID[1]
            PID_VALUES["D1"] = temp_PID[2]
            PID_VALUES["P2"] = temp_PID[3]
            PID_VALUES["I2"] = temp_PID[4]
            PID_VALUES["D2"] = temp_PID[5]
            PID_VALUES["P3"] = temp_PID[6]
            PID_VALUES["I3"] = temp_PID[7]
            PID_VALUES["D3"] = temp_PID[8]
            PID_VALUES["P4"] = temp_PID[9]
            PID_VALUES["I4"] = temp_PID[10]
            PID_VALUES["D4"] = temp_PID[11]
            PID_VALUES["SetPoint1"] = temp_PID[12]
            PID_VALUES["SetPoint2"] = temp_PID[13]
            PID_VALUES["SetPoint3"] = temp_PID[14]
            PID_VALUES["SetPoint4"] = temp_PID[15]
            PRESET1_PID_VALUES = json_data["1"]
            PRESET2_PID_VALUES = json_data["2"]
            PRESET3_PID_VALUES = json_data["3"]
        f.close()

    # Load all log files and update the log selection dropdown menu on the GUI with the available log files
    def load_current_logs(self):
        log_index = 0
        log_file_options = []
        for log_index in range(100):  # Change if max log file limit is changed
            try:
                with open(f"LOG{log_index}_eCVT.csv", "r") as f:
                    pass
                log_file_options.append(f"LOG {log_index}")
            except FileNotFoundError:
                pass
        dataLogger.update_log_selection_dropdown(self, log_file_options)

    # Save the current configuration into the JSON file
    def save_presets(self):
        LOG_RATE = self.logging_rate_label.cget("text").split()[0]
        current_pid = [PID_VALUES["P1"],PID_VALUES["I1"],PID_VALUES["D1"],
                       PID_VALUES["P2"],PID_VALUES["I2"],PID_VALUES["D2"],
                       PID_VALUES["P3"],PID_VALUES["I3"],PID_VALUES["D3"],
                       PID_VALUES["P4"],PID_VALUES["I4"],PID_VALUES["D4"],
                       PID_VALUES["SetPoint1"],PID_VALUES["SetPoint2"],PID_VALUES["SetPoint3"],PID_VALUES["SetPoint4"]]
        pid_presets = {"0": current_pid, "1": PRESET1_PID_VALUES, "2": PRESET2_PID_VALUES, "3": PRESET3_PID_VALUES, "LOG_RATE": LOG_RATE, "HIST": PIDHistory}
        with open("config.json","w") as f:
            json.dump(pid_presets, f, indent=4)
        f.close()
    
    # Send a request to the microcontroller to change the logging rate based on user input and update the status label on the GUI based on the result of the request
    def set_logging_rate(self):
        self.status_label.config(text="Changing Logging Rate", bg="#e0e0e0")
        result = dataLogger.change_logging_rate_request(int(float(self.logging_rate_label.cget("text").split()[0])))
        if result == 1:
            self.status_label.config(text="Logging Rate Changed Successfully", bg="#e0e0e0")
        else:
            self.status_label.config(text="Error Changing Logging Rate", bg="#e0e0e0")


    def update_graph_with_selected_log(self, event):
        log_file_selected = self.logfile_selection_dropdown.get().split(" ")[1]  # Assuming the format is "Log n"
        log_file_name = f"LOG{log_file_selected}_eCVT.csv"
        self.graph_log_file(log_file_name)
        # Open Json file and update the PID labels to match the PID values from the log file
        with open("log_PIDs.json", "r") as f:
            log_pid_data = json.load(f)    
        log_PIDs = log_pid_data.get(log_file_name, 'Not found')
        log_PID_text = f"Log {log_file_selected} PID Values:\n {log_PIDs[0]}\n {log_PIDs[1]}\n {log_PIDs[2]}\n {log_PIDs[3]}"
        self.log_pid_value_label.config(text=log_PID_text)
        pass
    
    # Send a request to the microcontroller to delete the selected log file from the SD card and update the log selection dropdown menu on the GUI with the remaining available log files
    def delete_log_file_usb(self):
        log_file_selected = self.logfile_selection_dropdown.get().split(" ")[1]  # Assuming the format is "Log n"
        # TODO: Remove log file option from dropdown menu after deletion (currently requires restarting the program to update the dropdown menu)
        dataLogger.delete_log_file_usb_request(self, log_file_selected)

    # When the user attempts to close the program, save the current configuration to the JSON file, close the serial connection to the microcontroller if it is open, close all Matplotlib figures to free resources, stop the Tkinter mainloop and destroy the window, and finally force the process to exit
    def on_close(self):
        # 1. Save the current configuration to the JSON file to preserve user settings and PID presets for the next time the program is run
        self.save_presets()
        # 2. Close the serial connection to the microcontroller if it is open to free up the COM port and allow for a clean exit
        if hasattr(dataLogger, 'ser') and dataLogger.ser.is_open:
            dataLogger.ser.close()
        # 3. Explicitly close Matplotlib figures to free resources
        plt.close('all') 
        # 4. Stop the Tkinter mainloop and destroy the window
        self.quit() 
        self.destroy()
        # 5. Force the process to exit
        sys.exit(0)

if __name__ == "__main__":
    # Before launching the GUI, check if the connection to the STM microcontroller was successful. If it was, launch the GUI. 
        app = App()
        app.protocol("WM_DELETE_WINDOW", app.on_close)
        app.mainloop()