#include <Servo.h>  // Included servo.h library
Servo myservo;      // Created a servo object
int pos = 0;        // pos variable stores servo’s position
boolean fire = false; // boolean variable fire tracks if there's fire

// Defined PINs for each sensor, motor and buzzer
#define Left 8      
#define Right 9     
#define Forward 10  
#define LM1 2       
#define LM2 3       
#define RM1 4       
#define RM2 5       
#define pump 6
#define buzzerPin 7 

void setup()
{
  // Set pin modes as input or output (sensors: inputs, and motors, pump, and buzzer: outputs)
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(buzzerPin, OUTPUT); 
  
  // Attached servo to pin 11 and set initial position
  myservo.attach(11);
  myservo.write(90); 
}

// Function to put off fire
void put_off_fire()
{
    // Stop the motors
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    
    // Activate the water pump to extinguish the fire
    digitalWrite(pump, HIGH);
    delay(1000); //Wait for 1 second while water is sprayed
    
    // Sweep the servo arm back and forth to simulate extinguishing the fire
    for (pos = 50; pos <= 130; pos += 1) { 
      myservo.write(pos); 
      delay(10);  
    }
    for (pos = 130; pos >= 50; pos -= 1) { 
      myservo.write(pos); 
      delay(10);
    }
  
    // Turn off the water pump and reset the servo arm to its neutral position
    digitalWrite(pump,LOW);
    myservo.write(90);
  
    fire=false; // Reset fire status flag
}

// Function to make the buzzer beep
void beep()
{
  tone(buzzerPin, 1000); // Play a tone of frequency 1000 Hz
  delay(1000); 
  tone(buzzerPin, 700); // Play a tone of frequency 700 Hz
  delay(1000); // We can adjust the delay for desired beep duration
  noTone(buzzerPin); // Stop the tone
  delay(100); // We can adjust the delay for a desired interval between beeps
}

void loop()
{
   myservo.write(90); // Center the servo
  
    // Check sensor readings to determine movement
    if (digitalRead(Left) == 1 && digitalRead(Right) == 1 && digitalRead(Forward) == 1) 
    {
      // If all sensors detect no fire, stop the robot
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, HIGH);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, HIGH);
    }
    else if (digitalRead(Forward) == 0) 
    {
      // If the front sensor detects a fire, move forward and set fire flag
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      fire = true;
    }
    else if (digitalRead(Left) == 0)
    {
      // If the left sensor detects an obstacle, turn left and beep
      digitalWrite(LM1, LOW);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      beep();
    }
    else if (digitalRead(Right) == 0) 
    {
      // If the right sensor detects fire, turn right and beep
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, LOW);
      digitalWrite(RM2, LOW);
      beep();
    }
    
    // If the fire flag is set, beep and put off the fire
    if (fire == true)
    {
      beep();
      put_off_fire();
    }
    
    delay(100); // We can adjust this value to adjust the distance between movements
}
