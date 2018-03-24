// InputCaptureTestMain.c
// Runs on LM4F120/TM4C123
// Use Timer0A in edge time mode to request interrupts on the rising
// edge of PB0 (CCP0), and count the pulses.
// Daniel Valvano
// May 3, 2015

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
   Example 6.1, Program 6.1

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// external signal connected to PB6 (T0CCP0) (trigger on rising edge)
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "InputCapture.h"


void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
int checkPeriod(int period);

enum{
	red,
	green,
	blue
};

volatile uint32_t CurrentColor;      // incremented on interrupt
void UserTask(int period){
  //use the period to do something
	//IMPORTANT: You are in an interrupt handle. 
	//Keep the processing here short and sweet
	switch(checkPeriod(period))
	{
		case red:
			CurrentColor = red;
			break;
		case green:
			CurrentColor = green;
			break;
		case blue:
			CurrentColor = blue;
			break;
	}
}

int checkPeriod(int period)
{
	// return "red", "green", or "blue
	// If frequency == 100Hz, return red.
  // If frequency == 500Hz, return blue.
  // If frequency == 1000Hz, return green.
	return red;
}

void ChangeColor(void)
{
	// read CurrentColor, output to LED array
}

int main(void){
  TimerCapture_Init(&UserTask);    // initialize timer0A in capture mode on PB6
  while(1){
		ChangeColor();
    WaitForInterrupt();
  }
}