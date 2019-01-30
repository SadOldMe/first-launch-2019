#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Encoder.h>
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/BaseMotorController.h>
#include <frc/Solenoid.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/Joystick.h>
#include <frc/BuiltInAccelerometer.h>

using namespace frc;

// Variable declaration //

WPI_TalonSRX tln_leftWheel { 1 }; //left motor
WPI_TalonSRX tln_rightWheel { 2 }; //right motor
WPI_TalonSRX tln_arm { 3 }; //arm connected to Cargo In/Out box
WPI_TalonSRX tln_cargoIO { 4 }; //axel + wheels used for intake and output of cargo balls

DifferentialDrive drv_Wheels { tln_leftWheel, tln_rightWheel }; //left + right wheel diff. drive

Encoder enc_leftWheel { 0, 1 }; //left wheel encoder
Encoder enc_rightWheel { 2, 3 }; //right wheel encoder
Encoder enc_arm { 4, 5 }; //arm encoder

Joystick joy_xbox { 0 }; //xbox controller

BuiltInAccelerometer accelerometer; //RoboRIO built-in accelerometer

double accelMult = 0.01; //used to modify acceleration multiplier on drive
const double pi = 3.141592653; //used for encoder distances

// End variable declaration //

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  SmartDashboard::PutData("Auto Modes", &m_chooser);

  drv_Wheels.SetRightSideInverted(true);

  enc_rightWheel.SetSamplesToAverage(5);
  enc_rightWheel.SetDistancePerPulse(1.0 / 360.0 * 2.0 * pi * 1.5);
  enc_rightWheel.SetMinRate(1.0);

  enc_leftWheel.SetSamplesToAverage(5);
  enc_leftWheel.SetDistancePerPulse(1.0 / 360.0 * 2.0 * pi * 1.5);
  enc_leftWheel.SetMinRate(1.0);

  enc_arm.SetSamplesToAverage(5);
  enc_arm.SetDistancePerPulse(1.0 / 360.0 * 2.0 * pi * 1.5); //to do: find radius of wheel/motor/thing that moves the arm
  enc_arm.SetMinRate(1.0); 
  }

void Robot::RobotPeriodic() {
  if(accelMult < 1. && (joy_xbox.GetRawAxis(1) > 0.01 || joy_xbox.GetRawAxis(5) > 0.01)){
    accelMult += 0.01;
  }

  if(joy_xbox.GetRawAxis(1) < 0.1 && joy_xbox.GetRawAxis(5) < 0.1) { //the sticks were stopped being pushed forward
    AutoBrake(drv_Wheels);
    accelMult = 0.01;
  }

  SmartDashboard::PutNumber("Acceleration Multiplier", accelMult);
}

void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    enc_leftWheel.Reset();
    enc_rightWheel.Reset();
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    /** To do: make default auto, which does the following:
     * Drives forward and off of the hab platform
     * Add more to this list.
     **/
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  drv_Wheels.TankDrive(joy_xbox.GetRawAxis(1) * accelMult, joy_xbox.GetRawAxis(5) * accelMult);
}

//Use these functions to test controls BEFORE putting them in periodic classes.
void Robot::TestInit() {}

void Robot::TestPeriodic() {}

// User-defined functions //

void Robot::AutoBrake(DifferentialDrive& drive) {
  while(accelerometer.GetX() > 1.0 || accelerometer.GetX() < -1.0) {
    drive.TankDrive(-accelerometer.GetX(), -accelerometer.GetX());
  }
}

// End user-defined functions //

#ifndef RUNNING_FRC_TESTS
int main() { return StartRobot<Robot>(); }
#endif
