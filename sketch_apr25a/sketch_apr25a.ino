#include <Interp.h>




void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  int v;
  int i;
  for (i = 0; i < 500; i) {
    v = Interp::LERP(0, 2766, 500, i++);
    Serial.print(i); Serial.print(", "); Serial.println(v);
  }
  
}
