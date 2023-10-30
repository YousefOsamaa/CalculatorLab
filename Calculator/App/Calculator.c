#include "../Library/BitMath.h"
#include "../Library/STD.h"

#include "../LCD/LCD.h"
#include "../keypad/keypad.h"

#include "Calculator.h"



static void vid_ConvertFloatToInteger(f32* Copy_f32_DecimalDigits, u8 Copy_u8_FloatPrecision);


void CalculatorInitialzie(void)
{
    LCD_Init();
}

void Calculator(void)
{
    State_t CurrentState = CALCULATOR_FIRST_DIGIT;

    u8 KeyPressed = KEYPAD_DEFAULT_VALUE;

    u8 FirstDigit;
    u8 SecondDigit;
    u8 Operation;

    while (1)
    {

        switch (CurrentState)
        {
            case CALCULATOR_FIRST_DIGIT:
            {

                KeyPressed = keypad_scan();

                if ( (KeyPressed >= '0' ) && (KeyPressed <= '9') )
                {
                    FirstDigit = KeyPressed - 48;

                    LCD_GoToXY(0,0);

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
                u8 Result;

                switch (Operation)
                {
                    case '+':
                    {
                        Result = FirstDigit + SecondDigit;

                        LCD_GoToXY(0, 8);

                        LCD_PutChar(Result + 48);

                        break;
                    }

                    case '-':
                    {

                        Result = FirstDigit - SecondDigit;

                        LCD_GoToXY(0, 8);

                        LCD_PutChar(Result + 48);

                        break;
                    }

                    case 'x':
                    {

                        Result = FirstDigit * SecondDigit;

                        LCD_GoToXY(0, 8);

                        LCD_PutChar(Result + 48);

                        break;
                    }

                    case '/':
                    {
                        f32 FloatResultPart = (f32)FirstDigit / SecondDigit;

                        u8 IntegerResultPart = FloatResultPart;

                        FloatResultPart = FloatResultPart - IntegerResultPart;

                        vid_ConvertFloatToInteger(&FloatResultPart, 2);



                        LCD_GoToXY(0, 8);

                        LCD_PutChar(IntegerResultPart + 48);

                        if(FloatResultPart != 0)
                        {
                            LCD_PutChar('.');

                            //Using IntegerResultPart for safety
                            IntegerResultPart = FloatResultPart;
                            
                            while (IntegerResultPart)
                            {
                                LCD_PutChar((IntegerResultPart % 10) + 48);

                                IntegerResultPart /= 10;
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

static void vid_ConvertFloatToInteger(f32* Copy_f32_DecimalDigits, u8 Copy_u8_FloatPrecision)
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

static void PrintResult(f32 Copy_f32_Result)
{

}