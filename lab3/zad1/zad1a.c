#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){
    char c;
    int source,outcome;
    source=open("s", O_RDONLY);
    outcome=open("o",O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
    off_t p = lseek(source,-1,SEEK_END);
    while(read(source,&c,1) == 1 && p > -1){
        p--;
        write(outcome,&c,1);
        lseek(source,p,SEEK_SET);
    }


    close(source);

    close(outcome);
}