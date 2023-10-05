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

static void Oled_Clear(void)
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
    Write_Cmd(0x0F);//��������0x00-0xFF,��ֵԽ������Խ��
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

void Oled_Refresh_Ram(void)
{
    for(u8 page=0;page<8;page++)
    {
        Write_Cmd(0xB0|page);
        Write_Cmd(0x00);
        Write_Cmd(0x10);
        for(u8 j=0;j<128;j++){
            Write_Data(Oled_RAM[page][j]);
        }
    }
}

//64*128
static void Draw_Point(u8 x,u8 y,u8 dis)
{
    if(x>=64)
        x=63;
    
    if(y>=128)
        y=127;
        
    int xPos=0,xPagePos=0;
    xPos=x/8;
    xPagePos=x%8;
    if(dis)
        Oled_RAM[xPos][y] |= (1 << xPagePos);
    else
        Oled_RAM[xPos][y] &= ~(1<<xPagePos);
}

void Oled_DrawLine(u8 x,u8 y,u8 x1,u8 y1,u8 dis)
{
    int deltaX=0,deltaY=0,temp=0;
    float k=0.0,b=0.0,tempX=0.0;
    
    if(x>x1){
        temp=x;x=x1;x1=temp;
        temp=y;y=y1;y1=temp;
    }
    
    deltaX = x1-x;
    deltaY = y1-y;
    
    if(deltaX == 0){
        if(y<y1){
            for(int tempY=0;tempY <= deltaY;tempY++){
                if(dis)
                    Draw_Point(x,y+tempY,DISPLAY);
                else
                    Draw_Point(x,y+tempY,UNDISPLAY);
            }
        }else{
            for(int tempY=0;tempY <= -deltaY;tempY++){
                if(dis)
                    Draw_Point(x,y1+tempY,DISPLAY);
                else
                    Draw_Point(x,y1+tempY,UNDISPLAY);
            }
        }
    }else if(deltaY==0){
        for(int tempX=0;tempX <= deltaX;tempX++){
            if(dis)
                Draw_Point(x+tempX,y,DISPLAY);
            else
                Draw_Point(x+tempX,y,UNDISPLAY);
        }
    }else{
        k=1.0*deltaY/deltaX;//б��
        b=1.0*y1-k*x1;
        
        if(k>1 || k<-1){
            for(tempX=x;tempX<x1;tempX+=0.01){
                temp = (int)round(k*tempX+b);
                if(dis)
                    Draw_Point(tempX,temp,DISPLAY);
                else
                    Draw_Point(tempX,temp,UNDISPLAY);
            }
        }else{
            for(;x<x1;x++){
                temp = (int)round(k*x+b);
                if(dis)
                    Draw_Point(x,temp,DISPLAY);
                else
                    Draw_Point(x,temp,UNDISPLAY);
            }
        }
    }
}

void Oled_DrawRect(u8 x1,u8 y1,u8 x2,u8 y2,u8 dis)
{
    Oled_DrawLine(x1,y1,x1,y2,dis);
    Oled_DrawLine(x1,y1,x2,y1,dis);
    Oled_DrawLine(x2,y1,x2,y2,dis);
    Oled_DrawLine(x1,y2,x2,y2,dis);
}

void Oled_FillRect(u8 x1,u8 y1,u8 x2,u8 y2,u8 dis)
{
    u8 temp=0;
    if(y1 > y2){
        temp = x1;x1=x2;x2=temp;
        temp = y1;y1=y2;y2=temp;
    }
    
    temp = y2-y1;
    for(int i=0;i<=temp;i++){
        Oled_DrawLine(x1,y1+i,x2,y1+i,dis);
    }
}

void Oled_DrawPic(u8 index)
{
    for(u8 page=0;page<8;page++)
    {
        Write_Cmd(0xB0|page);
        Write_Cmd(0x00);
        Write_Cmd(0x10);
        for(u8 j=0;j<128;j++){
            if(index==1){
                Write_Data(pic[page][j]);
            }else if(index==2){
                Write_Data(pic1[page][j]);
            }
        }
    }
}

void Oled_DrawCircle(u8 x,u8 y,u8 r,u8 dis)
{
    float angle,rx,ry;
    Draw_Point(x,y,dis);
    for(int i=180;i>-180;i--){
        angle = 1.0*i*PI/180;
        rx = ceil(x+r*cos(angle));
        ry = ceil(y+r*sin(angle));
        Draw_Point((int)rx,(int)ry,dis);
    }
    Oled_Refresh_Ram();
}
