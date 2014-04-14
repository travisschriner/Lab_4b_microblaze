/*
 * main.c
 *
 *  Created on: Apr 8, 2014
 *      Author: C15Travis.Schriner
 */

#include <xuartlite_l.h>
#include <xparameters.h>
#include <xil_io.h>
#include "head.h"

unsigned char nextLine = 0x0A;
unsigned char carryReturn = 0x0D;
unsigned char space = 0x20;

int main(void)
{
	while(1)
	{
		unsigned char c, d, e;
		c = XUartLite_RecvByte(0x84000000);
		XUartLite_SendByte(0x84000000, c);

		d = XUartLite_RecvByte(0x84000000);
		XUartLite_SendByte(0x84000000, d);


		e = XUartLite_RecvByte(0x84000000);
		XUartLite_SendByte(0x84000000, e);

		led(c,d,e);
		swt(c,d,e);
		vga(c,d,e);

		XUartLite_SendByte(0x84000000, nextLine);
		XUartLite_SendByte(0x84000000, carryReturn);





	}
//Xil_Out32(0x83000000, c);
	return 0;
}

unsigned char led(unsigned char a, unsigned char b, unsigned char c){
	if(a=='l' && b=='e' && c=='d'){
		unsigned char upper, lower;
		XUartLite_SendByte(0x84000000, space);
		upper = XUartLite_RecvByte(0x84000000);
		XUartLite_SendByte(0x84000000, upper);
		lower = XUartLite_RecvByte(0x84000000);
		XUartLite_SendByte(0x84000000, lower);
		upper = upperOut(upper);
		lower = lowerOut(lower);
		Xil_Out32(0x83000000, upper&lower);
	}
	return 0;
}

//C2C Jason Mossing explained that doing math wasn't working
//for some reason so we just had to make a big cascading if statement.
unsigned char upperOut(unsigned char a){

	if(a == '0'){
		return 0b00001111;
	}
	else if(a == '1'){
		return 0b00011111;
	}
	else if(a == '2'){
		return 0b00101111;
	}
	else if(a == '3'){
		return 0b00111111;
	}
	else if(a == '4'){
		return 0b01001111;
	}
	else if(a == '5'){
		return 0b01011111;
	}
	else if(a == '6'){
		return 0b01101111;
	}
	else if(a == '7'){
		return 0b01111111;
	}
	else if(a == '8'){
		return 0b10001111;
	}
	else if(a == '9'){
		return 0b10011111;
	}
	else if(a == 'A'){
		return 0b10101111;
	}
	else if(a == 'B'){
		return 0b10111111;
	}
	else if(a == 'C'){
		return 0b11001111;
	}
	else if(a == 'D'){
		return 0b11011111;
	}
	else if(a == 'E'){
		return 0b11101111;
	}
	else{
		return 0b11111111;
	}
}

unsigned char lowerOut(unsigned char a){

	if(a == '0'){
		return 0b11110000;
	}
	else if(a == '1'){
		return 0b11110001;
	}
	else if(a == '2'){
		return 0b11110010;
	}
	else if(a == '3'){
		return 0b11110011;
	}
	else if(a == '4'){
		return 0b11110100;
	}
	else if(a == '5'){
		return 0b11110101;
	}
	else if(a == '6'){
		return 0b11110110;
	}
	else if(a == '7'){
		return 0b11110111;
	}
	else if(a == '8'){
		return 0b11111000;
	}
	else if(a == '9'){
		return 0b11111001;
	}
	else if(a == 'A'){
		return 0b11111010;
	}
	else if(a == 'B'){
		return 0b11111011;
	}
	else if(a == 'C'){
		return 0b11111100;
	}
	else if(a == 'D'){
		return 0b11111101;
	}
	else if(a == 'E'){
		return 0b11111110;
	}
	else{
		return 0b11111111;
	}
}

unsigned char swt(unsigned char a, unsigned char b, unsigned char c){
	if(a=='s' && b=='w' && c=='t'){
		unsigned char upper, lower;
		XUartLite_SendByte(0x84000000, space);
		unsigned char switchPosition = Xil_In8(0x83000004);
		upper = topNibble(switchPosition);
		lower = bottomNibble(switchPosition);
		upper = topNibbleToAscii(upper);
		lower = bottomNibbleToAscii(lower);
		XUartLite_SendByte(0x84000000, upper);
		XUartLite_SendByte(0x84000000, lower);
		upper = upperOut(upper);
		lower = lowerOut(lower);
		Xil_Out32(0x83000000, upper&lower);



	}
	return 0;
}

unsigned char topNibble(unsigned char ascii){
	unsigned char top;
	top = ascii & 0b11110000;
	return top;
}

unsigned char bottomNibble(unsigned char ascii){
	unsigned char btm;
	btm = ascii & 0b00001111;
	return btm;
}

unsigned char topNibbleToAscii(unsigned char a){
	if(a == 0b00000000){
		return '0';
	}
	else if(a == 0b00010000){
		return '1';
	}
	else if(a == 0b00100000){
		return '2';
	}
	else if(a == 0b00110000){
		return '3';
	}
	else if(a == 0b01000000){
		return '4';
	}
	else if(a == 0b01010000){
		return '5';
	}
	else if(a == 0b01100000){
		return '6';
	}
	else if(a == 0b01110000){
		return '7';
	}
	else if(a == 0b10000000){
		return '8';
	}
	else if(a == 0b10010000){
		return '9';
	}
	else if(a == 0b10100000){
		return 'A';
	}
	else if(a == 0b10110000){
		return 'B';
	}
	else if(a == 0b11000000){
		return 'C';
	}
	else if(a == 0b11010000){
		return 'D';
	}
	else if(a == 0b11100000){
		return 'E';
	}
	else{
		return 'F';
	}
}

unsigned char bottomNibbleToAscii(unsigned char a){
	if(a == 0b00000000){
		return '0';
	}
	else if(a == 0b00000001){
		return '1';
	}
	else if(a== 0b00000010){
		return '2';
	}
	else if(a == 0b00000011){
		return '3';
	}
	else if(a == 0b00000100){
		return '4';
	}
	else if(a == 0b00000101){
		return '5';
	}
	else if(a == 0b00000110){
		return '6';
	}
	else if(a == 0b00000111){
		return '7';
	}
	else if(a == 0b00001000){
		return '8';
	}
	else if(a == 0b00001001){
		return '9';
	}
	else if(a == 0b00001010){
		return 'A';
	}
	else if(a == 0b00001011){
		return 'B';
	}
	else if(a == 0b00001100){
		return 'C';
	}
	else if(a == 0b00001101){
		return 'D';
	}
	else if(a == 0b00001110){
		return 'E';
	}
	else{
		return 'F';
	}
}
unsigned char vga(unsigned char a, unsigned char b, unsigned char c){
	if(a=='v' && b=='g' && c=='a'){



	}
	return 0;
}
