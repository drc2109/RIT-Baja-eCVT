#include <stdio.h>
#include "Controller_P7.h"

int testmain(void) {
    // 1. Initialize the controller (Run this ONLY ONCE at startup)
    Controller_P7_initialize();

    // 2. Main execution loop
    // In a real embedded system, this loop is often triggered by a hardware timer 
    // interrupt so it runs at a precise sample rate (e.g., exactly every 10ms).
    int i = 0;
    while (i<50) {
        
        // --- A. PASS IN VARIABLES ---
        // Read your hardware sensors and assign them to the input structure
        Controller_P7_U.Omega_Primary = 325.0f; // ReadEngineSpeedSensor(); // e.g., 1500.0f
        Controller_P7_U.Omega_Secondary = 200.0f; // ReadSecondarySpeedSensor(); // e.g., 1500.0f
        Controller_P7_U.Theta_Helix = 1.3f; //ReadGearRatioSensor(); // e.g., 1.5f

        // --- B. DO A STEP ---
        // Run the control algorithm using the new inputs
        Controller_P7_step();

        // --- C. GET THE OUTPUT ---
        // Extract the calculated control signal
        double control_command = Controller_P7_Y.Command;
        printf("Control Command: %f\n", control_command);
        // Use the output somewhere else in your hardware
        // ApplyActuatorVoltage(control_command); 

        // --- D. WAIT ---
        // Wait until it is time for the next control step
        // WaitForNextSampleTime(); 
        i++;
    }

    return 0;
}
