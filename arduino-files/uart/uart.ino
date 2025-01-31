void setup() {
  Serial.begin(9600); /* Computer Serial. */
  Serial1.begin(115200); /* UART. */
}

enum car_direction {
    STANDBY,
    BREAK,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
};

int currentDirection = STANDBY;
unsigned long previousMillis = 0;
const unsigned long interval = 3000; /* Send each direction every 3 seconds. */

void loop() {
  unsigned long currentMillis = millis();
  Serial1.print(currentDirection); /* Send command via UART. */

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    Serial.print("Send: ");
    Serial.println(currentDirection);

    currentDirection += 1;

    if (currentDirection > RIGHT) {
      currentDirection = STANDBY;
    }
  }

  delay(100); /* UART delay. */
}
