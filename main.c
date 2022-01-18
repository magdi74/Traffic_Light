//***************************************************
//C Libraries
#include "stdint.h"
#include <stdbool.h>
#include <stdio.h>

//****************************************************
//TIVAWARE HEADER FILES ... USED THE ABSOLUTE PATH BECAUSE THE TIVAWARE DIDN'T WORK IN ANY OTHER WAY

#include "C:\TI\TivaWare_C_Series-2.2.0.295\inc/hw_ssi.h"
#include "C:\TI\TivaWare_C_Series-2.2.0.295\inc/hw_types.h"
#include "C:\TI\TivaWare_C_Series-2.2.0.295\driverlib/ssi.h"
#include "C:\TI\TivaWare_C_Series-2.2.0.295\inc/tm4c1294ncpdt.h"
#include "C:\TI\TivaWare_C_Series-2.2.0.295\driverlib/gpio.h"
#include "C:\TI\TivaWare_C_Series-2.2.0.295\driverlib/pin_map.h"
#include "C:\TI\TivaWare_C_Series-2.2.0.295\inc/hw_memmap.h"
#include "C:\TI\TivaWare_C_Series-2.2.0.295\driverlib/sysctl.h"
#include "C:\TI\TivaWare_C_Series-2.2.0.295\driverlib/interrupt.h"
#include "C:\TI\TivaWare_C_Series-2.2.0.295\driverlib/systick.h"
#include "C:\TI\TivaWare_C_Series-2.2.0.295\driverlib/sysctl.h"
#include "C:\TI\TivaWare_C_Series-2.2.0.295\driverlib/adc.h"
#include "C:\TI\TivaWare_C_Series-2.2.0.295\driverlib/uart.h"
#include "C:\TI\TivaWare_C_Series-2.2.0.295\driverlib/timer.h"
#include "C:\TI\TivaWare_C_Series-2.2.0.295\driverlib/sysctl.h"
#include "tm4c123gh6pm.h"

//************************************************
//GLOBAL VARIABLES
int sec=0; //FOR FINITE STATE MACHINE

//***************************
//FUNCTION PROTOTYPE
void Init_PORTA();          //Initializing the GPIO_PORTA
void Init_PORTB();          //Initializing the GPIO_PORTB
void Init_PORTD();          //Initializing the GPIO_PORTD
void TIMER0();              //Initializing TIMER0
void TIMER1();              //Initializing TIMER1
void Car_Handling();        //Handling the car for the traffic lights
void NORTH_PED_Handler();   //Handling the pedestrian from the North
void EAST_PED_Handler();    //Handling the pedestrian from the East
void PED_TIMER();           //Pedestrian Timer


//************************************************
//Main Program

int main()
{
    //Initializing the GPIO_PORTA using Tivaware
    Init_PORTA();
    //Initializing the GPIO_PORTB using Tivaware
    Init_PORTB();
    //Initializing the GPIO_PORTD using Tivaware
    Init_PORTD();
    //Initializing the TIMER0 using Tivaware
    TIMER0();
    //Initializing the TIMER1 using Tivaware
    TIMER1();
    
    // Initializing Port B Pin 6 to be always equal to 1
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 1);
    
    //while loop to ensure being in the program all the time
    while(1){

        //DO NOTHING
    }
    //Unreachable Statement because we will never make it
    //out of the while loop until the program termiates
    return 0;
}

void Init_PORTA(){
  // Enable the GPIOA peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // Wait for the GPIOA module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)){}
    
    // Set pins 7 as output (Pedestrian)
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_7);
    
}


void Init_PORTB(){

    // Enable the GPIOB peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    // Wait for the GPIOB module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)){}
    // Initialize the GPIO pin configuration.
    // Set PIN 3 as Input for pedestrian (Switch)
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_3);
    // Sets the pad configuration for PIN3
    GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);
    // Disables GPIO PIN 3
    GPIOIntDisable(GPIO_PORTB_BASE, GPIO_PIN_3);
    // Sets the interrupt type for PIN3
    GPIOIntTypeSet(GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_FALLING_EDGE);
    // Register the port-level interrupt handler. This handler is the first
    // level interrupt handler for all the pin interrupts for the North Pedestrians.
    GPIOIntRegister(GPIO_PORTB_BASE, NORTH_PED_Handler);
    // Enables GPIO PIN 3
    GPIOIntEnable(GPIO_PORTB_BASE, GPIO_PIN_3);
    // Set pins 0,1,2,4,5 as output.
    // PIN 0 as Output (Traffic)
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0);
    // PIN 1 as Output (Traffic)
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_1);
    // PIN 2 as Output (Traffic)
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_2);
    // PIN 4 as Output (Pedestrian)
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4);
    // PIN 5 as Output (Pedestrian)
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5);
}

