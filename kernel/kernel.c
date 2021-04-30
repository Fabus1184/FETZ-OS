#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"

void main() {
    isr_install();
    irq_install();

    clear_screen();

    kprint("WELCOME TO FETZ-OS!\n> ");
}

void user_input(char *input) {

    char sub[4];
    substring(sub, input, 0, 4);
    if (strcmp("ECHO", sub) == 0){
        substring(sub, input, 5, strlen(input));
        kprint(sub);
        kprint("\n>");
        return;
    }
    
    if (strcmp("HELP", input) == 0){
        kprint("HELP: ...");
        kprint("\n>");
        return;
    }

    if (strcmp("BB", input) == 0){
        kprint("SO, ICH HAU AB.");
        asm volatile("hlt");
    }

    kprint("NO SUCH COMMAND, TYPE HELP FOR FURTHER REFERENCE");
    kprint("\n> ");
    return;
}