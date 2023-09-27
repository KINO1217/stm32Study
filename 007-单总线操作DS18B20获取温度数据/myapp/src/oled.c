#include "oled.h"
#include "oled_font.h"

static void Write_Cmd(u8 cmd)
{
    IIC_Start();
    IIC_Send_Byte(0x78);
    IIC_Check_ACK();//��������
    IIC_Send_Byte(0x00);
    IIC_Check_ACK();
    IIC_Send_Byte(cmd);
    IIC_Check_ACK();
    IIC_Stop();
}

static void Write_Data(u8 data)
{
    IIC_Start();
    IIC_Send_Byte(0x78);
    IIC_Check_ACK();
    IIC_Send_Byte(0x40);
    IIC_Check_ACK();
    IIC_Send_Byte(data);
    IIC_Check_ACK();
    IIC_Stop();
}

void Oled_Clear(void)
{
    for(u8 i=0;i<8;i++)
    {
        Write_Cmd(0xB0|i);
        Write_Cmd(0x00);
        Write_Cmd(0x10);
        for(u8 j=0;j<128;j++){
            Write_Data(0x00);
        }
    }
}

void Oled_On(void)
{
    Write_Cmd(0x8D);//��������
    Write_Cmd(0x14);//��
    Write_Cmd(0xAF);
}

void Oled_Off(void)
{
    Write_Cmd(0x8D);
    Write_Cmd(0x10);//�ر�
    Write_Cmd(0xAE);
}

void Oled_Init(void)
{
    IIC_Init();
    Delay_Ms(200);
    
    Write_Cmd(0xA8);//���÷ֱ���
    Write_Cmd(0x3F);//0x3f : 128*64  0x1f  128*32
    
    Write_Cmd(0xDA);//����COMӲ���������ã���Ӧ�ֱ���
    Write_Cmd(0x12);//0x12 : 0.96->128*64  0x02 : 0.91->128*32
    
    Write_Cmd(0xD3);//������ʾƫ��
    Write_Cmd(0x00);//Ĭ����ƫ��
    Write_Cmd(0x40);//������ʾ��ʼ0-63
    Write_Cmd(0xA1);//��SEGMENT��ӳ�����IIC�Ľ�OLEDҪ����Ϊ0xA1
    Write_Cmd(0x81);//�Աȶ�����
    Write_Cmd(0x7F);//��������0x00-0xFF,��ֵԽ������Խ��
    Write_Cmd(0xA4);//�����ѭRAM���ݣ�0x05�������RAM����
    Write_Cmd(0xA6);//��ʾ��ʽ������ʾ��0xA7������ʾ,���룬0��������1����
    Write_Cmd(0xD5);//������ʾʱ�ӷ�Ƶ/����Ƶ��
    Write_Cmd(0xF0);//���÷ֱ���ֵ
    Write_Cmd(0x8D);//��������
    Write_Cmd(0x14);//��������ʾ������ʱ��ʹ�ã�0x10:�������ڿ���ǰʹ��
    Write_Cmd(0xAE);//��ʾ�رգ�0xAF��ʾ����
    Write_Cmd(0x20);//�����ڴ��ַģʽ ˮƽ/��ֱ/ҳѰַ(Ĭ��)
    Write_Cmd(0x02);//ˮƽ0x00   ��ֱ0x01    ҳѰַ0x02
    Write_Cmd(0xC8);//����COMɨ�跽ʽ0xC0���·�������  0xC8�����ҵ���
    Write_Cmd(0xB0);//ΪҳѰַģʽ���ÿ�����ַ0-7
    Write_Cmd(0x00);//���õ��е�ַ
    Write_Cmd(0x10);//���ø��е�ַ
    Write_Cmd(0x40);//������ʾ��ʼ�� 0-63
    Write_Cmd(0xD9);//����Ԥ���ʱ��
    Write_Cmd(0x22);//���ʱ��
    Write_Cmd(0xDB);//����ȡ��ѡ�񼶱�
    Write_Cmd(0x20);//Ĭ��0x20 0.77xvcc
    Write_Cmd(0xAF);//��ʾ����
    
    Oled_Off();
    Oled_Clear();
    Oled_On();
}

