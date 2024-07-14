/*
  *
  **************************************************************************
  **                        STMicroelectronics				**
  **************************************************************************
  **                        marco.cali@st.com				**
  **************************************************************************
  *                                                                        *
  *			FTS API for MP test				 **
  *                                                                        *
  **************************************************************************
  **************************************************************************
  *
  */

/*!
  * \file ftsTest.h
  * \brief Contains all the definitions and structs related to the Mass
  *Production Test
  */

#ifndef FTS_TEST_H
#define FTS_TEST_H

#include "ftsSoftware.h"
#include "../../../huawei_ts_kit.h"
#ifndef LIMITS_H_FILE
/* /< Name of the Production Test Limit File */
#define LIMITS_FILE			"stm_fts_production_limits.csv"
#else
#define LIMITS_FILE		"NULL"
#endif

#define WAIT_FOR_FRESH_FRAMES	200	/* /< Time in ms to wait after start to
					 * sensing before reading a frame */
#define WAIT_AFTER_SENSEOFF	50	/* /< Time in ms to wait after stop
					 * sensing and before reading a frame
					 * from memory */

#define NO_INIT			0	/* /< No Initialization required during
					 * the MP */

#define RETRY_INIT_BOOT		3	/* /< number of retry of the
					 * initialization process at boot */

/** @defgroup mp_test Mass Production Test
  * Mass production test API.
  * Mass Production Test (MP) should be executed at least one time in the life
  * of every device \n
  * It used to verify that tit is not present any hardware damage and
  * initialize some value of the chip in order to guarantee the working
  * performance \n
  * The MP test is made up by 3 steps:
  * - ITO test = production_test_ito() \n
  * - Initialization = production_test_initialization() \n
  * - Data Test = production_test_data(),
  * it is possible to select which items test thanks to the TestToDo struct\n
  * To execute the Data Test it is mandatory load some thresholds that
  * are stored in the Limit File.
  * @{
  */

/** @defgroup limit_file Limit File
  * @ingroup mp_test
  * Production Test Limit File is a csv which contains thresholds of the data to
  * test.
  * This file can be loaded from the file system or stored as a header file
  * according to the LIMITS_H_FILE define \n
  * For each selectable test item there can be one or more associated labels
  * which store the corresponding thresholds \n
  * @{
  */
/* LABELS PRODUCTION TEST LIMITS FILE */
/** @defgroup test_labels Test Items Labels
  * @ingroup limit_file
  * Labels present in the Limit File and associated to the test items of
  *TestToDo
  * @{
  */
