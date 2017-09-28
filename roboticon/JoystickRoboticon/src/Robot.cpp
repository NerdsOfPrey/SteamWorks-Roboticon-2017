#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <time.h>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <DoubleSolenoid.h>
#include <CameraServer.h>
#include <Compressor.h>
#include <Joystick.h>
#include <ctrlib/CanTalonSRX.h>

class Robot: public frc::IterativeRobot {
public:
	void RobotInit() {
		CameraServer::GetInstance()->StartAutomaticCapture();
		jL = new Joystick(0);
		jR = new Joystick(1);
		leftGearShift = new DoubleSolenoid(0, 1);
		rightGearShift = new DoubleSolenoid(2, 3);
		grabSolenoidL = new DoubleSolenoid(4, 5);
		grabSolenoidR = new DoubleSolenoid(6, 7);
		fL = new CanTalonSRX(12);
		fR = new CanTalonSRX(14);
		bL = new CanTalonSRX(13);
		bR = new CanTalonSRX(15);
		liftMotor = new CanTalonSRX(7);
		c = new Compressor(0);
		gearGrabberState = false;
		banana = false;
	}


	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {
	}

	void TeleopInit() {
		leftGearShift->Set(DoubleSolenoid::Value::kForward);
		rightGearShift->Set(DoubleSolenoid::Value::kForward);
	}

	void TeleopPeriodic() {

		//Joysticks
		if(jL->GetRawAxis(1) < 2.4 && jL->GetRawAxis(1) > -2.4){
			fL->Set(jL->GetRawAxis(1));
			bL->Set(jL->GetRawAxis(1));
		}
		if(jR->GetRawAxis(1) < 2.4 && jR->GetRawAxis(1) > -2.4){
			fR->Set(-jR->GetRawAxis(1));
			bR->Set(-jR->GetRawAxis(1));
		}

		//Shift the gears!
		while(jL->GetRawButton(3)){
			if(leftGearShift->Get() == DoubleSolenoid::Value::kForward){
				leftGearShift->Set(DoubleSolenoid::Value::kReverse);
			} else {
				leftGearShift->Set(DoubleSolenoid::Value::kForward);
			}

			if(rightGearShift->Get() == DoubleSolenoid::Value::kForward){
				rightGearShift->Set(DoubleSolenoid::Value::kReverse);
			} else {
				rightGearShift->Set(DoubleSolenoid::Value::kForward);
			}

		}
		//Open/Close the gear grabber
		if(jL->GetRawButton(1)){
			grabSolenoidL->Set(DoubleSolenoid::Value::kForward);
			grabSolenoidR->Set(DoubleSolenoid::Value::kForward);
		} else if (!jL->GetRawButton(1)){
			grabSolenoidL->Set(DoubleSolenoid::Value::kReverse);
			grabSolenoidR->Set(DoubleSolenoid::Value::kReverse);
		}

		if(jL->GetRawButton(2)){
			liftMotor->Set(1);
		} else {
			liftMotor->Set(0);
		}
	}

	void TestPeriodic() {
		lw->Run();
	}

private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	//Joystick
	Joystick *jL;
	Joystick *jR;
	//Buttons
	bool gearGrabberState;
	//Solenoids
	DoubleSolenoid *leftGearShift;
	DoubleSolenoid *rightGearShift;
	DoubleSolenoid *grabSolenoidL;
	DoubleSolenoid *grabSolenoidR;
	//Motors
	CanTalonSRX *fL;
	CanTalonSRX *fR;
	CanTalonSRX *bL;
	CanTalonSRX *bR;
	CanTalonSRX *liftMotor;
	Compressor *c;
	bool banana;
};

START_ROBOT_CLASS(Robot)
