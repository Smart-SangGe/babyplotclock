#include <stdio.h>
#include "duoji.h"
int main(){
    // mraa_pwm_context pwm0;
    float output;
    init();
    for(int i = 0; i < 10; i++){
    for(float de = 1; de < 180; de = de + 30){
        rotate(pwm0, de);
        output = mraa_pwm_read(pwm0);
        fprintf(stdout, "PWM value is %f\n", output);
        usleep(500000);
    }
    }
    mraa_pwm_write(pwm0, 0.99);
    usleep(500000);
    output = mraa_pwm_read(pwm0);
    fprintf(stdout, "PWM value is %f\n", output);
    deinit();
    printf("deinit finished");
    return 0;
}