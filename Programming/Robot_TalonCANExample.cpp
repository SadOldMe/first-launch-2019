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

//int speed = .20;

class Robot : public frc::IterativeRobot {
 public:
  void TeleopPeriodic() override {
    //Chaotic Corner Drive
    //mtr_talonLeft.Set(mode, joy_xbox.GetY()/2); 
    //mtr_talonRight.Set(mode, joy_xbox.GetX()/2);

    //Tank Drive
    mtr_talonLeft.Set(mode, -joy_xbox.GetRawAxis(1)/1); 
    mtr_talonRight.Set(mode, joy_xbox.GetRawAxis(5)/1);
   
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
