// https://www.tinkercad.com/things/0oIwrfFeaTK-m1t2p
// Arduino will use 2 pins, one for a button and one for the LED
const uint8_t SENSOR_PIN = 2;
const uint8_t LED_PIN = 13;

// By default, the LED’s state is LOW (not turned on)
uint8_t ledState = LOW;

// Need a setup function to connect the hardwares together
void setup()
{
  // Add button as an input
  pinMode(SENSOR_PIN, INPUT);
  // Add LED as an output
  pinMode(LED_PIN, OUTPUT);
  // Setup serial communication
  Serial.begin(9600);
  // Attach interrupt to sensor pin  
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), toggle, CHANGE); 
}

void toggle() {
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

void loop() {
  // Logging statements
  Serial.print("Montion detected: ");
  Serial.println(digitalRead(SENSOR_PIN));
  
  Serial.print("LED turned on: ");
  Serial.println(ledState);
}
