# include "DIO.h"
# include <stdint.h>
# include "tm4c123gh6pm.h"
# include "bitwise_operation.h"

int main(){
  
  DIO_Init(PORTF,0,IN);
  DIO_Init(PORTF,1,OUT);
  DIO_Init(PORTF,2,OUT);
  DIO_Init(PORTF,3,OUT);
  DIO_Init(PORTF,4,IN);
  
  while(1){
    int volatile counter = 0 ;

    while(counter < 1000000){
    DIO_WritePort(PORTF,0x02);  //red color
    ++counter;
  }
  
  counter = 0 ;
  while(counter < 1000000){
    DIO_WritePort(PORTF,0x04);  //blue color
    ++counter;
  }
  
  counter = 0 ;
  while(counter < 1000000){
    DIO_WritePort(PORTF,0x08);  //Green color
    ++counter;
  }
}
}
