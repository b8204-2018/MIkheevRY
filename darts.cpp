#include <math.h>
#include "darts.h"
int darts(int a,int b){
    double r;
    int z;
    r=sqrt(a*a+b*b);
    if (r>=0 && r<1){
        z=5;
    } else if (r>=1 && r<2){
        z=4;
    } else if (r>=2 && r<3){
        z=3;
    } else if (r>=3 && r<4){
        z=2;
    } else if (r>=4 && r<=5){
        z=1;
    } else if (r>5){
        z=0;
    }
    return z;
}