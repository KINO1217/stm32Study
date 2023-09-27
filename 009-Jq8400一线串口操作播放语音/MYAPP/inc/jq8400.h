#ifndef __JQ8400_H__
#define __JQ8400_H__
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"

#define JQ8400_GPIO GPIOB
#define JQ8400_GPIO_PIN GPIO_Pin_5

#define SDA PBout(5)

//��ʼ��
void jq8400Init(void);
//����һ�ֽ����ݣ���λ�ȷ�
void jq8400SendOneByteData(u8 dataOrCmd);

#endif
