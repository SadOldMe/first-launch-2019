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
#include <frc/DoubleSolenoid.h>
#include <frc/Compressor.h>
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

    drv_wheels.TankDrive(joy_xbox.GetRawAxis(1) * speed, joy_xbox.GetRawAxis(5) * speed, true);

    /***PNEUMATICS CONTROL***/

    //Hatch
    if (joy_xbox.GetRawButton(1)) { //'a' button
      sol_hatch.Get() == DoubleSolenoid::Value::kForward ? sol_hatch.Set(DoubleSolenoid::Value::kReverse) : sol_hatch.Set(DoubleSolenoid::Value::kForward);
    }

    //Front Wheel
    if (joy_xbox.GetRawButton(4)) { //Left Bumper
      sol_legsFront.Get() == DoubleSolenoid::Value::kForward ? sol_legsFront.Set(DoubleSolenoid::Value::kReverse) : sol_legsFront.Set(DoubleSolenoid::Value::kForward);
      
    } 

    //Back Wheels
    if (joy_xbox.GetRawButton(5)) { //Right Bumper
      sol_legsBack.Get() == DoubleSolenoid::Value::kForward ? sol_legsBack.Set(DoubleSolenoid::Value::kReverse) : sol_legsBack.Set(DoubleSolenoid::Value::kForward);
    } 
    
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

    //Solenoids

    DoubleSolenoid sol_legsBack {4, 5};
    DoubleSolenoid sol_legsFront {2, 3};
    DoubleSolenoid sol_hatch {0, 1};

    //Compressors

    Compressor cmp_pneumatics {0};
   
};

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); /*std::cout << "testing" << std::endl;*/}
#endif
