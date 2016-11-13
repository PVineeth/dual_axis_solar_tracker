/* Dual Axis Motion Tracker Project
Code By Vineeth Penugonda
Email: 201401002@daiict.ac.in*/

#include<Servo.h>

//Horizontal Servo
Servo horizontal;
int servoh = 180;

int servohLimitRight = 180; //180 horizontal MAX
int servohLimitLeft = 65; //65 horizontal MIN

//Vertical Servo
Servo vertical;
int servov = 45; 

int servovLimitRight = 80; //80 vertical MAX
int servovLimitLeft = 15;  //15 vertical MIN

//LDR Analog pin connections
int ldr_top_right = 1;
int ldr_top_left = 0;
int ldr_down_right = 3;
int ldr_down_left = 2;

void setup() {
  Serial.begin(9600); //9600 bauds=9600 bits per second
  Serial.print("**** Dual Solar Tracker Project ****");
  Serial.print(" ");
  Serial.print("Initializing...");
  horizontal.attach(9);
  vertical.attach(10);
  horizontal.write(180); //Inital angle at which horizontal servo should be
  vertical.write(45); //Inital angle at which vertical servo should be
  delay(3000);
}

void loop() {
  //Read Values from the LDR's
  int lt = analogRead(ldr_top_left);
  int rt = analogRead(ldr_top_right);
  int ld = analogRead(ldr_down_left);
  int rd = analogRead(ldr_down_right);

  int delay_time = 10; //10 milliseconds
  int tolerance = 50;

  int avg_top = (ldr_top_left + ldr_top_right) / 2; //average value top
  int avg_down = (ldr_down_left + ldr_down_right) / 2; //average value down
  int avg_left = (ldr_down_left + ldr_top_left) / 2; //average value left
  int avg_right = (ldr_down_right + ldr_top_right) / 2; //average value right

  int diff_v = avg_top - avg_down; //Difference between top and down average values
  int diff_h = avg_left - avg_right; //Difference between left and right average values

  Serial.print(" ");
  Serial.print("Average Value Top: ");
  Serial.print(avg_top);
  Serial.print(" ");
  Serial.print("Average Value Down: ");
  Serial.print(avg_down);
  Serial.print(" ");
  Serial.print("Average Value Left: ");
  Serial.print(avg_left);
  Serial.print(" ");
  Serial.print("Average Value Right: ");
  Serial.print(avg_right);
  Serial.print("   ");

  // Set vertical servo into position
  // diff_v can be both positive or negative. It depends on average top and average down values.
  if(-1*tolerance > diff_v || diff_v > tolerance) 
  {
    if(avg_top > avg_down)
    {
      servov= ++servov; //Increase by 1 degree
      if(servov > servovLimitRight)
      {
        servov = servovLimitRight;
      }
    } 
    else if(avg_top < avg_down)
    {
      servov= --servov;
    if (servov < servovLimitLeft)
  {
    servov = servovLimitLeft;
  }
    }
    vertical.write(servov);
  }

  // diff_h can be both positive or negative. It depends on average left and average right values.
  if(-1*tolerance > diff_h || diff_h > tolerance)
  {
    if(avg_left > avg_right)
    {
      servoh= --servoh; // Decrease by 1 degree
      if(servoh < servovLimitLeft)
      {
        servoh = servovLimitLeft;
      }
    } else if(avg_left < avg_right)
    {
      servoh= ++servoh; //Increase by 1 degree
      if(servoh > servohLimitRight)
      {
        servoh = servovLimitRight;
      }
    }
  else if(avg_left = avg_right)
  {
    // Do Nothing
  }
  horizontal.write(servoh);
}
  delay(delay_time);
}
