#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

struct pak{
    int i;
    char lit;
} ob1;
/*program przy kazdym uzyciu klawiszy ctrl-c (SIGINT) ma wyslac obiekt o1 przez
potok nazwany 'potok1'*/
//
//
FILE * potok1 = NULL;


void handle(int id){
    if (potok1 != NULL){
        fwrite((void *) &ob1, sizeof(ob1), 1, potok1);
    }
}

int main (int lpar, char *tab[]){
//
//
    potok1 = fopen("potok1", "w");
    signal(SIGINT, handle);

    ob1.i=0;
    ob1.lit='a';
    while(1) {
        printf("%d %c\n",ob1.i,ob1.lit); fflush(stdout);
        ob1.i++;
        ob1.lit=ob1.lit<'e'?ob1.lit+1:'a';
        sleep(1);
    }
    return 0;
}