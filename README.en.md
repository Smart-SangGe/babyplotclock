#babyplotclock

[简体中文](README.md) | [English](README.en.md)

## This project is based on the Rock Pi 4A and should work on the 4 series.

### Implemented functions
1. Realize handwriting function
2. Realize voice time reporting
### Unimplemented functionality
1. Realize handwritten Chinese time
2. Realize manual time adjustment
3. Realize the rechargeable function

gpio reference: https://wiki.radxa.com/Rockpi4/hardware/gpio
Pin Mapping
-----------

PROCK Pi 4 has a 40-pin expansion header. Each pin is distinguished by color.

|Additional Function |  Primary Function|  PIN  |  PIN  |  Primary Function  | Additional Function |
|--------------------|------------------|:------|------:|--------------------|---------------------|
|                    |      +3.3V       |   1   |   2   |    +5.0V           |                     |
|                    |      I2C7_SDA    |   3   |   4   |    +5.0V           |                     |
|                    |      I2C7_SCL    |   5   |   6   |    GND             |                     |
|                    |      SPI2_CLK    |   7   |   8   |    UART2_TXD       |                     |
|                    |      GND         |   9   |   10  |    UART2_RXD       |                     |
|                    |      PWM0        |   11  |   12  |    I2S1_SCLK       |                     |
|                    |      PWM1        |   13  |   14  |    GND             |                     |
|                    |      SPDIF_TX    |   15  |   16  |    GPIO4_D2        |                     |
|                    |      +3.3V       |   17  |   18  |    GPIO4_D4        |                     |
|         UART4_TXD  |      SPI1_TXD    |   19  |   20  |    GND             |                     |
|         UART4_RXD  |      SPI1_RXD    |   21  |   22  |    GPIO4_D5        |                     |
|                    |      SPI1_CLK    |   23  |   24  |    SPI1_CSn        |                     |
|                    |      GND         |   25  |   26  |    ADC_IN0         |                     |
|                    |      I2C2_SDA    |   27  |   28  |    I2C2_CLK        |                     |
|           I2C6_SCL |      SPI2_TXD    |   29  |   30  |    GND             |                     |
|           I2C6_SDA |      SPI2_RXD    |   31  |   32  |    SPDIF_TX        | UART3_CTSn          |
|                    |      SPI2_CSn    |   33  |   34  |    GND             |                     |
|                    |      I2S1_LRCK_TX|   35  |   36  |    I2S1_LRCK_RX    |                     |
|                    |      GPIO4_D6    |   37  |   38  |    I2S1_SDI        |                     |
|                    |      GND         |   39  |   40  |    I2S1_SDO        |                     |


Driver library reference: https://wiki.radxa.com/Rockpi4/dev/libmraa
Driver library source code warehouse: https://github.com/eclipse/mraa
Python3.7 cannot be installed with apt. . . So compile and install it with the source code, and it works.

Red vcc, brown gnd, yellow sig
Pin definition:
No. 1 servo (control up and down): sig->11 (gpio no.146)
No. 2 servo (left): sig->11 (gpio no.146)
No. 3 servo (right): sig->13 (gpio no.150)
Relay: sig->15 (gpio no.149)
Since the rockpi4 board only has 2 pwm ports, I used a relay to let the two servos share a sig interface, and one of the servos was disconnected from the power supply by controlling the relay.
The steering gear is powered by a lithium battery boosted to 5v, and the steering gear should share the ground with the board, otherwise there will be no response.


Sox is used as the voice playback software.