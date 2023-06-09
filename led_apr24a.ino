#include "arduino_secrets.h"
//Greta Galli 2023

#include "thingProperties.h" 

//collegamenti pin PWM
#define green 2
#define red 4
#define blue 3

unsigned long tempo; //variabile per il millis

//Inizializzazione led accesi, quindi colore bianco
int realRed = 0;
int realBlue = 0;
int realGreen = 0;

void setup() {
  Serial.begin(9600);
  
  //Codice di avvio del cloud
  delay(1500); 
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
  //dichiarazione led come output
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  
  //assegnazione alle variabili per primo avvio
  fadeEffect = 1;
  onlyColor = 0;
  
  //inizializzazione millis
  tempo = millis();
}

void loop() {
  ArduinoCloud.update(); //si aggiorna continuamente col cloud
  
  //decide quale effetto fare in base ai valori delle variabili
  if(fadeEffect)
    fade();
  else if(onlyColor)
    color();
  
}

void fade(){
  tempo = millis();
  int aspetta = 5;
  for (int i = 255; i >= 0; i --){
    analogWrite(red, i);
    do{
    }while((millis()-tempo) < aspetta);
    tempo = millis();
  }
  for (int i = 255; i >= 0; i --){
    analogWrite(green, i);
    do{
    }while((millis()-tempo) < aspetta);
    tempo = millis();
  }
  for (int i = 255; i >= 0; i --){
    analogWrite(blue, i);
    do{
    }while((millis()-tempo) < aspetta);
    tempo = millis();
  }
  for (int i = 0; i <= 255; i ++){
    analogWrite(green, i);
    analogWrite(red, i);
    analogWrite(blue, i);
    do{
    }while((millis()-tempo) < aspetta);
    tempo = millis();
  }
  
}


void onRedLightChange()  {
  realRed = map(redLight, 0, 255, 255, 0);
}

void onGreenLightChange()  {
  realGreen = map(greenLight, 0, 255, 255, 0);
}

void onBlueLightChange()  {
  realBlue = map(blueLight, 0, 255, 255, 0);
}


void onOnlyColorChange()  {
}

void color(){
  if(onlyColor){
    analogWrite(red, realRed);
    analogWrite(blue, realBlue);
    analogWrite(green, realGreen);
  }
}

void onFadeEffectChange()  {
}

