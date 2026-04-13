#include <stdint.h>
#include "RCC_Driver.h"
#include "GPIO_Driver.h"

#include "stm32f407xg.h"

int main(void)
{
	RCC->AHB1ENR |= (1 << 0); // GPIOA
	RCC->AHB1ENR |= (1 << 3); // GPIOD

	GPIOA->MODER &= ~(0x3 << (2 * 0));
	GPIOD->MODER &= ~(0x3 << (2 * 12));
	GPIOD->MODER |=  (0x1 << (2 * 12));

	uint8_t stable_count = 0;
	uint8_t state = 0;

	while(1)
	{
		if(GPIOA->IDR & (1 << 0))
		{
			stable_count++;
		}
		else
		{
			stable_count = 0;
		}

		if(stable_count > 100) // threshold
		{
			if(state == 0)
			{
				GPIOD->ODR ^= (1 << 12);
				state = 1;
			}
		}
		else
		{
			state = 0;
		}
	}
}
