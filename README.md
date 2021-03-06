# Simple Pomodoro
A simple pomodoro timer written in C with **PIC16F84A**

## How to Use
- When you turn on, LED (rgb) will blink GREEN 3 times on init. The 25 minutes is running!
- after 25 minutes, Led will blink RED, you need to push the button to start the 5 minutes rest timer. The led turns (and stay) blue.
- ater the 5 minutes rest time, LED will blink blue. You need to push the button to restart the pomodoro to the 25 minutes.
## Code
- set fuse bits as in **config.h** file
- set in/out pin in **pins.h** file
- set another \[X\] (for 1st timer) and \[Y\] (for 2nd. timer) in loop at main function:
```c
  tempo(X);       //25 minutes
  focusBeep();
  tempo(Y);       //5 minutes
  restTime();
```
## Schematic, PCB  and 3D view

Schematic                  |  Printed Circuit Board |   3D visualization             
:-------------------------:|:-------------------------:|:-------------------------:
<img src="img/sch.png" width="480">  |  <img src="img/PCB.PNG" width="480">   |   <img src="img/3D.PNG" width="480">      


