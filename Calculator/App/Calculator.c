#include "../Library/BitMath.h"
#include "../Library/STD.h"

#include "../LCD/LCD.h"
#include "../keypad/keypad.h"

#include "Calculator.h"



void vid_ConvertFloatToInteger(f32* Copy_f32_DecimalDigits, u8 Copy_u8_FloatPrecision);

void vid_ReverseInteger(u32* Copy_pu32_Num);

u32 vid_CountNumber(u32 Num);



void CalculatorInitialzie(void)
{
    LCD_Init();
}

void Calculator(void)
{
    State_t CurrentState = CALCULATOR_FIRST_DIGIT;

    u8 KeyPressed = KEYPAD_DEFAULT_VALUE;

    s32 FirstDigit;
    s32 SecondDigit;
    u8 Operation;

    u8 NegativeFlag = False;
	
    while (1)
    {

        switch (CurrentState)
        {
            case CALCULATOR_FIRST_DIGIT:
            {

                KeyPressed = keypad_scan();


                if( KeyPressed == '-')
                {
                    LCD_GoToXY(0,0);

                    NegativeFlag = True;

                    LCD_PutChar('-');
                }
                else if ( (KeyPressed >= '0' ) && (KeyPressed <= '9') )
                {
                    
                    FirstDigit = (KeyPressed - 48);

                    if(NegativeFlag)
                    {
                        FirstDigit *= -1;

                        NegativeFlag = False;
                    }

                    LCD_PutChar(KeyPressed);

                    CurrentState = CALCULATOR_OPERATION;
                }

                KeyPressed = KEYPAD_DEFAULT_VALUE;

                break;
            }            

            case CALCULATOR_OPERATION:
            {
                KeyPressed = keypad_scan();

                if ( (KeyPressed == '+' ) || (KeyPressed == '-' ) || (KeyPressed == 'x' ) || (KeyPressed == '/' )  )
                {
                    Operation = KeyPressed;

                    LCD_GoToXY(0,2);

                    LCD_PutChar(KeyPressed);

                    CurrentState = CALCULATOR_SECOND_DIGIT;
                }

                KeyPressed = KEYPAD_DEFAULT_VALUE;

                break;
            }

            case CALCULATOR_SECOND_DIGIT:
            {
                KeyPressed = keypad_scan();

                if ( (KeyPressed >= '0' ) && (KeyPressed <= '9') )
                {
                    SecondDigit = KeyPressed - 48;

                    LCD_GoToXY(0,4);

                    LCD_PutChar(KeyPressed);

                    CurrentState = CALCULATOR_EQUAL_OPERATOR;
                }

                KeyPressed = KEYPAD_DEFAULT_VALUE;                

                break;
            }

            case CALCULATOR_EQUAL_OPERATOR:
            {
                KeyPressed = keypad_scan();

                if ( KeyPressed == '=' )
                {

                    LCD_GoToXY(0,6);

                    LCD_PutChar(KeyPressed);

                    CurrentState = CALCULATOR_RESULT;
                }

                KeyPressed = KEYPAD_DEFAULT_VALUE;    

                break;
            }
        
            case CALCULATOR_RESULT:
            {
                s32 Result;

                switch (Operation)
                {
                    case '+':
                    {
                        Result = FirstDigit + SecondDigit;
						
                        LCD_GoToXY(0, 8);

                        if(Result < 0 )
                        {
                            LCD_PutChar('-');

                            Result *= -1;

                        }   

						u32 Count = vid_CountNumber(Result);

                        vid_ReverseInteger(Result);

                        while (Result)
                        {
                            LCD_PutChar((Result % 10) + 48);

                            Result /= 10;

                            Count--;    
                        }

                        while(Count)
                        {
                            LCD_PutChar('0');
                            
                            Count--;
                        }

                        break;
                    }

                    case '-':
                    {

                        Result = FirstDigit - SecondDigit;

                        LCD_GoToXY(0, 8);

                        if(Result < 0 )
                        {
                            LCD_PutChar('-');

                            Result *= -1;
                        }                        
                        
                        u32 Count = vid_CountNumber(Result);

                        vid_ReverseInteger(&Result);

                        while (Result)
                        {
                            LCD_PutChar((Result % 10) + 48);

                            Result /= 10;

                            Count--;    
                        }

                        while(Count)
                        {
                            LCD_PutChar('0');
                            
                            Count--;
                        }

                        break;
                    }

                    case 'x':
                    {
                        
                        Result = FirstDigit * SecondDigit;

                        LCD_GoToXY(0, 8);

                        if(Result < 0 )
                        {
                            LCD_PutChar('-');

                            Result *= -1;
                        }                        
                        
                        u32 Count = vid_CountNumber(Result);

                        vid_ReverseInteger(&Result);

                        while (Result)
                        {
                            LCD_PutChar((Result % 10) + 48);

                            Result /= 10;

                            Count--;    
                        }

                        while(Count)
                        {
                            LCD_PutChar('0');
                            
                            Count--;
                        }

                        break;
                    }

                    case '/':
                    {
                        f32 FloatResultPart = (((f32)FirstDigit) / SecondDigit);

                        LCD_GoToXY(0, 8);

                        if(FloatResultPart < 0 )
                        {
                            LCD_PutChar('-');

                            FloatResultPart *= -1;
                        }   

                        u32 IntegerResultPart = FloatResultPart;

                        FloatResultPart = FloatResultPart - (f32)IntegerResultPart;

                        u8 DecimalDigitsCount = FLOAT_PRECISION;

                        vid_ConvertFloatToInteger(&FloatResultPart, DecimalDigitsCount);
                        
                        LCD_PutChar(IntegerResultPart + 48);

                        if(FloatResultPart != 0)
                        {
                            LCD_PutChar('.');

                            //Using IntegerResultPart for safety
                            IntegerResultPart = FloatResultPart;

                            vid_ReverseInteger(&IntegerResultPart);
                            
                            while (DecimalDigitsCount)
                            {
                                LCD_PutChar((IntegerResultPart % 10) + 48);

                                IntegerResultPart /= 10;

                                DecimalDigitsCount--;
                            }

                            //To Print any lost zeroes when the num was reversed
                            while(DecimalDigitsCount)
                            {
                                LCD_PutChar('0');

                                DecimalDigitsCount--;
                            }
                            
                        }

                        break;
                    }
 
                }

                CurrentState = CALCULATOR_CLEAR_RESULT;

                break;
            }
        
            case CALCULATOR_CLEAR_RESULT:
            {

                KeyPressed = keypad_scan();

                if ( KeyPressed == '*' )
                {

                    LCD_Clear();

                    CurrentState = CALCULATOR_FIRST_DIGIT;
                }

                KeyPressed = KEYPAD_DEFAULT_VALUE;    

                break;
            }

        }

    }
}

