#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

#define DEBUG_SW 1

// Pins of Fan Regulator Knob
#define s1  15
#define s2  2

//pins for Switches
#define S5 4
#define S6 5
#define S7 18
#define S8 19

// Pins of Relay (Appliances Control)
#define R5 13
#define R6 12
#define R7 14
#define R8 27

// Pins of Relay (Fan Speed Control)
#define Speed1 26
#define Speed2 25
#define Speed3 33
#define Speed4 32

//Led indication
#define Speed1_LED 21
#define Speed2_LED 22
#define Speed3_LED 23
#define Speed4_LED 35
#define WiFi_LED 34

int speed_flag = 0;
int switch_ON_Flag1_previous_I = 0;
int switch_ON_Flag2_previous_I = 0;
int switch_ON_Flag3_previous_I = 0;
int switch_ON_Flag4_previous_I = 0;
int MODE = 0;

char auth[] = " PfFX0RHa5UX4AHYqi-jH8z51TRRaLmz_";

char ssid[] = "#VEER";
char pass[] = "12345678";

BLYNK_WRITE(V0)
{
  int fan_speed = param.asInt(); // assigning incoming value from pin V1 to a variable
  if (fan_speed == 0)
  {
    speed0();
  }
  if (fan_speed == 1)
  {
    speed1();
  }
  if (fan_speed == 2)
  {
    speed2();
  }
  if (fan_speed == 3)
  {
    speed3();
  }
  if (fan_speed == 4)
  {
    speed4();
  }
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  digitalWrite(R5, pinValue);
  // process received value
}

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V2 to a variable
  digitalWrite(R6, pinValue);
  // process received value
}

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V3 to a variable
  digitalWrite(R7, pinValue);
  // process received value
}

BLYNK_WRITE(V4)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V4 to a variable
  digitalWrite(R8, pinValue);
  // process received value
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
 
  pinMode(S5, INPUT);
  pinMode(S6, INPUT);
  pinMode(S7, INPUT);
  pinMode(S8, INPUT);

  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);
  
  pinMode(Speed1, OUTPUT);
  pinMode(Speed2, OUTPUT);
  pinMode(Speed3, OUTPUT);
  pinMode(Speed4, OUTPUT);

  pinMode(Speed1_LED, OUTPUT);
  pinMode(Speed2_LED, OUTPUT);
  pinMode(Speed3_LED, OUTPUT);
  pinMode(Speed4_LED, OUTPUT);
  pinMode(WiFi_LED, OUTPUT);


  Serial.begin(9600);
  WiFi.begin(ssid, pass);

  timer.setInterval(3000L, checkBlynk); // check if connected to Blynk server every 3 seconds

  Blynk.config(auth);//, ssid, pass);
}


void loop()
{

  if (WiFi.status() != WL_CONNECTED)
  {
    if (DEBUG_SW) Serial.println("Not Connected");
    }
  else
  {
    if (DEBUG_SW) Serial.println(" Connected");
    Blynk.run();
  }


  timer.run(); // Initiates SimpleTimer

  if (MODE == 0)
  {
  digitalWrite(WiFi_LED,HIGH);
    with_internet();
  }
  else
  {
  digitalWrite(WiFi_LED,LOW);
    without_internet();
  // put your main code here, to run repeatedly:
}
}

void checkBlynk()
{
  bool isconnected = Blynk.connected();
  if (isconnected == false)
  {
    MODE = 1;
  }
  if (isconnected == true)
  {
    MODE = 0;
  }
}

void speed0()
{
  //All Relays Off - Fan at speed 0
  if (DEBUG_SW)Serial.println("SPEED 0");
  digitalWrite(Speed1, HIGH);
  digitalWrite(Speed2, HIGH);
  digitalWrite(Speed3, HIGH);
  digitalWrite(Speed4, HIGH);
digitalWrite(Speed1_LED, LOW);
digitalWrite(Speed2_LED, LOW);
digitalWrite(Speed3_LED, LOW);
digitalWrite(Speed4_LED, LOW);
  }

void speed1()
{
  //Speed1 Relay On - Fan at speed 1
  if (DEBUG_SW)Serial.println("SPEED 1");
  digitalWrite(Speed1, HIGH);
  digitalWrite(Speed2, HIGH);
  digitalWrite(Speed4, HIGH);
  digitalWrite(Speed3, HIGH);
  digitalWrite(Speed1_LED, HIGH);
digitalWrite(Speed2_LED, LOW);
digitalWrite(Speed3_LED, LOW);
digitalWrite(Speed4_LED, LOW);
  delay(1000);
  digitalWrite(Speed1, LOW);
}

void speed2()
{
  //Speed2 Relay On - Fan at speed 2
  if (DEBUG_SW)Serial.println("SPEED 2");
  digitalWrite(Speed1, HIGH);
  digitalWrite(Speed2, HIGH);
  digitalWrite(Speed4, HIGH);
  digitalWrite(Speed3, HIGH);
  digitalWrite(Speed1_LED, LOW);
digitalWrite(Speed2_LED, HIGH);
digitalWrite(Speed3_LED, LOW);
digitalWrite(Speed4_LED, LOW);
  delay(1000);
  digitalWrite(Speed2, LOW);

}

void speed3()
{
  //Speed1 & Speed2 Relays On - Fan at speed 3
  if (DEBUG_SW)Serial.println("SPEED 3");
  digitalWrite(Speed1, HIGH);
  digitalWrite(Speed2, HIGH);
  digitalWrite(Speed4, HIGH);
  digitalWrite(Speed3, HIGH);
  digitalWrite(Speed1_LED, LOW);
digitalWrite(Speed2_LED, LOW);
digitalWrite(Speed3_LED, HIGH);
digitalWrite(Speed4_LED, LOW);
  delay(1000);
  digitalWrite(Speed3, LOW);

}

