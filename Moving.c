#pragma config(Sensor, port2,  touchLED,       sensorVexIQ_LED)
#pragma config(Sensor, port3,  colorDetector,  sensorVexIQ_ColorHue)
#pragma config(Sensor, port4,  gyroSensor,     sensorVexIQ_Gyro)
#pragma config(Sensor, port7,  distanceMM,     sensorVexIQ_Distance)
#pragma config(Sensor, port8,  bumpLSwitch,    sensorVexIQ_Touch)
#pragma config(Sensor, port9,  bumpRSwitch,    sensorVexIQ_Touch)
#pragma config(Motor,  motor1,          leftMotor,     tmotorVexIQ, openLoop, driveLeft, encoder)
#pragma config(Motor,  motor6,          rightMotor,    tmotorVexIQ, openLoop, reversed, driveRight, encoder)
#pragma config(Motor,  motor10,         armMotor,      tmotorVexIQ, openLoop, encoder)
#pragma config(Motor,  motor11,         clawMotor,     tmotorVexIQ, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
// Simple movement program using motor encoders
// Geoff Hall
// Configuration for my robot
/*------------------------------------------------------------------------------------------------
Move robot straight and return to start with 2 turns
  Plan
  1)move your robot forward for 1000 encoder units(?).
  2)turn your robot x degrees
  3)move robot back for 100 encoder units
  4)turn you robot x degress
  5) return to start by moving straight for x encoder units

  At the end of the program, all motors
  will shut down automatically and turn off.

Untested code
------------------------------------------------------------------------------------------------*/

task main
{

  //Reset the armMotor back to zero
  resetMotorEncoder(leftMotor);
  resetMotorEncoder(rightMotor);

 //Sets the absolute position target of the motor plugged
 //into leftMotor and rightMotor ports to 1000 encoder units at a speed of 50%
 //This causes the motor to move 1000 encoder units forward from its start point

 //---------------
 // Move robot forward
 setMotorTarget(leftMotor, 1000, 50);
 setMotorTarget(rightMotor, 1000, 50);

 //Holds program flow until the motors come to a complete stop.
 waitUntilMotorStop(leftMotor);
 waitUntilMotorStop(rightMotor);

 //---------------
 // Turn robot
 setMotorTarget(leftMotor, 100, 50);
 setMotorTarget(rightMotor, 50, 10);

 //Holds program flow until the motors come to a complete stop.
 waitUntilMotorStop(leftMotor);
 waitUntilMotorStop(rightMotor);

 //---------------
 // Reverse robot
 setMotorTarget(leftMotor, -100, 50);
 setMotorTarget(rightMotor, -100, 50);

 //Holds program flow until the motors come to a complete stop.
 waitUntilMotorStop(leftMotor);
 waitUntilMotorStop(rightMotor);

 //---------------
 // Turn robot
 setMotorTarget(leftMotor, 100, 50);
 setMotorTarget(rightMotor, 50, 10);

 //Holds program flow until the motors come to a complete stop.
 waitUntilMotorStop(leftMotor);
 waitUntilMotorStop(rightMotor);

 //---------------
 // Move robot forward
 setMotorTarget(leftMotor, 1000, 50);
 setMotorTarget(rightMotor, 1000, 50);

 //Holds program flow until the motors come to a complete stop.
 waitUntilMotorStop(leftMotor);
 waitUntilMotorStop(rightMotor);

 // Adjust distances moved and angles turned to return robot to starting location

}
