#include "MoGoLift.h"
#include "Controller.h"

PID MoGoLift::pid
(
    40, 0.1, 0,
    AbstractMotor::gearset::green,
    "Mo-go lift PID"
);

MoGoLift::LiftPosition MoGoLift::target = Bottom;

Motor MoGoLift::liftMotor (11);
Piston MoGoLift::hookPiston ('A');

void MoGoLift::SetTarget(LiftPosition _position)
{
    target = _position;
}

void MoGoLift::incrementTarget()
{
    if(target == Middle)
        target = Top;
    else if(target == Bottom)
        target = Middle;
}

void MoGoLift::decrementTarget()
{
    if(target == Top)
        target = Middle;
    else if(target == Middle)
        target = Bottom;
}

// void MoGoLift::RunUserControl()
// {
//     if(RightUpTrigger.isPressed())
//         liftMotor.moveVelocity(12000);
//     else if(RightDownTrigger.isPressed())
//         liftMotor.moveVelocity(-12000);
//     else
//         liftMotor.moveVelocity(0);

//     if(AButton.changedToPressed())
//         hookPiston.Toggle();
// }

void MoGoLift::RunUserControl()
{
    if(RightUpTrigger.changedToPressed())
        incrementTarget();
    else if(RightDownTrigger.changedToPressed())
        decrementTarget();

    if(AButton.changedToPressed())
        hookPiston.Toggle();

    RunPID();
}

void MoGoLift::RunPID()
{
    pid.SetTarget(target);

    int16_t power = pid.Calculate( liftMotor.getPosition() );
    liftMotor.moveVoltage(power);
}

void MoGoLift::PrintPositions()
{
    cout << liftMotor.getPosition() << endl;
}