#include "AIRSPEED.h"

AIRSPEED::AIRSPEED() {
  address = 0x28;
  k = 1.0;
  initial_PR = 0;
}

byte AIRSPEED::fetchPressure(unsigned int *p_P_dat) {
  byte Press_H, Press_L, _status;
  unsigned int P_dat;

  Wire.beginTransmission(address);
  Wire.endTransmission();
  delay(10);

  Wire.requestFrom((int)address, (int)4);
  Press_H = Wire.read();
  Press_L = Wire.read();
  Wire.endTransmission();

  _status = (Press_H >> 6) & 0x03;
  Press_H = Press_H & 0x3f;

  P_dat = (((unsigned int)Press_H) << 8) | Press_L;
  *p_P_dat = P_dat;

  return _status;
}

float AIRSPEED::AS() {
  byte _status;
  unsigned int P_dat;
  float PR, initial_PRs, Samples, V, AS;

  _status = fetchPressure(&P_dat);

  PR = (float)((P_dat - 819.0) / (15563.0));
  PR = (PR - 0.49060678);
  PR = abs(PR);

  if (initial_PR == 0) {
    for (int x = 0; x < 500; x++) {
      initial_PRs = PR;
      Samples = Samples + initial_PRs;
    }
    initial_PR = Samples / 500.0;
  }

  PR -= initial_PR;

  V = PR * 11256.74644898 * k;
  if (V < 0) {
    V = V * -1;
  } else {
    AS = sqrt(V);
  }

  return AS;
}
