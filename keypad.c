#include "keypad.h"

/**** functions prototypes */////

#if(N_col==4)
static uint8 keypad_adjust_number_4x4 (uint8 button_number);
#elif(N_col==3)
static uint8 keypad_adjust_number_4x3 (uint8 button_number);
#endif	 
uint8 Keypad_getpressed(){
	uint8 col,row;
	while(1){
		for(col=0;col<N_col;col++){
			KeyPad_DIR = (0x10<<col);
			keypad_Digital_en = 0XFF;
			Keypad_pull_up = 0X0F;
			//// 3mlt kda 3shan kol mra f loop l col byt8yer f ana 3ayz a5le wa7d bs b zero w l ba2i b wa7d
			if(col==0){
				Keypad_port_out_in &=~(1<<(col+4));
				Keypad_port_out_in |=(0xE0); /// 3shan a5le a5r 3 coloumn b wa7ayed w zero 3la awl wa7d
			}
			if(col==1){
				Keypad_port_out_in &=~(1<<(col+4));
				Keypad_port_out_in |=(0xD0); /// 3shan a5le a5r 2 coloumn w awl wa7d b wa7ayed w zero 3la tani wa7d
			}
			if(col==2){
				Keypad_port_out_in &=~(1<<(col+4));
				Keypad_port_out_in |=(0xB0); /// 3shan a5le a5r 1 coloumn w awl atnen b wa7ayed w zero 3la talt wa7d
			}
			if(col==3){
			Keypad_port_out_in &=~(1<<(col+4));
			Keypad_port_out_in |=(0x70); /// 3shan a5le awl 3 coloumn b wa7ayed w zero 3la a5r wa7d
			}
			for(row=0;row<N_row;row++){
				if(BIT_IS_CLEAR(Keypad_port_out_in,row)){
					#if(N_col==4)
					return keypad_adjust_number_4x4((row*N_col)+col+1);
					#elif(N_col==3)
					return keypad_adjust_number_4x3 ((row*N_col)+col+1);
					#endif
					
				}
			}
		}
	}
}
			

#if(N_col==3)
static uint8 keypad_adjust_number_4x3 (uint8 button_number){
	switch(button_number){
		case 10: return '*';
		break;
		case 11: return  0;
		break;
		case 12: return '#';
		break;
		default : return button_number;
		break;
	}
}
#elif(N_col==4)
static uint8 keypad_adjust_number_4x4 (uint8 button_number){
	switch(button_number){
		case 1: return 7;
		break;
		case 2: return 8;
		break;
		case 3: return 9;
		break;
		case 4: return '%';
		break;
		case 5: return  4;
		break;
		case 6: return  5;
		break;
		case  7: return 6;
		break;
		case  8: return '*';
		break;
		case  9: return   1;
		break;
		case 10: return 2;
		break;
		case 11: return 3;
		break;
		case 12: return '-';
		break;
		case 13: return 13;
		break;
		case 14: return 0;
		break;
		case 15: return '=';
		break;
		case 16: return '+';
		break;
		default : return button_number;
		break;
	}
}
#endif