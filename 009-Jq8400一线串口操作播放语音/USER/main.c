#include "jq8400.h"

//������
int main(void)
{
    jq8400Init();
    jq8400SendOneByteData(0x0A);//�ȷ������֣��ٷ���ָ��,�������ָ��
    jq8400SendOneByteData(0x01);//��������1
    //jq8400SendOneByteData(0x00);//��������0������������10
    jq8400SendOneByteData(0x0B);//ȷ��ѡ��ָ��
    
    jq8400SendOneByteData(0x11);//����ָ���ָ��
}
