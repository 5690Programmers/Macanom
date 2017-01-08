#include <iostream>
#include <memory>
#include <string>

#include <Joystick.h>
#include <SampleRobot.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <RobotDrive.h>
#include <Timer.h>
#include <interFaces/Gyro.h>

using frc;

class Robot: public frc::SampleRobot {
	RobotDrive myRobot {0, 1, 2, 3};
	Joystick stick {0};
	SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";

public:
	Robot() {
		myRobot.SetExpiration(0.1);
	}

	void RobotInit() {
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		SmartDashboard::PutData("Auto Modes", &chooser);
	}

	void Autonomous() {
		auto autoSelected = chooser.GetSelected();
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
			std::cout << "Running custom Autonomous" << std::endl;
			myRobot.SetSafetyEnabled(false);
			myRobot.Drive(-0.5, 1.0); // spin at half speed
			Wait(2.0);                // for 2 seconds
			myRobot.Drive(0.0, 0.0);  // stop robot
		} else {
			// Default Auto goes here
			std::cout << "Running default Autonomous" << std::endl;
			myRobot.SetSafetyEnabled(false);
			myRobot.Drive(-0.5, 0.0); // drive forwards half speed
			Wait(2.0);                // for 2 seconds
			myRobot.Drive(0.0, 0.0);  // stop robot
		}
	}

	void OperatorControl() override {
		myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled()) {

			myRobot.MecanumDrive_Cartesian(stick.GetX(), stick.GetY(), 0)

			// wait for a motor update time
			Wait(0.005);
		}
	}

	void Test() override {

	}
};

START_ROBOT_CLASS(Robot)
