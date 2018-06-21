#include <CurieBLE.h>
#include <Servo.h>

#define trigPin1 12
#define echoPin1 13
#define trigPin2 10
#define echoPin2 11

Servo myservo;

int counter;
int flag;

void setup() {    //init BLE and Serial and servo and distance sensor
  Serial.begin(115200);
  counter=0;
  flag=0;
  // initialize the BLE hardware
  BLE.begin();

  //Serial.println("BLE Central scan");
  myservo.attach(6);
  myservo.write(75);
  // start scanning for peripheral
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);
  BLE.scan();
}

void loop() {
  // check if a peripheral has been discovered
  BLE.scan();//ble scan
  delay(100);
  BLEDevice peripheral = BLE.available();//found ble

  if (peripheral) {   //Scan success
      // discovered a peripheral
      String address = peripheral.address();
      
    //check RSSI and print address used serial port
    int rssi = peripheral.rssi();
    if(abs(rssi)<90){
      Serial.print(address);
      delay(300);
    }
  }
  if(Serial.available()){//if serial read
    if(Serial.read() == '1'){//exist mac address
        counter = 70;//if can`t scan matching mac address 
    }
    if(Serial.read() == '0'){//not exist mac address
      if(counter < 0)
      {
        counter = 0 ;
      }
      else{
        counter--;
      }
    }   
    if(counter > 0) // exist mac address car
    {
      if(flag == 0){
        myservo.write(0); // block open
        flag = 1;
      }
      if(distanceCheck1() <= 10) // parking state 1 car parking
      {
        Serial.print("kkkkkkkkkkkkkk111"); // send message
          //parkingCheck1
      }
      else // parking state 1 car isn't parking
      {
        Serial.print("kkkkkkkkkkkkkk110"); // send message
      }
      if(distanceCheck2() <= 10) // parking state 2 car parking
      {
        Serial.print("kkkkkkkkkkkkkk221"); // send message
          //parkingCheck2
      }
      else // parking state 2 car isn't parking
      {
        Serial.print("kkkkkkkkkkkkkk220"); // send message
      }
    }
    else
    {
      if(flag == 1) // can't find exist mac address 
      {
        flag = 0;
        myservo.write(75);   // block close
      }
    }
  }
}

long distanceCheck1()   //check distance parking place 1
{
  long duration;
  long distance;
  digitalWrite(trigPin1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1,LOW);

  duration = pulseIn(echoPin1,HIGH);
  if(duration == 0)
  {
    distance = 0;    
  }
  else
  {
    distance = duration / 58.2;
  }
  return distance;
}

long distanceCheck2()  //check distance parking place 2
{
  long duration;
  long distance;
  digitalWrite(trigPin2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2,LOW);

  duration = pulseIn(echoPin2,HIGH);
  if(duration == 0)
  {
    distance = 0;    
  }
  else
  {
    distance = duration / 58.2;
  }
  return distance;
}
