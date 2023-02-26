
#include "arduinoFFT.h"

#define SAMPLES 1024                 
#define sampling_frequency 1000      
#define sampling_period 1000         
#define E1 82.41
#define A 110
#define D 146.83
#define G 196
#define B 246.94
#define E2 329.63

arduinoFFT FFT = arduinoFFT();

unsigned long microseconds;
double vReal[SAMPLES];
double vImag[SAMPLES];
int i = 0;
int sensor = A0;
int button = 5;

int blue = 2;
int green = 3; 
int red = 4;

int buttonState = LOW;
int ledState = LOW;
int led = 7;
int waitDebounce = 50;
unsigned long lastTimeDebounce = 0;
int lastReading = LOW;

double peak = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(sensor, INPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  digitalWrite(led, ledState);
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);
}

void loop()
{
  int reading = digitalRead(button);
  if(reading != lastReading)
  {
    lastTimeDebounce = millis();
  }

  if((millis() - lastTimeDebounce) > waitDebounce)
  {
    if(reading != buttonState and reading == HIGH)
    {
      ledState = !ledState;
      digitalWrite(led, ledState);
    }
    buttonState = reading;
  }

  lastReading = reading;
  
   
  /*SAMPLING*/

  if(ledState == HIGH)
  {
    for(i=0; i<SAMPLES; i++)
    {
      microseconds = micros();           // this overflows around 70 minutes

      vReal[i] = analogRead(sensor);
      vImag[i] = 0;
  
      while(micros() < (microseconds + sampling_period))
      {
      }
    }
  
    /*FFT*/

    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    peak = FFT.MajorPeak(vReal, SAMPLES, sampling_frequency);

    /*PRINT RESULTS*/
  
    Serial.println(peak);                 //print the most dominant frequency (fundamental)
  }

  if(peak<E1-1 and peak>E1-5)
  {
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
  }

  else if(peak>E1-0.5 and peak<E1+0.5)
  {
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
  } 

  else if(peak>E1 + 1 and peak < E1 + 5)
  {
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
  }
  
  else if(peak<A-1 and peak>A-5)
  {
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
  }

  else if(peak>A-0.5 and peak<A+0.5)
  {
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
  } 

  else if(peak>A + 1 and peak < A + 5)
  {
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
  }
    
  else if(peak<D-1 and peak>D-5)
  {
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
  }

  else if(peak>D-0.5 and peak<D+0.5)
  {
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
  } 

  else if(peak>D + 1 and peak < D + 5)
  {
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
  }
    
  else if(peak<G-1 and peak>G-5)
  {
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
  }

  else if(peak>G-0.5 and peak<G+0.5)
  {
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
  } 

  else if(peak>G + 1 and peak < G + 5)
  {
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
  }
    
  else if(peak<B-1 and peak>B-5)
  {
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
  }

  else if(peak>B-0.5 and peak<B+0.5)
  {
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
  } 

  else if(peak>B + 1 and peak < B + 5)
  {
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
  }
    
  else if(peak<E2-1 and peak>E2-5)
  {
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
  }

  else if(peak>E2-0.5 and peak<E2+0.5)
  {
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
  } 

  else if(peak>E2 + 1 and peak < E2 + 5)
  {
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
  }
   
  /*for(i=0; i<(SAMPLES/2); i++)
  {
    Serial.println(vReal[i], 1);
  }*/
  
  delay(1000);                          //repeat the process every second
  
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);

  
  //while(1);                             //run code once
  
}
