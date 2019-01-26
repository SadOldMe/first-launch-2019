//Files the program will pull definitions from
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/IterativeRobot.h>
#include <frc/talon.h>  
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/BaseMotorController.h>
#include <frc/RobotDrive.h>

//so we don't have to put frc:: in front of everything
using namespace frc;

double speed = 1; 

class Robot : public frc::IterativeRobot {
 public:
  void TeleopPeriodic() override {
  
    drv_wheels.TankDrive(joy_xbox.GetRawAxis(1) * speed, joy_xbox.GetRawAxis(5) * speed, true);
    
  }

 private:

    //DON'T FORGET SEMICOLONS HERE!!!

    /***DEFINE VATAIBLES***/

    Joystick joy_xbox { 0 };

    //Use WPI_TalonSRX because those can be used in differential drives

    WPI_TalonSRX mtr_talonRight { 1 };
    WPI_TalonSRX mtr_talonLeft { 2 };

    ControlMode mode;

    //Construct the Differential Drive

    DifferentialDrive drv_wheels {mtr_talonRight, mtr_talonLeft};
   
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
