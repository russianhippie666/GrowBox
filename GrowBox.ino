#include "DHT.h"

#define PUMP_PIN 22
#define VEG_LIGHT_PIN 24
#define FLOWER_LIGHT_PIN 26

// Definitions for the DHT11 temp/humidity sensors
#define DHTTYPE DHT11
#define TEMP_H_PIN_VEG 22
#define TEMP_H_PIN_FLOWER 24

#define PH_PIN A2
#define TDS_PIN A3
#define INTERNAL_FAN_PIN 28
#define EXTERNAL_FAN_PIN 30
#define ON 1
#define OFF 0

// These values are the defaults if the device were to reset
int pumpState = OFF;
// TODO: revise default
int pumpRunTimeSec = 15;
// TODO: revise default
int pumpIntervalTimeHour = 12;
int vegLightState = ON;
int vegDaylightHours = 20;
int flowerLightState = ON;
int flowerDaylightHours = 12;
int internalFanState = ON;
int externalFanState = ON;
long pumpStartTime = -1;
long vegLightStartTime = 0;
long flowerLightStartTime = 0;
long currentTime = 0;

// Holds the serial input from the Raspberry Pi
String inputString = "";
boolean stringComplete = false;

// There are the two temp/humidity sensors
DHT tempHumidVeg(TEMP_H_PIN_VEG, DHTTYPE);
DHT tempHumidFlower(TEMP_H_PIN_FLOWER, DHTTYPE);

// Use this is a preventative measure. Pump will be handled in loop
void setPumpOff()
{
  pumpState = OFF;
}

// Turns pump on, and sets start time. Running managed in loop
void runPump()
{
  pumpState = ON;
  pumpStartTime = currentTime;
}

void setPumpRunTime(int in)
{
}

void setPumpInterval(int in)
{
}

void setVegLight(int in)
{
}

void setVegDaylight(int in)
{
}

void setFlowerLight(int in)
{
}

void setFlowerDaylight(int in)
{
}

void setInternalFan(int in)
{
}

void setExternalFan(int in)
{
}

int getPump()
{
  return pumpState;
}

int getVegLight()
{
  return vegLightState;
}

long getVegLightDuration()
{
  return vegDaylightHours;
}

int getFlowerLight()
{
  return flowerLightState;
}

int getFlowerLightDuration()
{
  return flowerDaylightHours;
}

int getExternalFan()
{
  return externalFanState;
}

int getInternalFan()
{
  return internalFanState;
}

float getTemp()
{
  float temp = tempHumidVeg.readTemperature(true);
  if(isnan(temp))
  {
    return -1;
  }
  else
  {
    return temp;
  }
}

float getTemp(int sensor)
{
  return 0.0;
}

float getHumidity()
{
  return tempHumidVeg.readHumidity();
}

float getHumidity(int sensor)
{
  return 0.0;
}

long getPh()
{
  return 0.0;
}

long getTds()
{
  return 0.0;
}

// Sets up the values needed for Serial and timing
void setup()
{
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  // Start the temp/humidity sensors
  tempHumidVeg.begin();
  tempHumidFlower.begin();
}

// Continuously running loop after setup
void loop()
{
  if(stringComplete)
  {
    // Print the string back
    // TODO: parse string into a command
    handleInput(inputString);
    // Clear the string and mark as not received
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent()
{
  while(Serial.available())
  {
    // Read the top of the queue
    char input = (char)Serial.read();
    // Append read char to the string
    inputString += input;
    // If last char was a newline, the input is done
    if(input == '\n')
    {
      stringComplete = true;
    }
  }
}

// Determines what command to execute
void handleInput(String input)
{
  // Declare result variables outside of switch
  int resultInt;
  float resultFloat;
  int i = 0;
  String command = "";
  String args = "";
  
  // Pull command from first 3 chars (limit to 1000 commands)
  do 
  {
    // Command will be in the first 3 characters
    if(i < 3)
    {
      command += input[i];
    }
    // If past 3 characters, update the arguments. Will end up null terminated
    else
    {
      args += input[i];
    }
    i++;
  }
  // Do this until the string input is terminated
  while(input[i - 1] != '\n');
  
  // Terminate the command in case it hasn't been
  command += '\n';
  
  switch (command.toInt())
  {
    case 0:
      resultFloat = getTemp();
      if(resultFloat > 0)
      {
        Serial.println("Temperature: "); 
        Serial.println(resultFloat);
      }
      else
      {
        Serial.println("Getting temperature failed!"); 
      }
      break;
    case 1:
      Serial.println(1);
      break;
    case 2:
      Serial.println(1);
      break;
    case 3:
      Serial.println(1);
      break;
    case 4:
      Serial.println(1);
      break;
    case 5:
      Serial.println(1);
      break;
    case 6:
      Serial.println(1);
      break;
    case 7:
      Serial.println(1);
      break;
    case 8:
      Serial.println(1);
      break;
    case 9:
      Serial.println(1);
      break;
    case 10:
      Serial.println(1);
      break;
    case 11:
      Serial.println(1);
      break;
    case 12:
      Serial.println(1);
      break;
    case 13:
      Serial.println(1);
      break;
    case 14:
      Serial.println(1);
      break;
    case 15:
      Serial.println(1);
      break;
    case 16:
      Serial.println(1);
      break;
    case 17:
      Serial.println(1);
      break;
    case 18:
      Serial.println(1);
      break;
    case 19:
      Serial.println(1);
      break;
    case 20:
      Serial.println(1);
      break;
    case 21:
      Serial.println(1);
      break;
    default:
      Serial.println("Not a valid input");
      break;
  }
}
