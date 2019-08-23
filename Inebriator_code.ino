#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int ledPin = 13;
int sensorPin = A0;
int value = 0;
const int threshold = 800;
int timesTosend=1;
int count=1;
char phone_no[]="9597094478"; 
void setup()
{
  //Serial.begin(9600);
  lcd.begin(16,2);
  Serial.begin(9600);  //Open Serial connection at baud 9600
  delay(2000);
  Serial.println("AT+CMGF=1"); //set GSM to text mode
  delay(200);
  
}
void loop()
{
  int Value = analogRead(sensorPin);
  value = analogRead(0);
  if(Value > threshold)
  {
    digitalWrite(ledPin, HIGH);
    
  }
  else{
    digitalWrite(ledPin, LOW);
    
  }

  lcd.print("alcohol level:");
  lcd.println(value);
  Serial.println(value,DEC);

   if(Value < threshold)
   {
    count=0;
    lcd.print("alert");
    //Serial.print("alert");
    while(count<timesTosend){
delay(1500);
Serial.print("AT+CMGS=\"");
Serial.print(phone_no);
Serial.println("\"");
while (Serial.read()!='>');
{
Serial.print("Test hello");  //SMS body
delay(500);
Serial.write(0x1A);  // sends ctrl+z end of message
    Serial.write(0x0D);  // Carriage Return in Hex
Serial.write(0x0A);  // Line feed in Hex
//The 0D0A pair of characters is the signal for the end of a line and beginning of another.
delay(5000);
}
count++;
}

   }
   else{
    lcd.print("normal");
    Serial.print("normal");
   }

   delay(1000);
   lcd.clear();
   
}
