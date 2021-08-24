#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../kernel/kernel.h"
#include "../lib/functions.h"
#include <stdio.h>
#include <string.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define SHIFTON 42
#define SHIFTOFF 170

static char key_buffer[256];

#define SC_MAX 57
#define SC_MIN 02

const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};

const char sc_ascii_low[] = {
        '_', '_', 
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '?', '?', '\b', '?',
        'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', '?', '?', 
        '?', '?',
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '?', '?', '?', '?', '?', 
        'y', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', '?', '?', '?', ' '};

const char sc_ascii_up[] = {
        '_', '_', 
        '!', '"', 159, '$', '%', '&', '/', '(', ')', '=', '?', '?', '\b', '?',
        'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P', '?', '?', 
        '?', '?',
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '?', '?', '?', '?', '?', 
        'Y', 'X', 'C', 'V', 'B', 'N', 'M', ';', ':', '_', '?', '?', '?', ' '};

const char valid[] = {
        0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xe,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
        0x1c,
        0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26,
        0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
        0x39
        };

int shift = 0;

int validkey(char val)
{
    int i;
    for(i = 0; i < 43; i++)
    {
        if(valid[i] == val)
            return 0;
    }
    return 1;
}

static void keyboard_callback(registers_t regs) {

    u8 scancode = port_byte_in(0x60);

    if(scancode == SHIFTOFF || scancode == SHIFTON){
        shift ^= 1;
    }

    // if(scancode == SHIFTON){
    //     shift = 1;
    // }

    // if(scancode == SHIFTOFF){
    //     shift = 0;
    // }

    if (validkey(scancode) == 1) return;

    if (scancode == BACKSPACE) {
        if (strlen(key_buffer) > 0){
            backspace(key_buffer);
            kprint_backspace();
            return;
        }
        return;

    } else if (scancode == ENTER) {
        kprint("\n");
        user_input(key_buffer);

        for(int i=0; i<256; i++){
            key_buffer[i] = '\0';
        }

        return;

    } else {

        char letter = sc_ascii_low[(int)scancode];

        if(shift == 1){
            letter = sc_ascii_up[(int)scancode];
        }

        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
    }
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}
