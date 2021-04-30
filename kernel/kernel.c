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


void exec(int index, char *input){
    switch (index)
    {
        case 0:;
            kprint("HELP: ...");
            kprint("\n>");
            break;
        
        case 1:;
            char sub[strlen(input)];
            substring(sub, input, 4, strlen(input));
            kprint(sub);
            kprint("\n>");
            break;
    }
    return;
}

char commands[][10] = {"HELP", "ECHO", "BB"};

void user_input(char *input) {

    for(int i=0; i<3; i++){

        kprint(commands[i]);

        int len = strlen(commands[i]);
        char ninput[len];

        substring(ninput, input, 0, len+1);

        if (strcmp(ninput, commands[i]) == 0){
            exec(i, input);
            return;
        }
    }
    kprint("NO SUCH COMMAND, TYPE HELP FOR FURTHER REFERENCE");
    kprint("\n> ");
    return;
}