#ifndef __CONFIG_H
#define __CONFIG_H

/*=========================
   Application configuration
 *=========================*/

#define CONFIG_SYSTEM_SAVE_FILE_PATH          "/SystemSave.json"
#define CONFIG_SYSTEM_SAVE_FILE_BACKUP_PATH   "/.SystemSaveBackup.json"
#define CONFIG_SYSTEM_LANGUAGE_DEFAULT        "en-GB"
#define CONFIG_SYSTEM_TIME_ZONE_DEFAULT       8    // GMT+ 8
#define CONFIG_SYSTEM_SOUND_ENABLE_DEFAULT    true

#define CONFIG_WEIGHT_DEFAULT                 65   // kg

#ifdef ARDUINO
#  define CONFIG_GPS_REFR_PERIOD              1000 // ms
#else
#  define CONFIG_GPS_REFR_PERIOD              100 // ms
#endif

#define CONFIG_GPS_LONGITUDE_DEFAULT          116.391332f
#define CONFIG_GPS_LATITUDE_DEFAULT           39.907415f

#define CONFIG_TRACK_FILTER_OFFSET_THRESHOLD  2 // pixel
#define CONFIG_TRACK_RECORD_FILE_DIR_NAME     "Track"

#define CONFIG_MAP_USE_WGS84_DEFAULT          false
#define CONFIG_MAP_DIR_PATH_DEFAULT           "/MAP"

#define CONFIG_MAP_EXT_NAME_DEFAULT           "bin"

#ifdef ARDUINO
#  define CONFIG_MAP_PNG_DECODE_ENABLE        0
#else
#  define CONFIG_MAP_PNG_DECODE_ENABLE        1
#endif

#ifndef CONFIG_MAP_IMG_PNG_ENABLE
#  define CONFIG_MAP_IMG_PNG_ENABLE           0
#endif

#define CONFIG_ARROW_THEME_DEFAULT            "default"

#define CONFIG_LIVE_MAP_LEVEL_DEFAULT         16

#define CONFIG_LIVE_MAP_DEBUG_ENABLE          0
#if CONFIG_LIVE_MAP_DEBUG_ENABLE
#  define CONFIG_LIVE_MAP_VIEW_WIDTH          240
#  define CONFIG_LIVE_MAP_VIEW_HEIGHT         240
#else
#  define CONFIG_LIVE_MAP_VIEW_WIDTH          LV_HOR_RES
#  define CONFIG_LIVE_MAP_VIEW_HEIGHT         LV_VER_RES
#endif

#define CONFIG_MONKEY_TEST_ENABLE             0
#if CONFIG_MONKEY_TEST_ENABLE
#  define CONFIG_MONKEY_INDEV_TYPE            LV_INDEV_TYPE_ENCODER
#  define CONFIG_MONKEY_PERIOD_MIN            10
#  define CONFIG_MONKEY_PERIOD_MAX            100
#  define CONFIG_MONKEY_INPUT_RANGE_MIN       -5
#  define CONFIG_MONKEY_INPUT_RANGE_MAX       5
#endif

#endif
