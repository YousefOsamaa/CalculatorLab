
#ifndef CALCULATOR_H_
#define CALCULATOR_H_

typedef enum
{
    CALCULATOR_FIRST_DIGIT,
    CALCULATOR_OPERATION,
    CALCULATOR_SECOND_DIGIT,
    CALCULATOR_EQUAL_OPERATOR,
    CALCULATOR_RESULT,
    CALCULATOR_CLEAR_RESULT,

}State_t;

extern void CalculatorInitialzie(void);

extern void Calculator(void);





#endif 