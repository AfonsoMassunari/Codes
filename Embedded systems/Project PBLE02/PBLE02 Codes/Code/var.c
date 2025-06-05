#include "var.h"
#include "ds1307.h"


static char state;
static char language;
static int alarmLevel_1_High;
static int alarmLevel_2_High;
static int alarmLevel_1_Low;
static int alarmLevel_2_Low;
static int pos;

void varInit(void) { //valores iniciais das variáveis
    state = 0;
    pos = 0;
    setAlarmLevel_1_Low(64);
    setAlarmLevel_2_Low(64);
    setAlarmLevel_1_High(192);
    setAlarmLevel_2_High(192);
}

//gets e sets das variáveis
int getPos(void) {
    return pos;
}

void setPos(int newPos) {
    pos = newPos;
}

char getState(void) {
    return state;
}
void setState(char newState) {
    state = newState;
}

int getAlarmLevel_1_Low(void) {
    alarmLevel_1_Low = dsReadData(0x20);
    return alarmLevel_1_Low;
}
void setAlarmLevel_1_Low(int newAlarmLevel) {
    if(newAlarmLevel<258)
    dsWriteData(newAlarmLevel,0x20);
}

int getAlarmLevel_1_High(void) {
    alarmLevel_1_High = dsReadData(0x21);
    return alarmLevel_1_High;
}
void setAlarmLevel_1_High(int newAlarmLevel) {
    if(newAlarmLevel<258)
    dsWriteData(newAlarmLevel,0x21);
}

int getAlarmLevel_2_Low(void) {
    alarmLevel_2_Low = dsReadData(0x22);
    return alarmLevel_2_Low;
}

void setAlarmLevel_2_Low(int newAlarmLevel) {
    if(newAlarmLevel<258)
    dsWriteData(newAlarmLevel,0x22);
}

int getAlarmLevel_2_High(void) {
    alarmLevel_2_High = dsReadData(0x23);
    return alarmLevel_2_High;
}
void setAlarmLevel_2_High(int newAlarmLevel) {
    if(newAlarmLevel<258)
    dsWriteData(newAlarmLevel,0x23);
}

char getLanguage(void){
    language = dsReadData(0x24)%2;
    return language;
}
void setLanguage(char newLanguage){
   dsWriteData((newLanguage%2),0x24);
}
