#include "ThisThread.h"
#include "mbed.h"
#include "BME280.h"

BME280 sensor(I2C_SDA, I2C_SCL);
DigitalOut oled1(LED1);
InterruptIn ibutton1(BUTTON1);

Ticker t;

static auto sleep_time = 1000ms;

void led_ticker()
{
    oled1=!oled1;
}
void pressed()
{
    t.detach(); 
    t.attach(&led_ticker, sleep_time);
}

char buf[2];

int main()
{
    t.attach(&led_ticker, sleep_time);
    while (true)
    {
        printf("%d degC, %d hPa, %d \n", (int)sensor.getTemperature(),(int)sensor.getPressure(), (int)sensor.getHumidity());
        if ((int)sensor.getTemperature()<28)
        {
            oled1=1;
        }
        if (((int)sensor.getTemperature()>=28) && ((int)sensor.getTemperature()<31))
        {
            oled1=1;
            ThisThread::sleep_for(2000ms);
            oled1=0;
            ThisThread::sleep_for(2000ms);
        }
        if ((int)sensor.getTemperature()>=31)
        {
             oled1=1;
            ThisThread::sleep_for(500ms);
            oled1=0;
            ThisThread::sleep_for(500ms);
        }

    }
    t.detach();
}

