#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(){
    fopen("pipe", "w+");
    mkfifo("pipe",0777);
    //wysyla hello world
    fwrite("hello world", sizeof("hello world"), 1, "pipe"); //?
}