#define MS_STRENGTH_MIN_MAX			"MS_STRENGTH_DATA_MIN_MAX" 
#define MS_RAW_MIN_MAX			"MS_RAW_DATA_MIN_MAX"
#define MS_RAW_EACH_NODE_MIN 	"MS_RAW_DATA_EACH_MIN"
#define MS_RAW_EACH_NODE_MAX	"MS_RAW_DATA_EACH_MAX"
#define MS_RAW_GAP			"MS_RAW_DATA_GAP"
#define MS_RAW_ADJH			"MS_RAW_DATA_ADJ_HORIZONTAL"
#define MS_RAW_ADJV			"MS_RAW_DATA_ADJ_VERTICAL"
#define MS_RAW_ITO_ADJH			"MS_RAW_ITO_DATA_ADJ_HORIZONTAL"
#define MS_RAW_ITO_ADJV			"MS_RAW_ITO_DATA_ADJ_VERTICAL"
#define MS_RAW_LP_MIN_MAX		"MS_RAW_LOWPOWER_DATA_MIN_MAX"
#define MS_RAW_LP_EACH_NODE_MIN 	"MS_RAW_LOWPOWER_DATA_EACH_MIN"
#define MS_RAW_LP_EACH_NODE_MAX		"MS_RAW_LOWPOWER_DATA_EACH_MAX"
#define MS_RAW_LP_GAP			"MS_RAW_LOWPOWER_DATA_GAP"
#define MS_RAW_LP_ADJH			"MS_RAW_LOWPOWER_DATA_ADJ_HORIZONTAL"
#define MS_RAW_LP_ADJV			"MS_RAW_LOWPOWER_DATA_ADJ_VERTICAL"
#define MS_RAW_ADJH_GAP		"MS_RAW_DATA_ADJ_HORIZONTAL_P2P"
#define MS_RAW_ADJV_GAP		"MS_RAW_DATA_ADJ_VERTICAL_P2P"
#define MS_RAW_ADJ_PEAK			"MS_RAW_DATA_ADJ_PEAK"
#define MS_CX1_MIN_MAX			"MS_TOUCH_ACTIVE_CX1_MIN_MAX"
#define MS_CX2_MAP_MIN			"MS_TOUCH_ACTIVE_CX2_MIN"
#define MS_CX2_MAP_MAX			"MS_TOUCH_ACTIVE_CX2_MAX"
#define MS_CX2_ADJH_MAP_MAX		"MS_TOUCH_ACTIVE_CX2_ADJ_HORIZONTAL"
#define MS_CX2_ADJV_MAP_MAX		"MS_TOUCH_ACTIVE_CX2_ADJ_VERTICAL"
#define MS_TOTAL_CX_MAP_MIN		"MS_TOUCH_ACTIVE_TOTAL_CX_MIN"
#define MS_TOTAL_CX_MAP_MAX		"MS_TOUCH_ACTIVE_TOTAL_CX_MAX"
#define MS_TOTAL_CX_ADJH_MAP_MAX "MS_TOUCH_ACTIVE_TOTAL_CX_ADJ_HORIZONTAL"
#define MS_TOTAL_CX_ADJV_MAP_MAX	"MS_TOUCH_ACTIVE_TOTAL_CX_ADJ_VERTICAL"
#define MS_CX1_LP_MIN_MAX		"MS_TOUCH_LOWPOWER_CX1_MIN_MAX"
#define MS_CX2_LP_MAP_MIN		"MS_TOUCH_LOWPOWER_CX2_MIN"
#define MS_CX2_LP_MAP_MAX		"MS_TOUCH_LOWPOWER_CX2_MAX"
#define MS_CX2_ADJH_LP_MAP_MAX	"MS_TOUCH_LOWPOWER_CX2_ADJ_HORIZONTAL"
#define MS_CX2_ADJV_LP_MAP_MAX	"MS_TOUCH_LOWPOWER_CX2_ADJ_VERTICAL"
#define MS_TOTAL_CX_LP_MAP_MIN	"MS_TOUCH_LOWPOWER_TOTAL_CX_MIN"
#define MS_TOTAL_CX_LP_MAP_MAX	"MS_TOUCH_LOWPOWER_TOTAL_CX_MAX"
#define MS_TOTAL_CX_ADJH_LP_MAP_MAX "MS_TOUCH_LOWPOWER_TOTAL_CX_ADJ_HORIZONTAL"
#define MS_TOTAL_CX_ADJV_LP_MAP_MAX "MS_TOUCH_LOWPOWER_TOTAL_CX_ADJ_VERTICAL"
#define SS_RAW_FORCE_MIN_MAX		"SS_RAW_DATA_FORCE_MIN_MAX"
#define SS_RAW_FORCE_EACH_NODE_MIN 	"SS_RAW_DATA_FORCE_EACH_MIN"
#define SS_RAW_FORCE_EACH_NODE_MAX	"SS_RAW_DATA_FORCE_EACH_MAX"
#define SS_RAW_SENSE_MIN_MAX		"SS_RAW_DATA_SENSE_MIN_MAX"
#define SS_RAW_SENSE_EACH_NODE_MIN 	"SS_RAW_DATA_SENSE_EACH_MIN"
#define SS_RAW_SENSE_EACH_NODE_MAX	"SS_RAW_DATA_SENSE_EACH_MAX"

#define SS_STRENGTH_FORCE_MIN_MAX		"SS_STRENGTH_DATA_FORCE_MIN_MAX"
#define SS_STRENGTH_SENSE_MIN_MAX		"SS_STRENGTH_DATA_SENSE_MIN_MAX"

