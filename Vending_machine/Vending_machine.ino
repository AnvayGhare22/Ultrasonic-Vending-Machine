#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // Standard library for I2C LCD
#include <Servo.h>

// Initialize LCD: address 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo motor1;

const int trigPin = 7;
const int echoPin = 8;
const int servoPin = 3;

float duration, distance;

void setup() {
  // Initialize LCD
  lcd.init();      // Some libraries use begin(), most use init()
  lcd.backlight();
  
  // Initial Greeting
  lcd.setCursor(0,0);
  lcd.print("Welcome User!");
  lcd.setCursor(0,1);
  lcd.print("Hand under lid");

  // Pin Modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Initialize Motor
  motor1.attach(servoPin);
  motor1.write(0); // Make sure motor is at "Closed" position initially
  
  Serial.begin(9600);
  delay(2000); // Short delay to let user read the welcome message
}

void loop() {
  // 1. Measure Distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;
  
  Serial.print("Distance: ");
  Serial.println(distance);

  // 2. Logic Check
  // We use a small delay here just to stabilize sensor readings, 
  // but NOT 5000ms. 100ms is enough.
  delay(100); 

  if (distance > 0 && distance <= 10.0) {
    dispenseProduct(); // Call the custom function below
  } 
  
  // We do NOT need an "Else" block that prints errors constantly. 
  // It causes the screen to flicker. 
  // The screen stays on "Welcome" (set in setup or end of dispense) 
  // until the sensor is triggered.
}

// 3. Custom Function to handle the vending process
void dispenseProduct() {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Success!.");
    lcd.setCursor(0,1);
    lcd.print("Enjoy your cookie");
    
    // Push the bottle
    motor1.write(90); // Move to push
    delay(2000);       // Wait for bottle to drop
    
    // Return mechanism
    motor1.write(0);   // Return to home position
    delay(1000);       // Wait for motor to get back

    // Reset Screen for next user
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Welcome User!");
    lcd.setCursor(0,1);
    lcd.print("Hand under lid");
}