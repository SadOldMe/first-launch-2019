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
WPI_TalonSRX tln_leftFront { 1 }; //left front motor
WPI_TalonSRX tln_leftBack { 2 }; //left back motor
WPI_TalonSRX tln_rightFront { 3 }; // right front motor
WPI_TalonSRX tln_rightBack { 4 }; //right back motor

Encoder enc_leftWheel { 0, 1 }; //left wheel encoder
Encoder enc_rightWheel { 2, 3 }; //right wheel encoder

DifferentialDrive drv_wheels { tln_leftFront, tln_rightFront }; //left + right wheel diff. drive
double accelMult = 0.3; //used to modify acceleration multiplier for the wheels
double accelMultMax = 0.75;

Joystick joy_driver { 0 }; //controller for main driver
int driver_leftStickY = 1, driver_rightStickY = 3; //driver sticks

// CO-DRIVER //
WPI_TalonSRX tln_arm { 5 }; //arm connected to Cargo In/Out box
//WPI_TalonSRX tln_cargoIO { 6 }; //axle + wheels used for intake and output of cargo balls

Encoder enc_arm { 4, 5 }; //encoder for arm holding cargo bay
const double pi = 3.141592653; //used for encoder distances

Joystick joy_codriver { 1 }; //controller for co driver (Arm control)
int co_stickY = 1;

// End variable declaration //

void Robot::RobotInit() {
  tln_leftFront.SetInverted(true);
  tln_rightFront.SetInverted(true);

  tln_arm.SetSafetyEnabled(true);
  tln_arm.SetNeutralMode(NeutralMode::Brake);

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
  bool sticksMoving = (joy_driver.GetRawAxis(driver_leftStickY) > 0.1 || joy_driver.GetRawAxis(driver_rightStickY) > 0.1 || 
     joy_driver.GetRawAxis(driver_leftStickY) < -0.1 || joy_driver.GetRawAxis(driver_rightStickY) < -0.1);
  if( sticksMoving && accelMult < accelMultMax ) { //the sticks were moved
    accelMult += 0.01;
  }

  else if(sticksMoving && accelMult >= accelMultMax) {
    accelMult = accelMultMax;
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
  drv_wheels.TankDrive(joy_driver.GetRawAxis(driver_leftStickY) * accelMult, joy_driver.GetRawAxis(driver_rightStickY) * accelMult);
  tln_arm.Set(joy_codriver.GetRawAxis(co_stickY) * 0.25);
}

//Use these functions to test controls BEFORE putting them in periodic classes.
void Robot::TestInit() {}

void Robot::TestPeriodic() {
    drv_wheels.TankDrive(-1, -1);
}

#ifndef RUNNING_FRC_TESTS
int main() { return StartRobot<Robot>(); }
#endif
