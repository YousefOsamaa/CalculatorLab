#ifndef F_CPU
#define F_CPU 16000000UL // 16 MHz clock speed
#endif

#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>

//Macros for reconfigurations
#define lcd_port PORTD
#define lcd_port_dir DDRD
#define LCD_RS      0x20
#define LCD_EN      0x80

// Functions Prototypes
void lcd_reset ();
void LCD_Init ();
void lcd_cmd (char cmd);
void lcd_data (unsigned char dat);
void LCD_GoToXY (char posX,char posY);
void LCD_Clear (void);
void LCD_PutChar (unsigned char data);
void LCD_PutStr (char *str);
void LCD_PutConst (const char *str);
void LCD_Custom_Char (unsigned char loc, unsigned char *msg);
