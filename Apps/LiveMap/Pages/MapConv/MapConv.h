#ifndef __MAP_CONV_H
#define __MAP_CONV_H

#include <stdint.h>
#include <string.h>
#include "TileSystem/TileSystem.h"

#define MAP_CONV_DIR_PATH_MAX 16
#define MAP_CONV_EXT_NAME_MAX 8

class MapConv
{
public:
    typedef struct
    {
        uint32_t tileX;
        uint32_t tileY;
        uint32_t subX;
        uint32_t subY;
    } MapTile_t;

public:
    MapConv();
    ~MapConv() {}

    void SetLevel(int level);
    void SetLevelUp()
    {
        SetLevel(GetLevel() + 1);
    }
    void SetLevelDown()
    {
        SetLevel(GetLevel() - 1);
    }
    static void SetDirPath(const char* path)
    {
        strncpy(dirPath, path, sizeof(dirPath));
        dirPath[sizeof(dirPath) - 1] = '\0';
    }
    static void SetExtName(const char* name)
    {
        strncpy(extName, name, sizeof(extName));
        extName[sizeof(extName) - 1] = '\0';
    }

    static void SetCoordTransformEnable(bool en)
    {
        coordTransformEnable = en;
    }

    static void SetLevelRange(int16_t min, int16_t max)
    {
        levelMin = min;
        levelMax = max;
    }

    int16_t GetLevel()
    {
        return priv.level;
    }
    static int16_t GetLevelMax()
    {
        return levelMax;
    }
    static int16_t GetLevelMin()
    {
        return levelMin;
    }

    void GetMapTile(double longitude, double latitude, MapTile_t* mapTile);
    void ConvertPosToTile(int32_t x, int32_t y, MapTile_t* mapTile);
    int ConvertMapPath(int32_t x, int32_t y, char* path, uint32_t len);
    void ConvertMapCoordinate(
        double longitude, double latitude,
        int32_t* mapX, int32_t* mapY
    );
    void ConvertMapLevelPos(
        int32_t* destX, int32_t* destY,
        int32_t srcX, int32_t srcY, int srcLevel
    );

protected:
    struct
    {
        int16_t level;
        uint16_t tileSize;
    } priv;

    static char dirPath[MAP_CONV_DIR_PATH_MAX];
    static char extName[MAP_CONV_EXT_NAME_MAX];
    static int16_t levelMin;
    static int16_t levelMax;
    static bool coordTransformEnable;
};

#endif
