#include "UltraSonic.h"
#include "infusion.h"

#define PWM_NUM 30

extern Airbubble airbubble;
extern NoBubble_State noBubble_State;

/*
***************************************************************************
* Function: // gpio_UltraSonic_init
* Description: //���ó������������GPIO
* Called By: // 
* Input: // 
* Return: //
* Others: //
*/
void gpio_UltraSonic_init(void)
{
		gpio_init_type  gpio_init_struct = {0};
		 
		/*enable the gpio click*/
		crm_periph_clock_enable(CRM_TMR1_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_TMR2_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_TMR14_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);
		crm_periph_clock_enable(CRM_IOMUX_PERIPH_CLOCK, TRUE);

		/*SONIC-TX PA8,TMR1_CH1 */
		gpio_init_struct.gpio_pins = GPIO_PINS_8;
		gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init(GPIOA, &gpio_init_struct);  
	
		
		/*SONIC-RX PB14 53 �������ⲿ�жϿ�,���ƽ���pwm����ĸ���*/
		gpio_init_struct.gpio_pins = GPIO_PINS_14;
		gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
		gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
		gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
		gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
		gpio_init(GPIOB, &gpio_init_struct);	
		gpio_exint_line_config(GPIO_PORT_SOURCE_GPIOB, GPIO_PINS_SOURCE14);
}

/*
***************************************************************************
* Function: // sonic_tx_pwm_init
* Description: //���ó������������PWM
* Called By: // 
* Input: // 
* Return: //
* Others: //
*/
void sonic_tx_pwm_init(void)
{
	tmr_output_config_type tmr_output_struct;

	tmr_repetition_counter_set(TMR1, PWM_NUM-1);
	tmr_base_init(TMR1,29,3); //pr div tmr_clk=240Mhz
	tmr_cnt_dir_set(TMR1, TMR_COUNT_UP);			//ctrl1_bit.cnt_dir
	tmr_clock_source_div_set(TMR1, TMR_CLOCK_DIV1); //ctrl1_bit.clkdiv
	tmr_output_default_para_init(&tmr_output_struct);
	tmr_output_struct.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_B;
	tmr_output_struct.oc_output_state = TRUE;
	tmr_output_struct.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
	tmr_output_struct.oc_idle_state = TRUE;
	tmr_output_channel_config(TMR1, TMR_SELECT_CHANNEL_1, &tmr_output_struct); //ctrl2,c m1_output_bit.c1octrl,  cctrl
	tmr_channel_value_set(TMR1, TMR_SELECT_CHANNEL_1, 15);   //c1dt  c1dtΪռ�ձ�
	tmr_one_cycle_mode_enable(TMR1, TRUE);
	tmr_output_enable(TMR1, TRUE);	
	tmr_interrupt_enable(TMR1, TMR_OVF_INT, TRUE);
	/* tmr2 trigger interrupt nvic init */
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
	nvic_irq_enable(TMR1_OVF_TMR10_IRQn, 0, 0);	
	tmr_counter_enable(TMR1, TRUE);
}

/*
***************************************************************************
* Function: // sonic_tmr_init
* Description: //tmr2���ó������Ͷ�ʱ����ÿ10ms����һ��
* Called By: // 
* Input: // 
* Return: //
* Others: //
*/
void sonic_tmr_init(void)
{
	/* enable tmr2 clock */
  crm_periph_clock_enable(CRM_TMR2_PERIPH_CLOCK, TRUE);
	tmr_base_init(TMR2,19,239);  //20us   1Mhz /20 5000HZ = 0.2ms  20us
  tmr_cnt_dir_set(TMR2, TMR_COUNT_UP);
	tmr_counter_value_set(TMR2, 0);
	tmr_period_buffer_enable(TMR2, TRUE);
  
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(TMR2_GLOBAL_IRQn, 0, 0);
	tmr_flag_clear(TMR2, TMR_OVF_FLAG); 
	tmr_interrupt_enable(TMR2, TMR_OVF_INT, FALSE); 
  tmr_counter_enable(TMR2, FALSE);		
	
	/* enable tmr6 clock */
  crm_periph_clock_enable(CRM_TMR6_PERIPH_CLOCK, TRUE);
	tmr_base_init(TMR6,99,2399);  //10ms
  tmr_cnt_dir_set(TMR6, TMR_COUNT_UP);
	tmr_counter_value_set(TMR6, 0);
	tmr_period_buffer_enable(TMR6, TRUE);
  
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(TMR6_GLOBAL_IRQn, 0, 0);
	tmr_flag_clear(TMR6, TMR_OVF_FLAG); 
	tmr_interrupt_enable(TMR6, TMR_OVF_INT, FALSE); 
  tmr_counter_enable(TMR6, FALSE);	
}

