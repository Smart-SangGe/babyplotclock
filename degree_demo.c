#include "duoji.h"
#include <unistd.h>
int main()
{
    init();
    rotate(pwm0,90);
    usleep(400000);
    rotate(pwm1,90);
    usleep(400000);
    deinit();
    return 0;
}