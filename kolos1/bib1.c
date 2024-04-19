#include <stdlib.h>
#include <stdio.h>
#include "bib1.h"

/*napisz biblioteke ladowana dynamicznie przez program zawierajaca funkcje:

1) zliczajaca sume n elementow tablicy tab:*/
int sumuj(int *tab, int n){
    int s = 0;
    for (int i = 0; i < n; i++){
        s += tab[i];
    }
    return s;
}
/*
2) liczaca srednia n elementow tablicy tab
*/
double srednia(int *tab, int n){
    return (double) sumuj(tab,n) / (double) n;
}
