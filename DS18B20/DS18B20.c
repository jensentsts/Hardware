#include "ds18b20.h"
#include "stm32f10x.h"                  // Device header
#include "delay.h"

#define ds18b20_dq_gpiox GPIOA
#define ds18b20_dq_pin GPIO_Pin_3
#define ds18b20_dq_get GPIO_ReadInputDataBit(ds18b20_dq_gpiox, ds18b20_dq_pin)
#define ds18b20_dq_set(val) GPIO_WriteBit(ds18b20_dq_gpiox, ds18b20_dq_pin, (BitAction)(val))
#define ds18b20_dq_set_low ds18b20_dq_set(0)
#define ds18b20_dq_set_high ds18b20_dq_set(1)

void ds18b20_write(uint8_t dat){
	uint8_t i;
	for (i = 0; i < 8; ++i){
		ds18b20_dq_set_low;
		ds18b20_dq_set(dat & 0x01);
		delay_us(5);
		ds18b20_dq_set_high;
		dat >>= 1;
	}
	delay_us(5);
}

uint8_t ds18b20_read(void){
	uint8_t i = 0;
	uint8_t dat = 0;
	
	for (i = 0; i < 8; i++){
		ds18b20_dq_set_low;
		dat >>= 1;
		ds18b20_dq_set_high;
		if (ds18b20_dq_get){
			dat |= 0x80;
		}
		delay_us(5);
	}
	return dat;
}

uint8_t ds18b20_init(void){
	uint8_t init_flag = 0;
	
	GPIO_InitTypeDef gpio_init_structure;
	gpio_init_structure.GPIO_Mode = GPIO_Mode_Out_OD;
	gpio_init_structure.GPIO_Pin = ds18b20_dq_pin;
	gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ds18b20_dq_gpiox, &gpio_init_structure);
	
	
	ds18b20_dq_set_high;
	delay_us(12);
	ds18b20_dq_set_low;
	delay_us(80);
	ds18b20_dq_set_high;
	delay_us(10);
	init_flag = ds18b20_dq_get;
	delay_us(5);
	
	return init_flag;
}

float ds18b20_get(void){
	uint8_t high = 0, low = 0;
	
	ds18b20_init();
	ds18b20_write(0xCC);
	ds18b20_write(0x44);
	
	
	ds18b20_init();
	ds18b20_write(0xCC);
	ds18b20_write(0xBE);
	
	low = ds18b20_read();
	high = ds18b20_read();
	
	return ((high << 8) | low) / 16.0;
}
