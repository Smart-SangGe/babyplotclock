#include<stdio.h>
#include<stdlib.h>

int main()
{
    system("echo 41 > /sys/class/gpio/export");
    system("echo 39 > /sys/class/gpio/export");
    system("echo 158 > /sys/class/gpio/export");
    system("echo 133 > /sys/class/gpio/export");
    system("echo 156 > /sys/class/gpio/export");
    system("echo 154 > /sys/class/gpio/export");
    system("echo out > /sys/class/gpio/gpio41/direction");
    system("echo out > /sys/class/gpio/gpio39/direction");
    system("echo out > /sys/class/gpio/gpio158/direction");
    system("echo out > /sys/class/gpio/gpio133/direction");
    system("echo out > /sys/class/gpio/gpio156/direction");
    system("echo out > /sys/class/gpio/gpio154/direction");
}