// Pin definitions for motors
#define E1 10  // Enable Pin for motor 1
#define E2 11  // Enable Pin for motor 2
#define I1 8   // Control pin 1 for motor 1
#define I2 9   // Control pin 2 for motor 1
#define I3 12  // Control pin 1 for motor 2
#define I4 13  // Control pin 2 for motor 2

// Pin definition for switch
#define IR_SENSOR 7  // Pin for the switch

// Motion speed and timing
int motorSpeed = 255;       // Maximum speed
unsigned long moveTime = 300; // Time for each side movement (300ms)

// Number of rapid side-to-side movements
unsigned int movements = 10; // Moves back and forth 10 times

void setup() {
  // Initialize motor control pins as output
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(I3, OUTPUT);
  pinMode(I4, OUTPUT);

  // Initialize IR SENSOR as input with pull-up resistor
  pinMode(IR_SENSOR, INPUT_PULLUP);

  // Enable motors by setting Enable pins high
  digitalWrite(E1, HIGH);
  digitalWrite(E2, HIGH);

  // Start Serial Communication for output
  Serial.begin(9600);
  Serial.println("Bot Motion Control Started!");
}

void loop() {
  // Read the state of the switch
  int switchState = digitalRead(IR_SENSOR);

  if (switchState == LOW) { // Switch is ON (active low)
    Serial.println("Switch ON: Performing frustrated motion");

    // Perform frustrated motion
    frustratedMotion();
    delay(2000); // Wait for 2 seconds before repeating
  } else { // Switch is OFF
    Serial.println("Switch OFF: Moving backward");

    // Move backward and stop
    moveBackward();
    delay(2000); // Move backward for 2 seconds
    stopMotors(); // Stop the bot
    while (digitalRead(SWITCH_PIN) == HIGH) {
      // Wait until the switch is turned on again
    }
  }
}

// Function for frustrated side-to-side motion
void frustratedMotion() {
  for (int i = 0; i < movements; i++) {
    Serial.println("Moving to the left");
    moveLeft();
    delay(moveTime); // Delay for the left movement

    Serial.println("Moving to the right");
    moveRight();
    delay(moveTime); // Delay for the right movement
  }
}

// Function to move the bot to the left
void moveLeft() {
  // Set motors to turn left
  digitalWrite(I1, HIGH); // Motor 1 forward
  digitalWrite(I2, LOW);
  digitalWrite(I3, LOW);  // Motor 2 backward
  digitalWrite(I4, HIGH);

  // Set motor speed
  analogWrite(E1, motorSpeed); // Speed for Motor 1
  analogWrite(E2, motorSpeed); // Speed for Motor 2
}

// Function to move the bot to the right
void moveRight() {
  // Set motors to turn right
  digitalWrite(I1, LOW);  // Motor 1 backward
  digitalWrite(I2, HIGH);
  digitalWrite(I3, HIGH); // Motor 2 forward
  digitalWrite(I4, LOW);

  // Set motor speed
  analogWrite(E1, motorSpeed); // Speed for Motor 1
  analogWrite(E2, motorSpeed); // Speed for Motor 2
}

// Function to move the bot backward
void moveBackward() {
  // Set motors to move backward
  digitalWrite(I1, LOW);
  digitalWrite(I2, HIGH);
  digitalWrite(I3, LOW);
  digitalWrite(I4, HIGH);

  // Set motor speed
  analogWrite(E1, motorSpeed); // Speed for Motor 1
  analogWrite(E2, motorSpeed); // Speed for Motor 2
}

// Function to stop the motors
void stopMotors() {
  // Stop both motors
  digitalWrite(I1, LOW);
  digitalWrite(I2, LOW);
  digitalWrite(I3, LOW);
  digitalWrite(I4, LOW);
  analogWrite(E1, 0); // Stop Motor 1
  analogWrite(E2, 0); // Stop Motor 2
}