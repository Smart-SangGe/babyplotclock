/*
* Author: Liang Junyong
* reference: mraa/example/c/pwm.c
*
* usage: xxxxx
*/

#pragma once

/* standard headers */
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/* mraa header */
#include "mraa/pwm.h"

/* PWM declaration */
#define PWM1 11
#define PWM2 13

/* PWM period(周期) in us */
#define PWM_FREQ 20000

/* 初始化 */
void init(int pin){
	
}

//舵机顺时针转
void clockwise{

}

//舵机逆时针转
void anticlockwise{

}

/**
 * A structure representing a PWM pin
 * 引用一段不知哪里写着的结构体
 */
/** struct _pwm {
 *  int pin;  the pin number, as known to the os. 
 *  int chipid;  the chip id, which the pwm resides 
 *  int duty_fp;  File pointer to duty file 
 *  int period;   Cache the period to speed up setting duty
 *  mraa_boolean_t owner;  Owner of pwm context
 *  mraa_adv_func_t* advance_func;  override function table 
 **/
