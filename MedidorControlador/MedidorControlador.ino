bool bProcessando = false;
void setup()
{
  Serial.begin(115200);
}

void loop()
{
  if(!bProcessando){
  digitalWrite(13, !digitalRead(13));
  delay(2000);	
  }
}

void serialEvent(){
  char inChar=(char)Serial.read();
  Serial.println(inChar);
  bProcessando = inChar=='1';
  Serial.println(bProcessando);
}