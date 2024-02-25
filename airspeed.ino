#include "AIRSPEED.h"
AIRSPEED airspeed;
void setup() {
  Serial.begin(9600);
  delay(500);
}

void loop() {
  Serial.println(airspeed.AS());
  delay(100); 
}
