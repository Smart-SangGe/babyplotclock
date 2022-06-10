#include <stdio.h>
#include <unistd.h>
#include "duoji.h"
int main(){
    // mraa_pwm_context pwm0;
    float output, duty;
    init();
    for (float degree = 0; degree < 180;degree = degree + 30){
        rotate(pwm0, degree);
        usleep(400000);
    }
    for (float degree = 180; degree >= 0;degree = degree - 30){
        rotate(pwm0, degree);
        usleep(400000);
    }
    // duty = 0.925;
    // mraa_pwm_write(pwm0, duty);
    // output = mraa_pwm_read(pwm0);
    // fprintf(stdout, "PWM value is %f\n", output);
    // usleep(200000);
    // duty = 0.958333;
    // mraa_pwm_write(pwm0, duty);
    // output = mraa_pwm_read(pwm0);
    // fprintf(stdout, "PWM value is %f\n", output);
    // usleep(200000);
    deinit();
    printf("deinit finished");
    return 0;
}