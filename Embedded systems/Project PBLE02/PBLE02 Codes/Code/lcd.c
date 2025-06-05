#include "lcd.h"
#include "pic18f4550.h"
#include "bits.h"
#include <xc.h>

//portd
#define RS 0 //RE0
#define EN 1 //RE1
//portb
#define D4 3 //RD3
#define D5 2 //RD2
#define D6 1 //RD1
#define D7 0 //RD0

void Delay40us(void) {
    unsigned char j;
    for (j = 0; j < 68; j++);
}

void Delay2ms(void) {
    unsigned char j, k;
    for (j = 0; j < 20; j++)
        for (k = 0; k < 178; k++);
}

void pulseEnable() {
    bitSet(PORTE, EN);
    bitClr(PORTE, EN);
}

void lcdCommand4bits(unsigned char cmd, unsigned char data) {

    if (data) {
        bitSet(PORTE, RS); //dados
    } else {
        bitClr(PORTE, RS); //comando
    }

    //resolveu o bug rb4
    //PORTB = 0x00;

    if (bitTst(cmd, 7)) {
        bitSet(PORTD, D7);
    } else {
        bitClr(PORTD, D7);
    }


    if (bitTst(cmd, 6)) {
        bitSet(PORTD, D6);
    } else {
        bitClr(PORTD, D6);
    }


    if (bitTst(cmd, 5)) {
        bitSet(PORTD, D5);
    } else {
        bitClr(PORTD, D5);
    }


    if (bitTst(cmd, 4)) {
        bitSet(PORTD, D4);
    } else {
        bitClr(PORTD, D4);
    }

    pulseEnable();
}

void lcdCommand(unsigned char cmd) {

    lcdCommand4bits(cmd, 0);
    lcdCommand4bits(cmd << 4, 0);


    if ((cmd == 0x02) || (cmd == 0x01)) {
        Delay2ms();
        //__delay_ms(2);
    } else {
        Delay40us();
       //__delay_us(40);
    }
}

void lcdData(unsigned char valor) {
    lcdCommand4bits(valor, 1);
    lcdCommand4bits(valor << 4, 1);


    Delay40us();
    //__delay_us(40);
}

void lcdInit(void) {
    unsigned char i;
    // configurações de direção dos terminais
    bitClr(TRISE, RS); //RS
    bitClr(TRISE, EN); //EN
    bitClr(TRISD, D4); //dados
    bitClr(TRISD, D5);
    bitClr(TRISD, D6);
    bitClr(TRISD, D7);

    //    BitClr(SPPCFG, 5);

    //ADCON1 = 0b00001110; //apenas

    // garante inicialização do LCD (+-15ms)
    for (i = 0; i < 7; i++)
        Delay2ms();
        //__delay_ms(2);

    //precisa enviar 4x pra garantir 8 bits
    lcdCommand4bits(0x30, 0); //8bits, 2 linhas, 5x8
    Delay2ms();
    //__delay_ms(2);

    lcdCommand4bits(0x30, 0); //8bits, 2 linhas, 5x8
    Delay2ms();
    //__delay_ms(2);

    lcdCommand4bits(0x30, 0); //8bits, 2 linhas, 5x8
    Delay2ms();
    //__delay_ms(2);

    lcdCommand4bits(0x20, 0); //4bits
    Delay2ms();
    //__delay_ms(2);
    
    lcdCommand(0x28); //4bits
    lcdCommand(0x06); //modo incremental
    //lcdCommand(0x0F); //display e cursor on, com blink
    lcdCommand(0x0C); //// Display on, cursor off, blink off
    lcdCommand(0x01); //limpar display

    /*
    lcdCommand(0x28); //4bits
    lcdCommand(0x06); //modo incremental
    lcdCommand(0x0F); //display e cursor on, com blink
    lcdCommand(0x01); //limpar display
     */

}

void lcd_write_string(const char *str) {//envia uma string pro lcd
    while(*str) {
        lcdData(*str++);
    }
}

void lcdInt(int val) {//envia um int pro lcd
    if (val < 0) {
        val = val * (-1);
        lcdData('-');
    }
    lcdData((val / 10000) % 10 + 48);
    lcdData((val / 1000) % 10 + 48);
    lcdData((val / 100) % 10 + 48);
    lcdData((val / 10) % 10 + 48);
    lcdData((val / 1) % 10 + 48);

}