// https://www.tinkercad.com/things/7t3TDsW5A5f-m1t1p
// Arduino will use 2 pins, one for the motion sensor and one for the LED
const uint8_t SENSOR_PIN = 2;
const uint8_t LED_PIN = 13;

// By default, the LED’s state is LOW (not turned on)
uint8_t ledState = LOW;
// By default, no motion detected
bool montionFlag = false;

// Need a setup function to connect the hardwares together
void setup()
{
  // Add sensor as an input
  pinMode(SENSOR_PIN, INPUT);
  // Add LED as an output
  pinMode(LED_PIN, OUTPUT);
  // Setup serial communication
  Serial.begin(9600);
}

void loop() {
  // Logging statements
  montionFlag = digitalRead(SENSOR_PIN);
  Serial.print("Montion detected: ");
  Serial.println(montionFlag);
  
  ledState = montionFlag ? HIGH : LOW;
  digitalWrite(LED_PIN, ledState);
  Serial.print("LED turned on: ");
  Serial.println(ledState);
}
