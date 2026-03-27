#include <string.h>
#include <stdio.h>

void run_idor(const char*,const char*,const char*);
void run_fuzz(const char*,const char*,const char*);
void run_header(const char*);
void run_smart(const char*,const char*,const char*);

typedef struct {
    char name[20];
    void (*run)(const char*,const char*,const char*);
} Module;

Module modules[] = {
    {"idor", run_idor},
    {"fuzz", run_fuzz},
    {"header", (void*)run_header},
    {"smart", run_smart}
};

int module_count = 4;

Module* get_module(char *name){
    for(int i=0;i<module_count;i++){
        if(strcmp(modules[i].name,name)==0)
            return &modules[i];
    }
    return NULL;
}
