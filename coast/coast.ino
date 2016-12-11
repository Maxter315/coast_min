#include <ShiftOutX.h>
#include <ShiftPinNo.h>

#define PWMR 16

#define BUTTON 3
#define SWITCH 4

#define CLK 11
#define DATA 8
#define LATCH 12

#define LIGHTHOUSE_RED 5
#define COASTHOUSE 6
#define SHIP_YELLOW 7
#define SHIP_RED 0

shiftOutX regOne(LATCH, DATA, CLK, MSBFIRST, 2); 

void srSet(uint16_t val){
  digitalWrite(LATCH, LOW);
  shiftOut_16(DATA, CLK, LSBFIRST, val);
  digitalWrite(LATCH, HIGH);
  //delay(1);
  digitalWrite(LATCH, LOW);
}

void pwmSet(uint8_t lvl_a, uint8_t lvl_b, uint8_t offset, uint8_t tick){
    uint16_t val = 0;
    uint16_t state = 0;
    state = 0;
    if (lvl_a > tick){
      state |= (1<<offset);
    }
    if (lvl_b > tick){
      if(offset==15) state |= 1;
      else state |= (2<<offset);
    }
    //val = (state);// << offset;
    srSet(state);    
}

void setup(){
    //Serial.begin(9600);
    pinMode(BUTTON,INPUT);
    pinMode(SWITCH,INPUT);
  //pinMode(3,OUTPUT);
  //digitalWrite(3,HIGH);
}

unsigned long crTime, prTime;
uint16_t tick = 0;
uint16_t pos;
uint8_t level=0,offset=0;
int8_t cycle = (-PWMR);

void loop(){
  
  pwmSet(PWMR-level,level,offset,tick); 
  tick>PWMR ? tick=0 : tick++;
  
  crTime = millis();
  if (crTime - prTime > 15){
    prTime = crTime; 

    cycle>=PWMR ? cycle = (-PWMR+15) : cycle++;
    if(cycle > 0){
      level = cycle;
      if(cycle == PWMR) {
        level=0;
        offset==15? offset=0 : offset++;
      }
    }else{
      level = 0;
    }   
      //level++;
      //if(level > (PWMR-1)) {
        //level = 0;
        //offset>14 ? offset=0 : offset++;
      //}
    
	  //for (uint8_t i = 0; i < 8; ++i){
      //pwmSet(1, 1, 0, tick%8);

    //Serial.print(cycle);
    //Serial.print("\t");
    //Serial.println(level);
    //if(tick == 200) lvl++;      
    //temp = 1<<i;
    //delay(1000);
    //delayMicroseconds(100);
	  //}
  }
}
