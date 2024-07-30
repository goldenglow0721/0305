
/* include --------------------------------------------------------------*/
#include "gt_port_vf.h"
#include "../gt.h"
#include "../src/others/gt_log.h"


/* private define -------------------------------------------------------*/



/* private typedef ------------------------------------------------------*/



/* static variables -----------------------------------------------------*/
static const gt_vfs_st virt_file_sys[] ={
	/* name, w, h, addr, size, is_alpha */
    {"f:img_120x110_daiji.png", 120, 110, 3739412, 39600, 1},
	{"f:img_120x110_guanji.png", 120, 110, 3779012, 39600, 1},
	{"f:img_130x50_L2_Btn.png", 130, 50, 3818612, 19500, 1},
	{"f:img_130x50_button120X50.png", 130, 50, 3838112, 19500, 1},
	{"f:img_15x20_charge.png", 15, 20, 3857612, 900, 1},
	{"f:img_19x30_Run.png", 19, 30, 3858512, 1710, 1},
	{"f:img_19x30_img_20x30_RunBright.png", 19, 30, 3860222, 1710, 1},
	{"f:img_20x30_46_keyboard_shift.png", 20, 30, 3861932, 1800, 1},
	{"f:img_214x30_Runstrip.png", 214, 30, 3863732, 19260, 1},
	{"f:img_242x162_1717237298272.jpg", 242, 162, 3882992, 117612, 1},
	{"f:img_30x30_AudioPause.png", 30, 30, 4000604, 2700, 1},
	{"f:img_325x160_PowerOff.png", 325, 160, 4003304, 156000, 1},
	{"f:img_480x320_ansha.png", 480, 320, 4159304, 307200, 0},
	{"f:img_480x320_fydb.png", 480, 320, 4466504, 307200, 0},
	{"f:img_480x320_yiye.png", 480, 320, 4773704, 307200, 0},
	{"f:img_480x320_zhongke.png", 480, 320, 5080904, 307200, 0},
	{"f:img_480x320_zhongxing_ch.png", 480, 320, 5388104, 307200, 0},
	{"f:img_480x320_zhongxing_ch_vet.png", 480, 320, 5695304, 307200, 0},
	{"f:img_480x320_zhongxing_en_vet.png", 480, 320, 6002504, 307200, 0},
	{"f:img_480x320_zhongxing_peo.png", 480, 320, 6309704, 307200, 0},
	{"f:img_48x48_electronic_locks_close_51_29.png", 48, 48, 6616904, 6912, 1},
	{"f:img_48x48_electronic_locks_open_51_28.png", 48, 48, 6623816, 6912, 1},
	{"f:img_50x44_40_dismiss_.png", 50, 44, 6630728, 6600, 1},
	{"f:img_50x50_start.png", 50, 50, 6637328, 7500, 1},
	{"f:img_55x35_outline_battery_45.png", 55, 35, 6644828, 5775, 1},
	{"f:img_58x60_setting_two_0_2.png", 58, 60, 6650603, 10440, 1},
	{"f:img_60x35_battery_00.png", 60, 35, 6661043, 6300, 1},
	{"f:img_60x40_infusionbottle.png", 60, 40, 6667343, 7200, 1},
	{"f:img_60x60_hamburger_button_0_3.png", 60, 60, 6674543, 10800, 1},
	{"f:img_60x60_more_app_0_2.png", 60, 60, 6685343, 10800, 1},
	{"f:img_60x60_refresh_0_1.png", 60, 60, 6696143, 10800, 1},
	{"f:img_60x60_tool_0_4.png", 60, 60, 6706943, 10800, 1},
	{"f:img_65x35_battery_0.png", 65, 35, 6717743, 6825, 1},
	{"f:img_65x35_battery_1.png", 65, 35, 6724568, 6825, 1},
	{"f:img_65x35_battery_2.png", 65, 35, 6731393, 6825, 1},
	{"f:img_65x35_battery_3.png", 65, 35, 6738218, 6825, 1},
	{"f:img_65x35_battery_4.png", 65, 35, 6745043, 6825, 1},
	{"f:img_65x35_battery_5.png", 65, 35, 6751868, 6825, 1},
	{"f:img_65x65_arrow_circle_down_2_16.png", 65, 65, 6758693, 12675, 1},
	{"f:img_65x65_arrow_circle_up_2_15.png", 65, 65, 6771368, 12675, 1},
	{"f:img_75x65_12_enter_left.png", 75, 65, 6784043, 14625, 1},
    {NULL,0,0,0,0},
};

/* macros ---------------------------------------------------------------*/



/* static functions -----------------------------------------------------*/


/* global functions / API interface -------------------------------------*/

#if GT_USE_MODE_FLASH
/**
 * @brief [flash] write or read data from flash
 *
 * @param data_write the data to be written
 * @param len_write the length of the data to be written
 * @param data_read the data to be read from flash
 * @param len_read the length need to read from flash
 *
 * @return uint32_t The number of bytes data read back preferentially,
 *      otherwise the number of bytes written successfully.
 */
extern uint32_t spi_wr(uint8_t * data_write, uint32_t len_write, uint8_t * data_read, uint32_t len_read);

#endif

void gt_port_vf_init(void)
{
#if GT_USE_MODE_FLASH
    gt_vf_init(virt_file_sys);

	gt_vf_drv_register(spi_wr);
#endif
}

/* end ------------------------------------------------------------------*/

