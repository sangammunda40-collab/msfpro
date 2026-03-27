#ifndef BANNER_H
#define BANNER_H

#include <unistd.h>
#include <stdio.h>

static void slow_print(const char *s){
    for(int i=0;s[i];i++){
        putchar(s[i]);
        fflush(stdout);
        usleep(15000);
    }
}

static void show_banner(){
    printf("\033[2J\033[H");

    slow_print("\033[1;31m       =[ msf-pro v2 ]=\033[0m\n");
    slow_print("\033[1;32m+ -- --=[ Web Exploitation Framework ]\033[0m\n");
    slow_print("\033[1;33m+ -- --=[ Modules: idor fuzz header smart ]\033[0m\n");
    slow_print("\033[1;36m+ -- --=[ Ready for Bug Hunting 😈 ]\033[0m\n\n");

    slow_print("[*] Loading modules...\n");
    usleep(300000);
    slow_print("[*] Initializing engine...\n");
    usleep(300000);
    slow_print("[*] Done.\n\n");
}

#endif
