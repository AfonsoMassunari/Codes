#ifndef LCD_H
	#define LCD_H

	void lcdCommand(unsigned char cmd);
    
void lcdCommand4bits(unsigned char cmd, unsigned char data);
	void lcdData(unsigned char valor);
	void lcdInit(void);
    void lcd_write_string(const char *str);
    void lcdInt(int val);    
#endif