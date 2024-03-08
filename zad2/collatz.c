int collatz_conjecture(int input){
    if (input % 2 == 0){
        return input / 2;
    }else{
        return input * 3 + 1;
    }
}
int test_collatz_convergence(int input, int max_iter){
    int n = input;
    int i = 0;
    while(n != 1 && i < max_iter){
        n = collatz_conjecture(n);
        i++;
    }
    return (i <= max_iter) ? (i) : (-1);
}