void speed4()
{
  //Speed4 Relay On - Fan at speed 4
  if (DEBUG_SW)Serial.println("SPEED 4");
  digitalWrite(Speed1, HIGH);
  digitalWrite(Speed2, HIGH);
  digitalWrite(Speed4, HIGH);
  digitalWrite(Speed3, HIGH);
  digitalWrite(Speed1_LED, LOW);
digitalWrite(Speed2_LED, LOW);
digitalWrite(Speed3_LED, LOW);
digitalWrite(Speed4_LED, HIGH);
  delay(1000);
  digitalWrite(Speed4, LOW);

}

void without_internet()
{
   if ((digitalRead(s1)==1)&&(speed_flag<=4))
{ 
  speed_flag++;
}
if ((digitalRead(s2)==1)&&(speed_flag>=0))
{
  speed_flag--;
}
  // FOR FAN
  if (speed_flag == 1)
  {
    speed1();
  }
  if (speed_flag == 2)
  {
    speed2();
  }
  if (speed_flag == 3)
  {
    speed3();
  }
  if (speed_flag == 4)
  {
    speed4();
  }
  if (speed_flag == 0)
  {
    speed0();
  }


  // FOR SWITCH
  digitalWrite(R5, !digitalRead(S5));
  digitalWrite(R6, !digitalRead(S6));
  digitalWrite(R7, !digitalRead(S7));
  digitalWrite(R8, !digitalRead(S8));
}

void with_internet()
  {
     if ((digitalRead(s1)==1)&&(speed_flag<=4))
{ 
  speed_flag++;
}
if ((digitalRead(s2)==1)&&(speed_flag>=0))
{
  speed_flag--;
}
  // FOR FAN
  if (speed_flag == 1)
  {
    speed1();
    Blynk.virtualWrite(V0, 1);
   }
  if (speed_flag == 2)
  {
    speed2();
    Blynk.virtualWrite(V0, 2);
   }
  if (speed_flag== 3)
  {
    speed3();
    Blynk.virtualWrite(V0, 3);
  }
  if (speed_flag == 4)
  {
    speed4();
    Blynk.virtualWrite(V0, 4);
   }
  if (speed_flag == 0)
  {
    speed0();
    Blynk.virtualWrite(V0, 0);
  }


  // FOR SWITCH
  if (digitalRead(S5) == LOW)
  {
    if (switch_ON_Flag1_previous_I == 0 )
    {
      digitalWrite(R5, HIGH);
      if (DEBUG_SW) Serial.println("Relay1- ON");
      Blynk.virtualWrite(V1, 1);
      switch_ON_Flag1_previous_I = 1;
    }
    if (DEBUG_SW) Serial.println("Switch1 -ON");

  }
  if (digitalRead(S5) == HIGH )
  {
    if (switch_ON_Flag1_previous_I == 1)
    {
      digitalWrite(R5, LOW);
      if (DEBUG_SW) Serial.println("Relay1 OFF");
      Blynk.virtualWrite(V1, 0);
      switch_ON_Flag1_previous_I = 0;
    }
    if (DEBUG_SW)Serial.println("Switch1 OFF");
  }


  if (digitalRead(S6) == LOW)
  {
    if (switch_ON_Flag2_previous_I == 0 )
    {
      digitalWrite(R6, HIGH);
      if (DEBUG_SW)  Serial.println("Relay2- ON");
      Blynk.virtualWrite(V2, 1);
      switch_ON_Flag2_previous_I = 1;
    }
    if (DEBUG_SW) Serial.println("Switch2 -ON");

  }
  if (digitalRead(S6) == HIGH )
  {
    if (switch_ON_Flag2_previous_I == 1)
    {
      digitalWrite(R6, LOW);
      if (DEBUG_SW) Serial.println("Relay2 OFF");
      Blynk.virtualWrite(V2, 0);
      switch_ON_Flag2_previous_I = 0;
    }
    if (DEBUG_SW)Serial.println("Switch2 OFF");
    //delay(200);
  }

  if (digitalRead(S7) == LOW)
  {
    if (switch_ON_Flag3_previous_I == 0 )
    {
      digitalWrite(R7, HIGH);
      if (DEBUG_SW) Serial.println("Relay3- ON");
      Blynk.virtualWrite(V3, 1);
      switch_ON_Flag3_previous_I = 1;
    }
    if (DEBUG_SW) Serial.println("Switch3 -ON");

  }
  if (digitalRead(S7) == HIGH )
  {
    if (switch_ON_Flag3_previous_I == 1)
    {
      digitalWrite(R7, LOW);
      if (DEBUG_SW) Serial.println("Relay3 OFF");
      Blynk.virtualWrite(V3, 0);
      switch_ON_Flag3_previous_I = 0;
    }
    if (DEBUG_SW)Serial.println("Switch3 OFF");
    //delay(200);
  }

  if (digitalRead(S8) == LOW)
  {
    if (switch_ON_Flag4_previous_I == 0 )
    {
      digitalWrite(R8, HIGH);
      if (DEBUG_SW) Serial.println("Relay4- ON");
      Blynk.virtualWrite(V4, 1);
      switch_ON_Flag4_previous_I = 1;
    }
    if (DEBUG_SW) Serial.println("Switch4 -ON");

  }
  if (digitalRead(S8) == HIGH )
  {
    if (switch_ON_Flag4_previous_I == 1)
    {
      digitalWrite(R8, LOW);
      if (DEBUG_SW) Serial.println("Relay4 OFF");
      Blynk.virtualWrite(V4, 0);
      switch_ON_Flag4_previous_I = 0;
    }
    if (DEBUG_SW) Serial.println("Switch4 OFF");
    //delay(200);
  }


}