/*
***************************************************************************
* Function: // sonic_rx_receiver_init
* Description: //���ó�����������Ķ�ʱ���ж�
* Called By: // 
* Input: // 
* Return: //
* Others: //
*/
void sonic_rx_receiver_init(void)
{
	exint_init_type exint_init_struct;
	
  exint_default_para_init(&exint_init_struct);
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_select = EXINT_LINE_14;
  exint_init_struct.line_polarity = EXINT_TRIGGER_RISING_EDGE;
  exint_init(&exint_init_struct);

  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
  nvic_irq_enable(EXINT15_10_IRQn, 1, 0);
  exint_interrupt_enable(EXINT_LINE_14, FALSE);
	
}

/*
***************************************************************************
* Function: // airbubble_default_para_init
* Description: //������ؽṹ�������ʼ��
* Called By: // 
* Input: // 
* Return: //
* Others: //
*/
void airbubble_default_para_init(Airbubble *Airbubble_struct)
{

	Airbubble_struct->sonic_rx_num = 0;
	Airbubble_struct->no_bubble_state = Bubble_FALSE;
}


/*
***************************************************************************
* Function: // ultrasonic_init
* Description: //����ģ���ʼ��
* Called By: // 
* Input: // 
* Return: //
* Others: //
*/
void ultrasonic_init(void)
{
	airbubble_default_para_init(&airbubble);
	gpio_UltraSonic_init();
	
	sonic_tmr_init();
	sonic_rx_receiver_init();
	sonic_tx_pwm_init();

}




/*
***************************************************************************
* Function: // TMR2_GLOBAL_IRQHandler
* Description: //�ٴο��������ź�
* Called By: // 
* Input: // 
* Return: //
* Others: //���ս����󣬹رն�ʱ�����ر��ⲿ�жϣ��ж��������
*/
void TMR2_GLOBAL_IRQHandler(void)
{
	if(tmr_flag_get(TMR2, TMR_OVF_FLAG) != RESET)
	{
			exint_interrupt_enable(EXINT_LINE_14, FALSE); 
			tmr_counter_enable(TMR2, FALSE);
			tmr_interrupt_enable(TMR2, TMR_OVF_INT, FALSE);
			if(airbubble.sonic_rx_num >= 30)
			{
				airbubble.no_bubble_state = Bubble_TRUE;
				sensorpack.BubbleStatus = Bubble_FALSE;
			}
			else
			{
				airbubble.no_bubble_state	= Bubble_FALSE;
				sensorpack.BubbleStatus = Bubble_TRUE;
			}
			tmr_interrupt_enable(TMR6, TMR_OVF_INT, TRUE); 
			tmr_counter_enable(TMR6, TRUE);
	}
	tmr_flag_clear(TMR2, TMR_OVF_FLAG);    
}

/*
***************************************************************************
* Function: // TMR6_GLOBAL_IRQHandler
* Description: //�ٴο��������ź�
* Called By: // 
* Input: // 
* Return: //
* Others: //���ս������ٴο�������
*/
void TMR6_GLOBAL_IRQHandler(void)
{
	if(tmr_flag_get(TMR6, TMR_OVF_FLAG) != RESET)
	{
			
		tmr_interrupt_enable(TMR6, TMR_OVF_INT, FALSE); 
		tmr_counter_enable(TMR6, FALSE);
		tmr_counter_enable(TMR1, TRUE);
	}
	tmr_flag_clear(TMR6, TMR_OVF_FLAG);    
}
/*
***************************************************************************
* Function: // TMR1_OVF_TMR10_IRQHandler
* Description: //���͹̶�������ɺ�����ж�
* Called By: // 
* Input: // 
* Return: //
* Others: //30�����巢����Ϻ����ⲿ�жϽ��������źţ�������ʱ������ʱ����
*/
void TMR1_OVF_TMR10_IRQHandler(void)
{
	if(tmr_flag_get(TMR1, TMR_OVF_FLAG) != RESET)
	{
		airbubble.sonic_rx_num = 0;
		tmr_counter_enable(TMR2, TRUE);	
		tmr_interrupt_enable(TMR2, TMR_OVF_INT, TRUE); 
		exint_interrupt_enable(EXINT_LINE_14, TRUE);
		
	}
	tmr_flag_clear(TMR1, TMR_OVF_FLAG);
    
}

/*
***************************************************************************
* Function: // EXINT15_10_IRQHandler
* Description: //���͹̶�������ɺ�����ж�
* Called By: // 
* Input: // 
* Return: //
* Others: //��¼�������
*/
void EXINT15_10_IRQHandler(void)
{
  if(exint_flag_get(EXINT_LINE_14) != RESET)
  {
		airbubble.sonic_rx_num++;
    	exint_flag_clear(EXINT_LINE_14);
  }
}











