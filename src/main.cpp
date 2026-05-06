#include <Arduino.h>
/*
to whoever is reading this, this is my understanding of whats happening
and ive left you the skeleton code and all you have to do is fill in the blanks
ill explain line by line just in case some of my assumptions are wrong so you can make the proper edit
*/


// all analog input pins 
const int txex_pin = 1; // these numbers are arbitrary, you can set them to whatever you want.
const int dpsk_pin = 2;
const int tofro_pin = 3;
const int scanningbeam_pin = 4;
const int antselrd_pin = 5;

// output to mc1496 pin
const int dpskModulator_pin = A1; // this pin is not arbitrary, needs to be analog output for the modulator to control voltage

// timer ints
unsigned long dpskInterval = 0;
unsigned long antselrdInterval = 0;

void dpskFunction(int);
void tofroFunction();
void scanningBeanFunction();
void antselrdFunction();


void setup() {
  Serial.begin(9600); // just in case you want to print out statements
  pinMode(txex_pin, INPUT_PULLUP);
  pinMode(dpsk_pin, INPUT_PULLUP);
  pinMode(tofro_pin, INPUT_PULLUP);
  pinMode(scanningbeam_pin, INPUT_PULLUP); // this might be able to be removed if just using to and fro for scanning
  pinMode(antselrd_pin, INPUT_PULLUP);
  pinMode(dpskModulator_pin, OUTPUT);
}

void loop() { // assumption that only one function runs at a time
  if(digitalRead(txex_pin) == HIGH){ // if transmission enable is on, start trying to read the other pins
    if(digitalRead(dpsk_pin) == HIGH){
      dpskInterval = millis();
      dpskFunction(dpskInterval);
    }
    if(digitalRead(antselrd_pin) == HIGH){
      antselrdInterval == millis();
      antselrdFunction();
    }

    if(digitalRead(tofro_pin) == HIGH){
      tofroFunction();
    }



  }
}


void dpskFunction(int time){
  int dpskInterval = 500; // time to read dpsk in milliseconds
  while( (millis() - time) < dpskInterval){
    if(digitalRead(dpsk_pin == HIGH)){
      // DO SOMETHING TO THE MODULATOR PIN
    }
  } // when this while statement ends, dpsk is done being checked to change the output
}

void antselrdFunction(){
  // im going to implement this later, idk how we want to do this.
  // it would really be easy to do with an analog output from UTCU
  // to just give me a voltage and i can read said voltage for the antenna.
  // this should not be catastrophic
}

void tofroFunction(){
  // this is where you do your amplitude modulation based on the formula given by laberge.
  // just adjust the voltage of the output pin specified earlier
  // dpskmodulator_pin is the thing you want to manipulate the output voltage
}




