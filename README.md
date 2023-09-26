# stm32Study

1.STM32操作GPIO端口输出高低电平，控制LED灯的量灭，使用标准库文件stm32f10x_gpio.c和stm32f10x_rcc.c，驱动文件led.c。

2.STM32外部中断识别端口输入状态操作按键，使用标准库文件stm32f10x_gpio.c、stm32f10x_rcc.c、misc.c、stm32f10x_exti.c，驱动文件sys.c和key.c。

#################GPIO输入输出的学习#################

3.系统滴答定时器实现us和ms延时函数，标准库文件stm32f10x_gpio.c、stm32f10x_rcc.c、misc.c，驱动文件delay.c。