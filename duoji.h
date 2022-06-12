/*
* Author: Liang Junyong
* reference: mraa/example/c/pwm.c mraa/example/c/gpio.c
*
* usage: main函数在程序开始时直接调用init()来初始化所有引脚
* 程序结束时调用deinit()来释放所有引脚!!!
* 设逆时针旋转为正方向。0度->占空比0.875，180度->占空比0.975
* 调用rotate(mraa_pwm_context dev, float degree)来使舵机旋转到指定角度
* 注意旋转角度为0-180度,调用完rotate函数要至少usleep(400000)来确保
* 舵机不丢步。
* 调用mraa_gpio_write(gpio1, 0)来使GPIO输出高低电平
*/

#pragma once

/* standard headers */
//#include <cstdlib>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/* mraa header */
#include "c/pwm.h"
#include "mraa/pwm.h"
#include "mraa/gpio.h"

/* PWM declaration */
#define PWM0 11
#define PWM1 13

/* GPIO declaration */
#define GPIO_PIN_1 15

/* PWM period(周期) in ms */
#define PWM_FREQ 20

/* 定义针脚 */
mraa_pwm_context pwm0;
mraa_pwm_context pwm1;
mraa_gpio_context gpio1;


/* 定义函数 */
void init();
void rotate(mraa_pwm_context dev, float degree);
void deinit();

/* 初始化函数 */
void init(){

    /* 定义状态码 */
    mraa_result_t status = MRAA_SUCCESS;

    
    /* 初始化引脚，如果初始化失败则退出 */
    gpio1 = mraa_gpio_init(GPIO_PIN_1);
	pwm0 = mraa_pwm_init(PWM0);
	pwm1 = mraa_pwm_init(PWM1);
	if (gpio1 == NULL) {
        fprintf(stderr, "Failed to initialize GPIO %d\n", GPIO_PIN_1);
        mraa_deinit();
        return EXIT_FAILURE;
    }
    if (pwm0 == NULL) {
        fprintf(stderr, "Failed to initialize PWM0\n");
        mraa_deinit();
        return EXIT_FAILURE;
    }
    if (pwm1 == NULL) {
        fprintf(stderr, "Failed to initialize PWM1\n");
        mraa_deinit();
        return EXIT_FAILURE;
    }
    
    /* set PWM period */
    status = mraa_pwm_period_ms(pwm0, PWM_FREQ);
    if (status != MRAA_SUCCESS) {
        mraa_result_print(status);
		mraa_pwm_close(pwm0);
		mraa_deinit();
		return EXIT_FAILURE;
    }
    status = mraa_pwm_period_ms(pwm1, PWM_FREQ);
    if (status != MRAA_SUCCESS) {
		mraa_result_print(status);
		mraa_pwm_close(pwm1);
		mraa_deinit(); 
		return EXIT_FAILURE;   
	}
    
    /* enable PWM */
    status = mraa_pwm_enable(pwm0, 1);
    if (status != MRAA_SUCCESS) {
        mraa_result_print(status);
		mraa_pwm_close(pwm0);
		mraa_deinit(); 
		return EXIT_FAILURE;
    }
    status = mraa_pwm_enable(pwm1, 1);
    if (status != MRAA_SUCCESS) {
        mraa_result_print(status);
		mraa_pwm_close(pwm1);
		mraa_deinit(); 
		return EXIT_FAILURE;
    }
    
    /* set GPIO to output */
    status = mraa_gpio_dir(gpio1, MRAA_GPIO_OUT);
    if (status != MRAA_SUCCESS) {
        mraa_result_print(status);
        mraa_deinit();
		return EXIT_FAILURE;
    }
    
    
}

/* rotate TO 1-180 degree */
void rotate(mraa_pwm_context dev, float degree){

    /* 定义状态码 */
    mraa_result_t status = MRAA_SUCCESS;

    /* 容错判断 */
    // if(degree > 180 || degree < 0){
    //     fprintf(stderr, "Invalid degree\n");
    //     deinit();
    //     return EXIT_FAILURE;
    // }
    if(degree < 0){
        degree = 0;
    }
    if(degree > 180){
        degree = 180;
    }

	/* write PWM duty cyle */
    float duty;
    duty = 0.875 + (degree / 1800);
    status = mraa_pwm_write(dev, duty);
        if (status != MRAA_SUCCESS) {
            mraa_result_print(status);
            mraa_pwm_close(dev);
            mraa_deinit();
		    return EXIT_FAILURE;
        }
}

/* 释放所有引脚 */
void deinit(){
	mraa_pwm_close(pwm0);
	mraa_pwm_close(pwm1);
	mraa_gpio_close(gpio1);
	mraa_deinit();
}

/**
 * A structure representing a PWM pin
 */
/** struct _pwm {
 *  int pin;  the pin number, as known to the os. 
 *  int chipid;  the chip id, which the pwm resides 
 *  int duty_fp;  File pointer to duty file 
 *  int period;   Cache the period to speed up setting duty
 *  mraa_boolean_t owner;  Owner of pwm context
 *  mraa_adv_func_t* advance_func;  override function table 
 **/

/**
 * A structure representing a gpio pin.
 */
/** struct _gpio {
 *  
 *   int pin;   the pin number, as known to the os. 
 *   int phy_pin;    pin passed to clean init. -1 none and raw
 *   int value_fp;      the file pointer to the value of the gpio 
 *   void (* isr)(void *);  the interrupt service request 
 *   void *isr_args;  args return when interrupt service request triggered 
 *   pthread_t thread_id;  the isr handler thread id 
 *   int isr_value_fp;  the isr file pointer on the value 
 * #ifndef HAVE_PTHREAD_CANCEL
 *   int isr_control_pipe[2];  a pipe used to interrupt the isr from polling the value fd
 * #endif
 *   mraa_boolean_t isr_thread_terminating;  is the isr thread being terminated? 
 *   mraa_boolean_t owner;  If this context originally exported the pin 
 *   mraa_result_t (*mmap_write) (mraa_gpio_context dev, int value);
 *   int (*mmap_read) (mraa_gpio_context dev);
 *   mraa_adv_func_t* advance_func;  override function table 
 * #if defined(MOCKPLAT)
 *   mraa_gpio_dir_t mock_dir;  mock direction of the pin 
 *   int mock_state;   mock state of the pin 
 * #endif
 *   @}
 * #ifdef PERIPHERALMAN
 *   AGpio *bgpio;
 * #endif
 *   struct _gpio_group *gpio_group;
 *   unsigned int num_chips;
 *   int *pin_to_gpio_table;
 *   unsigned int num_pins;
 *   mraa_gpio_events_t events;
 *   int *provided_pins;
 *   struct _gpio *next;
 * };
**/
