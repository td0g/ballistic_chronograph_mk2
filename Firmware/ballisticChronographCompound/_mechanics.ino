
float calcLinearAcceleration(byte g0, byte g1, byte g2){
  /*
 a = (s1 * t2 - t2 * s1 - t1 * s1)/(t2*t1*(0.5*t1-1.5*t2))
   */

   
//a = 2*(s1 / t1 - s2 / t2)/(t1-t2)


  float s0 = 0;
  for (byte i = 0; i < g0; i++){
    s0 += gateSeparation[i];
  }
  float s1 = 0;
  for (byte i = 0; i < g1; i++){
    s1 += gateSeparation[i];
  }
  float s2 = 0;
  for (byte i = 0; i < g2; i++){
    s2 += gateSeparation[i];
  }
  s1 -= s0;
  s2 -= s0;
  s2 /= 1000;
  s1 /= 1000;
  float t1 = testTimes[g1] - testTimes[g0];
  t1 /= 2000000;
  float t2 = testTimes[g2] - testTimes[g0];
  t2 /= 2000000;
  float _x = s1 / t1 - s2 / t2;
  _x *= 2;
  float _y = t1 - t2;
  _x /= _y;
  /*
  float _x = (s1*t2-t1*s2-s1*t1);
  float _y = (0.5 * t1 - 1.5 * t2);
  _y = _y * t2 * t1;
  _x = _x / _y;
  */
  return _x;
}

float calcSpeedMPS(byte g0, byte g1){
  float objectSpeed = 0;
  for (byte i = g0; i < g1; i++){
    objectSpeed += gateSeparation[i];
  }
  objectSpeed *= 2000;
  objectSpeed = objectSpeed / (testTimes[g1] - testTimes[g0]);
  return objectSpeed;
}

float calcSpeedFPS(byte g0, byte g1){
  return calcSpeedMPS(g0, g1) * 3.280;
}
