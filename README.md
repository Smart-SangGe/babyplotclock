# babyplotclock

## 本项目基于Rock Pi 4A，应该适用于4系列。

1.实现手写功能  
2.实现手写中文时间  
3.实现手动调时  
4.实现语音报时  
5.实现可充电功能  

gpio参考:https://wiki.radxa.com/Rockpi4/hardware/gpio  
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

驱动库参考：https://wiki.radxa.com/Rockpi4/dev/libmraa  
驱动库源码仓库：https://github.com/eclipse/mraa  
用apt安装不上python3.7。。。于是用源码编译安装一下，能用了。  

红色vcc，棕色gnd，黄色sig  
引脚定义:  
1号舵机（控制上下）：sig->11(gpio no.146)  
2号舵机（左边）：sig->11(gpio no.146)  
3号舵机（右边）：sig->13(gpio no.150)  
继电器：sig->15(gpio no.149)
由于rockpi4这个板子只有2个pwm口，所以我用了继电器，让两个舵机共用一个sig接口，通过控制继电器开让其中一个舵机断开供电。  
舵机采用升压到5v的锂电池供电，而且舵机应与板子共地，不然会出现没反应的情况。  
