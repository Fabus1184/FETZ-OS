#include "kernel.h"

int crs = 0;

int cursor(){
	if(crs > BUFSIZE){
		crs=0;
	}
	return crs++;
}

int strlen(char*p)
{
	int count = 0;
	while (*p != '\0') {
	count++;
	p++;
}
return count;
}

uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color)
{
	uint16 ax = 0;
	uint8 ah = 0, al = 0;

	ah = back_color;
	ah <<= 4;
	ah |= fore_color;
	ax = ah;
	ax <<= 8;
	al = ch;
	ax |= al;

	return ax;
}

//clear video buffer array
void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color)
{
	uint32 i;
	for (i = 0; i < BUFSIZE; i++)
	{
		(*buffer)[i] = vga_entry(0, fore_color, back_color);
	}
}

//initialize vga buffer
void init_vga(uint8 fore_color, uint8 back_color)
{
	vga_buffer = (uint16 *)VGA_ADDRESS;
	clear_vga_buffer(&vga_buffer, fore_color, back_color);
}

void print(char string[], int fg, int bg){
	for(int i=0; i<strlen(string); i++){
		vga_buffer[cursor()] = vga_entry(string[i], fg, bg);
	}
}

void println(char string[], int fg, int bg){
	for(int i=0; i<strlen(string); i++){
		vga_buffer[cursor()] = vga_entry(string[i], fg, bg);
	}

	for(int i=0; i<120-(crs % 120); i++){
		vga_buffer[cursor()] = vga_entry(' ', fg, bg);
	}

}

void main()
{
	init_vga(WHITE, BLACK);

	char a[] = "HALLO WELT !11!1!!!";
	println(a,MAGENTA, BLACK);

	char b[] = "test";
	print(b,GREEN,BLACK);

	/*
	char c[] = "neeext123123";
	println(c,YELLOW,BLACK);
	*/
}