//Files the program will pull definitions from
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include <frc/drive/DifferentialDrive.h>
#include <IterativeRobot.h>
#include <frc/talon.h>
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/BaseMotorController.h>

//so we don't have to put frc:: in front of everything
using namespace frc;

class Robot : public frc::IterativeRobot {
 public:
  void TeleopPeriodic() override {
   tln_left.Set(mode, joy_xbox.GetY());
   tln_right.Set(mode, -joy_xbox.GetY());
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