#define SS_RAW_FORCE_GAP		"SS_RAW_DATA_FORCE_GAP"
#define SS_RAW_SENSE_GAP		"SS_RAW_DATA_SENSE_GAP"
#define SS_RAW_LP_FORCE_MIN_MAX		"SS_RAW_LOWPOWER_DATA_FORCE_MIN_MAX"
#define SS_RAW_LP_SENSE_MIN_MAX		"SS_RAW_LOWPOWER_DATA_SENSE_MIN_MAX"
#define SS_RAW_LP_FORCE_EACH_NODE_MIN 	"SS_RAW_LOWPOWER_DATA_FORCE_EACH_MIN"
#define SS_RAW_LP_FORCE_EACH_NODE_MAX	"SS_RAW_LOWPOWER_DATA_FORCE_EACH_MAX"
#define SS_RAW_LP_SENSE_MIN_MAX		"SS_RAW_LOWPOWER_DATA_SENSE_MIN_MAX"
#define SS_RAW_LP_SENSE_EACH_NODE_MIN 	"SS_RAW_LOWPOWER_DATA_SENSE_EACH_MIN"
#define SS_RAW_LP_SENSE_EACH_NODE_MAX 	"SS_RAW_LOWPOWER_DATA_SENSE_EACH_MAX"
#define SS_RAW_LP_FORCE_GAP		"SS_RAW_LOWPOWER_DATA_FORCE_GAP"
#define SS_RAW_LP_SENSE_GAP		"SS_RAW_LOWPOWER_DATA_SENSE_GAP"
#define SS_IX1_FORCE_MIN_MAX		"SS_TOUCH_ACTIVE_IX1_FORCE_MIN_MAX"
#define SS_IX1_SENSE_MIN_MAX		"SS_TOUCH_ACTIVE_IX1_SENSE_MIN_MAX"
#define SS_CX1_FORCE_MIN_MAX		"SS_TOUCH_ACTIVE_CX1_FORCE_MIN_MAX"
#define SS_CX1_SENSE_MIN_MAX		"SS_TOUCH_ACTIVE_CX1_SENSE_MIN_MAX"
#define SS_IX2_FORCE_MAP_MIN		"SS_TOUCH_ACTIVE_IX2_FORCE_MIN"
#define SS_IX2_FORCE_MAP_MAX		"SS_TOUCH_ACTIVE_IX2_FORCE_MAX"
#define SS_IX2_SENSE_MAP_MIN		"SS_TOUCH_ACTIVE_IX2_SENSE_MIN"
#define SS_IX2_SENSE_MAP_MAX		"SS_TOUCH_ACTIVE_IX2_SENSE_MAX"
#define SS_IX2_FORCE_ADJV_MAP_MAX	"SS_TOUCH_ACTIVE_IX2_ADJ_VERTICAL"
#define SS_IX2_SENSE_ADJH_MAP_MAX	"SS_TOUCH_ACTIVE_IX2_ADJ_HORIZONTAL"
#define SS_CX2_FORCE_MAP_MIN		"SS_TOUCH_ACTIVE_CX2_FORCE_MIN"
#define SS_CX2_FORCE_MAP_MAX		"SS_TOUCH_ACTIVE_CX2_FORCE_MAX"
#define SS_CX2_SENSE_MAP_MIN		"SS_TOUCH_ACTIVE_CX2_SENSE_MIN"
#define SS_CX2_SENSE_MAP_MAX		"SS_TOUCH_ACTIVE_CX2_SENSE_MAX"
#define SS_CX2_FORCE_ADJV_MAP_MAX	"SS_TOUCH_ACTIVE_CX2_ADJ_VERTICAL"
#define SS_CX2_SENSE_ADJH_MAP_MAX	"SS_TOUCH_ACTIVE_CX2_ADJ_HORIZONTAL"


