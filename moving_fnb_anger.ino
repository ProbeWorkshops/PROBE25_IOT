// Pin definitions for motors
#define E1 10  // Enable Pin for motor 1
#define E2 11  // Enable Pin for motor 2
#define I1 8   // Control pin 1 for motor 1
#define I2 9   // Control pin 2 for motor 1
#define I3 12  // Control pin 1 for motor 2
#define I4 13  // Control pin 2 for motor 2
#define IR_SENSOR 7 // Pin for the push button (switch)

// Define motor speed (PWM range 0-255)
int motorSpeed = 255;  // Maximum speed (high speed)

// Define time intervals (in milliseconds)
unsigned long forwardTime = 3000;  // 3 seconds forward
unsigned long stopTime = 1000;     // 1 second stop
unsigned long backwardTime = 3000; // 3 seconds backward

void setup() {
  // Initialize motor control pins as output
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(I3, OUTPUT);
  pinMode(I4, OUTPUT);
  
  // Initialize the button pin as input with pull-up resistor
  pinMode(IR_SENSOR, INPUT_PULLUP);

  // Enable motors by setting Enable pins high
  digitalWrite(E1, HIGH);  // Motor 1 enabled
  digitalWrite(E2, HIGH);  // Motor 2 enabled

  // Start Serial Communication for output
  Serial.begin(9600);
  Serial.println("Motor Control with Push Button Started!");
}

void loop() {
  // Read the button state
  int buttonState = digitalRead(IR_SENSOR);

  // If the switch is ON (LOW), run the usual motor sequence
  if (buttonState == LOW) {
    Serial.println("Switch ON: Running motor sequence");

    moveForward();
    delay(forwardTime); // Move forward for the specified time

    stopMotors();
    delay(stopTime); // Pause for 1 second

    moveBackward();
    delay(backwardTime); // Move backward for the specified time

    stopMotors();
    delay(stopTime); // Pause for 1 second
  } 
  // If the switch is OFF (HIGH), move backward continuously
  else {
    Serial.println("Switch OFF: Moving backward");
    moveBackward();
  }
}

// Function to move motors forward
void moveForward() {
  digitalWrite(I1, HIGH);
  digitalWrite(I2, LOW);
  digitalWrite(I3, HIGH);
  digitalWrite(I4, LOW);
  analogWrite(E1, motorSpeed);
  analogWrite(E2, motorSpeed);
}

// Function to move motors backward
void moveBackward() {
  digitalWrite(I1, LOW);
  digitalWrite(I2, HIGH);
  digitalWrite(I3, LOW);
  digitalWrite(I4, HIGH);
  analogWrite(E1, motorSpeed);
  analogWrite(E2, motorSpeed);
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(I1, LOW);
  digitalWrite(I2, LOW);
  digitalWrite(I3, LOW);
  digitalWrite(I4, LOW);
  analogWrite(E1, 0); // Stop Motor 1
  analogWrite(E2, 0); // Stop Motor 2
}