#ifndef VAR_H
#define	VAR_H
void varInit(void);
char getState(void);
void setState(char newState);
int getAlarmLevel_1_High(void);
void setAlarmLevel_1_High(int newAlarmLevel);
int getAlarmLevel_1_Low(void);
void setAlarmLevel_1_Low(int newAlarmLevel);
int getAlarmLevel_2_High(void);
void setAlarmLevel_2_High(int newAlarmLevel);
int getAlarmLevel_2_Low(void);
void setAlarmLevel_2_Low(int newAlarmLevel);
char getLanguage(void);
void setLanguage(char newLanguage);
char getBufferSize(void);
void setBufferSize(char newBufferSize);
int getPos(void);
void setPos(int newPos);
#endif	/* VAR_H */
