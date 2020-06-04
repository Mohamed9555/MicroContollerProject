#include "stdint.h"
#include <stdio.h>
#include <string.h>
#include "keypad.h"
#include "C:/Keil_v5/EE319KwareSpring2020/inc/tm4c123gh6pm.h"
#define RED	0x02
//void SystemInit() {} // error cause it's defined in other file !!


void SysTick_init(void) {
	NVIC_ST_CTRL_R=0;
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R=0;
	NVIC_ST_CTRL_R=0x00000005;
}

void SysTick_Wait(uint32_t delay){
	NVIC_ST_RELOAD_R = delay - 1;
	NVIC_ST_CURRENT_R = 0;
	while((NVIC_ST_CTRL_R & 0x00010000) == 0){}
}

void SysTick_Wait_ten(uint32_t delay){
	for(int i=0; i < delay; i++){
		SysTick_Wait(800.000);
	}
}

void init(void) {
	uint32_t delay;
	SYSCTL_RCGCGPIO_R |= 0x21; // clk to port f // 5
	delay=1;//dummy var
	// unlock reg // don't unlock port c !!!!
	GPIO_PORTF_LOCK_R = 0x4C4F434B; // unlocks F
	GPIO_PORTF_CR_R = 0x1F; // decide which pins to enable data in  
	GPIO_PORTF_AFSEL_R = 0; // just i/o
	GPIO_PORTF_PCTL_R = 0; 
	GPIO_PORTF_AMSEL_R = 0;
	GPIO_PORTF_DIR_R = 0x0E; // define PF1,PF2,PF3 as output
	GPIO_PORTF_DEN_R = 0x1F;
	GPIO_PORTF_PUR_R = 0x11; // 2 switches at pin 1 and 4
	///////
	///////
	/// for keypad
	GPIO_PORTA_LOCK_R = 0x4C4F434B; // unlocks A
	GPIO_PORTA_CR_R = 0xFF; // decide which pins to enable data in  
	GPIO_PORTA_AFSEL_R = 0; // just i/o
	GPIO_PORTA_PCTL_R = 0; 
	GPIO_PORTA_AMSEL_R = 0;
	GPIO_PORTA_DIR_R = 0x00; // 
	GPIO_PORTA_DEN_R = 0xFF;
}


void UART_init(void){
	uint32_t m;
	SYSCTL_RCGCUART_R |= 0X01;
	m=1;
	SYSCTL_RCGCGPIO_R |= 0X01; 
	m=2;
	UART0_CTL_R &=~0X01;
	UART0_IBRD_R=52;
	UART0_FBRD_R=5;
	UART0_LCRH_R=0x0070;
	UART0_CTL_R=0X301;
	GPIO_PORTB_AFSEL_R|=0X03;
	GPIO_PORTB_PCTL_R=(GPIO_PORTB_PCTL_R & 0XFFFFFF00) + 0X11;
	GPIO_PORTB_DEN_R |=0X03;
	GPIO_PORTB_AMSEL_R &= ~0X03;
}

char UART0_Read(void){

	while((UART0_FR_R & 0x0010) != 0){};
	return (char)(UART0_DR_R & 0xFF);	
}

void UART0_Write(char data){
	while((UART0_FR_R & 0x0020) != 0){};
	UART0_DR_R = data; 
}


void recieve(char *data){
	int counter = 0;
	data[0] = UART0_Read();
	while(data[counter] != '*'){
		data[counter] = UART0_Read();
		SysTick_Wait_ten(30);
		counter ++;
	}
}


int main (){
	init();
	UART_init();
	SysTick_init();
	char data[6];
	char user_password[4];
	char password[5];
	char *rooms_number;
	recieve(rooms_number); 
	SysTick_Wait_ten(100);
	while(1){
		recieve(data);
		SysTick_Wait_ten(100);
		int n = strlen(data);
		// check in
		if(data[1] == '1') {
			int position = 2;
			int c=0;
			while(c != n-1){
				password[c] = data[position+c];
				c++;
			}
		} /// PASS
		// check out or cleaning 
		else{
			if(data[1] == '0'){
				GPIO_PORTF_DATA_R = 0x00;
				password[0] = 'k';
			}
			else if (data[1] == '2') {
				GPIO_PORTF_DATA_R = RED;
			}
		}
		int i=0;
		while(i<5) {
			SysTick_Wait_ten(50);
			user_password[i] = Keypad_getpressed();
			i++;
		}
		/// user
		if(strcmp(user_password, password) == 0){
			GPIO_PORTF_DATA_R = RED;
		}
	}
}
	