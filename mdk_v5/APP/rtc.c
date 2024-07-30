#include "rtc.h"
#include "infusion.h"
#include "battery_manage.h"

calendar_type calendar;
extern __IO  uint8_t   DeviceFlag;


/* monthly correction data sheet */
const uint8_t table_week[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};

/* monmonth data table of common year */
const uint8_t mon_table[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/**
  * @brief  rtc peripheral initialization.
  * @param  calendar
  * @retval 0: rtc already init
            1: rtc init
  */
uint8_t rtc_init(calendar_type *calendar)
{
	
  exint_init_type exint_init_struct;

  /* config the exint line of the rtc alarm */
  exint_init_struct.line_select   = EXINT_LINE_17;
  exint_init_struct.line_enable   = TRUE;
  exint_init_struct.line_mode     = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_polarity = EXINT_TRIGGER_RISING_EDGE;
  exint_init(&exint_init_struct);
	
	
  /* enable pwc and bpr clocks */
  crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_BPR_PERIPH_CLOCK, TRUE);

  /* enable the battery-powered domain write operations */
  pwc_battery_powered_domain_access(TRUE);

  /* check if rtc is initialized */
  if(bpr_data_read(BPR_DATA1) != 0x1234)
  {
    /* reset battery-powered domain register */
    bpr_reset();
    
    /* enable the lext osc */
    crm_clock_source_enable(CRM_CLOCK_SOURCE_LICK, TRUE);
    /* wait lext is ready */
    while(crm_flag_get(CRM_LICK_STABLE_FLAG) == RESET);
    /* select the rtc clock source */
    crm_rtc_clock_select(CRM_RTC_CLOCK_LICK);

    /* enable rtc clock */
    crm_rtc_clock_enable(TRUE);

    /* wait for rtc registers update */
    rtc_wait_update_finish();

    /* wait for the register write to complete */
    rtc_wait_config_finish();

    /* enable the rtc second */
    rtc_interrupt_enable(RTC_TS_INT, TRUE);

    /* wait for the register write to complete */
    rtc_wait_config_finish();

    /* set rtc divider: set rtc period to 1sec */
    rtc_divider_set(40000);

    /* wait for the register write to complete */
    rtc_wait_config_finish();

    /* tamper pin disabled */
    bpr_tamper_pin_enable(FALSE);

    /* configure and enable rtc interrupt */
    nvic_irq_enable(RTC_IRQn, 0, 0);
	
	/* wait for the register write to complete */
    rtc_wait_config_finish();
    
    /* enable alarm interrupt */
    rtc_interrupt_enable(RTC_TA_INT, FALSE);
    
    /* wait for the register write to complete */
    rtc_wait_config_finish();
	
	rtc_flag_clear(RTC_TA_FLAG);

    /* set time */
    rtc_time_set(calendar);

    /* writes data to bpr register */
    bpr_data_write(BPR_DATA1, 0x1234);

    return 1;
  }
  else
  {

   
    /* enable the lext osc */
    crm_clock_source_enable(CRM_CLOCK_SOURCE_LICK, TRUE);
    /* wait lext is ready */
    while(crm_flag_get(CRM_LICK_STABLE_FLAG) == RESET);
    /* select the rtc clock source */
    crm_rtc_clock_select(CRM_RTC_CLOCK_LICK);

    /* enable rtc clock */
    crm_rtc_clock_enable(TRUE);

    /* wait for rtc registers update */
    rtc_wait_update_finish();

    /* wait for the register write to complete */
    rtc_wait_config_finish();

    /* enable the rtc second */
    rtc_interrupt_enable(RTC_TS_INT, TRUE);

    /* wait for the register write to complete */
    rtc_wait_config_finish();

    /* set rtc divider: set rtc period to 1sec */
    rtc_divider_set(40000);

    /* wait for the register write to complete */
    rtc_wait_config_finish();

    /* tamper pin disabled */
    bpr_tamper_pin_enable(FALSE);

    /* configure and enable rtc interrupt */
    nvic_irq_enable(RTC_IRQn, 0, 0);

    
    /* enable alarm interrupt */
    rtc_interrupt_enable(RTC_TA_INT, FALSE);
    
    /* wait for the register write to complete */
    rtc_wait_config_finish();
	
	rtc_flag_clear(RTC_TA_FLAG);

    return 0;
  }
}