/* TOTAL SS */
#define SS_TOTAL_IX_FORCE_MAP_MIN	"SS_TOUCH_ACTIVE_TOTAL_IX_FORCE_MIN"
#define SS_TOTAL_IX_FORCE_MAP_MAX	"SS_TOUCH_ACTIVE_TOTAL_IX_FORCE_MAX"
#define SS_TOTAL_IX_SENSE_MAP_MIN	"SS_TOUCH_ACTIVE_TOTAL_IX_SENSE_MIN"
#define SS_TOTAL_IX_SENSE_MAP_MAX	"SS_TOUCH_ACTIVE_TOTAL_IX_SENSE_MAX"
#define SS_TOTAL_IX_FORCE_ADJV_MAP_MAX	"SS_TOUCH_ACTIVE_TOTAL_IX_ADJ_VERTICAL"
#define SS_TOTAL_IX_SENSE_ADJH_MAP_MAX \
	"SS_TOUCH_ACTIVE_TOTAL_IX_ADJ_HORIZONTAL"
#define SS_TOTAL_CX_FORCE_MAP_MIN	"SS_TOUCH_ACTIVE_TOTAL_CX_FORCE_MIN"
#define SS_TOTAL_CX_FORCE_MAP_MAX	"SS_TOUCH_ACTIVE_TOTAL_CX_FORCE_MAX"
#define SS_TOTAL_CX_SENSE_MAP_MIN	"SS_TOUCH_ACTIVE_TOTAL_CX_SENSE_MIN"
#define SS_TOTAL_CX_SENSE_MAP_MAX	"SS_TOUCH_ACTIVE_TOTAL_CX_SENSE_MAX"
#define SS_TOTAL_CX_FORCE_ADJV_MAP_MAX	"SS_TOUCH_ACTIVE_TOTAL_CX_ADJ_VERTICAL"
#define SS_TOTAL_CX_SENSE_ADJH_MAP_MAX \
	"SS_TOUCH_ACTIVE_TOTAL_CX_ADJ_HORIZONTAL"

/* Idle (LP)  version*/
#define SS_IX1_LP_FORCE_MIN_MAX		"SS_TOUCH_IDLE_IX1_FORCE_MIN_MAX"
#define SS_IX1_LP_SENSE_MIN_MAX	    "SS_TOUCH_IDLE_IX1_SENSE_MIN_MAX"
#define SS_CX1_LP_FORCE_MIN_MAX        "SS_TOUCH_IDLE_CX1_FORCE_MIN_MAX"
#define SS_CX1_LP_SENSE_MIN_MAX        "SS_TOUCH_IDLE_CX1_SENSE_MIN_MAX"
#define SS_IX2_LP_FORCE_MAP_MIN        "SS_TOUCH_IDLE_IX2_FORCE_MIN"
#define SS_IX2_LP_FORCE_MAP_MAX        "SS_TOUCH_IDLE_IX2_FORCE_MAX"
#define SS_IX2_LP_SENSE_MAP_MIN        "SS_TOUCH_IDLE_IX2_SENSE_MIN"
#define SS_IX2_LP_SENSE_MAP_MAX        "SS_TOUCH_IDLE_IX2_SENSE_MAX"
#define SS_IX2_LP_FORCE_ADJV_MAP_MAX    "SS_TOUCH_IDLE_IX2_ADJ_VERTICAL"
#define SS_IX2_LP_SENSE_ADJH_MAP_MAX    "SS_TOUCH_IDLE_IX2_ADJ_HORIZONTAL"
#define SS_CX2_LP_FORCE_MAP_MIN        "SS_TOUCH_IDLE_CX2_FORCE_MIN"
#define SS_CX2_LP_FORCE_MAP_MAX        "SS_TOUCH_IDLE_CX2_FORCE_MAX"
#define SS_CX2_LP_SENSE_MAP_MIN        "SS_TOUCH_IDLE_CX2_SENSE_MIN"
#define SS_CX2_LP_SENSE_MAP_MAX        "SS_TOUCH_IDLE_CX2_SENSE_MAX"
#define SS_CX2_LP_FORCE_ADJV_MAP_MAX    "SS_TOUCH_IDLE_CX2_ADJ_VERTICAL"
#define SS_CX2_LP_SENSE_ADJH_MAP_MAX    "SS_TOUCH_IDLE_CX2_ADJ_HORIZONTAL"


