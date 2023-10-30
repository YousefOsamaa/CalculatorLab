

#include <avr/io.h>
#include "../Library/STD.h"
#include "../Library/BitMath.h"
#include "Calculator.h"
#define F_CPU 16000000UL

int main(void)
{
	
	CalculatorInitialzie();

	Calculator();
	
}

