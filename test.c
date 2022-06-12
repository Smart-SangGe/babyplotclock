#include <stdio.h>

// 设逆时针旋转为正方向。0度->占空比0.875，180度->占空比0.975

int main(){
    // mraa_pwm_context pwm0;
    float degree, duty;
    degree = 150;
    duty = 0.875 + (degree / 1800);
    printf("%f",duty);  
    return 0;
}