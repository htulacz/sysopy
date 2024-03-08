#include <stdio.h>
int test_collatz_convergence(int input,int max_iter);
int main(){
    printf("%d\n", test_collatz_convergence(4,30));
    printf("%d\n", test_collatz_convergence(7,30));
    printf("%d\n", test_collatz_convergence(10,30));
    return 0;
}