#define PCINT_PIN A5

#include <YetAnotherPcInt.h>

const uint8_t SENSOR_MOTION_PIN = 2;
const uint8_t SENSOR_MOTION_2_PIN = 3;
const uint8_t LED_PIN = 13;
const uint8_t LED_PIN_2 = 7;


// By default, the LED’s state is LOW (not turned on)
uint8_t ledState = LOW;


// Need a setup function to connect the hardwares together
void setup()
{
  // Add sensors as an input
  pinMode(SENSOR_MOTION_PIN, INPUT);
  pinMode(SENSOR_MOTION_2_PIN, INPUT);
  
  // Add LEDs as an output
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  
  
  // Setup serial communication
  Serial.begin(9600);
  
  // Attach interrupt to sensor pin  
  attachInterrupt(digitalPinToInterrupt(SENSOR_MOTION_PIN), toggle, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SENSOR_MOTION_2_PIN), toggle, CHANGE);

  // Add a third interrupt that called when the "tail sensor" touches high voltage
  pinMode(PCINT_PIN, INPUT);
  PcInt::attachInterrupt(PCINT_PIN, pinChanged, RISING);

  // Start the TimerInterrupt
  startTimer();
}

void pinChanged(bool pinstate) {
  Serial.println("Ouch, the tail touches high voltage!");
}

void toggle() {
  // The LED is turned on whenever motion is detected on either sensors
  ledState = digitalRead(SENSOR_MOTION_PIN) || digitalRead(SENSOR_MOTION_2_PIN);
  digitalWrite(LED_PIN, ledState);
}

void startTimer(){
  noInterrupts();
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 0.5 Hz increments
  OCR1A = 31249; // = 16000000 / (1024 * 0.5) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}


ISR(TIMER1_COMPA_vect){
   // TimerInterrupt turns the second LED on or off
   digitalWrite(LED_PIN_2, !digitalRead(LED_PIN_2));
   Serial.print("(TIMER INTERRUPT) Second LED is toggled to ");
   Serial.println(digitalRead(LED_PIN_2));
}


void loop() {
  // Logging statements
  Serial.print("Montion 1 detected: ");
  Serial.println(digitalRead(SENSOR_MOTION_PIN));

  Serial.print("Montion 2 detected: ");
  Serial.println(digitalRead(SENSOR_MOTION_2_PIN));
  
  Serial.print("LED 1 turned on: ");
  Serial.println(ledState);
  
  delay(2000);
}
