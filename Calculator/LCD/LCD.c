#include "LCD.h"
char columnCount;
char lastPOSx;

void lcd_reset()
{
	    lcd_port_dir=0XFF;
        lcd_port = 0xFF;
        _delay_ms(20);
        lcd_port = 0x03+LCD_EN;
        lcd_port = 0x03;
        _delay_ms(10);
        lcd_port = 0x03+LCD_EN;
        lcd_port = 0x03;
        _delay_ms(1);
        lcd_port = 0x03+LCD_EN;
        lcd_port = 0x03;
        _delay_ms(1);
        lcd_port = 0x02+LCD_EN;
        lcd_port = 0x02;
        _delay_ms(1);
}

void LCD_Init(void)
{
	columnCount= 16;
	lastPOSx=0;
        lcd_reset();         // Call LCD reset
        lcd_cmd(0x28);       // 4-bit mode - 2 line - 5x7 font. 
        lcd_cmd(0x0c);       // Display no cursor - no blink.
        lcd_cmd(0x06);       // Automatic Increment - No Display shift.
        lcd_cmd(0x80);       // Address DDRAM with 0 offset 80h.
 }
 void lcd_cmd (char cmd)
{
        lcd_port = ((cmd >> 4) & 0x0F)|LCD_EN;
        lcd_port = ((cmd >> 4) & 0x0F);

        lcd_port = (cmd & 0x0F)|LCD_EN;
        lcd_port = (cmd & 0x0F);

        _delay_us(200);
        _delay_us(200);
}

//Print character
void lcd_data (unsigned char dat)
{
        lcd_port = (((dat >> 4) & 0x0F)|LCD_EN|LCD_RS);
        lcd_port = (((dat >> 4) & 0x0F)|LCD_RS);
       
        lcd_port = ((dat & 0x0F)|LCD_EN|LCD_RS);
        lcd_port = ((dat & 0x0F)|LCD_RS);

        _delay_us(200);
        _delay_us(200);
}

//Go to Location
void LCD_GoToXY(char posX,char posY)
{
    if (posX==0 ) 
        lcd_cmd((1<<7)+0x00+posY);
    else
	{
        lcd_cmd((1<<7)+0x40+posY);
	lastPOSx=1;
	}		
		_delay_us(40);
}

//Clears Page
void LCD_Clear(void)
{
	lcd_cmd(0x01);
	_delay_ms(2);
	lcd_cmd(0x02);
	_delay_ms(2);
}

//Prints Char
void LCD_PutChar(unsigned char data)
{
	lcd_data(data);
}

//Prints string
void LCD_PutStr( char *str)
{
	unsigned char i=0;
	
	while(*(str+i)!='\0'&&i<columnCount)
	{
	lcd_data(str[i]);
	i++;	
	}
	if (i>columnCount-1 && lastPOSx==0)
	{
		i=columnCount;
		LCD_GoToXY(1,0);
	
	while(*(str+i)!='\0')
	{
	lcd_data(str[i]);
	i++;	
	}
	}
	
}

void LCD_PutConst(const char *str)
{
	unsigned char i=0;
	
	while(*(str+i)!='\0'&& i<columnCount)
	{
	lcd_data(str[i]);
	i++;	
	}
	if (i>columnCount-1&&lastPOSx==0)
	{
		i=columnCount;
		LCD_GoToXY(1,0);
	
	while(*(str+i)!='\0')
	{
	lcd_data(str[i]);
	i++;	
	}
	}
}

void LCD_Custom_Char (unsigned char loc, unsigned char *msg)
{
	unsigned char i;
	if(loc<8)
	{
		lcd_cmd (0x40 + (loc*8));	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)	/* Write 8 byte for generation of 1 character */
		LCD_PutChar(msg[i]);
	}
}