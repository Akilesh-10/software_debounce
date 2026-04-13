#include <stdint.h>
#include "RCC_Driver.h"
#include "GPIO_Driver.h"

#include "stm32f407xg.h"

void delay(volatile int t)
{
	for(int i = 0; i < t; i++);
}

int main(void)
{
	/* Enable clocks */
	RCC->AHB1ENR |= (1 << 0); // GPIOA
	RCC->AHB1ENR |= (1 << 3); // GPIOD

	/* PA0 → Input */
	GPIOA->MODER &= ~(0x3 << (2 * 0));

	/* PD12 → Output */
	GPIOD->MODER &= ~(0x3 << (2 * 12));
	GPIOD->MODER |=  (0x1 << (2 * 12));

	while(1)
	{
		if(GPIOA->IDR & (1 << 0)) // button pressed
		{
			delay(50000); // debounce delay

			// check again
			if(GPIOA->IDR & (1 << 0))
			{
				GPIOD->ODR ^= (1 << 12); // toggle LED

				// wait until release
				while(GPIOA->IDR & (1 << 0));
			}
		}
	}
}