/* TOTAL SS */
#define SS_TOTAL_IX_LP_FORCE_MAP_MIN    "SS_TOUCH_IDLE_TOTAL_IX_FORCE_MIN"
#define SS_TOTAL_IX_LP_FORCE_MAP_MAX    "SS_TOUCH_IDLE_TOTAL_IX_FORCE_MAX"
#define SS_TOTAL_IX_LP_SENSE_MAP_MIN    "SS_TOUCH_IDLE_TOTAL_IX_SENSE_MIN"
#define SS_TOTAL_IX_LP_SENSE_MAP_MAX    "SS_TOUCH_IDLE_TOTAL_IX_SENSE_MAX"
#define SS_TOTAL_IX_LP_FORCE_ADJV_MAP_MAX \
    "SS_TOUCH_IDLE_TOTAL_IX_ADJ_VERTICAL"
#define SS_TOTAL_IX_LP_SENSE_ADJH_MAP_MAX \
    "SS_TOUCH_IDLE_TOTAL_IX_ADJ_HORIZONTAL"
#define SS_TOTAL_CX_LP_FORCE_MAP_MIN    "SS_TOUCH_IDLE_TOTAL_CX_FORCE_MIN"
#define SS_TOTAL_CX_LP_FORCE_MAP_MAX    "SS_TOUCH_IDLE_TOTAL_CX_FORCE_MAX"
#define SS_TOTAL_CX_LP_SENSE_MAP_MIN    "SS_TOUCH_IDLE_TOTAL_CX_SENSE_MIN"
#define SS_TOTAL_CX_LP_SENSE_MAP_MAX    "SS_TOUCH_IDLE_TOTAL_CX_SENSE_MAX"
#define SS_TOTAL_CX_LP_FORCE_ADJV_MAP_MAX \
    "SS_TOUCH_IDLE_TOTAL_CX_ADJ_VERTICAL"
#define SS_TOTAL_CX_LP_SENSE_ADJH_MAP_MAX \
    "SS_TOUCH_IDLE_TOTAL_CX_ADJ_HORIZONTAL"

/* CONSTANT TOTAL IX */
#define SS_IX1_FORCE_W            "IX1_FORCE_W"
#define SS_IX2_FORCE_W            "IX2_FORCE_W"
#define SS_IX1_SENSE_W            "IX1_SENSE_W"
#define SS_IX2_SENSE_W            "IX2_SENSE_W"
/** @}*/
#define SAVE_FLAG_RETRY        3

#define FTS_LIMIT_FILE_NAME_MAX_LEN    64
#define ST_NP_TEST_RES_BUF_LEN    50


#define    MUTUALRAWTYPE 0x01
#define SELFFORCERAWTYPE 0x02
#define SELFSENSERAWTYPE 0x03
#define STRENGTHTYPE 0x04
#define MUTUALCOMPENSATIONTYPE 0x05
#define SSFORCEPRXTYPE 0x06
#define SSSENSEPRXTYPE 0x07
#define SSSENSEDATATYPE 0x08
typedef struct {
    bool I2c_Check;
    bool Init_Res;
    bool MutualRawRes;
    bool MutualRawResGap;
    bool MutualCx2Res;
    bool MutualCx2Adj;
    bool MutualStrengthRes;
    bool SelfForceRawRes;
    bool SelfForceIxTotalRes;
    bool SelfSenseRawRes;
    bool SelfSenseStrengthData;
    bool SelfForceStrengthData;
    bool SelfSenseIxTotalRes;
    bool ITO_Test_Res;
    bool SelfSenseData;
    char mutal_raw_res_buf[ST_NP_TEST_RES_BUF_LEN];
    char mutal_noise_res_buf[ST_NP_TEST_RES_BUF_LEN];
    char mutal_cal_res_buf[ST_NP_TEST_RES_BUF_LEN];

} TestResult;

