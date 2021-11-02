# include "bitwise_operation.h"
# include "DIO.h"
# include "type.h"

void DIO.Init (int_8 port, int_8 pin, int_8 dir)
{

  set_bit(SYSCTL_RCGCGPIO_R, port)
  while((SYSCTL_PRGPIO_R & port) == 0){};
  
    switch(port){
        
      case port PORTA:
        GPIO_PORTA_LOCK_R = 0x4C4F434B;
        if (dir)
          set_bit(GPIO_PORTA_DIR_R, pin)
            else
              clear_bit(GPIO_PORTA_DIR_R, pin)
        break;
        
              
      case port PORTB:
        GPIO_PORTB_LOCK_R = 0x4C4F434B;
        if (dir)
          set_bit(GPIO_PORTB_DIR_R, pin)
            else
              clear_bit(GPIO_PORTB_DIR_R, pin)
        break;
              
       case port PORTC:
        GPIO_PORTC_LOCK_R = 0x4C4F434B;
        if (dir)
          set_bit(GPIO_PORTC_DIR_R, pin)
            else
              clear_bit(GPIO_PORTC_DIR_R, pin)
        break;  
              
       case port PORTD:
        GPIO_PORTD_LOCK_R = 0x4C4F434B;
        if (dir)
          set_bit(GPIO_PORTD_DIR_R, pin)
            else
              clear_bit(GPIO_PORTD_DIR_R, pin)
        break;
              
        case port PORTE:
        GPIO_PORTE_LOCK_R = 0x4C4F434B;
        if (dir)
          set_bit(GPIO_PORTE_DIR_R, pin)
            else
              clear_bit(GPIO_PORTE_DIR_R, pin)
        break;
              
        case port PORTF:
        GPIO_PORTF_LOCK_R = 0x4C4F434B;
        if (dir)
          set_bit(GPIO_PORTF_DIR_R, pin)
            else
              clear_bit(GPIO_PORTF_DIR_R, pin)
        break;
    }

}

void DIO_WritePort(int_8 port,int_8 value){
switch(port){
      case port PORTA:
        GPIO_PORTA_DATA_R = value;
        break;
    
      case port PORTB:
        GPIO_PORTB_DATA_R = value;
        break; 
    
      case port PORTC:
        GPIO_PORTC_DATA_R = value;
        break;
    
      case port PORTD:
        GPIO_PORTD_DATA_R = value;
        break;
    
      case port PORTE:
        GPIO_PORTE_DATA_R = value;
        break;
    
      case port PORTF:
        GPIO_PORTF_DATA_R = value;
        break;
    }
}


void DIO_WritePin (int_8 port, int_8 pin, int_8 value)
{

    switch(port){

        case port PORTA:
        if (value == 1){
            set_bit(GPIO_PORTA_DATA_R, pin)
            }
            else if (value == 0){
                clear_bit(GPIO_PORTA_DATA_R, pin)
                }
        break;

        case port PORTB:
        if (value == 1){
            set_bit(GPIO_PORTB_DATA_R, pin)
            }
            else if (value == 0){
                clear_bit(GPIO_PORTB_DATA_R, pin)
                }
        break;

        case port PORTC:
        if (value == 1){
            set_bit(GPIO_PORTC_DATA_R, pin)
            }
            else if (value == 0){
                clear_bit(GPIO_PORTC_DATA_R, pin)  
                }
        break;

        case port PORTD:
        if (value == 1){
            set_bit(GPIO_PORTD_DATA_R, pin)
            }
            else if (value == 0){
                clear_bit(GPIO_PORTD_DATA_R, pin)
                }
        break;

        case port PORTE:
        if (value == 1){
            set_bit(GPIO_PORTE_DATA_R, pin)
            }
            else if (value == 0){
                clear_bit(GPIO_PORTE_DATA_R, pin)
                }
        break;

        case port PORTF:
        if (value == 1){
            set_bit(GPIO_PORTF_DATA_R, pin)
            }
            else if (value == 0){
                clear_bit(GPIO_PORTF_DATA_R, pin)
                }
        break;
    }

}
