const int relayPin = 2;
const int sensorPin = 3;
const int debugPin = 4;

const unsigned long defaultOnLength = 1000L * 60L * 5L;
const unsigned long debugOnLength = 1000 * 20;
unsigned long onLength = defaultOnLength;

unsigned long lastSensorTrigger = 0;

bool lightOn = false;

void blink(int speed) {
	digitalWrite(LED_BUILTIN, HIGH); 
	delay(speed);
	digitalWrite(LED_BUILTIN, LOW);
	delay(speed);    
}

void setup() {
	pinMode(relayPin, OUTPUT);
	pinMode(sensorPin, INPUT);
	pinMode(debugPin, INPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	blink(2000);
}

void setLightOn() {
	lastSensorTrigger = millis();
	digitalWrite(relayPin, HIGH);
	lightOn = true;
}

void setLightOff() {
	digitalWrite(relayPin, LOW);
	lightOn = false;
}

void loop() {
	if (digitalRead(debugPin) == HIGH) {
		onLength = debugOnLength;
	} else {
		onLength = defaultOnLength;
	}

	if (digitalRead(sensorPin) == HIGH) {
		setLightOn();
		blink(2000);
	}

	if (lightOn && millis() - lastSensorTrigger > onLength) {
		setLightOff();
	}
}
