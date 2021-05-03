#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"

void main() {
    isr_install();
    irq_install();

    //SCHEISSE LESEN


    clear_screen();

    kprint("WELCOME TO FETZ-OS v1.0");
    kprint(shell);
}   

void user_input(char *input) {

    char sub0[6];

    char sub[4];
    substring(sub, input, 0, 5);
    if (strcmp("ECHO ", sub) == 0){
        substring(sub, input, 5, strlen(input));
        kprint(sub);
        kprint(shell);
        return;
    }
    
    if (strcmp("HELP", input) == 0){
        kprint("HELP: TEXT HIER");
        kprint(shell);
        return;
    }

    if (strcmp("BB", input) == 0){
        kprint("SO, ICH HAU AB.");
        asm volatile("HLT");
    }

    if (strcmp("REBOOT", input) == 0){
        kprint("REBOOTING...");
        asm volatile("HLT");
    }

    kprint("NO SUCH COMMAND, TYPE HELP FOR FURTHER REFERENCE");
    kprint(shell);
    return;
}