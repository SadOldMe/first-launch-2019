/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019                                                         */
/* 2018 FIRST. All Rights Reserved.                                           */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//All of the libraries for the robot to take functions and information from
#include "Robot.h"
#include <iostream>
#include <Joystick.h>
#include <Drive/DifferentialDrive.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <Spark.h>
#include <Talon.h>
#include <Solenoid.h>
#include <Encoder.h>
#include <ctre/Phoenix.h>

//Declare Variables
int speed = 1;

//Joystick decleration
frc::Joystick joy_1 { 0 };

/***SPARK***/

//This creates the Spark differential drive
//Defines the motors
frc::Spark mtr_sparkLeft { 0 };
frc::Spark mtr_sparkRight { 1 };

//Combines motors into the differential drive
frc::DifferentialDrive drv_wheelsSpark {mtr_left, mtr_right};

/***TALON***/
//Defines the motors
frc::Talon mtr_talonLeft { 0 };
frc::Talon mtr_talonRight { 1 };

//Combines motors into the differential drive
frc::DifferentialDrive drv_wheelsTalon {mtr_left2, mtr_right2};

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  //srx.Set(ControlMode::PercentOutput, 0);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}
/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString(
  //     "Auto Selector", kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {

/*All values in the differential drive must be negative, otherwise when you go 
forwards, it will go back and vice versa. Only 1 of the four drives should ever
be used at once, so comment out the rest you are not using*/

/***SPARK***/

/*Tank Drive for 4 axes remote*/
drv_wheels.TankDrive(-joy_1.GetRawAxis(3), -joy_1.GetRawAxis(1), true);

/*Tank Drive for 6 axes remote*/
//drv_wheels.TankDrive(-joy_1.GetRawAxis(5) * speed, -joy_1.GetRawAxis(1) * speed, true);

/***TALON***/

/*Tank Drive for 4 axes remote*/
//drv_wheelsTalon.TankDrive(-joy_1.GetRawAxis(3), -joy_1.GetRawAxis(1), true);

/*Tank Drive for 6 axes remote*/
//drv_wheelsTalon.TankDrive(-joy_1.GetRawAxis(5) * speed, -joy_1.GetRawAxis(1) * speed, true);
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
