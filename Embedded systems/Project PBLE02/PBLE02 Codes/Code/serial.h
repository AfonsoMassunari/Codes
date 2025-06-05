#ifndef SERIAL_H
	#define SERIAL_H

	void serialSend(unsigned char c);
	unsigned char serialRead(void);
	void serialInit(void);
    void serialInt(int val);
    void serial_string(const char *str);
    void serial_string2(char msg[]);
#endif