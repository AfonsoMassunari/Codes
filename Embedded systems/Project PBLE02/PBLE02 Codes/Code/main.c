/*
 * File:   main.c
 * Author: Marcelo
 *
 * Created on 3 de Abril de 2023, 14:43
 */


#include <xc.h>
#include "Config.h"
#include "I2c.h"
#include "io.h"
#include "lcd.h"
#include "adc.h"
#include "bits.h"
#include "ds1307.h"
#include "event.h"
#include "output.h"
#include "keypad.h"
#include "stateMachine.h"
#include "var.h"
#include "serial.h"
#include <pic18f4550.h>

void main(void) {
    ADCON1 = 0x0f;
    i2cInit();
    lcdInit();
    dsInit();
    dsStartClock();
    adcInit();
    varInit();
    kpInit();
    smInit(); 
    outputInit();    
    dsWriteData(0x80,0);
    
    for(;;){  
       smLoop();//começa a máquina de estados
    }    
}