/**
  * Struct used to specify which test perform during the Mass Production Test.
  * For each test item selected in this structure, there should be one or
  * more labels associated in the Limit file from where load the thresholds
  */
typedef struct {
    int MutualRaw;    /* /< MS Raw min/Max test */
    int MutualRawMap;    /* /< MS Raw min/Max test for each node */
    int MutualRawGap;    /* /< MS Raw Gap(max-min) test */
    int MutualRawAdj;    /* /< MS Raw Adjacent test */
    int MutualRawAdjGap;    /* /< MS Raw Adjacent Gap (max-min) test */
    int MutualRawAdjPeak;    /* /< MS Raw Adjacent Peak
                 * max(max(adjv),max(adjh)) test */
    int MutualRawLP;    /* /< MS Low Power Raw min/Max test */
    int MutualRawMapLP;    /* /< MS Low Power Raw min/Max test
                 * for each node */
    int MutualRawGapLP;    /* /< MS Low Power Raw Gap(max-min) test */
    int MutualRawAdjLP;    /* /< MS Low Power Raw Adjacent test */
    int MutualRawAdjITO;    /* /< MS Raw Adjacent test during ITO test */

    int MutualCx1;    /* /< MS Cx1 min/Max test */
    int MutualCx2;    /* /< MS Cx2 min/Max (for each node) test */
    int MutualCx2Adj;    /* /< MS Vertical and Horizontal Adj Cx2 min/Max
                 * (for each node) test */
    int MutualCxTotal;    /* /< MS Total Cx min/Max (for each node) test
                 * */
    int MutualCxTotalAdj;    /* /< MS Total vertical and Horizontal Adj Cx2
                 * min/Max (for each node) test */

    int MutualCx1LP;    /* /< MS LowPower Cx1 min/Max test */
    int MutualCx2LP;    /* /< MS LowPower Cx2 min/Max (for each node) test */
    int MutualCx2AdjLP;    /* /< MS LowPower Vertical and Horizontal Adj Cx2 min/Max
                 * (for each node) test */
    int MutualCxTotalLP;    /* /< MS Total LowPower Cx min/Max (for each node) test
                 * */
    int MutualCxTotalAdjLP;    /* /< MS Total LowPower vertical and Horizontal Adj Cx2
                 * min/Max (for each node) test */

    int MutualKeyRaw;    /* /< MS Raw Key min/Max test */
    int MutualKeyCx1;    /* /< MS Cx1 Key min/Max test */
    int MutualKeyCx2;    /* /< MS Cx2 Key min/Max (for each node) test */
    int MutualKeyCxTotal;    /* /< MS Total Cx Key min/Max (for each node)
                 * test */

    int SelfForceRaw;    /* /< SS Force Raw min/Max test */
    int SelfForceRawGap;    /* /< SS Force Raw Gap(max-min) test */
    int SelfForceRawMap;    /* /< SS Force Raw min/Max Map test */
    int SelfForceRawLP;    /* /< SS Low Power Force Raw min/Max test */
    int SelfForceRawGapLP;    /* /< SS Low Power Force Raw Gap(max-min)test */
    int SelfForceRawMapLP;    /* /< SS Low Power Force Raw min/Max Map test */

    int SelfForceIx1;    /* /< SS Force Ix1 min/Max test */
    int SelfForceIx2;    /* /< SS Force Ix2 min/Max (for each node) test
                 * */
    int SelfForceIx2Adj;    /* /< SS Vertical Adj Force Ix2 min/Max
                  * (for each node) test */
    int SelfForceIxTotal;    /* /< SS Total Force Ix min/Max (for each node)
                 * test */
    int SelfForceIxTotalAdj;    /* /< SS Total Vertical Adj Force Ix
                     * min/Max (for each node) test */
    int SelfForceCx1;    /* /< SS Force Cx1 min/Max test */
    int SelfForceCx2; /* /< SS Force Cx2 min/Max (for each node) test */
    int SelfForceCx2Adj;    /* /< SS Vertical Adj Force Cx2 min/Max (for
                 * each node) test */
    int SelfForceCxTotal;    /* /< SS Total Force Cx min/Max (for each node)
                 * test */
    int SelfForceCxTotalAdj;    /* /< SS Total Vertical Adj Force Cx
                     * min/Max (for each node) test */

    int SelfForceIx1LP;    /* /< SS LP Force Ix1 min/Max test */
    int SelfForceIx2LP;    /* /< SS LP Force Ix2 min/Max (for each node)
                 *  test */
    int SelfForceIx2AdjLP;    /* /< SS LP Vertical Adj Force Ix2 min/Max
                  * (for each node) test */
    int SelfForceIxTotalLP;    /* /< SS LP Total Force Ix min/Max
                 * (for each node) test */
    int SelfForceIxTotalAdjLP;    /* /< SS LP Total Vertical Adj Force Ix
                     * min/Max (for each node) test */
    int SelfForceCx1LP;    /* /< SS LP Force Cx1 min/Max test */
    int SelfForceCx2LP; /* /< SS LP Force Cx2 min/Max (for each node) test */
    int SelfForceCx2AdjLP;    /* /< SS LP Vertical Adj Force Cx2 min/Max (for
                 * each node) test */
    int SelfForceCxTotalLP;    /* /< SS LP Total Force Cx min/Max
                 * (for each node) test */
    int SelfForceCxTotalAdjLP;    /* /< SS LP Total Vertical Adj Force Cx
                     * min/Max (for each node) test */

    int SelfSenseRaw;    /* /< SS Sense Raw min/Max test */
    int SelfSenseRawGap;    /* /< SS Sense Raw Gap(max-min) test */
    int SelfSenseRawMap;    /* /< SS Sense Raw min/Max test for each node */
    int SelfSenseRawLP;    /* /< SS Low Power Sense Raw min/Max test */
    int SelfSenseRawGapLP;    /* /< SS Low Power Sense Raw Gap(max-min) test */
    int SelfSenseRawMapLP;    /* /< SS Low Power Sense Raw min/Max test for
                 * each node */

    int SelfSenseIx1;    /* /< SS Sense Ix1 min/Max test */
    int SelfSenseIx2; /* /< SS Sense Ix2 min/Max (for each node) test */
    int SelfSenseIx2Adj;    /* /< SS Horizontal Adj Sense Ix2 min/Max
                  * (for each node) test */
    int SelfSenseIxTotal;    /* /< SS Total Horizontal Sense Ix min/Max
                  * (for each node) test */
    int SelfSenseIxTotalAdj;    /* /< SS Total Horizontal Adj Sense Ix
                     * min/Max (for each node) test */
    int SelfSenseCx1;    /* /< SS Sense Cx1 min/Max test */
    int SelfSenseCx2; /* /< SS Sense Cx2 min/Max (for each node) test */
    int SelfSenseCx2Adj;    /* /< SS Horizontal Adj Sense Cx2 min/Max
                  * (for each node) test */
    int SelfSenseCxTotal;    /* /< SS Total Sense Cx min/Max (for each node)
                 * test */
    int SelfSenseCxTotalAdj;    /* /< SS Total Horizontal Adj Sense Cx
                     * min/Max (for each node) test */

    int SelfSenseIx1LP;    /* /< SS LP Sense Ix1 min/Max test */
    int SelfSenseIx2LP; /* /< SS LP Sense Ix2 min/Max (for each node)
                 * test */
    int SelfSenseIx2AdjLP;    /* /< SS LP Horizontal Adj Sense Ix2 min/Max
                  * (for each node) test */
    int SelfSenseIxTotalLP;    /* /< SS LP Total Horizontal Sense Ix min/Max
                  * (for each node) test */
    int SelfSenseIxTotalAdjLP; /* /< SS LP Total Horizontal Adj Sense Ix
                     * min/Max (for each node) test */
    int SelfSenseCx1LP;    /* /< SS LP Sense Cx1 min/Max test */
    int SelfSenseCx2LP; /* /< SS LP Sense Cx2 min/Max (for each node)
                * test */
    int SelfSenseCx2AdjLP;    /* /< SS LP Horizontal Adj Sense Cx2 min/Max
                  * (for each node) test */
    int SelfSenseCxTotalLP;    /* /< SS LP Total Sense Cx min/Max
                 * (for each node) test */
    int SelfSenseCxTotalAdjLP; /* /< SS LP Total Horizontal Adj Sense Cx
                     * min/Max (for each node) test */
} TestToDo;


