#include "PORT_CORE.h"
#include "Smart_Lock_Door.h"
#include "IRQH_Core.h"

#define F_CPU 16000000U
#include <util/delay.h>

int main(void)
{
uint8 i=0,element=0,mode=0;
PORT_INIT();
IRQH_SetGlobalINT(INT_ENABLE);
SmartLockDoor_Init();

while(i<5)
{
	element=EEPROM_ReadByte(0B01010000,i);
	Pass[i]=element;
	_delay_ms(1);
	i++;
}

while (1)
{
	mode=SmartLockDoor_SelectMode();
	if (mode=='1')
	{
		bool res=Get_Password();
		if (res==true)
		{
			SmartLockDoor_SetPassword();
		}
		else if (res==false)
		{
			Fire_Alarm();
		}
		else{}
	}
	else if (mode=='2')
	{
		bool res=Get_Password();
		if (res==true)
		{
			Open_Door();
		}
		else if (res==false)
		{
			Fire_Alarm();
		}
		else{}
	}
}
}