/**
  * @brief  judge the leap year or common year.
  *         - mon       1  2  3  4  5  6  7  8  9  10 11 12
  *         - leap year   31 29 31 30 31 30 31 31 30 31 30 31
  *         - common year 31 28 31 30 31 30 31 31 30 31 30 31
  * @param  year
  * @retval 1: leap year
            2: common year
  */
uint8_t is_leap_year(uint16_t year)
{
  if(year % 4 == 0)
  {
    if(year % 100 == 0)
    {
      if(year % 400 == 0)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return 1;
    }
  }
  else
  {
    return 0;
  }
}

/**
  * @brief  set time. convert the input clock to a second.
  *         the time basic : 1970.1.1
  *         legitimate year: 1970 ~ 2099
  * @param  calendar
  * @retval 0: set time right.
  *         1: set time failed.
  */
uint8_t rtc_time_set(calendar_type *calendar)
{
  uint32_t t;
  uint32_t seccount = 0;

  if(calendar->year < 1970 || calendar->year > 2099)
  {
    return 1;
  }

  for(t = 1970; t < calendar->year; t++)
  {
    if(is_leap_year(t))
    {
      seccount += 31622400;
    }
    else
    {
      seccount += 31536000;
    }
  }

  calendar->mon -= 1;

  for(t = 0; t < calendar->mon; t++)
  {
    seccount += (uint8_t)mon_table[t] * 86400;

    if(is_leap_year(calendar->year) && t == 1)
    {
      seccount += 86400;
    }
  }

  seccount += (uint8_t)(calendar->day - 1) * 86400;

  seccount += (uint8_t)calendar->hour * 3600;

  seccount += (uint8_t)calendar->min * 60;

  seccount += calendar->sec;

  /* enable pwc and bpr clocks */
  crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_BPR_PERIPH_CLOCK, TRUE);

  /* enable write access to bpr domain */
  pwc_battery_powered_domain_access(TRUE);

  /* set the rtc counter value */
  rtc_counter_set(seccount);

  /* wait for the register write to complete */
  rtc_wait_config_finish();

  return 0;
}

/**
  * @brief  get current time.
  * @param  none.
  * @retval none.
  */
void rtc_time_get()
{
  static uint16_t daycnt = 0;
  uint32_t timecount = 0;
  uint32_t temp = 0;
  uint32_t temp1 = 0;

  timecount = rtc_counter_get();
  temp = timecount / 86400;

  if(daycnt != temp)
  {
    daycnt = temp;
    temp1 = 1970;

    while(temp >= 365)
    {
      if(is_leap_year(temp1))
      {
        if(temp >= 366)
        {
          temp -= 366;
        }
        else
        {
          temp1++;
          break;
        }
      }
      else
      {
        temp -= 365;
      }

      temp1++;
    }

    calendar.year = temp1;
    temp1 = 0;

    while(temp >= 28)
    {
      if(is_leap_year(calendar.year) && temp1 == 1)
      {
        if(temp >= 29)
        {
          temp -= 29;
        }
        else
        {
          break;
        }
      }
      else
      {
        if(temp >= mon_table[temp1])
        {
          temp -= mon_table[temp1];
        }
        else
        {
          break;
        }
      }

      temp1++;
    }

    calendar.mon = temp1 + 1;
    calendar.day = temp + 1;
  }

  temp = timecount % 86400;
  calendar.hour = temp / 3600;
  calendar.min = (temp % 3600) / 60;
  calendar.sec = (temp % 3600) % 60;
}



void RTC_IRQHandler(void)
{

  	flag_status PowerSupply;
	flag_status Cell;

  	PowerSupply = gpio_input_data_bit_read(GPIOC,GPIO_PINS_1);
	Cell = gpio_input_data_bit_read(GPIOC,GPIO_PINS_2);
	if(rtc_flag_get(RTC_TS_FLAG) != RESET)
	{
		if(DeviceFlag == DEVICE_STOP)       //进入关机
		{
			BatteryManagement_PD();
		}
		else if(DeviceFlag == DEVICE_STATUP)      //进入开机
		{
			BatteryManagement();
		}
		else if(PowerSupply ==RESET && Cell == RESET)     //金电容供电
		{ 
			BeepWork();
		}
		rtc_flag_clear(RTC_TS_FLAG);
	}
}





/**
  * @}
  */

/**
  * @}
  */
