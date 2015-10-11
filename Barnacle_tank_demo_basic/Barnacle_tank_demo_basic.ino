/* Barnacle_tank.ino
	Luke Miller 2015

	Hardware:
	Arduino Uno
	Big Easy Driver (BED) stepper motor controller board
	Two buttons (tactile switches)
	
	Wiring:
	Arduino pin D8 to BED DIR pin
	Arduino pin D9 to BED STEP pin
	Arduino pin D4 to BED Enable pin
	Arduino pin D2 to button1
	Arduino pin D3 to button2 
	Wire other leg of buttons to GND
*/

#include <Arduino.h>

const byte stepperDir = 8; 	// define stepper direction pin.
const byte stepperStep = 9;	// define stepper step pin.

const byte stepperEnable = 4;	// define motor driver enable pin

const byte button1 = 2; // define button1 pin 
const byte button2 = 3; // define button2 pin

byte button1Flag = true;	// set true by default, when pressed this will turn false
byte button2Flag = true; 	// set true by default, when pressed this will turn false
byte motorEnabled = false;

int lowSpeed = 100;	// defining a delay in microSeconds for motor stepping
int highSpeed = 50;	// defining a delay in microSeconds for motor stepping
int stepSpeed = 0; 	// the actual delay used between steps, based on low or high speed

// Welcome to the setup loop
void setup(){  
	//--------------------------------------------------
  pinMode(stepperDir, OUTPUT);   // direction pin for Big Easy Driver
  pinMode(stepperStep, OUTPUT);  // step pin for Big Easy driver. One step per rise.
  pinMode(stepperEnable, OUTPUT); // enable pin for Big Easy driver motor power
  digitalWrite(stepperDir, LOW);
  digitalWrite(stepperStep, LOW);
  digitalWrite(stepperEnable, HIGH); // turns off motor power when high
  pinMode(button1, INPUT_PULLUP); // button1 connected to GND will run motor one direction
  pinMode(button2, INPUT_PULLUP); // button2 connected to GND will run motor other direction
  
  
    // For debugging output to serial monitor
  Serial.begin(115200);
  Serial.println("Hello");
	
}

void loop()
{
	// Main loop
	// Read button states
	button1Flag = digitalRead(button1); // reads true when button not pressed
	button2Flag = digitalRead(button2); // reads true when button not pressed
	// Set stepping speed
	stepSpeed = lowSpeed;
	
	// If neither button is pressed, disable the Big Easy Driver power
	if ( button1Flag == true & button2Flag == true){
		digitalWrite(stepperEnable, HIGH); // pull high to disable motor
		motorEnabled = false;
	}
	
	// If either button is pressed and the motor isn't already enabled, then enable
	// the motor
	if (( button1Flag == false | button2Flag == false ) & motorEnabled == false){
		motorEnabled = true;
		digitalWrite(stepperEnable, LOW); // turn on motor power
		delay(10);
	}
	
	// Turn one direction
	if (button1Flag == false & button2Flag == true){
		// Set motor direction
		digitalWrite(stepperDir, HIGH);
		// Step motor 200 times, through 1 revolution
		for (int i = 0; i < 200; i++){
			digitalWrite(stepperStep, HIGH);
			delayMicroseconds(stepSpeed);
			digitalWrite(stepperStep, LOW);
		}
	} else if (button1Flag == true & button2Flag == false){
		// Set motor direction in reverse
		digitalWrite(stepperDir, LOW);
		// Step motor 200 times, through 1 revolution
		for (int i = 0; i < 200; i++){
			digitalWrite(stepperStep, HIGH);
			delayMicroseconds(stepSpeed);
			digitalWrite(stepperStep, LOW);		
		}
	}
	

}