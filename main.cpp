#include <iostream>
#include <stdio.h>
#include "darts.h"
using namespace std;
int main() {
    int x,y;
    printf("Input X\n");
    scanf("%d",&x);
    printf("Input Y\n");
    scanf("%d",&y);
    printf("%d\n", darts(x,y));
    return 0;
}