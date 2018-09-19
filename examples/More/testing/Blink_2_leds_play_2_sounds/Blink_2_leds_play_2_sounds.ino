// BlinkUsingTaskFunction
// This demonstrates the use of the FunctionTask feature of Task library
// It will use two FunctionTasks to to blink a LED repeatedly, by alternating 
// which task is active and flpping the state of the LED pin

#include <Arduino.h>
#include <Task.h>
#include <Maqueen.h>
Maqueen bot;

//NewPing.h and Adafruit_Microbit.h are inlcuded the library header
//but still need to be invoked here.
Adafruit_Microbit_Matrix microbit;

// Pin 13 has an LED connected on most Arduino boards.
int ledPin = 12; // BUILTIN_LED
int ledPin2 = 8;

TaskManager taskManager;

// foreward delcare functions passed to task constructors now required
void OnUpdateTaskLedOn(uint32_t deltaTime); 
void OnUpdateTaskLedOff(uint32_t deltaTime);

void OnUpdateTaskLedOn2(uint32_t deltaTime); 
void OnUpdateTaskLedOff2(uint32_t deltaTime);

void PlayUhOh(uint32_t deltaTime);
void PlayWaka(uint32_t deltaTime);

FunctionTask taskTurnLedOn(OnUpdateTaskLedOn, MsToTaskTime(400)); // turn on the led in 400ms
FunctionTask taskTurnLedOff(OnUpdateTaskLedOff, MsToTaskTime(600)); // turn off the led in 600ms
FunctionTask taskTurnLedOn2(OnUpdateTaskLedOn2, MsToTaskTime(1000)); // turn on the led in 400ms
FunctionTask taskTurnLedOff2(OnUpdateTaskLedOff2, MsToTaskTime(2000)); // turn off the led in 600ms
FunctionTask taskPlayUhOh(PlayUhOh, MsToTaskTime(5000)); // play sound
FunctionTask taskPlayWaka(PlayWaka, MsToTaskTime(6000));

void setup()
{
  bot.begin();
    pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
    taskManager.StartTask(&taskTurnLedOn); // start with turning it on
    taskManager.StartTask(&taskTurnLedOn2);
    taskManager.StartTask(&taskPlayUhOh);
}

void loop()
{
    taskManager.Loop();
}

void PlayUhOh(uint32_t deltaTime) {
  bot.uhoh();
  taskManager.StopTask(&taskPlayUhOh);
  taskManager.StartTask(&taskPlayWaka);
}

void PlayWaka(uint32_t deltaTime) {
  bot.waka();
  taskManager.StopTask(&taskPlayWaka);
  taskManager.StartTask(&taskPlayUhOh);
}

void OnUpdateTaskLedOn(uint32_t deltaTime)
{
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    
    taskManager.StopTask(&taskTurnLedOn); // stop trying to turn the LED On
    taskManager.StartTask(&taskTurnLedOff); // start the task to turn the LED off
    
}

void OnUpdateTaskLedOff(uint32_t deltaTime)
{
    digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
    taskManager.StopTask(&taskTurnLedOff); // stop trying to turn the LED Off
    taskManager.StartTask(&taskTurnLedOn); // start the task to turn the LED On
}

void OnUpdateTaskLedOn2(uint32_t deltaTime)
{
    digitalWrite(ledPin2, HIGH);   // turn the LED on (HIGH is the voltage level)
    taskManager.StopTask(&taskTurnLedOn2); // stop trying to turn the LED On
    taskManager.StartTask(&taskTurnLedOff2); // start the task to turn the LED off
}

void OnUpdateTaskLedOff2(uint32_t deltaTime)
{
    digitalWrite(ledPin2, LOW);    // turn the LED off by making the voltage LOW
    taskManager.StopTask(&taskTurnLedOff2); // stop trying to turn the LED Off
    taskManager.StartTask(&taskTurnLedOn2); // start the task to turn the LED On
}
