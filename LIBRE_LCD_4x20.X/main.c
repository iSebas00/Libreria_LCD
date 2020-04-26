


#include <xc.h>
#include <stdio.h>
#include "config.h"
#include "Lcd.h"

int contador=0;
char aux[20];
void main(void) {
    ADCON1 = 0x0F;
    Lcd_Init();
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Out(1,1,"Temp: ");
    
    while(1){
        sprintf(aux,"Temp: %d",contador);
        Lcd_Out(1,1,aux);
        contador++;
        __delay_ms(200);
    }
    return;
}
