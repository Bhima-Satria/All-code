void refresh()
{
  //Output led indikator
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  digitalWrite(led4, LOW);
  digitalWrite(led1, HIGH);
  delay(125);
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(125);
  digitalWrite(led2, LOW);
  digitalWrite(led3, HIGH);
  delay(125);
  digitalWrite(led3, LOW);
  digitalWrite(led4, HIGH);
  delay(125);
}
