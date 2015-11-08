/* Keyboard Typer
 * http://mironiasty.net/tags/teensy
 * Copyright (c) 2015 Miron Pawlik
 * 
 */
#include <stdlib.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "type_helper.h"
#include "usb_keyboard.h"

void assignKey(uint8_t* keys, int place, int keyNum, int modifier)
{
	keys[place*2] = keyNum;
	keys[place*2+1] = modifier;
}

void convertStrningToKeys(char* text, uint8_t* keys, int size)
{
	for(int i =0; i<size; i++)
	{
		if(text[i] >= 97 && text[i]<=122)//a-z
		{
			assignKey(keys, i, text[i]-93, 0);
		}
		else if(text[i] >= 65 && text[i]<=90)//A-Z
		{
			assignKey(keys, i, text[i]-61, KEY_LEFT_SHIFT);
		}
		else if(text[i] >= 49 && text[i]<=57)//1-9
		{
			assignKey(keys, i, text[i]-19, 0);
		}
		else{
			switch(text[i]){
				case 10:
					assignKey(keys, i, KEYPAD_ENTER, 0);
					break;
				case 32: //space
					assignKey(keys, i, KEY_SPACE, 0);
					break;
				case 33: //!
					assignKey(keys, i, KEY_1, KEY_LEFT_SHIFT);
					break;
				case 34: //"
					assignKey(keys, i, KEY_QUOTE, KEY_LEFT_SHIFT);
					break;
				case 35: //#
					assignKey(keys, i, KEY_3, KEY_LEFT_SHIFT);
					break;
				case 36: //$
					assignKey(keys, i, KEY_4, KEY_LEFT_SHIFT);
					break;
				case 37: //%
					assignKey(keys, i, KEY_5, KEY_LEFT_SHIFT);
					break;
				case 38: //&
					assignKey(keys, i, KEY_7, KEY_LEFT_SHIFT);
					break;
				case 39: //'
					assignKey(keys, i, KEY_QUOTE, 0);
					break;
				case 40: //(
					assignKey(keys, i, KEY_9, KEY_LEFT_SHIFT);
					break;
				case 41: //)
					assignKey(keys, i, KEY_0, KEY_LEFT_SHIFT);
					break;
				case 42: //*
					assignKey(keys, i, KEY_8, KEY_LEFT_SHIFT);
					break;
				case 43: //+
					assignKey(keys, i, KEY_EQUAL, KEY_LEFT_SHIFT);
					break;
				case 44: //,
					assignKey(keys, i, KEY_COMMA, 0);
					break;
				case 45: //-
					assignKey(keys, i, KEY_MINUS, 0);
					break;
				case 46: //.
					assignKey(keys, i, KEY_PERIOD, 0);
					break;
				case 47: // /
					assignKey(keys, i, KEY_SLASH, 0);
					break;
				case 48: // 0
					assignKey(keys, i, KEY_0, 0);
					break;
				case 58: // :
					assignKey(keys, i, KEY_SEMICOLON, KEY_LEFT_SHIFT);
					break;
				case 59: // ;
					assignKey(keys, i, KEY_SEMICOLON, 0);
					break;
				case 60: // <
					assignKey(keys, i, KEY_COMMA, KEY_LEFT_SHIFT);
					break;
				case 61: // =
					assignKey(keys, i, KEY_EQUAL, 0);
					break;
				case 62: // >
					assignKey(keys, i, KEY_PERIOD, KEY_LEFT_SHIFT);
					break;
				case 63: // ?
					assignKey(keys, i, KEY_SLASH, KEY_LEFT_SHIFT);
					break;
				case 64: // @
					assignKey(keys, i, KEY_2, KEY_LEFT_SHIFT);
					break;
				case 91: // [
					assignKey(keys, i, KEY_LEFT_BRACE, 0);
					break;
				case 92: // \
					assignKey(keys, i, KEY_BACKSLASH, 0);
					break;
				case 93: // ]
					assignKey(keys, i, KEY_RIGHT_BRACE, 0);
					break;
				case 94: // ^
					assignKey(keys, i, KEY_6, KEY_LEFT_SHIFT);
					break;
				case 95: // _
					assignKey(keys, i, KEY_MINUS, KEY_LEFT_SHIFT);
					break;
				case 96: // `
					assignKey(keys, i, KEY_TILDE, 0);
					break;
				case 123: // {
					assignKey(keys, i, KEY_LEFT_BRACE, KEY_LEFT_SHIFT);
					break;
				case 124: // |
					assignKey(keys, i, KEY_BACKSLASH, KEY_LEFT_SHIFT);
					break;
				case 125: // }
					assignKey(keys, i, KEY_RIGHT_BRACE, KEY_LEFT_SHIFT);
					break;
				case 126: // ~
					assignKey(keys, i, KEY_TILDE, KEY_LEFT_SHIFT);
					break;
				default:
					assignKey(keys, i, KEY_L, KEY_LEFT_ALT);
					break;
			}
		}
	}
}

void writeKeys(uint8_t* keys, int textSize)
{
	for(int i =0; i<textSize; i++){
		usb_keyboard_press(keys[i*2], keys[i*2+1]);
		_delay_ms(40);
	}
}