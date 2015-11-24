void setup()
{                
  Serial.begin(38400);
}

int val;

void loop()                     
{
  val = analogRead(17);
  Serial.print("analog 0 is: ");
  Serial.println(val);
  delay(250);
}

