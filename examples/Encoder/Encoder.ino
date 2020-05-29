
#include <ESP32Encoder.h>

ESP32Encoder encoder;
ESP32Encoder encoder2;

// timer and flag for example, not needed for encoders
unsigned long encoder2lastToggled;
bool encoder2Paused = false;

void setup(){
	
	Serial.begin(115200);
	// Enable the weak pull down resistors

	ESP32Encoder::useInternalWeakPullResistors=DOWN;
	// Enable the weak pull up resistors
	ESP32Encoder::useInternalWeakPullResistors=UP;
	// set starting count value

	// Attache pins for use as encoder pins
	encoder.attachHalfQuad(12, 13);
	// Attache pins for use as encoder pins
	encoder2.attachHalfQuad(2, 15);
		
	// set starting count value after attaching
	encoder.setCount(37);

	// clear the encoder's raw count and set the tracked count to zero
	encoder2.clearCount();
	Serial.println("Encoder Start = "+String((int32_t)encoder.getCount()));
	// set the lastToggle
	encoder2lastToggled = millis();
}

void loop(){
	// Loop and read the count
	Serial.println("Encoder count = "+String((int32_t)encoder.getCount())+" "+String((int32_t)encoder2.getCount()));
	delay(100);

	// every 5 seconds toggle encoder 2
	if (millis() - encoder2lastToggled >= 5000) {
		if(encoder2Paused) {
			Serial.println("Resuming Encoder 2");
			encoder2.resumeCount();
		} else {
			Serial.println("Paused Encoder 2");
			encoder2.pauseCount();
		}

		encoder2Paused = !encoder2Paused;
		encoder2lastToggled = millis();
	}
}

