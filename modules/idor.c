#include <stdio.h>
void run_idor(const char *TARGET,const char *COOKIE,const char *HEADER){
    for(int i=1;i<=10;i++){
        printf("[TEST] %s?id=%d\n",TARGET,i);
    }
}
