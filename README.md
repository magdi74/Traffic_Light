PROJECT DESCRIPTION

In our project, it was requested that we should implement two traffic lights and two
pedestrian lights with 1 push button and 2 LEDs (green and red) each; where in
each traffic light, the green light should stay for 5 seconds, yellow light for 2
seconds, then red light.

Exactly after 1 second, the next one shall repeat the previous sequence with same
interval periods and so on.

For the pedestrian lights, it’s needed that whenever the pedestrian presses the green
light, the running traffic light should be interrupted in case it was on a green light,
and the pedestrian green light would be green for 2 seconds then it will turn to red,
and the running traffic light shall resume from when it was paused.

For example, if the traffic light was green for 2 seconds and then interrupted by the
pedestrian light, it will resume the remaining 3 seconds to complete the 5 seconds.
We have successfully implemented all of the previous tasks using interrupts and
timers.

Also, we have succeeded in implementing the first bonus part which stated that:

1. If two pedestrians pressed two push buttons at the same time

2. If the same button was pressed more than 1 time during the same period of
the pedestrians crossing the street.

3. In case the button was pressed after 1 second from the end of the period of
pedestrians crossing.

FUNCTIONS DESCRIPTION

We wrote 9 functions with TivaWare Drivers to implement the project which are

void Init_PORTA();

void Init_PORTB();

void Init_PORTD();

void TIMER0();

void TIMER1();

void Car_Handling();

void NORTH_PED_Handler();

void EAST_PED_Handler();

void PED_TIMER();

Now, we are going to discuss each function separately.

void Init_PORTA() function:

We set the 7th pin to be an output pin for pedestrians light.

void Init_PORTB() function:

we set pin 3 to be an input to act as an interrupt for the North-South traffic and set
interrupt handler to NORTH_PED_Handler function
and also set pins 0,1,2,4,5 as an output pins such that:

• Pins 0,1,2 for the traffic lights

• Pins 4,5 for the pedestrians lights

void Init_PORTD() function:

we set pin 3 to be an input to act as an interrupt for the East-West traffic and set
interrupt handler to EAST_PED_Handler function
and also set pins 0,1,2,6as an output pins such that:

• Pins 0,1,2 for the traffic lights

• Pins 6 for the pedestrians light

void TIMER0() function:

we set the time of timer0 to 1 second, periodic_up counting, set its priority to 5 to
handle the case if two pedestrians pushed the button together in two different
traffics
this timer is used to call function car_handling after one second.

void TIMER1() function:

we set the time of timer1 to 2 second, periodic_up counting, set its priority to 5 to
handle the case if two pedestrians pushed the button together in two different
traffics
this timer is used to call function PED_TIMER after two seconds.

void Car_Handling() function:

We set our normal traffic light system which is the traffic light shall stay GREEN
for 5 seconds, then YELLOW for 2 seconds, then turns RED. When one of the
traffic lights is set to RED the other one has to go GREEN exactly after 1 second,
by using switch cases that switches on the number of seconds

void PED_TIMER() function:

at first we clear timer0 and the switches which are pin3 in both portB and portD,
then we disable timer1 and enable timer0 to return to car_handling function.

void NORTH_PED_Handle() function:

at first, we disable the interrupts to prevent any unexpected issue or behavior,
disable timer0 and enable timer1 to give the pedestrians their 2 seconds from that
we will enable the North-South Pedestrian GREEN LED and disable the RED
LED for Pedestrian and set Traffic B and D is RED.

void EAST_PED_Handler() function:

at first, we disable the interrupts to prevent any unexpected issue or behavior,
disable timer0 and enable timer1 to give the pedestrians their 2 seconds from that
we will enable the East-West Pedestrian GREEN LED and disable the RED LED
for Pedestrian and set Traffic B and D is RED.

At the end the main function calls these functions for initialization:

 Init_PORTA();
 
 Init_PORTB();
 
 Init_PORTD();
 
 TIMER0();
 
 TIMER1();
 
And do a while loop to ensure being in the program all the time.


