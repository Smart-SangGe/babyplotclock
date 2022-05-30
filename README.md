# babysudoku
c语言期末大作业  
1.实现手写功能  
2.实现中文时间  
3.实现手动调时  
4.实现语音报时  
5.实现可充电功能  

gpio参考:https://wiki.radxa.com/Rockpi4/hardware/gpio  
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
