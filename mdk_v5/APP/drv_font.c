#include "drv_font.h"
#include "spi.h"
//#include "GT32L24F0210.h"


/**
  * @brief  gpio configuration. ����PA5-PA7(Ϊ������)  ������ģʽ
  * @param  none
  * @retval none
  */
void gpio_font_config(void) 
{
  gpio_init_type gpio_initstructure;
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
  gpio_default_para_init(&gpio_initstructure);
	
	/* spi1 cs pin */
	gpio_initstructure.gpio_mode					 =GPIO_MODE_OUTPUT;
	gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_pull           = GPIO_PULL_NONE;
	gpio_initstructure.gpio_pins = GPIO_PINS_4;
	gpio_init(GPIOA, &gpio_initstructure);
  
	/* spi1 sck pin */
  gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_PUSH_PULL;
  gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_initstructure.gpio_pull           = GPIO_PULL_DOWN;
  gpio_initstructure.gpio_mode         = GPIO_MODE_MUX;
  gpio_initstructure.gpio_pins = GPIO_PINS_5;
  gpio_init(GPIOA, &gpio_initstructure);

  /* spi1 miso pin */  /****��������,�ӻ����****/
  gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
  gpio_initstructure.gpio_mode         = GPIO_MODE_INPUT;
  gpio_initstructure.gpio_pins = GPIO_PINS_6;
  gpio_init(GPIOA, &gpio_initstructure);

  /* spi1 mosi pin */ /****�������,�ӻ�����****/
  gpio_initstructure.gpio_pull           = GPIO_PULL_UP;
  gpio_initstructure.gpio_mode         = GPIO_MODE_MUX;
  gpio_initstructure.gpio_pins = GPIO_PINS_7;
  gpio_init(GPIOA, &gpio_initstructure);

}




void drv_font_init(void)
{
	
	spi1_config();
	gpio_font_config();
	//�ֿ��ʼ��
	//GT_Font_Init();
	
}