static void Oled_Display(u8 x,u8 y,u8 g,u8 k,u8 *dat)  //x����ʾ�� ��y����ʾ�У�g���ָ�/8   k���ֿ�
{
    for(u8 i=0;i<g;i++)
    {
        Write_Cmd((0xB0|i)+x);//����ҳ
        Write_Cmd(0x10+(y>>4&0x0f));//�����иߵ�ַ
        Write_Cmd(y&0x0f);//�����е͵�ַ
        for(u8 j=0;j<k;j++){
            Write_Data(*dat++);
        }
    }
}

static void Oled_Show_Char(u8 x,u8 y,u8 ch) //8*16
{
    ch=ch-' ';
    Oled_Display(x*(0x01<<1),y*(0x01<<3),2,8,char_1608[ch]);
}

static void ITOA(int num,char *str)
{
    if(num==0){
        *str='0';
        *++str='\0';
        return;
    }
        
    char *left = str;
    int flag = num;
    if (num < 0)   //���ǵ����������
        num = -num;
    while (num > 0)
    {
        *str++ = num % 10 + '0';
        num /= 10;
    }
    
    if (flag < 0)
    {
        *str++ = '-';
    }
    *str = '\0';
    //��ʱ�������ŵģ���Ҫ��ת����
    char *right = str - 1;
    while (left < right)
    {
        char tmp = *left;
        *left = *right;
        *right = tmp;
        ++left;
        --right;
    }
}

void Oled_Show_String(u8 x,u8 y,char* chs,...)
{
    /***************����ƴ��*****************/
    int str_len=strlen(chs);
	int str_pos=0;
	
	va_list ap;
	va_start(ap,chs);
	
	char temp_buf[100];
	memset(temp_buf,0,sizeof(temp_buf));
	char temp_d[30];
	
	for(str_pos=0;str_pos<str_len;str_pos++){
		if(chs[str_pos]=='%'&&chs[str_pos+1]=='d'){
			ITOA(va_arg(ap,int),temp_d);
			strcat(temp_buf,temp_d);
			str_pos++;
		}else if(chs[str_pos]=='%'&&chs[str_pos+1]=='s'){
			strcat(temp_buf,va_arg(ap,char*));
			str_pos++;
		}else{
			int temp_len=strlen(temp_buf);
			temp_buf[temp_len]=chs[str_pos];
			temp_buf[temp_len+1]='\0';
		}
	}
	va_end(ap);
    
    /***********��ʾ�ַ�������***********/
    u8 pos=0;
    u8 width=0;
    str_pos=0;
    
    while(temp_buf[str_pos]!='\0')
    {
        width=pos+y;
        
        if(width>=16){
            break;
        }
        
        Oled_Show_Char(x,width,(u8)temp_buf[str_pos]);
        pos++;
        str_pos++;
    }
}

static void Oled_Show_One_Chinese(u8 x,u8 y,char chs[2])//16*16
{
    int pos=0;
    for(pos=0;pos<MAX_CHINESE_NUM;pos++){
        if(chs[0]==chinese_1616[pos].index[0]&&chs[1]==chinese_1616[pos].index[1]){
            Oled_Display(x*(0x01<<1),y*(0x01<<4),2,16,chinese_1616[pos].words);
        }
    }
}

void Oled_Show_Chinese(u8 x,u8 y,char *chs)
{
    char temp_ch[20],temp_str[2];
    memset(temp_ch,0,sizeof(temp_ch));
    strcpy(temp_ch,chs);
    int str_len=strlen(temp_ch);
    int pos;
    int temp_index=y;
    
    for(pos=0;pos<str_len;pos+=2){
        if(temp_index>=8){
            break;
        }
        temp_str[0]=temp_ch[pos];
        temp_str[1]=temp_ch[pos+1];
        Oled_Show_One_Chinese(x,temp_index,temp_str);
        temp_index++;
    }
}
