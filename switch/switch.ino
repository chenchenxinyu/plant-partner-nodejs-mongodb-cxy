

int switchA0 = 2;//D1
int switchA1 = 3;//D2
int switchA2 = 4;//D3
void setup(void)
{
  pinMode(switchA0, OUTPUT);
  pinMode(switchA1, OUTPUT);
  pinMode(switchA2, OUTPUT);
}
void loop()
{
  digitalWrite(switchA0, HIGH);
  digitalWrite(switchA1, HIGH);
  digitalWrite(switchA2, HIGH);
  delay(2000);
  digitalWrite(switchA0, LOW);
  digitalWrite(switchA1, LOW);
  digitalWrite(switchA2, HIGH);
  delay(2000);
}
