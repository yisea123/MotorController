#include "mbed.h"
#include "Motor.h"

CAN can1(PB_8,PB_9,250000);
AnalogIn ain(A0);

Motor::Motor() {
    char const * serial = "0002173";  // Can this be removed?
    can1.frequency(500000);
}

void Motor::drive() {
    int is_velocity_set = set_velocity();
    if (is_velocity_set != 0)
        printf("Set velocity failed. CAN error code: %i\n\r", is_velocity_set);
    
    int is_power_set = set_power();
    if (is_power_set != 0)
        printf("Set power failed. CAN error code: %i\n\r", is_power_set);
}
    
int Motor::set_velocity() {
    int id = DC_BASE + DC_DRIVE;
    
    float pedal_position = ain.read();
    
    // Defaults in case something goes wrong I guess
    float current = MAX_CURRENT;
    float velocity = MAX_VELOCITY;
    current = MAX_CURRENT * pedal_position;
    velocity = MAX_VELOCITY * pedal_position;

    if (DEBUG) printf("Velocity: %.2f\n\r", velocity);
    
    // Create data for CAN
    // Current and velocity flipped for endianness
    float data[2];
    data[1] = current;
    data[0] = velocity;
   
    // Write to CAN
    int write_success = can1.write(CANMessage(id, (char*)data, 8));
    return write_success;
}

int Motor::set_power() {
    float bus_current = MAX_CURRENT;
    float data[2];
    data[1] = bus_current;
    data[0] = 0.0;
    
    int id = DC_BASE + DC_POWER;
    int write_success = can1.write(CANMessage(id, (char*)data, 8));
    return write_success;
}