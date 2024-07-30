

#include "clock_manage.h"

/**
  * @brief  system clock config program
  * @note   the system clock is configured as follow:
  *         - system clock        = hext / 2 * pll_mult
  *         - system clock source = pll (hext)
  *         - hext                = 8000000
  *         - sclk                = 240000000
  *         - ahbdiv              = 1
  *         - ahbclk              = 240000000
  *         - apb2div             = 2
  *         - apb2clk             = 120000000
  *         - apb1div             = 2
  *         - apb1clk             = 120000000
  *         - pll_mult            = 60
  *         - pll_range           = GT72MHZ (greater than 72 mhz)
  * @param  none
  * @retval none
  */
  
  
void system_clock_config(enum CLOCK_WHICH clock_which)
{
  /* reset crm */
  crm_reset();

  crm_clock_source_enable(CRM_CLOCK_SOURCE_HICK, TRUE);

   /* wait till HICK is ready */
  while(crm_flag_get(CRM_HICK_STABLE_FLAG) == RESET)
  {
  }

  
  if(clock_which==USE_240MHZ)
  {
  //给pll的只有4M
  /* config pll clock resource */
  crm_pll_config(CRM_PLL_SOURCE_HICK, CRM_PLL_MULT_60, CRM_PLL_OUTPUT_RANGE_GT72MHZ);
  //4*60=240MHZ
  
  }else if(clock_which==USE_1MHZ)
  {
   crm_pll_config(CRM_PLL_SOURCE_HICK, CRM_PLL_MULT_2, CRM_PLL_OUTPUT_RANGE_LE72MHZ);
   //4*2=8MHZ
	  
	  
  } 
  /* enable pll */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* wait till pll is ready */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
  {
  }

  /* config ahbclk */
  
  if(clock_which==USE_240MHZ)
  {
    crm_ahb_div_set(CRM_AHB_DIV_1); /* sysclk 8M/1  8M */ 
  }
  else if(clock_which==USE_1MHZ)
  {
    crm_ahb_div_set(CRM_AHB_DIV_8); /* sysclk 8M/16   500khz */
  }
  
  /* config apb2clk, the maximum frequency of APB1/APB2 clock is 120 MHz */
  crm_apb2_div_set(CRM_APB2_DIV_2);

  /* config apb1clk, the maximum frequency of APB1/APB2 clock is 120 MHz  */
  crm_apb1_div_set(CRM_APB1_DIV_2);

  /* enable auto step mode */
  crm_auto_step_mode_enable(TRUE);

  /* select pll as system clock source */
  crm_sysclk_switch(CRM_SCLK_PLL);

  /* wait till pll is used as system clock source */
  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL)
  {
  }

  /* disable auto step mode */
  crm_auto_step_mode_enable(FALSE);

  /* update system_core_clock global variable */
  system_core_clock_update();
}




//外部时钟 
//void system_clock_config(void)
//{
//  /* reset crm */
//  crm_reset();

//  crm_clock_source_enable(CRM_CLOCK_SOURCE_HEXT, TRUE);

//   /* wait till hext is ready */
//  while(crm_hext_stable_wait() == ERROR)
//  {
//  }

//  /* config pll clock resource */
//  crm_pll_config(CRM_PLL_SOURCE_HEXT_DIV, CRM_PLL_MULT_25, CRM_PLL_OUTPUT_RANGE_GT72MHZ);

//  /* config hext division */
//  crm_hext_clock_div_set(CRM_HEXT_DIV_2);

//  /* enable pll */
//  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);     

//  /* wait till pll is ready */
//  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
//  {
//  }

//  /* config ahbclk */
//  crm_ahb_div_set(CRM_AHB_DIV_1);

//  /* config apb2clk, the maximum frequency of APB1/APB2 clock is 100 MHz */
//  crm_apb2_div_set(CRM_APB2_DIV_2);

//  /* config apb1clk, the maximum frequency of APB1/APB2 clock is 100 MHz  */
//  crm_apb1_div_set(CRM_APB1_DIV_2);

//  /* enable auto step mode */
//  crm_auto_step_mode_enable(TRUE);

//  /* select pll as system clock source */
//  crm_sysclk_switch(CRM_SCLK_PLL);

//  /* wait till pll is used as system clock source */
//  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL)
//  {
//  }

//  /* disable auto step mode */
//  crm_auto_step_mode_enable(FALSE);

//  /* update system_core_clock global variable */
//  system_core_clock_update();
//}













