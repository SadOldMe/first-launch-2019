#include <frc/Joystick.h>
#include <frc/Spark.h>
#include <frc/drive/DifferentialDrive.h>
#include <IterativeRobot.h>
#include <frc/talon.h>
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/BaseMotorController.h>

using namespace frc;

class Robot : public frc::IterativeRobot {
 public:
  void TeleopPeriodic() override {
    tln_left.Set(mode, joy_xbox.GetY());
    tln_right.Set(mode, -joy_xbox.GetY());
  }

 private:
  Joystick joy_xbox { 0 };

  TalonSRX tln_right { 1 };
  TalonSRX tln_left { 2 };

  ControlMode mode;
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
