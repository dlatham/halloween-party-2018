/* Halloween Party 2018
 *  A yard motion sensor
 *  Enable 2 motion sensors to set off 2 separate waves of effects
 */

const int motion1 = 4;
const int motion2 = 5;
const int relay1 = 6;
const int relay2 = 7;
const int relay3 = 8;
const int relay4 = 9;
long now = 0;
int maxtime1 = 0;
int maxtime2 = 0;

// TIMING CONFIGURATIONS {Motion detector trigger, relay, delay after trigger, time on}
int effects[4][4] = {{motion1, relay1, 1000, 1000},  //Sound effect #1
                    {motion2, relay2, 1000, 1000},  //Sound effect #2
                    {motion1, relay3, 0, 5000},     //Fog machine
                    {motion2, relay4, 1000, 1000}}; //Open effect


void setup() {
  Serial.begin(9600);
  Serial.println("Spookiness starting up...");
  //Pin setup
  pinMode(motion1, INPUT_PULLUP);
  pinMode(motion2, INPUT_PULLUP);
  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, HIGH);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay2, HIGH);
  pinMode(relay3, OUTPUT);
  digitalWrite(relay3, HIGH);
  pinMode(relay4, OUTPUT);
  digitalWrite(relay4, HIGH);
  //Calculate the maximum delays necessary to complete all tasks after motion
  for(int x=0; x<4; x++){
    if((effects[x][0]==motion1)&&((effects[x][2]+effects[x][3])>maxtime1)){
      maxtime1 = (effects[x][2]+effects[x][3]);
    }
  }
  for(int x=0; x<4; x++){
    if((effects[x][0]==motion2)&&((effects[x][2]+effects[x][3])>maxtime2)){
      maxtime2 = (effects[x][2]+effects[x][3]);
    }
  }
  maxtime1 = maxtime1 + 500;
  maxtime2 = maxtime2 + 500;
  Serial.print("Maximum delay times from configuration: {");
  Serial.print(maxtime1); Serial.print(","); Serial.print(maxtime2);
  Serial.println("}");
}

void loop() {
  if(motion1==LOW){
    now = millis();
    Serial.print("Motion sensor 1 triggered at "); Serial.println(now);
    while((millis()-now) < maxtime1){
      for(int x=0; x<4; x++){
        if((effects[x][0]==motion1)&&((millis()-now)>effects[x][2])&&((millis()-now)<effects[x][3])){  //If the timer is greater than the delay but less than the time on
          digitalWrite(effects[x][1], LOW);
          Serial.print("Relay "); Serial.print(effects[x][2]); Serial.print(" triggered after "); Serial.print((millis()-now)); Serial.println("ms");
        } else {
          digitalWrite(effects[x][1], HIGH);
        }
      }
    }
  }
  if(motion2==LOW){
    Serial.print("Motion sensor 2 triggered at "); Serial.println(now);
    now = millis();
    while((millis()-now) < maxtime2){
      for(int x=0; x<4; x++){
        if((effects[x][0]==motion2)&&((millis()-now)>effects[x][2])&&((millis()-now)<effects[x][3])){  //If the timer is greater than the delay but less than the time on
          digitalWrite(effects[x][1], LOW);
          Serial.print("Relay "); Serial.print(effects[x][2]); Serial.print(" triggered after "); Serial.print((millis()-now)); Serial.println("ms");
        } else {
          digitalWrite(effects[x][1], HIGH);
        }
      }
    }
  }
}