void Init_PORTD(){
    // Enable the GPIOD peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    // Wait for the GPIOB module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)){}
    // Initialize the GPIO pin configuration.
    // Set PIN 3 as Input.(Switch for the pedestrian for the other side of the road)
    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_3);
    // Sets the pad configuration for PIN3
    GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);
    // Disables GPIO PIN 3
    GPIOIntDisable(GPIO_PORTD_BASE, GPIO_PIN_3);
    // Sets the interrupt type for PIN3
    GPIOIntTypeSet(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_FALLING_EDGE);
    // Register the port-level interrupt handler. This handler is the first
    // level interrupt handler for all the pin interrupts for the East Pedestrians.
    GPIOIntRegister(GPIO_PORTD_BASE, EAST_PED_Handler);
    // Enables GPIO PIN 3
    GPIOIntEnable(GPIO_PORTD_BASE, GPIO_PIN_3);
    // Set pins 0,1,2,6 as output.
    // PIN 0 as Output (Traffic)
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);
    // PIN 1 as Output (Traffic)
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1);
    // PIN 2 as Output (Traffic)
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2);
    // PIN 6 as Output (Pedestrian)
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_6);

}
// Calls itself
void TIMER0()
{
    // Enable the Timer0 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    // Wait for the Timer0 module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));
    // Disable Timer0
    TimerDisable(TIMER0_BASE,TIMER_BOTH);
    // Set the count time for the the periodic timer (Timer0).
    TimerLoadSet(TIMER0_BASE,TIMER_BOTH,16000000-1);
    // Configuring the timer0 to be periodic
    TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC_UP);
    // Clears timer interrupt sources for timer0.
    TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
    // Controls the stall handling for timer0.
    TimerControlStall(TIMER0_BASE,TIMER_BOTH,true);
    // Sets the priority of an interrupt for timer0.
    IntPrioritySet(INT_TIMER0A,0x20);
    // This function enables the indicated timer0 interrupt sources
    TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
    // Registers an interrupt handler for the timer0 interrupt
    TimerIntRegister(TIMER0_BASE, TIMER_A,Car_Handling);
    //Enables the timer0
    TimerEnable(TIMER0_BASE,TIMER_BOTH);
}

// One-time timer
void TIMER1()
{
    // Enable the Timer1 peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    // Wait for the Timer1 module to be ready.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1));
    // Disable Timer1
    TimerDisable(TIMER1_BASE,TIMER_BOTH);
    // Set the count time for the the periodic timer (Timer1) 2 Seconds in this case.
    TimerLoadSet(TIMER1_BASE,TIMER_BOTH,2*16000000-1);
    // Configuring the timer 1 to be periodic
    TimerConfigure(TIMER1_BASE,TIMER_CFG_PERIODIC_UP);
    // Clears timer1 interrupt sources.
    TimerIntClear(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
    // Controls the stall handling for timer1.
    TimerControlStall(TIMER1_BASE,TIMER_BOTH,true);
    // Sets the priority of an interrupt for timer1.
    IntPrioritySet(INT_TIMER1A,0x20);
    // Registers an interrupt handler for the timer1 interrupt
    TimerIntRegister(TIMER1_BASE, TIMER_A,PED_TIMER);
    //Enables the timer1
    TimerIntEnable(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
}

void Car_Handling()
{
    // Clears timer0 interrupt sources
    TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
    // In case Traffic B is Green
    if(GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_2))
    {
      // Disable the Pedestrian traffic lights for PORTB in case Traffic B is green
      GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);
      // Make the Pedestrian traffic lights for PORTB RED so they won't cross
      GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);
    }
    // In case Traffic D is Green 
    if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_2))
    {
      // Disable the Pedestrian traffic lights for PORTD in case Traffic D  is green
      GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);
      // Make the Pedestrian traffic lights for PORTD RED so they won't cross
      GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_PIN_6);

    }
    // In case Traffic B is Yellow
    if(GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_1))
    {
      // Disable the Pedestrian traffic lights for PORTB in case Traffic B is green
      GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);
      // Make the Pedestrian traffic lights for PORTB RED so they won't cross
      GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);
    }
    // In case Traffic D is Yellow 
    if(GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_1))
    {
      // Disable the Pedestrian traffic lights for PORTD in case Traffic D  is green
      GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);
      // Make the Pedestrian traffic lights for PORTD RED so they won't cross
      GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_PIN_6);

    }

    //**********************************************************************
    // Two Traffic Lights System
    // Printing the number of seconds that passed
    printf("%d",sec);
    switch(sec){
    // Unique case
    case 0 :
        // BOTH Traffic Lights are RED
        // Second 1
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
        // Make the NORTH Pedestrian traffic lights for PORTB RED so they won't cross
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);
        // Make the EAST Pedestrian traffic lights for PORTD RED so they won't cross
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_PIN_6);
        // Traffic B is RED
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 1);
        // Traffic D is RED
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 1);
        sec++;
        break;
    //***************************************************//
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        // Traffic D is Green, Traffic B is RED
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
        // Traffic B is RED
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 1);
        // Disable the RED LED for NORTH Pedestrian
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);  
        // NORTH Pedestrian LED is Green
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5);
        // Traffic D is Green
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 4);
        // Disable the Pedestrian traffic lights for PORTD in case Traffic D  is green
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);
        // Make the Pedestrian traffic lights for PORTD RED so they won't cross
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_PIN_6);
        sec++;
        break;

    //***************************************************//
    case 6:
    case 7:
        // After 6 Seconds, Traffic D is Yellow, traffic B is RED
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
        // Traffic B is RED
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 1);
        // Disable the RED LED for NORTH Pedestrian
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);  
        // NORTH Pedestrian LED is Green
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5);
        // Traffic D is Yellow
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 2);
        // Disable the Pedestrian traffic lights for PORTD in case Traffic D  is green
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0);
        // Make the Pedestrian traffic lights for PORTD RED so they won't cross
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_PIN_6);
        sec++;
        break;

    //***************************************************//
    // Unique case
    case 8:
        // After 8 seconds, Traffic D turns into red, Traffic B is RED too
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
        // Traffic D is RED
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 1);
        // Disable the RED LED for EAST Pedestrian
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0); 
        // EAST Pedestrian LED is Green
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
        // Traffic B is RED
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 1);
        // Disable the RED LED for NORTH Pedestrian
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);  
        // NORTH Pedestrian LED is Green
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5);
        sec++;
        break;
    //***************************************************//
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        // After 9 Second, The sequence changes and Traffic B is GREEN, and Traffic D is RED
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
        // Traffic B is Green
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 4); 
        // Disable the Pedestrian traffic lights for PORTB in case Traffic B is green
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);
        // Make the Pedestrian traffic lights for PORTB RED so they won't cross
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);
        // Traffic D is RED
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 1);
        // Disable the RED LED for EAST Pedestrian
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0); 
        // EAST Pedestrian LED is Green
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
        sec++;
        break;

    //***************************************************//
    case 14:
    case 15:
        // After 14 Seconds, Traffic B is Yellow, Traffic D is RED
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
         // Traffic B is YELLOW
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 2);
        // Disable the Pedestrian traffic lights for PORTB in case Traffic B is green
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);
        // Make the Pedestrian traffic lights for PORTB RED so they won't cross
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, GPIO_PIN_4);
        // Traffic D is RED
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 1);
        // Disable the RED LED for EAST Pedestrian
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0); 
        // EAST Pedestrian LED is Green
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
        sec++;
        break;

    //***************************************************//
    case 16:
        sec = 0;
        // In case none of this happens
    default:
        sec++;
    }
}

