#include "oled.h"
#include "oled_font.h"

static void Write_Cmd(u8 cmd)
{
    IIC_Start();
    IIC_Send_Byte(0x78);
    IIC_Check_ACK();//可能有误
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
    Write_Cmd(0x8D);//操作充电泵
    Write_Cmd(0x14);//打开
    Write_Cmd(0xAF);
}

void Oled_Off(void)
{
    Write_Cmd(0x8D);
    Write_Cmd(0x10);//关闭
    Write_Cmd(0xAE);
}

void Oled_Init(void)
{
    IIC_Init();
    Delay_Ms(200);
    
    Write_Cmd(0xA8);//设置分辨率
    Write_Cmd(0x3F);//0x3f : 128*64  0x1f  128*32
    
    Write_Cmd(0xDA);//设置COM硬件引脚配置，适应分辨率
    Write_Cmd(0x12);//0x12 : 0.96->128*64  0x02 : 0.91->128*32
    
    Write_Cmd(0xD3);//设置显示偏移
    Write_Cmd(0x00);//默认无偏移
    Write_Cmd(0x40);//设置显示开始0-63
    Write_Cmd(0xA1);//段SEGMENT重映射对于IIC四角OLED要设置为0xA1
    Write_Cmd(0x81);//对比度设置
    Write_Cmd(0x0F);//亮度设置0x00-0xFF,数值越大亮度越大
    Write_Cmd(0xA4);//输出遵循RAM内容，0x05输出忽略RAM内容
    Write_Cmd(0xA6);//显示方式正常显示，0xA7反向显示,逆码，0点亮还是1点亮
    Write_Cmd(0xD5);//设置显示时钟分频/振荡器频率
    Write_Cmd(0xF0);//设置分辨率值
    Write_Cmd(0x8D);//充电泵设置
    Write_Cmd(0x14);//允许在显示开启的时候使用，0x10:不允许在开启前使用
    Write_Cmd(0xAE);//显示关闭，0xAF显示开启
    Write_Cmd(0x20);//设置内存地址模式 水平/垂直/页寻址(默认)
    Write_Cmd(0x02);//水平0x00   垂直0x01    页寻址0x02
    Write_Cmd(0xC8);//设置COM扫描方式0xC0上下反置左到右  0xC8正常右到左
    Write_Cmd(0xB0);//为页寻址模式设置开启地址0-7
    Write_Cmd(0x00);//设置低列地址
    Write_Cmd(0x10);//设置高列地址
    Write_Cmd(0x40);//设置显示开始行 0-63
    Write_Cmd(0xD9);//设置预充电时期
    Write_Cmd(0x22);//充电时间
    Write_Cmd(0xDB);//设置取消选择级别
    Write_Cmd(0x20);//默认0x20 0.77xvcc
    Write_Cmd(0xAF);//显示开启
    
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
        k=1.0*deltaY/deltaX;//斜率
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
