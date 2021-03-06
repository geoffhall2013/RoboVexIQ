#pragma config(Sensor, port2,  distanceMM,     sensorVexIQ_Distance)
#pragma config(Sensor, port3,  colorDetector,  sensorVexIQ_ColorHue)
#pragma config(Sensor, port4,  gyroSensor,     sensorVexIQ_Gyro)
#pragma config(Sensor, port5,  touchLED,       sensorVexIQ_LED)
#pragma config(Sensor, port8,  bumpSwitchLeft, sensorVexIQ_Touch)
#pragma config(Sensor, port9,  bumpSwitchRight, sensorVexIQ_Touch)
#pragma config(Motor,  motor1,          leftMotor,     tmotorVexIQ, openLoop, driveLeft, encoder)
#pragma config(Motor,  motor6,          rightMotor,    tmotorVexIQ, openLoop, reversed, driveRight, encoder)
#pragma config(Motor,  motor10,         armMotor,      tmotorVexIQ, openLoop, encoder)
#pragma config(Motor,  motor11,         clawMotor,     tmotorVexIQ, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------------------------------------------------
  This program
  - searches for objects
  - approaches object
  - picks object up if green
  - else backs up and searches again.
------------------------------------------------------------------------------------------------*/

task main
{
  int ISeeColor;
  int ISeeObject, ISeeObject_new;
	setColorMode(colorDetector, colorTypeRGB_Hue_Reflected);
	setDistanceMaxRange(distanceMM, 500);

	resetMotorEncoder(leftMotor);		//Reset the current position in the motor encoder to zero.
	resetMotorEncoder(rightMotor);
	resetMotorEncoder(armMotor); //Take current position as zero. Arm down
	resetMotorEncoder(clawMotor); // claw starts open

  wait1Msec(50); //Small delay

	// slowly rotate, looking for object
	setMotorSpeed(leftMotor, 30);
	setMotorSpeed(rightMotor, -30);


	ISeeColor= getColorHue(colorDetector);
	ISeeObject = getDistanceValue(distanceMM);

  while(ISeeObject > 400)
	  {
      wait1Msec(5);
      ISeeObject = getDistanceValue(distanceMM);
      displayTextLine(1, "LM: %d, RM: %d", getMotorEncoder(leftMotor), getMotorEncoder(rightMotor));
		  displayTextLine(2," Distance: %d",ISeeObject);
	      // note rotation count
	 }
	 // stop rotating when object detected
	 // note heading from gyro
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);

	// TODO: check that we are still moving toward object
	//   - stop
	//   - turn 10 degress left - take reading
	//   - turn 10 degress right - take reading       |
	//   - turn 10 degress right - take reading         /
	//  - turn and move towards greatest reading

	wait1Msec(500);

  // move toward object
	setMotorSpeed(leftMotor, 50);
	setMotorSpeed(rightMotor, 50);

	while(ISeeObject > 85)
	{
    //Display
		displayTextLine(1, "LM: %d, RM: %d", getMotorEncoder(leftMotor), getMotorEncoder(rightMotor));
		displayTextLine(2," Distance: %d",ISeeObject);
		wait1Msec(5);
		ISeeObject_new = getDistanceValue(distanceMM);
		if(ISeeObject_new <= ISeeObject) {ISeeObject = ISeeObject_new;} // while distance is decreasing - keep moving forward
		else //  Losing object, search for it again
    {
    	 // stop motors
    	 setMotorSpeed(leftMotor, 0);
 	     setMotorSpeed(rightMotor, 0);
 	     // TODO: - if distance increases (lost target) stop and aquire target again
 	   }
	}
	// Has reached object, Stop motors

  setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);
	ISeeColor= getColorHue(colorDetector);
	displayTextLine(3," Hue:%d", ISeeColor);
	// if Green lift claw
	if ((ISeeColor > 60) && (ISeeColor < 120)) // if green and close
	  {
	  	// close claw
	  	setServoTarget(clawMotor, 110);
	  	sleep(500);
	    //Lift arm up and down
	    setServoTarget(armMotor, 300);  //Enable Servo Mode and move to position 60.
	    sleep(2000);
	    setServoTarget(armMotor, 10);   //Enable Servo Mode and move to position 10.
	    sleep(2000);
	    setServoTarget(clawMotor, 0);
	    sleep(2000);
    } else {
	//if not, reverse for 500 encoder units
    	resetMotorEncoder(leftMotor);		//Reset the current position in the motor encoder to zero.
	    resetMotorEncoder(rightMotor);
      moveMotorTarget(leftMotor, -500, -50);  //Set motor to run 5000 counts at power level 50
	    moveMotorTarget(rightMotor, -500, -50);
	    waitUntilMotorStop(leftMotor);
	    waitUntilMotorStop(rightMotor);
	  }
	}
