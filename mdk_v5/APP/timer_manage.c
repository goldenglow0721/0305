
#include "at32f403a_407_board.h"
#include "clock_manage.h"
#include "timer_manage.h"

tmr_output_config_type tmr_oc_init_structure;



void tmr4_init(void)  //1HZ 用于电池管理
{

	crm_periph_clock_enable(CRM_TMR4_PERIPH_CLOCK, TRUE);
	// 240M/24000 = 10khz   
	tmr_base_init(TMR4,9999,23999);  

	tmr_cnt_dir_set(TMR4,TMR_COUNT_UP);

	/* overflow interrupt enable */
	tmr_interrupt_enable(TMR4, TMR_OVF_INT, TRUE); 

	/* tmr3 overflow interrupt nvic init */
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
	nvic_irq_enable(TMR4_GLOBAL_IRQn, 0, 0);

	/* enable tmr4 */
	tmr_period_buffer_enable(TMR4, TRUE);
	tmr_counter_enable(TMR4, TRUE);
}


void tmr5_init(void)  //用于ui中断
{
	crm_clocks_freq_type crm_clocks_freq_struct = {0};
	
	crm_periph_clock_enable(CRM_TMR5_PERIPH_CLOCK, TRUE);
	crm_clocks_freq_get(&crm_clocks_freq_struct);
	tmr_base_init(TMR5,9,(crm_clocks_freq_struct.apb2_freq * 2 / 10000) - 1);  
	tmr_cnt_dir_set(TMR5,TMR_COUNT_UP);

	/* overflow interrupt enable */
	tmr_interrupt_enable(TMR5, TMR_OVF_INT, TRUE); 

	/* tmr5 overflow interrupt nvic init */
	nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);
	nvic_irq_enable(TMR5_GLOBAL_IRQn, 0, 0);

	/* enable tmr5 */
	tmr_period_buffer_enable(TMR5, TRUE);
	tmr_counter_enable(TMR5, TRUE);
}


/*用于pwm输出beep*/
void tmr12_init(enum CLOCK_WHICH clock_which )
{
	if(clock_which == USE_240MHZ)
	{
	 tmr_base_init(TMR12,250-1,240-1); //pr div  ==4khz		
	}else if(clock_which == USE_1MHZ)
	{
	 tmr_base_init(TMR12,250-1,1-1); //pr div  ==4khz
	}
		
	tmr_clock_source_div_set(TMR12, TMR_CLOCK_DIV1); //ctrl1_bit.clkdiv
	tmr_cnt_dir_set(TMR12, TMR_COUNT_UP);			//ctrl1_bit.cnt_dir
	
	tmr_output_default_para_init(&tmr_oc_init_structure);
	tmr_oc_init_structure.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
	tmr_oc_init_structure.oc_idle_state = FALSE;
	tmr_oc_init_structure.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;
	tmr_oc_init_structure.oc_output_state = TRUE;
	tmr_output_channel_config(TMR12, TMR_SELECT_CHANNEL_2, &tmr_oc_init_structure); //ctrl2,c m1_output_bit.c1octrl,  cctrl
	tmr_channel_value_set(TMR12, TMR_SELECT_CHANNEL_2, 125-1);   //c1dt  c1dtΪռ�ձ�
	tmr_output_channel_buffer_enable(TMR12, TMR_SELECT_CHANNEL_2, TRUE); //cm1_output_bit.c1oben
	tmr_period_buffer_enable(TMR12, TRUE); //ctrl1_bit.prben
	/* tmr enable counter */	
	tmr_counter_enable(TMR12, FALSE); //ctrl1_bit.tmren
}


/*用于lcd背光亮度变化*/
void tmr13_init(void)
{
	static uint32_t temp;
	static uint32_t cnt=0;
	
	tmr_base_init(TMR13,500-1,240-1); //pr div  
	tmr_clock_source_div_set(TMR13, TMR_CLOCK_DIV1); //ctrl1_bit.clkdiv
	tmr_cnt_dir_set(TMR13, TMR_COUNT_UP);			//ctrl1_bit.cnt_dir
	
	tmr_output_default_para_init(&tmr_oc_init_structure);
	tmr_oc_init_structure.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;
	tmr_oc_init_structure.oc_idle_state = FALSE;
	tmr_oc_init_structure.oc_polarity = TMR_OUTPUT_ACTIVE_LOW;
	tmr_oc_init_structure.oc_output_state = TRUE;
	tmr_output_channel_config(TMR13, TMR_SELECT_CHANNEL_1, &tmr_oc_init_structure); //ctrl2,c m1_output_bit.c1octrl,  cctrl
	temp=tmr_period_value_get(TMR13);
	cnt = (uint32_t)(temp*0.8);
	tmr_channel_value_set(TMR13, TMR_SELECT_CHANNEL_1, cnt);   //c1dt  
	tmr_output_channel_buffer_enable(TMR13, TMR_SELECT_CHANNEL_1, TRUE); //cm1_output_bit.c1oben

	TMR13->brk   |=   0XC000;
	tmr_period_buffer_enable(TMR13, TRUE); //ctrl1_bit.prben
	/* tmr enable counter */
	tmr_counter_enable(TMR13, TRUE); //ctrl1_bit.tmren
}

