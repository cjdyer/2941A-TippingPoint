#pragma once
#include "DualMotorContainer.h"

class Chassis
{
public:
    
    /**
     * @brief Set's the robot's distance and time targets.
     * 
     * This function is only effective if you are
     * looping `Chassis::RunPID()` in a background task
     *  
     * @param _distance The number of encoder units to drive the robot
     * @param _time The maximum amount of time the movement should take
    **/
    static void DriveStraight(int16_t _distance, uint32_t _time = 0, uint16_t _max_output = 12000);

    /**
     * @brief Sets the robot's rotate and time targets.
     * 
     * This function is only effective if you are
     * looping `Chassis::RunPID()` in a background task
     * 
     * @param _angle The number of encoder units to rotate the robot
     * @param _time The maximum amount of time the movement should take
    **/
    static void Rotate(int16_t _angle, uint32_t _time = 0);

    /**
     * @brief Drives the robot using tank drive conrolls for am H-drive.
     * 
     * This function needs to be constantly looped to be effective
    **/
    static void HDrive();

    /**
     * @brief Executes the targeted actions.
     * 
     * This function needs to be constantly looped to be effective
    **/
    static void RunPID();

    static void ResetSensors();
    
    static double GetTrackingWheel();

private:
    static pros::IMU gyro;
    static RotationSensor trackingWheel;

    static double trackingWheelOffset;

    static DualMotorContainer leftDrive;
    static DualMotorContainer rightDrive;

    static Motor horizontalDrive;

    static PID rotatePID;
    static PID straightPID;
    
    static bool rotating;
};