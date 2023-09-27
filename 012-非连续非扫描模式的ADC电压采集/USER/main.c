#include "my_adc.h"
#include "math.h"

float v=0.0;
double ppm=0.0;

int main()
{
    MADC_Init();
    
    while(1)
    {
        v=Get_ValueV();
        ppm = pow(11.5428 * 7.04 * v/(3.3-v),(1/0.6549));
        for(int i=0;i<10000;i++);
    }
}
