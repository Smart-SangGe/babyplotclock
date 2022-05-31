/*
 * Author: Thomas Ingleby <thomas.c.ingleby@intel.com>
 * Contributors: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 * Copyright (c) 2014 Intel Corporation.
 *
 * SPDX-License-Identifier: MIT
 *
 * Example usage: Generates PWM signal of period 200us with variable dutycyle
 *                repeatedly. Press Ctrl+C to exit
 */

/* standard headers */
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/* mraa header */
#include "mraa/pwm.h"

/* PWM declaration */
#define PWM0 11
#define PWM1 13

/* PWM period in us */
#define PWM_FREQ 20000

volatile sig_atomic_t flag = 1;

void
sig_handler(int signum)
{
    if (signum == SIGINT) {
        fprintf(stdout, "Exiting...\n");
        flag = 0;
    }
}

int
main(void)
{
    mraa_result_t status0 = MRAA_SUCCESS;
    mraa_result_t status1 = MRAA_SUCCESS;
    // typedef struct _pwm* mraa_pwm_context;
    mraa_pwm_context pwm0;
    // _pwm* pwm0
    mraa_pwm_context pwm1;
    float value = 0.1f;
    float output0;
    float output1;

    /* initialize mraa for the platform (not needed most of the times) */
    mraa_init();

    //! [Interesting]
    pwm0 = mraa_pwm_init(PWM0);
    if (pwm0 == NULL) {
        fprintf(stderr, "Failed to initialize PWM\n");
        mraa_deinit();
        return EXIT_FAILURE;
    }
    pwm1 = mraa_pwm_init(PWM1);
    if (pwm1 == NULL) {
        fprintf(stderr, "Failed to initialize PWM\n");
        mraa_deinit();
        return EXIT_FAILURE;
    }

    /* set PWM period */
    status0 = mraa_pwm_period_us(pwm0, PWM_FREQ);
    status1 = mraa_pwm_period_us(pwm1, PWM_FREQ);
    if (status0 != MRAA_SUCCESS) {
        goto err_exit;
    }
    if (status1 != MRAA_SUCCESS) {
        goto err_exit;
    }

    /* enable PWM */
    status0 = mraa_pwm_enable(pwm0, 1);
    if (status0 != MRAA_SUCCESS) {
        goto err_exit;
    }
    status1 = mraa_pwm_enable(pwm1, 1);
    if (status1 != MRAA_SUCCESS) {
        goto err_exit;
    }


        /* write PWM duty cycle 占空比*/
        status0 = mraa_pwm_write(pwm0, value);
        status1 = mraa_pwm_write(pwm1, value);
        if (status0 != MRAA_SUCCESS) {
            goto err_exit;
        }
		if (status1 != MRAA_SUCCESS) {
            goto err_exit;
        }
        usleep(50000);


        /* read PWM duty cycle */
        output0 = mraa_pwm_read(pwm0);
        output1 = mraa_pwm_read(pwm1);
        fprintf(stdout, "PWM0 value is %f\n", output0);
        fprintf(stdout, "PWM1 value is %f\n", output1);
        
    

    /* close PWM */
    mraa_pwm_close(pwm0);
    mraa_pwm_close(pwm1);

    //! [Interesting]
    /* deinitialize mraa for the platform (not needed most of the times) */
    mraa_deinit();

    return EXIT_SUCCESS;

err_exit:
    mraa_result_print(status0);
    mraa_result_print(status1);

    /* close PWM */
    mraa_pwm_close(pwm0);
    mraa_pwm_close(pwm1);

    /* deinitialize mraa for the platform (not needed most of the times) */
    mraa_deinit();

    return EXIT_FAILURE;
}
