
#include "config.h"
#include "pins.h"


bool stop_beep = false;

void setup(void);


void __interrupt() btn(void){
    if(INTCONbits.T0IF){
        INTCONbits.T0IF = 0;
        if(!BUTTON){
            stop_beep = true;
            __delay_ms(1000);
        }
    }
}

void tempo (int t_min){
    for(unsigned int i = 0; i < (t_min*60); i++)
        __delay_ms(1000);  
}

void focusBeep(void){
    while(!stop_beep){ // enquanto o botão nao for pressionado não para o alarme
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
    while(!stop_beep){ // enquanto o botão nao for pressionado não para o alarme
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
        
        //ciclos de 25 / 5 pomodoro
        tempo(25);//25
        focusBeep();
        tempo(5);//5
        restTime();
        
    }
        
    return;
}

void setup(void){
    
    TRISBbits.TRISB1 = 0 ; // RB1 = saída
    TRISBbits.TRISB2 = 0 ; // RB2  = saída
    TRISBbits.TRISB3 = 0 ; // RB3 = saída
    TRISBbits.TRISB4 = 1 ; // RB4 = entrada
    TRISBbits.TRISB5 = 0 ; // RB5 = entrada
    
    INTCONbits.GIE = 1;
    INTCONbits.T0IE = 1;
    INTCONbits.T0IF = 0;
    
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0b111;
    TMR0 = 0;
    
    //inicializa dispositivos
    
    //inicializa LEDs apagados (lógica inversa)
    LED_R = 1; 
    LED_G = 1; 
    LED_B = 1; 
    
    BUZZER = 0; //inicializa BUZZER desligado
    
    beep_start();

    return;
}
