
#include "config.h"
#include "pins.h"

bool stop_beep = false;         

void setup(void);

//catch button at any time TMR0 interrupt
void __interrupt() btn(void){
    if(INTCONbits.T0IF){
        INTCONbits.T0IF = 0;
        if(!BUTTON){
            stop_beep = true;
            __delay_ms(700);
        }
    }
}

//get time in minutes
void tempo (int t_min){
    for(unsigned int i = 0; i < (t_min*60); i++)
        __delay_ms(1000);  
}

void focusBeep(void){
    while(!stop_beep){  //beep while button is not pressed
        for(char i = 0; i<5;i++){
            BUZZER = 1;
            LED_R = 0;
            __delay_ms(100);
            BUZZER = 0;
            LED_R = 1;
            __delay_ms(100);
        }   
        __delay_ms(1000);
    }
    LED_B = 0;
    stop_beep = false;    
}

void restTime(void){
    while(!stop_beep){ //beep while button is not pressed
        BUZZER = 1;
        LED_B = 0;
        __delay_ms(100);
        LED_B = 1;
        BUZZER = 0;
        __delay_ms(500);
    }
    LED_B = 1; 
}

void beep_start(void){
    for(char i = 0; i<3;i++){
        BUZZER = 1;
        LED_G = 0;
        __delay_ms(200);
        BUZZER = 0;
        LED_G = 1;
        __delay_ms(200);
    }    
}

void main(void) {
    setup();
    
    loop(){    
        // 25/5 pomodoro cycle
        tempo(25);              //25 minutes
        focusBeep();
        tempo(5);               //05 minutes
        restTime();   
    }    
    return;
}

void setup(void){
    
    TRISBbits.TRISB1 = 0 ;      // RB1 = saída   / out
    TRISBbits.TRISB2 = 0 ;      // RB2  = saída  / out
    TRISBbits.TRISB3 = 0 ;      // RB3 = saída   / out
    TRISBbits.TRISB4 = 1 ;      // RB4 = entrada / in
    TRISBbits.TRISB5 = 0 ;      // RB5 = entrada / out
    
    // interrupt bits config
    INTCONbits.GIE = 1;
    INTCONbits.T0IE = 1;
    INTCONbits.T0IF = 0;
    
    //timer config bits
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0b111;
    TMR0 = 0;
    
    // start all RGB colors off (reverse logic)
    // inicializa as cores RGB apagadas (lógica inversa)
    LED_R = 1; 
    LED_G = 1; 
    LED_B = 1; 
    
    // starts the buzzer off
    //inicializa BUZZER desligado
    BUZZER = 0; 
    
    beep_start();
    return;
}
