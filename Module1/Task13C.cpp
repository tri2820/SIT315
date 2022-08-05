// https://www.tinkercad.com/things/eJrNqeTOoOe-m1t3c
const uint8_t SENSOR_MOTION_PIN = 2;
const uint8_t SENSOR_MOTION_2_PIN = 3;
const uint8_t LED_PIN = 13;
const uint8_t LED_2_PIN = 12;

// By default, the LED’s state is LOW (not turned on)
uint8_t ledState = LOW;
uint8_t led2State = LOW;


// Need a setup function to connect the hardwares together
void setup()
{
  // Add sensors as an input
  pinMode(SENSOR_MOTION_PIN, INPUT);
  pinMode(SENSOR_MOTION_2_PIN, INPUT);
  
  // Add LEDs as an output
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_2_PIN, OUTPUT);
  
  // Setup serial communication
  Serial.begin(9600);
  
  // Attach interrupt to sensor pin  
  attachInterrupt(digitalPinToInterrupt(SENSOR_MOTION_PIN), toggle, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SENSOR_MOTION_2_PIN), toggle2, CHANGE);
}

void toggle() {
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

void toggle2() {
  led2State = !led2State;
  digitalWrite(LED_2_PIN, led2State);
}

void loop() {
  // Logging statements
  Serial.print("Montion 1 detected: ");
  Serial.println(digitalRead(SENSOR_MOTION_PIN));
  
  Serial.print("LED 1 turned on: ");
  Serial.println(ledState);
  
  // Logging statements
  Serial.print("Montion 2 detected: ");
  Serial.println(digitalRead(SENSOR_MOTION_2_PIN));
  
  Serial.print("LED 2 turned on: ");
  Serial.println(led2State);
}
