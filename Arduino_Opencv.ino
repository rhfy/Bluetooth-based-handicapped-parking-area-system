int speakerpin = 12; // buzzer pin number
int led = 13; // led pin number

void setup() {

  Serial.begin(9600);
  pinMode(led, OUTPUT); // led output mode

}

void loop() {
  if(Serial.available()){ // receive serial
   if(Serial.read() == '1'){ // receive serial '1'
    digitalWrite(led, HIGH); // led on
    tone(speakerpin, 500, 1000); // buzzer do
    }
    else
    {
         digitalWrite(led, LOW); // led off
    }
   }
}
