/*
 * head.h
 *
 *  Created on: Apr 9, 2014
 *      Author: C15Travis.Schriner
 */

#ifndef HEAD_H_
#define HEAD_H_


unsigned char led(unsigned char a, unsigned char b, unsigned char c);
unsigned char upperOut(unsigned char a);
unsigned char lowerOut(unsigned char a);

unsigned char swt(unsigned char a, unsigned char b, unsigned char c);
unsigned char topNibbleToAscii(unsigned char a);
unsigned char bottomNibbleToAscii(unsigned char a);
unsigned char topNibble(unsigned char ascii);
unsigned char bottomNibble(unsigned char ascii);

unsigned char vga(unsigned char a, unsigned char b, unsigned char c);

#endif /* HEAD_H_ */
