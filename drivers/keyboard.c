#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];

#define SC_MAX 57
#define SC_MIN 02

const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};

const char sc_ascii[] = {
        '_', '_', 
        '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '?', '?', '\b', '?',
        'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P', '?', '?', 
        '?', '?',
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '?', '?', '?', '?', '?', 
        'Y', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '-', '?', '?', '?', ' '};

const char valid[] = {
        0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xe,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
        0x1c,
        0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26,
        0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
        0x39
        };

int validkey(char val)
{
    int i;
    for(i = 0; i < 42; i++)
    {
        if(valid[i] == val)
            return 0;
    }
    return 1;
}

static void keyboard_callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = port_byte_in(0x60);
    
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
        user_input(key_buffer); /* kernel-controlled function */
        key_buffer[0] = '\0';

    } else {
        char letter = sc_ascii[(int)scancode];
        /* Remember that kprint only accepts char[] */
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
    }
    UNUSED(regs);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}