#define MAX_LIMIT_FILE_NAME 100    /* /< max number of chars of the limit file name
                 * */

/**
  * Struct which store the data coming from a Production Limit File
  */
typedef struct {
    char *data;    /* /< pointer to an array of char which contains
              * the content of the Production Limit File */
    int size;    /* /< size of data */
    char name[MAX_LIMIT_FILE_NAME];    /* /< identifier of the source from
                     * where the limits data were loaded (if
                     * loaded from a file it will be the
                     * file name, while if loaded from .h
                     * will be "NULL") */
} LimitFile;



int initTestToDo(void);
/**@}*/

/**@}*/


int computeAdjHoriz(i8 *data, int row, int column, u8 **result);
int computeAdjHorizTotal(short *data, int row, int column, u16 **result);
int computeAdjVert(i8 *data, int row, int column, u8 **result);
int computeAdjVertTotal(short *data, int row, int column, u16 **result);
int computeAdjHorizFromU(u8 *data, int row, int column, u8 **result);
int computeAdjHorizTotalFromU(u16 *data, int row, int column, u16 **result);
int computeAdjVertFromU(u8 *data, int row, int column, u8 **result);
int computeAdjVertTotalFromU(u16 *data, int row, int column, u16 **result);
int checkLimitsMinMax(short *data, int row, int column, int min, int max);
int checkLimitsMap(i8 *data, int row, int column, int *min, int *max);
int checkLimitsMapTotal(short *data, int row, int column, int *min, int *max);
int checkLimitsMapFromU(u8 *data, int row, int column, int *min, int *max);
int checkLimitsMapTotalFromU(u16 *data, int row, int column, int *min,
                 int *max);
