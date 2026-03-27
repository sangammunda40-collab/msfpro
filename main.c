#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void run_idor(const char*,const char*,const char*);
void run_fuzz(const char*,const char*,const char*);
void run_header(const char*);
void run_smart(const char*,const char*,const char*);
void run_xss(const char*,const char*,const char*);
void run_sqli(const char*,const char*,const char*);
void run_lfi(const char*,const char*,const char*);
void run_ssrf(const char*,const char*,const char*);

char TARGET[256]="";
char COOKIE[256]="";
char HEADER[256]="";
char CURRENT_MODULE[50]="";

void slow(const char*s){for(int i=0;s[i];i++){printf("%c",s[i]);fflush(stdout);usleep(20000);}}

void show_banner(){
    printf("\033[1;31m"); slow("       =[ msf-pro v2 ]=\n");
    printf("\033[1;36m"); slow("+ -- --=[ Web Exploitation Framework ]\n");
    printf("\033[1;32m"); slow("+ -- --=[ Ready for Bug Hunting 😈 ]\n\n");
    printf("\033[1;33m"); slow("[*] Loading modules...\n"); sleep(1);
    slow("[*] Initializing engine...\n"); sleep(1);
    slow("[*] Done.\n\n");
    printf("\033[0m");
}

int main(int argc,char *argv[]){

    if(argc > 1){
        if(strcmp(argv[1],"-help")==0 || strcmp(argv[1],"-h")==0){
            printf("msfpro usage:\n msfpro (interactive)\n msfpro -help\n msfpro -version\n");
            return 0;
        }
        if(strcmp(argv[1],"-version")==0 || strcmp(argv[1],"-v")==0){
            printf("msfpro v2.0 | web exploitation framework\n");
            return 0;
        }
    }

    char input[512];

    show_banner();

    while(1){
        printf("\033[1;32mmsf-pro> \033[0m");

        if(!fgets(input,sizeof(input),stdin)) break;
        input[strcspn(input,"\n")] = 0;

        char cmd[100];
        sscanf(input,"%s",cmd);

        // use
        if(strcmp(cmd,"use")==0){
            sscanf(input,"%*s %s",CURRENT_MODULE);
            printf("[+] Using %s\n",CURRENT_MODULE);
        }

        // set
        else if(strcmp(cmd,"set")==0){
            char key[50], val[256];
            sscanf(input,"%*s %s %s",key,val);

            if(strcmp(key,"TARGET")==0) strcpy(TARGET,val);
            else if(strcmp(key,"COOKIE")==0) strcpy(COOKIE,val);
            else if(strcmp(key,"HEADER")==0) strcpy(HEADER,val);
        }

        // show
        else if(strcmp(cmd,"show")==0){
            char arg[50]="";
            sscanf(input,"%*s %s",arg);

            if(strcmp(arg,"modules")==0){
                printf("Modules:\n idor   - IDOR brute force scanner\n fuzz   - Parameter fuzz testing\n header - Header injection testing\n smart  - Auto combined scan\n xss    - XSS detection\n sqli   - SQLi detection\n lfi    - LFI detection\n ssrf   - SSRF detection\n");
            }
            else if(strcmp(arg,"options")==0){
                printf("Options:\n TARGET\n COOKIE\n HEADER\n");
            }
            else{
                printf("Usage: show modules | show options\n");
            }
        }

        // run
        else if(strcmp(cmd,"run")==0){
            if(strcmp(CURRENT_MODULE,"idor")==0) run_idor(TARGET,COOKIE,HEADER);
            else if(strcmp(CURRENT_MODULE,"fuzz")==0) run_fuzz(TARGET,COOKIE,HEADER);
            else if(strcmp(CURRENT_MODULE,"header")==0) run_header(TARGET);
            else if(strcmp(CURRENT_MODULE,"smart")==0) run_smart(TARGET,COOKIE,HEADER);
            else if(strcmp(CURRENT_MODULE,"xss")==0) run_xss(TARGET,COOKIE,HEADER);
            else if(strcmp(CURRENT_MODULE,"sqli")==0) run_sqli(TARGET,COOKIE,HEADER);
            else if(strcmp(CURRENT_MODULE,"lfi")==0) run_lfi(TARGET,COOKIE,HEADER);
            else if(strcmp(CURRENT_MODULE,"ssrf")==0) run_ssrf(TARGET,COOKIE,HEADER);
            else printf("[-] Unknown module\n");
        }

        // exit
        else if(strcmp(cmd,"exit")==0){
            break;
        }

        // shell fallback
        else{
            system(input);
        }
    }

    return 0;
}
