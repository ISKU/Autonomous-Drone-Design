#include <Servo.h>
#include <PID_v1.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

const int TrigPin = 6;
const int EchoPin = 7;
const int ModeSwitch = 8;
const int Led1 = A4;
const int MuxSwitch = A5;

//Define Variables we'll be connecting to
double Setpoint, Input, Output, Input_temp;
double mode_switch_val;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, 2, 5, 1, DIRECT);


int command_array[5] = {1500, 1500, 1500, 1500, 1500};   // a string to hold incoming data
unsigned char command_cnt = 0;         // a string to hold incoming data
unsigned char auto_thro_first_flg = 1;         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup()
{
  Serial.begin(9600);

  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  pinMode(ModeSwitch, INPUT);
  pinMode(Led1, OUTPUT);
  pinMode(MuxSwitch, OUTPUT);
  digitalWrite(MuxSwitch, HIGH);  //rc controller
  digitalWrite(Led1, HIGH);
  myservo1.attach(2);
  myservo2.attach(3);
  myservo3.attach(4);
  myservo4.attach(5);

  myservo1.writeMicroseconds(Output);
  myservo2.writeMicroseconds(1500);
  myservo3.writeMicroseconds(1500);
  myservo4.writeMicroseconds(1500);

  //initialize the variables we're linked to
  Setpoint = 50.0;
  myPID.SetOutputLimits(1000, 2000);
  myPID.SetMode(AUTOMATIC);
  digitalWrite(Led1, LOW);
}
void loop()
{
  mode_switch_val = pulseIn(ModeSwitch, HIGH);

  if (mode_switch_val > 1200)
  {
    digitalWrite(MuxSwitch, LOW);
    digitalWrite(Led1, HIGH);
    if (auto_thro_first_flg == 1)
    {
      Setpoint = 30.0;
      Input = 30.0; // 5.0
      Output = 1500; // 1000
      myPID.SetMode(AUTOMATIC);
      auto_thro_first_flg = 0;
    }

    digitalWrite(TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);
    Input_temp = pulseIn(EchoPin, HIGH) / 58.0;
    if (Input_temp < 500 && Input_temp > 1)
    {
      Input = Input_temp;
    }
    myPID.Compute();
    myservo1.writeMicroseconds(Output);
    myservo2.writeMicroseconds(command_array[1]);
    myservo3.writeMicroseconds(command_array[2]);
    myservo4.writeMicroseconds(command_array[3]);

      Serial.print(command_array[0]);
     Serial.print(" | ");
     Serial.print(command_array[1]);
      Serial.print(" | ");
     Serial.print(command_array[2]);
      Serial.print(" | ");
      Serial.print(command_array[3]);
      Serial.println();
    //Serial.print(Input);
    //Serial.print(" | ");
    //Serial.print(Output);
    //Serial.println();
    delay(100);
  }
  else
  {
    auto_thro_first_flg = 1;
    digitalWrite(MuxSwitch, HIGH);
    digitalWrite(Led1, LOW);
    Input = 60.0;
    myPID.SetMode(0);

    // myPID.Compute();
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    int inChar = (unsigned char)Serial.read();
    // add it to the inputString:
    if (inChar == 0x00)
    {
      command_cnt = 0;
    }
    else
    {
      command_array[command_cnt++] = 980 + (inChar * 4);
    }
  }
}

