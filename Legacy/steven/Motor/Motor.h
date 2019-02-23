// Driver controls CAN base address and packet offsets
#define DC_BASE         0x220
#define MC_BASE         0x240
#define DC_DRIVE        0x01
#define DC_POWER        0x02
#define DC_RESET        0x03
#define DC_SWITCH       0x04

#define DEBUG 0

#define MAX_VELOCITY 100 
#define MAX_CURRENT 1.0

class Motor {
public:
    // Initializes motor. Takes no parameters.
    Motor();
    
    // Main driver for motor
    void drive();
    
private:

    // Gets the velocity and current for motor and sends it via the CAN
    // Returns CAN::write(...) return value for error handling
    int set_velocity();
    
    // Gets the bus current and sends it via CAN to the motor
    // Returns CAN::write(...) return value for error handling
    int set_power();
};