#include <stdio.h>

int main(){
    FILE* ps_input = popen("ps aux | wc -l","w");
    fputs("",ps_input);
    pclose(ps_input);
    return 0;
}