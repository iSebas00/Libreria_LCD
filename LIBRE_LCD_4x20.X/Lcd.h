
#ifndef __MI_LCD_H
#define	__MI_LCD_H


/***********************************************/
// DECLARACION DE PINES DE DATOS PARA LA LCD   //
/***********************************************/
#define valor_D4 PORTDbits.RD4
#define valor_D5 PORTDbits.RD5
#define valor_D6 PORTDbits.RD6
#define valor_D7 PORTDbits.RD7
#define valor_RS PORTDbits.RD0
#define valor_EN PORTDbits.RD1
/***********************************************/
// DECLARACION DE PINES DE CONFIG LCD PARA I/O //
/***********************************************/
#define config_D4 TRISDbits.RD4
#define config_D5 TRISDbits.RD5
#define config_D6 TRISDbits.RD6
#define config_D7 TRISDbits.RD7
#define config_RS TRISDbits.RD0
#define config_EN TRISDbits.RD1
/********************************************************/
// DEFINICION DE  COMANDOS PROPUESTOS POR EL FABRICANTE //
//           CON MODELO MIKROC                          //
/********************************************************/
#define      _LCD_FIRST_ROW           128
#define      _LCD_SECOND_ROW          192
#define      _LCD_THIRD_ROW           148
#define      _LCD_FOURTH_ROW          212
#define      _LCD_CLEAR               1
#define      _LCD_RETURN_HOME         2
#define      _LCD_CURSOR_OFF          12
#define      _LCD_UNDERLINE_ON        14
#define      _LCD_BLINK_CURSOR_ON     15
#define      _LCD_MOVE_CURSOR_LEFT    16
#define      _LCD_MOVE_CURSOR_RIGHT   20
#define      _LCD_TURN_OFF            0
#define      _LCD_TURN_ON             8
#define      _LCD_SHIFT_LEFT          24
#define      _LCD_SHIFT_RIGHT         28
/***********************************************************/
/*      DEFINICION DE FUNCIONES A UTILIZAR                 */
/***********************************************************/
void Lcd_Init();
void Lcd_Cmd(char comando);
void Lcd_Out_Cp(char *mensaje);
void Lcd_Out(int y, int x, char *mensaje);
void Lcd_Chr(int y, int x, char mensaje);
void Lcd_Chr_Cp(char mensaje);
void set_comando(int valor_comando);
void cargar_comando();
int set_Cursor(int y, int x);


void set_valor(int valor_comando){
     valor_D7= (valor_comando & 0b00001000)>>3;
     valor_D6= (valor_comando & 0b00000100)>>2; 
     valor_D5= (valor_comando & 0b00000010)>>1;     
     valor_D4= (valor_comando & 0b00000001); 
     cargar_comando();
     __delay_us(100);
     return;
}

void cargar_comando(){
    valor_EN=1;
     __delay_us(10);
    valor_EN=0;
    return;
}

void Lcd_Init(){
    // configruar los pines de la LCD como salida.
    config_D4=config_D5=config_D6=config_D7=config_EN=config_RS=0;
    //inicializar los pines de la lcd
    valor_EN=valor_RS=valor_D4=valor_D5=valor_D6=valor_D7=0;
    __delay_ms(15); // esperamos un tiempo para iniciar con la secuencia
    
    // secuencia sugerida por los creadores para inicializar la LCD.    
    set_valor(3);
    __delay_ms(4);
    set_valor(3);
    set_valor(3);
    set_valor(3);
    set_valor(2);
    set_valor(2);
    set_valor(11);
    set_valor(0);
    set_valor(15);  
    __delay_ms(20);
    return;
}

void Lcd_Chr_Cp(char mensaje){
    int valor_palabra;
    valor_RS = 1; 
    valor_EN=0;
    valor_palabra=(mensaje & 0b10000000)|(mensaje & 0b01000000)|(mensaje & 0b00100000)|(mensaje & 0b00010000);
    set_valor((valor_palabra>>4));
    valor_palabra=(mensaje & 0b00001000)|(mensaje & 0b00000100)|(mensaje & 0b00000010)|(mensaje & 0b00000001);
    set_valor(valor_palabra);
    __delay_us(100);
    return;
}

void Lcd_Cmd(char comando){ // optimizarlo
    int valor_palabra;
    valor_RS = 0; 
    valor_EN=0;
    valor_palabra=(comando & 0b10000000)|(comando & 0b01000000)|
                    (comando & 0b00100000)|(comando & 0b00010000);
    set_valor((valor_palabra>>4));
    valor_palabra=(comando & 0b00001000)|(comando & 0b00000100)|
                    (comando & 0b00000010)|(comando & 0b00000001);
    set_valor(valor_palabra);
     __delay_us(100);
    return;
}

void Lcd_Out(int y, int x, char *mensaje){
    int cursor=set_Cursor(y,x);
    Lcd_Cmd(cursor);
    while(*mensaje){  // escribe todos los elementos del vector hasta que sea nulo               
        Lcd_Chr_Cp(*mensaje);
        mensaje++;               // Increment buffer
    }
    return;
}

void Lcd_Out_Cp(char* mensaje){  
    while(*mensaje){  // escribe todos los elementos del vector hasta que sea nulo               
        Lcd_Chr_Cp(*mensaje);
        mensaje++;               // Increment buffer
    }
    return;
}
    


void Lcd_Chr(int y, int x, char mensaje){
    int cursor=set_Cursor(y,x);
    Lcd_Cmd(cursor);               
    Lcd_Chr_Cp(mensaje);
    return;
}

int set_Cursor(int y, int x){
    unsigned int data; // la pos_x depende el valor de y
    switch (y)
    {
        case 1: data = 128 +(x-1); break;
        case 2: data = 192 +(x-1); break;
        case 3: data = 148 +(x-1); break;
        case 4: data = 212 +(x-1); break;
        default: break;
    }
    return data;
}

#endif	/* XC_HEADER_TEMPLATE_H */

