# include "type.h"

# define IN 0
# define OUT 1
# define PORTA 0
# define PORTB 1
# define PORTC 2
# define PORTD 3
# define PORTE 4
# define PORTF 5

void DIO_Init (int8 port, int8 pin, int8 dir);
void DIO_WritePort(int8 port,int8 value);
void DIO_WritePin (int8 port, int8 pin, int8 value);
