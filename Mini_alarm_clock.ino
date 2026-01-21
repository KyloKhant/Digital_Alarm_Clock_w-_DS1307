#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <SevSeg.h>
//Naming 7-seg as "sevseg"
SevSeg sevseg;

//initializing
int hr = 0;
int min = 0;
int time = 0;

int org_clk=0;
static unsigned long lastRead = 0;

int buzz = 40;
int button= 16;
int press= 0;
int snooze_btn = 18;
int snooze=0;
int s =1;


int alarm= 600;

int snooze_time = alarm;
int alarm_end=alarm+3;// End after 3 mins
int alarmed = 0;

bool memory = 0;// to store whether STOP is pressed or not

void setup() {
  Serial.begin(9600);
  while(!Serial);
  delay(200);

  pinMode(buzz, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(snooze_btn, INPUT_PULLUP);

  byte numDigits = 4;  
  byte digitPins[] = {2,5,6,13};
  byte segmentPins[] = {3, 7, 11, 9, 8, 4, 12, 10};
  bool resistorsOnSegments = 0; //No resistors on segment pins 
  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);
}

void loop() {
  //Naming DS1307 clock as "tm"
  tmElements_t tm;
  
  alarm_clock(tm.Hour*100+tm.Minute);//alarm function

  sevseg.refreshDisplay();
  // Read RTC once per second (to prevent flashing)
  if (millis() - lastRead >= 1000) {
    lastRead = millis();

     
    if (RTC.read(tm)) {
      hr = tm.Hour;
      min = tm.Minute;

      int newTime = hr * 100 + min;//time can only be displayed by a number 

      if (newTime != org_clk) {// update display ONLY when changed
        org_clk = newTime;
        sevseg.setNumber(org_clk, 2);// position of "."
      }
      
    }
  }
  
}
//Alarm function
void alarm_clock(int time){
  //reading the state of STOP & SNOOZE
  press = digitalRead(button);
  snooze = digitalRead(snooze_btn);
  //STOP is pressed
  if (press == LOW){
    noTone(buzz);
    memory=1;
    alarmed=0;
    s=0;
  }
  //SNOOZE is pressed
  if (snooze == LOW){
    noTone(buzz);
    s=1;
    snooze_time= pass59mins(time+2);// time to restart the alarm (after 2 mins)
    alarm_end= pass59mins(time+5);//time to end the alarm (3mins after alarm has started)
    alarmed=0;
    memory=1;
    snooze=1;
    }
  //alarm time is reached and no button is pressed
  if (time==alarm && memory ==0){
      
      alarmed=1;
      s=0;
  }
  // when alarmed & no button is pressed OR snoozed & snooze time is reached OR end of ringing time is reached & no button is pressed 
  if ((alarmed ==1 && memory ==0) || (s==1 && time>=snooze_time) || (memory==0 && time>=snooze_time))
  {
    //end of alarm is not reached
    if (time<alarm_end){
      alarm_sound();
    }
    //end of alarm is reached
    if(time==alarm_end){
      noTone(buzz);
      snooze_time=pass59mins(time+2);// time to restart the alarm
      alarm_end=pass59mins(time+5);//time to end the alarm
      memory=0;
      alarmed =0;
    }
        
  }     
  if (time == 0){//Memory reset at midnight 
    memory = 0;
  }
  
}
//to convert time after 59mins to hr and mins 
//e.g., 172 (1:72) to 212(2:12)
int pass59mins (int t){
  if (t%100>59){
    if ((t/100)+1!=24){
    t = (((t/100)+1))*100+((t%100)-60);
    return t;
    }
    else{
      t = ((t%100)-60);
      return t;
    }
  }
  else{
  return t;
  }
}
// Sound pattern of alarm (beep*__beep*)
void alarm_sound(){
  int freq= 1000;

  static long prev=0;
  long now=millis();
  int duration=100;
  
  static bool state=0;

  
  if(!state && now-prev>=250){
    tone(buzz,freq);
    prev=now;
    state=1;
  }
  else if(state && now-prev>=300){
    noTone(buzz);
    prev=now;
    state=0;
  }
}