void vid_ConvertFloatToInteger(f32* Copy_f32_DecimalDigits, u8 Copy_u8_FloatPrecision)
{
    u32 Local_u32_CheckVariable = 0;
    f32 Local_f32_TempDecimalDigits;

    if(Copy_f32_DecimalDigits)
    {
        while((*Copy_f32_DecimalDigits - Local_u32_CheckVariable) || ( Copy_u8_FloatPrecision == 0))
        {
            *Copy_f32_DecimalDigits *= 10;

            
            Local_u32_CheckVariable = (u32)(*Copy_f32_DecimalDigits);

            Copy_u8_FloatPrecision--;

        }
    

        Local_f32_TempDecimalDigits = *Copy_f32_DecimalDigits - Local_u32_CheckVariable;
        
        Local_f32_TempDecimalDigits *= 10;

        // First decimal digit is acquired
        Local_u32_CheckVariable = Local_f32_TempDecimalDigits;

        //Rounding number
        if(Local_u32_CheckVariable >= 5)
        {
            *Copy_f32_DecimalDigits++;
        }
	}
}

void vid_ReverseInteger(u32* Copy_pu32_Num)
{
    //Must cast any to u32 when using this function

    if(Copy_pu32_Num)
    {   
        u32 Local_u32_ReversedNum = 0;
        while(*Copy_pu32_Num)
        {
            Local_u32_ReversedNum = (Local_u32_ReversedNum*10) + (*Copy_pu32_Num % 10);
            *Copy_pu32_Num /= 10;
        }

        *Copy_pu32_Num = Local_u32_ReversedNum;

    }

}

u32 vid_CountNumber(u32 Num)
{
    u32 Count = 0;

    do
    {
        Num /= 10;

        Count++;

    }while(Num);

    return Count;

}