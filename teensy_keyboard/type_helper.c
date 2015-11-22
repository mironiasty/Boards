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




void pressKeysWithKeyboard(uint8_t key, uint8_t modifier)
{
	usb_keyboard_press(key, modifier);
	_delay_ms(10);
}

void tepeText(char* text)
{
	while(*text)
	{
		typeLetter(*text, &pressKeysWithKeyboard);
		*text++;
	}
	
}

void typeLetter(char letter, void (*pressKeys)(uint8_t, uint8_t))
{
	if(letter >= 97 && letter <= 122)//a-z
	{
		pressKeys(letter - 93, 0);
	}
	else if(letter >= 65 && letter <= 90)//A-Z
	{
		pressKeys(letter - 61, KEY_LEFT_SHIFT);
	}
	else if(letter >= 49 && letter <= 57)//1-9
	{
		pressKeys(letter - 19, 0);
	}
	else{
		switch(letter){
			case 10:
				pressKeys(KEYPAD_ENTER, 0);
				break;
			case 32: //space
				pressKeys(KEY_SPACE, 0);
				break;
			case 33: //!
				pressKeys(KEY_1, KEY_LEFT_SHIFT);
				break;
			case 34: //"
				pressKeys(KEY_QUOTE, KEY_LEFT_SHIFT);
				break;
			case 35: //#
				pressKeys(KEY_3, KEY_LEFT_SHIFT);
				break;
			case 36: //$
				pressKeys(KEY_4, KEY_LEFT_SHIFT);
				break;
			case 37: //%
				pressKeys(KEY_5, KEY_LEFT_SHIFT);
				break;
			case 38: //&
				pressKeys(KEY_7, KEY_LEFT_SHIFT);
				break;
			case 39: //'
				pressKeys(KEY_QUOTE, 0);
				break;
			case 40: //(
				pressKeys(KEY_9, KEY_LEFT_SHIFT);
				break;
			case 41: //)
				pressKeys(KEY_0, KEY_LEFT_SHIFT);
				break;
			case 42: //*
				pressKeys(KEY_8, KEY_LEFT_SHIFT);
				break;
			case 43: //+
				pressKeys(KEY_EQUAL, KEY_LEFT_SHIFT);
				break;
			case 44: //,
				pressKeys(KEY_COMMA, 0);
				break;
			case 45: //-
				pressKeys(KEY_MINUS, 0);
				break;
			case 46: //.
				pressKeys(KEY_PERIOD, 0);
				break;
			case 47: // /
				pressKeys(KEY_SLASH, 0);
				break;
			case 48: // 0
				pressKeys(KEY_0, 0);
				break;
			case 58: // :
				pressKeys(KEY_SEMICOLON, KEY_LEFT_SHIFT);
				break;
			case 59: // ;
				pressKeys(KEY_SEMICOLON, 0);
				break;
			case 60: // <
				pressKeys(KEY_COMMA, KEY_LEFT_SHIFT);
				break;
			case 61: // =
				pressKeys(KEY_EQUAL, 0);
				break;
			case 62: // >
				pressKeys(KEY_PERIOD, KEY_LEFT_SHIFT);
				break;
			case 63: // ?
				pressKeys(KEY_SLASH, KEY_LEFT_SHIFT);
				break;
			case 64: // @
				pressKeys(KEY_2, KEY_LEFT_SHIFT);
				break;
			case 91: // [
				pressKeys(KEY_LEFT_BRACE, 0);
				break;
			case 92: // \
				pressKeys(KEY_BACKSLASH, 0);
				break;
			case 93: // ]
				pressKeys(KEY_RIGHT_BRACE, 0);
				break;
			case 94: // ^
				pressKeys(KEY_6, KEY_LEFT_SHIFT);
				break;
			case 95: // _
				pressKeys(KEY_MINUS, KEY_LEFT_SHIFT);
				break;
			case 96: // `
				pressKeys(KEY_TILDE, 0);
				break;
			case 123: // {
				pressKeys(KEY_LEFT_BRACE, KEY_LEFT_SHIFT);
				break;
			case 124: // |
				pressKeys(KEY_BACKSLASH, KEY_LEFT_SHIFT);
				break;
			case 125: // }
				pressKeys(KEY_RIGHT_BRACE, KEY_LEFT_SHIFT);
				break;
			case 126: // ~
				pressKeys(KEY_TILDE, KEY_LEFT_SHIFT);
				break;
			default:
				pressKeys(KEY_L, KEY_LEFT_ALT);
				break;
		}
	}
}


