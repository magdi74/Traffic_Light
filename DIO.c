# include "bitwise_operation.h"
# include "DIO.h"
# include "tm4c123gh6pm.h"
# include "type.h"
# include <stdbool.h>
# include <stdint.h>

void DIO_Init (int8 port, int8 pin, int8 dir)
{
   set_bit(SYSCTL_RCGCGPIO_R,port)   
    switch(port){
        
        case PORTA:
          
        GPIO_PORTA_LOCK_R = 0x4C4F434B;
        if (dir){
          set_bit(GPIO_PORTA_DIR_R, pin)}
        else{
          clear_bit(GPIO_PORTA_DIR_R, pin)}
        
        set_bit(GPIO_PORTF_DEN_R, pin)
        break;
            
        case PORTB:
          
        GPIO_PORTB_LOCK_R = 0x4C4F434B; 
        if (dir){
          set_bit(GPIO_PORTB_DIR_R, pin)}
        else{
          clear_bit(GPIO_PORTB_DIR_R, pin)}
        
        set_bit(GPIO_PORTF_DEN_R, pin)
        break;
              
        case PORTC:
          
        GPIO_PORTC_LOCK_R = 0x4C4F434B;
        if (dir){
          set_bit(GPIO_PORTC_DIR_R, pin)}
        else{
          clear_bit(GPIO_PORTC_DIR_R, pin)}
        
        set_bit(GPIO_PORTF_DEN_R, pin)
        break;  
              
        case PORTD:
          
        GPIO_PORTD_LOCK_R = 0x4C4F434B;  
        if (dir){
          set_bit(GPIO_PORTD_DIR_R, pin)}
        else{
          clear_bit(GPIO_PORTD_DIR_R, pin)}
        
        set_bit(GPIO_PORTF_DEN_R, pin)
        break;
              
        case PORTE:
          
        GPIO_PORTE_LOCK_R = 0x4C4F434B;          
        if (dir){
          set_bit(GPIO_PORTE_DIR_R, pin)}
        else{
          clear_bit(GPIO_PORTE_DIR_R, pin)}
        
        set_bit(GPIO_PORTF_DEN_R, pin) 
        break;
              
        case PORTF:
          
        GPIO_PORTF_LOCK_R = 0x4C4F434B;
        if (dir){
          set_bit(GPIO_PORTF_DIR_R, pin)}
        else{
          clear_bit(GPIO_PORTF_DIR_R, pin)
          set_bit(GPIO_PORTF_PUR_R, pin)}
        
        set_bit(GPIO_PORTF_DEN_R, pin)
        break;
    }

}

void DIO_WritePort(int8 port,int8 value){
  
    switch(port){
          case PORTA:
            
            GPIO_PORTA_DATA_R = value;
            break;
        
          case PORTB:
            
            GPIO_PORTB_DATA_R = value;
            break; 
        
          case PORTC:
            
            GPIO_PORTC_DATA_R = value;
            break;
        
          case PORTD:
            
            GPIO_PORTD_DATA_R = value;
            break;
        
          case PORTE:
            
            GPIO_PORTE_DATA_R = value;
            break;
        
          case PORTF:
            
            GPIO_PORTF_DATA_R = value;
            break;
    }
}


void DIO_WritePin (int8 port, int8 pin, int8 value)
{

    switch(port){

        case PORTA:
          
        if (value == 1){
            set_bit(GPIO_PORTA_DATA_R, pin)}
        else if (value == 0){
             clear_bit(GPIO_PORTA_DATA_R, pin)}
        
        break;

        case PORTB:
          
        if (value == 1){
            set_bit(GPIO_PORTB_DATA_R, pin)}
        else if (value == 0){
             clear_bit(GPIO_PORTB_DATA_R, pin)}
        
        break;

        case PORTC:
        if (value == 1){
            set_bit(GPIO_PORTC_DATA_R, pin)}
        else if (value == 0){
            clear_bit(GPIO_PORTC_DATA_R, pin)}
        
        break;

        case PORTD:
          
        if (value == 1){
            set_bit(GPIO_PORTD_DATA_R, pin)}
        else if (value == 0){
             clear_bit(GPIO_PORTD_DATA_R, pin)}
        
        break;

        case PORTE:
          
        if (value == 1){
            set_bit(GPIO_PORTE_DATA_R, pin)}
        else if (value == 0){
            clear_bit(GPIO_PORTE_DATA_R, pin)}
        
        break;

        case PORTF:
          
        if (value == 1){
            set_bit(GPIO_PORTF_DATA_R, pin)}
        else if (value == 0){
            clear_bit(GPIO_PORTF_DATA_R, pin)}
        
        break;
    }

}
