#include <Wire.h>
#include <Adafruit_INA219.h>
#include <String.h>


int prevState = 0;
int state=0;

Adafruit_INA219 ina219;

int counter1 = 0;
int counter10 = 0;
float analyzedata = 0;
float shuntvoltage = 0;
float busvoltage = 0;
float current_mA = 0;
float loadvoltage = 0;
float power_mW = 0;


void setup(void) {
  Serial.begin(9600);
  pinMode(D5, INPUT);



  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    while (1) { delay(10); }
  }
  // Serial.println("Measuring voltage and current with INA219 ...");
  Serial.println("inicio");
}

int timeOnMillis;
void loop(void) {


  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);


  if (digitalRead(D5) == 1) {

    Serial.print((String)loadvoltage + "V;");
    Serial.print((String)current_mA + "mA");
    Serial.println();
  }
  state=digitalRead(D5);

  if(state!=prevState){
    prevState=state;
    if(state==1){
      //Serial.println("recebendo millis");
      timeOnMillis=millis();
    }
    if(state==0){
      timeOnMillis = millis() - timeOnMillis;
      Serial.print((String)timeOnMillis + "ms\n");
      Serial.println("-------------------------------------------------------");
      counter1++;

      if(counter1==3){
        counter10++;
        counter1=0;
      }
    }
  }
  
  if(counter10>=100){
    Serial.println("fim");
    counter10=0;
  }
}
