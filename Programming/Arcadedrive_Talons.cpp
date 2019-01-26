//Files the program will pull definitions from
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include <frc/drive/DifferentialDrive.h>
#include <IterativeRobot.h>
#include <frc/talon.h>  
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/BaseMotorController.h>
#include <RobotDrive.h>

//so we don't have to put frc:: in front of everything
using namespace frc;

double speed = 0.5; //DO NOT SET TO GREATER THAN 1.
double minStickApply = 0.2;

class Robot : public frc::IterativeRobot {
 public:
  void TeleopPeriodic() override {
    //Chaotic Corner Drive
    //mtr_talonLeft.Set(mode, joy_xbox.GetY()/2); 
    //mtr_talonRight.Set(mode, joy_xbox.GetX()/2);

    //Tank Drive
    //mtr_talonLeft.Set(mode, -joy_xbox.GetRawAxis(1) * speed);
    //mtr_talonRight.Set(mode, joy_xbox.GetRawAxis(5) * speed);

    //Arcade drive
    if(joy_xbox.GetRawAxis(0) > minStickApply){ //x axis
      mtr_talonLeft.Set(mode, joy_xbox.GetRawAxis(0) * speed);
      mtr_talonRight.Set(mode, joy_xbox.GetRawAxis(0) * speed);
    }
    else if(joy_xbox.GetRawAxis(1) > minStickApply){ //y axis
      mtr_talonLeft.Set(mode, -joy_xbox.GetRawAxis(1) * speed);
      mtr_talonRight.Set(mode, joy_xbox.GetRawAxis(1) * speed);
    }
  }

 private:
    Joystick joy_xbox { 0 };
    TalonSRX mtr_talonRight { 1 };
    TalonSRX mtr_talonLeft { 2 };
    ControlMode mode;
   
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
