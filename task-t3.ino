const int pirSensorPin = 3;        // Motion sensor connected to digital pin 2
const int irSensorPin = 2;         // Infrared sensor connected to digital pin 3
const int ledPin = 4;             // Built-in LED on Arduino board

volatile int pirState = LOW;
volatile int irState = LOW;

void setup() {
  pinMode(pirSensorPin, INPUT);
  pinMode(irSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(pirSensorPin), pirInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(irSensorPin), irInterrupt, CHANGE);
}

void loop() {
  // Your main loop code, if needed
}

void pirInterrupt() {
  int motionDetected = digitalRead(pirSensorPin);

  if (motionDetected == HIGH) {
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      updateLED();
      pirState = HIGH;
    }
  } else {
    if (pirState == HIGH) {
      Serial.println("Motion stopped");
      updateLED();
      pirState = LOW;
    }
  }
}

void irInterrupt() {
  int irValue = digitalRead(irSensorPin);

  if (irValue == HIGH) {
    if (irState == LOW) {
      Serial.println("IR signal detected!");
      updateLED();
      irState = HIGH;
    }
  } else {
    if (irState == HIGH) {
      Serial.println("No IR signal detected");
      updateLED();
      irState = LOW;
    }
  }
}

void updateLED() {
  digitalWrite(ledPin, HIGH);
  delay(500);  // Adjust the delay based on your preference
  digitalWrite(ledPin, LOW);
}
