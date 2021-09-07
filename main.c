
#include "config.h"
#include "pins.h"

bool stop_beep = false;     // controls when must beep
bool btn_active = false;    // controls when button works

// interrupt to get button press while beeping------ 
void __interrupt() btn(void){
    if(INTCONbits.T0IF){
        INTCONbits.T0IF = 0;
        if(!BUTTON && btn_active){
            stop_beep = true;
            btn_active = false;
            __delay_ms(400);
        }
    }
}
// get time in minutes ----------------------------- 
void tempo (int t_min){
    for(unsigned int i = 0; i < (t_min*60); i++)
        __delay_ms(1000);  
}
// play beep after focused time --------------------
void focusBeep(void){
    btn_active = true;
    while(!stop_beep){ // beep while button is not pressed
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
    btn_active = false;    
}
// play beep after rest time -----------------------
void restTime(void){
    btn_active = true;
    while(!stop_beep){ // beep while button is not pressed
        BUZZER = 1;
        LED_B = 0;
        __delay_ms(100);
        LED_B = 1;
        BUZZER = 0;
        __delay_ms(500);
    }
    LED_B = 1; 
    stop_beep = false;
    btn_active = false;
}
// beep on start -----------------------------------
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
// initial configuration-----------------------------
void setup(void){

    // PORTB bits configuration
    TRISBbits.TRISB1 = 0 ; // RB1 = saída
    TRISBbits.TRISB2 = 0 ; // RB2  = saída
    TRISBbits.TRISB3 = 0 ; // RB3 = saída
    TRISBbits.TRISB4 = 1 ; // RB4 = entrada
    TRISBbits.TRISB5 = 0 ; // RB5 = entrada

    // interrupt bits config
    INTCONbits.GIE = 1;
    INTCONbits.T0IE = 1;
    INTCONbits.T0IF = 0;

    // timer config bits
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
    BUZZER = 0; //inicializa BUZZER desligado

    beep_start();
    
    btn_active = false;
    stop_beep = false;

    return;
}
// main function ------------------------------------
void main(void) {
    setup();

    loop(){

        // 25/5 pomodoro cycle
        tempo(25);//25
        focusBeep();
        tempo(5);//5
        restTime();

    }
    return;
}