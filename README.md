# stm32Study

1.STM32操作GPIO端口输出高低电平，控制LED灯的量灭，使用标准库文件stm32f10x_gpio.c和stm32f10x_rcc.c，驱动文件led.c。

2.STM32外部中断识别端口输入状态操作按键，使用标准库文件stm32f10x_gpio.c、stm32f10x_rcc.c、misc.c、stm32f10x_exti.c，驱动文件sys.c和key.c。

#################GPIO输入输出的学习#################

3.系统滴答定时器实现us和ms延时函数，标准库文件stm32f10x_gpio.c、stm32f10x_rcc.c、misc.c，驱动文件delay.c。

4.位带操作，类似于51单片机直接操作单个端口，驱动文件sys.c。

5.增加串口操作，通过中断接收数据，配备发送字符串数据的函数，标准库文件stm32f10x_gpio.c、stm32f10x_rcc.c、misc.c、stm32f10x_usart.c，驱动文件uart.c。

6.软件IIC实现，操作OLED显示屏显示数字、字母，ASCII编码汉字，标准库文件stm32f10x_gpio.c、stm32f10x_rcc.c、misc.c，驱动文件delay.c、sys.c、my_iic.c、oled.c。

7.单总线协议学习，操作DS18B20温度传感器采集温度数据，标准库文件stm32f10x_gpio.c、stm32f10x_rcc.c、misc.c，驱动文件ds18b20.c、delay.c、sys.c。