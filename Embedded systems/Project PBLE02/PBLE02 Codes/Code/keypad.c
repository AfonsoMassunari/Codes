#include "keypad.h"
#include "pic18f4550.h"
#include "bits.h"

static unsigned char valor = 0x00;

unsigned char kpRead(void) {
    int valor = 0;
    //lê todas as portas dos botões caso uma esteja pressionada envia um valor referente ao botão
    if(bitTst(PORTC,0)){
        valor = 1;
    }
    if(bitTst(PORTC,1)){
        valor = 2;
    }
    if(bitTst(PORTC,2)){
        valor = 3;
    }
    if(bitTst(PORTD,4)){
        valor = 4;
    }
    if(bitTst(PORTD,5)){
        valor = 5;
    }
    
    return valor;
}

void kpDebounce(void) {
    unsigned char i, j;
    static unsigned char tempo;
    static unsigned char valorNovo = 0x0000;
    static unsigned char valorAntigo = 0x0000;

    for (i = 0; i < 4; i++) {
        TRISB = ~((unsigned char)1<<i);
        PORTB = ~((unsigned char)1<<i);

        //realiza o teste para cada bit e atualiza a variável
        for (j = 0; j < 2; j++) {
            if (!bitTst(PORTB, j + 4)) {
                bitSet(valorNovo, (i * 2) + j);
            } else {
                bitClr(valorNovo, (i * 2) + j);
            }
        }
    }
    if (valorAntigo == valorNovo) {
        tempo--;
    } else {
        tempo = 10;
        valorAntigo = valorNovo;
    }
    if (tempo == 0) {
        valor = valorAntigo;
    }
}

void kpInit(void) {
    TRISC |= 0b00000111; //quatro entradas e quatro saidas
    TRISD |= 0b00110000;
    bitClr(INTCON2, 7); //liga pull up
    ADCON1 = 0b00001110; //apenas AN0 é analogico, a referencia é baseada na fonte

#ifdef PIC18F4550
    SPPCFG = 0x00;          // SFR nao presente no PIC18F4520
#endif
}