int checkLimitsMapAdj(u8 *data, int row, int column, int *max);
int checkLimitsMapAdjTotal(u16 *data, int row, int column, int *max);
int checkLimitsGap(short *data, int row, int column, int threshold);
int checkLimitsGapOffsets(short *data, int row, int column, int threshold,
        int row_start, int column_start, int row_end, int column_end);
int production_test_ito(char *path_limits, TestToDo *todo,TestResult *result);
int production_test_initialization(u8 type);
int production_test_main(char *pathThresholds, int stop_on_fail, int saveInit,
             TestToDo *todo, u8 mpflag,struct ts_rawdata_info *info, TestResult *result);
int production_test_ms_raw(char *path_limits, int stop_on_fail, TestToDo *todo,
        struct ts_rawdata_info *info, TestResult *result);
int production_test_ms_cx(char *path_limits, int stop_on_fail, TestToDo *todo,
        struct ts_rawdata_info *info, TestResult *result);
int production_test_ms_cx_lp(char *path_limits, int stop_on_fail,TestToDo *todo);
int production_test_ss_raw(char *path_limits, int stop_on_fail, TestToDo *todo,struct ts_rawdata_info *info, TestResult *result);
int production_test_ss_raw_lp(char *path_limits, int stop_on_fail,TestToDo *todo);
int production_test_ss_ix_cx(char *path_limits, int stop_on_fail,
                 TestToDo *todo);
int production_test_ss_ix_cx_lp(char *path_limits, int stop_on_fail,
                 TestToDo *todo);
int production_test_data(char *path_limits, int stop_on_fail, TestToDo *todo,
        struct ts_rawdata_info *info, TestResult *result);
int parseProductionTestLimits(char *path, LimitFile *file, char *label,
                  int **data, int *row, int *column);
int readLine(char *data, char *line, int size, int *n);
int getLimitsFile(char *path, LimitFile *file);
int freeLimitsFile(LimitFile *file);
int freeCurrentLimitsFile(void);
/**@}*/


#endif
