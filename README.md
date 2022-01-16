

## Overview 

My daughter loves lights and switches so I decided to make her a box with lots
of these all over it so she could play with this rather than taking the Mummies
gadgets and potentially breaking them (yes, I know, I'm probably making this 
more likely to happen, not less :D)

Initial code copied from [this repo](https://github.com/fionahiklas/pic_large_led_display)

## Getting Started

### PICKit3

Following instructions that came with this so that the circuit to be 
programmed is powered.

#### Project Configuration

* Find the `Production` -> `Set Project Configuration` -> `Customize ...` menu
* From the dialog that appears select PICKit3 in the LHS and `Power` in the drop-down
* Make sure that the "Power Target circuit from PICKit3" is selected if you use a programming board (I did)
* Also I double clicked on the PICKit3 serial number/name and renamed the boards to distinguish between them

#### 


## Circuit

* Contains PIC 16F884
* Transistors to drive 5V and GND to LEDs
* 5V supply (based off 9V battery and stepped down) 
* Misc switches and LEDs



## Notes 

### Resistor Calculation

Total V = 5V
Forward voltage = 3V
Resistor voltage drop = 3.4V
Forward current = 20mA

Resistor = 3.4/0.02
         = 6400

Using 10k resistors for ease

 
## References

### PIC

* [Timer interrupt](http://ww1.microchip.com/downloads/en/DeviceDoc/51702A.pdf)
* [PIC interrupts](http://picguides.com/beginner/interrupts.php)
* [error: variable has incomplete type void, C99 error](https://www.microchip.com/forums/m1058706.aspx)
* [v2.00 xc8 interrupt syntax](https://www.microchip.com/forums/m1057526.aspx#1067160)
* [PIC16F884 local docs](file:///Applications/microchip/xc8/v2.20/docs/chips/16f884.html) 



