#pragma once
#include "main.h"
#include "PID.h"
#include "MotorContainer.h"

class DriveTrain
{
public:
    DriveTrain(int8_t _frontMotorPort, int8_t _backMotorPort, PID _PID, ControllerAnalog _controllerAxis);

    void RunUserControl(Controller *const _controller);

    void SetTarget(double _target);

private:
    MotorContainer front;
    MotorContainer back;

    PID pid;

    ControllerAnalog controllerAxis;
};