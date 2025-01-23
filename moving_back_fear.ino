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
int motorSpeed = 255;     // Maximum speed for rapid movement
unsigned long moveTime = 1000; // Move for 1 second (bot moves away)

// Flag to track whether the bot has already moved
bool hasMoved = false;

void setup() {
  // Initialize motor control pins as output
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(I3, OUTPUT);
  pinMode(I4, OUTPUT);

  // Initialize switch pin as input with pull-up resistor
  pinMode(IR_SENSOR , INPUT_PULLUP);

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

  if (switchState == LOW && !hasMoved) { // Switch is ON and bot has not moved yet
    Serial.println("Switch ON: Bot is afraid and moving away once!");

    // Perform sudden backward movement only once
    suddenMoveAway();

    // Set the flag to true so it doesn't move again
    hasMoved = true;
  } else if (switchState == HIGH) { // Switch is OFF
    Serial.println("Switch OFF: Bot is stationary");

    // Stop the motors when the switch is off
    stopMotors();
  }
}

// Function to make the bot move away quickly (backward) only once
void suddenMoveAway() {
  Serial.println("Moving away quickly...");

  // Set motor 1 to move backward
  digitalWrite(I1, LOW);   // Motor 1 backward
  digitalWrite(I2, HIGH);
  
  // Set motor 2 to move backward
  digitalWrite(I3, LOW);   // Motor 2 backward
  digitalWrite(I4, HIGH);

  // Set motor speed for rapid movement
  analogWrite(E1, motorSpeed); // Speed for Motor 1
  analogWrite(E2, motorSpeed); // Speed for Motor 2

  // Move backward for the defined time
  delay(moveTime);

  // After the move, stop the motors
  stopMotors();
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