void PED_TIMER()
{
    // Clears the Interrupt for Timer0
   TimerIntClear(TIMER1_BASE,TIMER_TIMA_TIMEOUT);
   // Clears the interrupts for the switches
   GPIOIntClear(GPIO_PORTB_BASE, GPIO_PIN_3);
   GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_3);
   // Disable Timer1
   TimerDisable(TIMER1_BASE,TIMER_BOTH);
   // Enable Timer0
   TimerEnable(TIMER0_BASE,TIMER_BOTH);
}

void NORTH_PED_Handler()
{
    // Disable the interrupt for the sake of preventing any unexpected issue or behavior
    __asm  ("    CPSID  I\n");
    // Clear the interrupt for PORTB
    GPIOIntClear(GPIO_PORTB_BASE, GPIO_PIN_3);
    // Enable Timer1
    TimerEnable(TIMER1_BASE,TIMER_BOTH);
    // Disable Timer0 without losing any data
    TimerDisable(TIMER0_BASE,TIMER_BOTH);
    // Pedestrian LED is Green
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5);
    // Disable the RED LED for Pedestrian
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
    // Traffic B is RED
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 1); 
    // Traffic D is RED
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 1); 
    // Enable the interrupt again so the code is protected from any unnecessary behavior
    __asm  ("    CPSIE  I\n");
}


void EAST_PED_Handler()
{
    // Disable the interrupt for the sake of preventing any unexpected issue or behavior
    __asm  ("    CPSID  I\n");
    // Clear the interrupt for PORTD
    GPIOIntClear(GPIO_PORTD_BASE, GPIO_PIN_3);
    // Enable Timer1
    TimerEnable(TIMER1_BASE,TIMER_BOTH);
    // Disable Timer0 without losing any data
    TimerDisable(TIMER0_BASE,TIMER_BOTH);
    // Pedestrian LED is Green
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7);
    // Disable the RED LED for Pedestrian
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0);
    // Enable the interrupt again so the code is protected from any unnecessary behavior
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, 0);
	// Traffic B is RED
	GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 1); 
	// Traffic D is RED
	GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 1); 
    __asm  ("    CPSIE  I\n");
}
