#include "output.h"
#include "lcd.h"
#include "stateMachine.h"
#include "var.h"
#include "serial.h"
#include "ds1307.h"

#define NUM_IDIOMAS 2
#define NUM_ESTADOS STATE_FIM

//msgs com 16 caracteres
//1 msg por estado (apenas linha de cima)
static char * msgs[NUM_ESTADOS][NUM_IDIOMAS] = {
    {"Alterar tempo  ", "Change time    "},
    {"Valor Alarme 1 ", "Value alarm 1  "},
    {"Alarme Baixo 1 ", "Low alarm 1    "},
    {"Alarme Alto 1  ", "High alarm 1   "},
    {"Valor Alarme 2 ", "Alarm value 2  "},
    {"Alarme Baixo 2 ", "Low alarm 2    "},
    {"Alarme Alto 2  ", "High alarm 2   "},
    {"Alterar idioma ", "Change language"}
};

void outputInit(void) {
    lcdInit();
}

void outputPrint(int numTela, int idioma) {

    if (numTela == STATE_TEMPO) {
        int hours = getHours();
        int minutes = getMinutes();
        int seconds = getSeconds();  
        lcdCommand(0x80);
        lcd_write_string(msgs[numTela][idioma]);//escreve testo referente ao estado
        lcdCommand(0xC0);
        lcdData((hours/ 10) % 10 + 48);//Escreve o horário do relógio de tempo real.
        lcdData((hours/ 1) % 10 + 48); 
        lcdData(10110010);
        lcdData((minutes/ 10) % 10 + 48);
        lcdData((minutes/ 1) % 10 + 48); 
        lcdData(10110010);
        lcdData((seconds/ 10) % 10 + 48);
        lcdData((seconds/ 1) % 10 + 48);
        lcd_write_string("           ");//para apagar os textos depois do numero
    }
    if (numTela == STATE_ALARME_1) {
        lcdCommand(0x80);
        lcd_write_string(msgs[numTela][idioma]);//escreve texto referente ao estado
        lcdCommand(0xC0);
        int tmp = adcRead(2)/4;//valor do pino analógico 1
        lcdData((tmp / 1000) % 10 + '0');
        lcdData((tmp / 100) % 10 + '0');
        lcdData((tmp / 10) % 10 + '0');
        lcdData((tmp / 1) % 10 + '0');
        lcd_write_string("           ");//para apagar os textos depois do numero
    }
    if (numTela == STATE_ALARME_1_Low) {
        lcdCommand(0x80);
        lcd_write_string(msgs[numTela][idioma]);//escreve texto referente ao estado
        lcdCommand(0xC0);
        lcdInt(getAlarmLevel_1_Low());//imprime o valor do alarme
        lcd_write_string("           ");//para apagar os textos depois do numero
    }
    if (numTela == STATE_ALARME_1_High) {
        lcdCommand(0x80);
        lcd_write_string(msgs[numTela][idioma]);//escreve texto referente ao estado
        lcdCommand(0xC0);
        lcdInt(getAlarmLevel_1_High());//imprime o valor do alarme
        lcd_write_string("           ");//para apagar os textos depois do numero
    }
    if (numTela == STATE_ALARME_2) {
        lcdCommand(0x80);
        lcd_write_string(msgs[numTela][idioma]);//escreve texto referente ao estado
        lcdCommand(0xC0);
        int tmp = adcRead(2)/4;//valor do pino analógico 2
        lcdData((tmp / 1000) % 10 + '0');
        lcdData((tmp / 100) % 10 + '0');
        lcdData((tmp / 10) % 10 + '0');
        lcdData((tmp / 1) % 10 + '0');
        lcd_write_string("           ");//para apagar os textos depois do numero
    }
    if (numTela == STATE_ALARME_2_Low) {
        lcdCommand(0x80);
        lcd_write_string(msgs[numTela][idioma]);//escreve texto referente ao estado
        lcdCommand(0xC0);
        lcdInt(getAlarmLevel_2_Low());//imprime o valor do alarme
        lcd_write_string("           ");//para apagar os textos depois do numero
    }
    if (numTela == STATE_ALARME_2_High) {
        lcdCommand(0x80);
        lcd_write_string(msgs[numTela][idioma]);//escreve texto referente ao estado
        lcdCommand(0xC0);
        lcdInt(getAlarmLevel_2_High());//imprime o valor do alarme
        lcd_write_string("           ");//para apagar os textos depois do numero
    }
    if (numTela == STATE_IDIOMA) {
        lcdCommand(0x80);
        lcd_write_string(msgs[numTela][idioma]);//escreve texto referente ao estado
        lcdCommand(0xC0);
        if (getLanguage() == 0) {//escreve a língua escolhida
            lcd_write_string("Portugues       ");
        }
        if (getLanguage() == 1) {
            lcd_write_string("English         ");
        }
    }

    //mesma função do lcd poprém em serial
    if (numTela == STATE_TEMPO) {
        int hours = getHours();
        int minutes = getMinutes();
        int seconds = getSeconds(); 
        serialSend('\n');
        serial_string(msgs[numTela][idioma]);
        serialSend('\n');
        serialSend('\r');
        serialSend((hours/ 10) % 10 + 48);
        serialSend((hours/ 1) % 10 + 48); 
        serialSend(10110010);
        serialSend((minutes/ 10) % 10 + 48);
        serialSend((minutes/ 1) % 10 + 48); 
        serialSend(10110010);
        serialSend((seconds/ 10) % 10 + 48);
        serialSend((seconds/ 1) % 10 + 48);
    }
    if (numTela == STATE_ALARME_1) {
        serialSend('\n');
        serial_string(msgs[numTela][idioma]);
        serialSend('\n');
        serialSend('\r');
        serialSend((adcRead(2)/ 1000) % 10 + '0');
        serialSend((adcRead(2)/ 100) % 10 + '0');
        serialSend((adcRead(2)/ 10) % 10 + '0');
        serialSend((adcRead(2)/ 1) % 10 + '0');
    }
    if (numTela == STATE_ALARME_1_Low) {
        serialSend('\n');
        serial_string(msgs[numTela][idioma]);
        serialSend('\n');
        serialSend('\r');
        serialInt(getAlarmLevel_1_Low());
    }
    if (numTela == STATE_ALARME_1_High) {
        serialSend('\n');
        serial_string(msgs[numTela][idioma]);
        serialSend('\n');
        serialSend('\r');
        serialInt(getAlarmLevel_1_High());
    }
    if (numTela == STATE_ALARME_2) {
        serialSend('\n');
        serial_string(msgs[numTela][idioma]);
        serialSend('\n');
        serialSend('\r');
        serialSend((adcRead(2)/ 1000) % 10 + '0');
        serialSend((adcRead(2)/ 100) % 10 + '0');
        serialSend((adcRead(2)/ 10) % 10 + '0');
        serialSend((adcRead(2)/ 1) % 10 + '0');
    }
    if (numTela == STATE_ALARME_2_Low) {
        serialSend('\n');
        serial_string(msgs[numTela][idioma]);
        serialSend('\n');
        serialSend('\r');
        serialInt(getAlarmLevel_2_Low());
    }
    if (numTela == STATE_ALARME_2_High) {
        serialSend('\n');
        serial_string(msgs[numTela][idioma]);
        serialSend('\n');
        serialSend('\r');
        serialInt(getAlarmLevel_2_High());
    }
    if (numTela == STATE_IDIOMA) {
        serialSend('\n');
        serial_string(msgs[numTela][idioma]);
        serialSend('\n');
        serialSend('\r');
        if (getLanguage() == 0) {
            serial_string("Portugues       ");
        }
        if (getLanguage() == 1) {
            serial_string("English         ");
        }
        
    }
    
   serialSend('\n');
   serialSend('\r');    
   serialSend('\n'); 
   serialSend('\r');
    
    
    
}
