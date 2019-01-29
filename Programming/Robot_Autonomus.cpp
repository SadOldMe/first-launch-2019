//Another possible project: Find speakers to use instead of yelling, "Enabling!"

//Files the program will pull definitions from
#include <frc/Joystick.h>
#include <frc/Spark.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/IterativeRobot.h>
#include <frc/talon.h>  
#include <ctre/Phoenix.h>
#include <ctre/phoenix/motorcontrol/can/BaseMotorController.h>
#include <frc/RobotDrive.h>
#include <frc/Encoder.h>
#include <iostream>

//so we don't have to put frc:: in front of everything
using namespace frc;

double speed = 1;
bool reversing = false;
int distance = 2001;

class Robot : public frc::IterativeRobot {

  

 public:

  void AutonomousInit() {

    enc_right.Reset();
    enc_left.Reset();
    reversing = false;

  }

  void AutonomousPeriodic() {

  if (enc_left.Get() <= distance && enc_left.Get() >= 0 && !reversing) {

    drv_wheels.TankDrive(-speed, -speed);
    std::cout << enc_left.Get() << std::endl;

  } else if (enc_left.Get() >= distance){

    reversing = true; 
    enc_left.Reset();  
    std::cout << enc_left.Get() << std::endl;

  } else if (enc_left.Get() >= distance-200 && reversing){

    drv_wheels.TankDrive(speed, speed);   
    std::cout << enc_left.Get() << std::endl; 

  } else {

    std::cout << "Robot Stopped" << std::endl;
    std::cout << enc_left.Get() << std::endl;

  }

  }

  void TeleopInit() override {}

  void TeleopPeriodic() override {
  
    /***TANK DRIVE***/

    //drv_wheels.TankDrive(joy_xbox.GetRawAxis(1) * speed, joy_xbox.GetRawAxis(5) * speed, true);

    /***ARCADE DRIVE***/

    drv_wheels.ArcadeDrive(joy_xbox.GetRawAxis(1) * speed, joy_xbox.GetRawAxis(0) * speed);

    /***TESTING***/
 
    //std::cout << enc_right.Get() << std::endl;
    //std::cout << enc_left.Get() << std::endl;
    
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

    //Encoders
    /*'a' channel has 3 wires whilest the 'b' channel has 1 wire (for 1 set of motors)*/

    Encoder enc_right {1, 2, false};
    Encoder enc_left {3, 4, false};
   
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); /*std::cout << "testing" << std::endl;*/}
#endif
