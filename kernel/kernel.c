#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../lib/functions.h"

#include <math.h>
#include <string.h>

#define shell "$>"

void main() {

    double d = sqrt(2);

    isr_install();
    irq_install();

    clear_screen();

    print("WELCOME TO FETZ-OS v1.0");

    for(int c = 0; c<16; c++){
        for(int d = 0; d<16; d++){
            kprint_at("-",-1,-1,16*c+d);
    }}

    print("");
    kprint(shell);
}

void user_input(char *input) {

    if(strcmp("", input) == 0){
        kprint(shell);
        return;
    }

    if (strcmp("clear", input) == 0){
        clear_screen();
        kprint(shell);
        return;
    }

    char dump[strlen(input)];

    strncpy(dump, input, 5);
    if (strcmp("echo ", dump) == 0){
        substring(dump, input, 5, strlen(input));
        print(dump);
        kprint(shell);
        return;
    }

    if (strcmp("colors", input) == 0){
        for(int c = 0; c<16; c++){
            for(int d = 0; d<16; d++){
                kprint_at("-",-1,-1,16*c+d);
            }
        }
        print("");
        kprint(shell);
        return;
    }

    substring(dump, input, 0, 6);
    if (strcmp("color ", dump) == 0 && strlen(input) == 8){
        substring(dump, input, 6, 8);

        if(char_to_int(dump[0]) == -1 || char_to_int(dump[1]) == -1){
            kprint(dump);
            print(" IS NOT A VALID COLOR!");
            print(shell);
            return;
        }

        int color = 0;

        color += 16*char_to_int(dump[0]);
        color += char_to_int(dump[1]);

        setcolor(color);

        kprint(shell);
        return;
    }

    if (strcmp("help", input) == 0){
        print("HELP: TEXT HIER");
        kprint(shell);
        return;
    }

    if (strcmp("bb", input) == 0){
        print("SO, ICH HAU AB.");
        asm volatile("HLT");
        return;
    }

    if (strcmp("reboot", input) == 0){
        print("REBOOTING...");
        asm volatile("HLT");
        return;
    }

    print("NO SUCH COMMAND, TYPE HELP FOR FURTHER REFERENCE");
    kprint(shell);
    return;
}