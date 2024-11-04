const int SPEAKER_PIN = 8;
const int redLED = 21;
const int blueLED = 26;

int lastLED = 21;
bool doubleTick = false;

unsigned long previousToneMillis = 0;
unsigned long previousLEDMillis = 0;
const unsigned long toneInterval = 200;
const unsigned long ledInterval = 150;

void setup() {
  Serial.begin(9600);
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousToneMillis >= toneInterval) {
    previousToneMillis = currentMillis;
    doPoliceTone();
  }

  if (currentMillis - previousLEDMillis >= ledInterval) {
    previousLEDMillis = currentMillis;
    checkLED();
  }
}

void checkLED() {
  if (lastLED == redLED) {
    tickLED(blueLED);
  } else {
    tickLED(redLED);
  }
}

void tickLED(int led) {
  if (doubleTick) {
    lastLED = led;
    doubleTick = false;
  } else {
    doubleTick = true;
  }
  digitalWrite(led, HIGH);
  delay(50);
  digitalWrite(led, LOW);
}

void doPoliceTone() {
  static bool toggle = false;
  
  if (toggle) {
    tone(SPEAKER_PIN, 800);
  } else {
    tone(SPEAKER_PIN, 600);
  }
  
  toggle = !toggle;
}
