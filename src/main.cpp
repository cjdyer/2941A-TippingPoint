#include "main.h"
#include "setup.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}


//Converts controller joystick value to voltage for motors.
float leftSpeed() { return controller.getAnalog(ControllerAnalog::leftY) * 12000; }
float rightSpeed() { return controller.getAnalog(ControllerAnalog::rightY) * 12000; }

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	bool goalHolding;//If the MoGo hook holding a MoGo?

	//All MoGo related motors to use lock position when stopped
	FrontMoGoLift.setBrakeMode(AbstractMotor::brakeMode::hold);
	BackMoGoLift.setBrakeMode(AbstractMotor::brakeMode::hold);

	while (true)
	{
		//Drives robot using tank control.
		LDrive.moveVoltage(leftSpeed());
		RDrive.moveVoltage(rightSpeed());

		//Simple MoGo lift control
		if(rightUp.isPressed())
			FrontMoGoLift.moveVoltage(11000);
		else if(rightDown.isPressed())
			FrontMoGoLift.moveVoltage(-5000);
		else
			FrontMoGoLift.moveVoltage(0);
			

		if(leftUp.isPressed())
			BackMoGoLift.moveVoltage(11000);
		else if(leftDown.isPressed())
			BackMoGoLift.moveVoltage(-11000);
		else
			BackMoGoLift.moveVoltage(0);

		delay(50);//Waits 50 milliseconds before rerunning.
	}
}