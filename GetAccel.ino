#include <Wire.h>
#include <BMA222.h>
#define RED 3
#define GREEN 4

//#define LED RED_LED

BMA222 mySensor;
int begX = 0;
int begY = 0;
int begZ = 0; 
int x = 0; 
int y = 0;
int z = 0; 
bool move1Hap = false;
bool move2Hap = false;
bool move3Hap = false; 


void setup()
{
  Serial.begin(115200);
  
  mySensor.begin();
  uint8_t chipID = mySensor.chipID();
  Serial.print("chipID: ");
  Serial.println(chipID);

  begX = mySensor.readXData();
  begY = mySensor.readYData();
  begZ = mySensor.readZData();

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);

  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);

//  pinMode(LED, OUTPUT); 
}

bool move1(int x, int y, int z)
{
  if (y<-50 && y>-70 && z>35 && z<70) 
    return true;
  return false;
}

bool move2(int x, int y, int z)
{
  if (x>-30 && x<0 && y<0 && y>-30 && z>20 && z<50)
    return true;
  return false;
}

bool move3(int x, int y, int z)
{
  if (x>-40 && x<-10 && y<-80 && y>-130 && z>5 && z<55)
    return true;
  return false;
}

void correct(){
  digitalWrite(GREEN, HIGH);
  delay(200);
  digitalWrite(GREEN, LOW);
}

void incorrect(){
  digitalWrite(RED, HIGH);
  delay(200);
  digitalWrite(RED, LOW);  
}

void outputData(){
  delay(500);
  int8_t data = mySensor.readXData();
  Serial.print("X: ");
  x = data - begX;
  Serial.print(x);

  data = mySensor.readYData();
  Serial.print(" Y: ");
  y = data - begY;
  Serial.print(y);

  data = mySensor.readZData();
  Serial.print(" Z: ");
  z = data - begZ;
  Serial.println(z);
}


void loop()
{

  outputData();
  while (!move1Hap){
    while (move1(x,y,z))
    {
      correct();
      move1Hap = true;
      Serial.print("move1Hap");
      outputData();
    }
    outputData();
    incorrect();
  }
  
  while (!move2Hap){
    while (move2(x,y,z))
    {
      correct();
      move2Hap = true;
      Serial.print("move2Hap");
      outputData();
    }
    outputData();
    incorrect();
  }
  
  while (!move3Hap){
    while (move3(x,y,z))
    {
      correct();
      move3Hap = true;
      Serial.print("move3Hap");
      outputData();
    }
    outputData();
    incorrect();
  }

  move1Hap = false;
  move2Hap = false;
  move3Hap = false;
}
