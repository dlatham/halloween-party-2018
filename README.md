# Halloween Party Effects
Written for our 2018 Halloween party, this is an Arduino program that monitors 2 motion detectors and triggers effects on 4 separate relays. You can configure the 4 different effects using the `effects` array which stores variables that control delay, relay closure time, etc.

## Configuration
All configuration is handled in the `effects` array which has parameters structured in the following way:

{_motion_sensor_, _relay_to_trigger_, _delay_, _active_time_)

**motion_sensor** : the motion sensor that triggers this effect (motion1, or motion2).

**relay_to_trigger** : the relay that should be triggered for this effect (relay1, relay2, relay3, or relay4).

**delay** : the amount of time (in milliseconds) that the program should wait after motion is detected and before triggering the effect.

**active_time** : the amount of time (in milliseconds) that the program will keep the relay closed (effect on).

Example configuration array:
```
int effects[4][4] = {{motion1, relay1, 1000, 1000},  //Sound effect #1
                    {motion2, relay2, 1000, 1000},  //Sound effect #2
                    {motion1, relay3, 0, 5000},     //Fog machine
                    {motion2, relay4, 1000, 1000}}; //Open effect
```

## Timing
Due to limitations of the Interrupt Service Routine (ISR), I opted to run delays and timing in the main loop of the application. This means that the application will ignore additional motion requests will the current effects program is carried out to completion. The program calculates the maximum time required (+500ms) to complete all effects and, only after that time has elapsed, returns to the main program loop.

This could and should be improved: An interrupt could set a state and timing for all effects could be handled in a central loop. Unfortunately the party is tomorrow so this will need to do for now.
