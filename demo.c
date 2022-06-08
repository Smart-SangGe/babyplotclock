#include <stdio.h>
#include "duoji.h"
int main(){
    init();
    for(float de = 1; de < 180; de= de + 1){
        rotate(pwm1, de);
    }
    deinit();
    return 0;
}