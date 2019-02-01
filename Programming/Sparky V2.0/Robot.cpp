#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Encoder.h>
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/BaseMotorController.h>
#include <frc/Solenoid.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/Joystick.h>

using namespace frc;

// Variable declaration //

// DRIVER //
WPI_TalonSRX tln_leftWheel { 1 }; //left motor
WPI_TalonSRX tln_rightWheel { 2 }; //right motor

Encoder enc_leftWheel { 0, 1 }; //left wheel encoder
Encoder enc_rightWheel { 2, 3 }; //right wheel encoder

DifferentialDrive drv_Wheels { tln_leftWheel, tln_rightWheel }; //left + right wheel diff. drive
double accelMult = 0.3; //used to modify acceleration multiplier for the wheels

Joystick joy_driver { 0 }; //controller for main driver
int driver_leftStickY = 1, driver_rightStickY = 3; //driver sticks

// CO-DRIVER //
WPI_TalonSRX tln_arm { 3 }; //arm connected to Cargo In/Out box
WPI_TalonSRX tln_cargoIO { 4 }; //axel + wheels used for intake and output of cargo balls

Encoder enc_arm { 4, 5 }; //encoder for arm holding cargo bay
const double pi = 3.141592653; //used for encoder distances

Joystick joy_codriver { 1 }; //controller for co driver (Arm control)

// End variable declaration //

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  SmartDashboard::PutData("Auto Modes", &m_chooser);

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
  if(joy_driver.GetRawAxis(driver_leftStickY) > 0.1 || joy_driver.GetRawAxis(driver_rightStickY) > 0.1 || 
     joy_driver.GetRawAxis(driver_leftStickY) < -0.1 || joy_driver.GetRawAxis(driver_rightStickY) < -0.01){ //the sticks were moved
    accelMult += 0.01;
  }

  else { //the sticks were stopped being pushed forward
    accelMult = 0.3;
  }
}

void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    //Default Auto goes here
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
  drv_Wheels.TankDrive(joy_driver.GetRawAxis(driver_leftStickY) * accelMult, joy_driver.GetRawAxis(driver_rightStickY) * accelMult);
}

//Use these functions to test controls BEFORE putting them in periodic classes.
void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return StartRobot<Robot>(); }
#endif
