
#include <Servo.h> // include Servo library 
#include<LiquidCrystal.h>
#define VOLT A5

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// 180 horizontal MAX
Servo horizontal; // horizontal servo
int servoh = 180;   // 90;     // stand horizontal servo

int servohLimitHigh = 180;
int servohLimitLow = 65;

// 65 degrees MAX
Servo vertical;   // vertical servo 
int servov = 45;    //   90;     // stand vertical servo

int x=0; // Wiper Timer

int servovLimitHigh = 80;
int servovLimitLow = 15;

Servo wiper;
int servow=0; // Wiper Servo

// LDR pin connections
//  name  = analogpin;
int ldrlt = 2; //LDR down left - BOTTOM LEFT    <--- BDG
int ldrrt = 3; //LDR down rigt - BOTTOM RIGHT 
int ldrld = 0; //LDR top left - TOP LEFT
int ldrrd = 1; //ldr top rigt - TOP RIGHT

int temp1;
float volts;

void setup()
{
  Serial.begin(9600);
// servo connections
// name.attacht(pin);
  // Attach two 4.7k's in parallel. Use Voltage Divider Circuit.
  pinMode(8, OUTPUT);  
  analogWrite(8, 25);
  lcd.begin(16, 2); 
  horizontal.attach(6); 
  vertical.attach(7);
  //wiper.attach(8); 
  horizontal.write(180);
  delay(1000);
  vertical.write(45);
  delay(1000);
  wiper.write(180);
}

void loop() 
{
  int lt = analogRead(ldrlt); // down left
  int rt = analogRead(ldrrt); // down right
  int ld = analogRead(ldrld); // top left
  int rd = analogRead(ldrrd); // top rigt
  
  // int dtime = analogRead(4)/20; // read potentiometers  
  // int tol = analogRead(5)/4;
  int dtime = 10;
  int tol = 50;
  
  int avt = (lt + rt) / 2; // average value top
  int avd = (ld + rd) / 2; // average value down
  int avl = (lt + ld) / 2; // average value left
  int avr = (rt + rd) / 2; // average value right

  int dvert = avt - avd; // check the diffirence of up and down
  int dhoriz = avl - avr;// check the diffirence og left and rigt
  
//  Serial,print(lt);
  Serial.print(avt);
  Serial.print(" ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print(avr);
  Serial.print("   ");
  Serial.print(dtime);
  Serial.print("   ");
  Serial.print(tol);
  Serial.println(" ");

 voltmeasure();

 

   
  if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle
  {
  if (avt > avd)
  {
    servov = ++servov;
     if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
  }
  else if (avt < avd)
  {
    servov= --servov;
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
  }
  vertical.write(servov);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
  {
  if (avl > avr)
  {
    servoh = --servoh;
    if (servoh < servohLimitLow)
    {
    servoh = servohLimitLow;
    }
  }
  else if (avl < avr)
  {
    servoh = ++servoh;
     if (servoh > servohLimitHigh)
     {
     servoh = servohLimitHigh;
     }
  }
  else if (avl = avr)
  {
    // nothing
  }
  horizontal.write(servoh);
  }

   
  
   delay(dtime);
   
   x+=dtime;
   
   if(x==10000)
   {
    x = wiperfunc();
   }
}

int wiperfunc()
{
  servow = 180;
  horizontal.write(120);
  vertical.write(45);
  wiper.write(180);
  // voltmeasure();      
  int i;
       
  for(i=0;i<=180;i++)
  {
   servow= --servow;
   wiper.write(servow);
   delay(100);
   }
       
   for(i=180;i>=0;i--)
   {
   servow = ++servow;
   wiper.write(servow);
   delay(100);
   }
   return 0;
   }

int voltmeasure()
{
  lcd.setCursor(0,1);
  temp1=analogRead(VOLT);
  volts= (temp1/511.5)*5;
  lcd.print("Voltage: ");
  lcd.print(volts);
  return 0;
}





