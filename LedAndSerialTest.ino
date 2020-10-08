void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN_LED1, OUTPUT);
 
}
 
void loop() {
  // put your main code here, to run repeatedly: 
  digitalWrite(PIN_LED1, LOW);
  delay(100);
  digitalWrite(PIN_LED1, HIGH);
  delay(100);  
  Serial.println("hello");
   
}