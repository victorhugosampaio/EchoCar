enum prediction {
    PREDICTION_BACKWARD,
    PREDICTION_FIVE,
    PREDICTION_FORWARD,
    PREDICTION_FOUR,
    PREDICTION_GO,
    PREDICTION_LEFT,
    PREDICTION_NOISE,
    PREDICTION_ONE,
    PREDICTION_RIGHT,
    PREDICTION_STOP,
    PREDICTION_THREE,
    PREDICTION_TWO,

    PREDICTION_QUANTITY,
};

const unsigned char chars[PREDICTION_QUANTITY] = {
    [PREDICTION_BACKWARD] = 'a',
    [PREDICTION_FIVE] = 'b',
    [PREDICTION_FORWARD] = 'c',
    [PREDICTION_FOUR] = 'd',
    [PREDICTION_GO] = 'e',
    [PREDICTION_LEFT] = 'f',
    [PREDICTION_NOISE] = 'g',
    [PREDICTION_ONE] = 'h',
    [PREDICTION_RIGHT] = 'i',
    [PREDICTION_STOP] = 'j',
    [PREDICTION_THREE] = 'k',
    [PREDICTION_TWO] = 'l',
  };

unsigned long previousMillis = 0;
const long interval = 3000; // 3 segundos

void setup() {
    Serial.begin(9600);
    Serial1.begin(115200);
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        static int index = 0;
        Serial.println(chars[index]); // Print no Serial normal
        Serial1.write(chars[index]); // Envio via Serial1

        index++;
        if (index >= 12) {
            index = 0;
        }
    }

    delay(100); // Necessário para a UART
}
