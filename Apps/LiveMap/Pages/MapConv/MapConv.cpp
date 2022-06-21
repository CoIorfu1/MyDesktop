#include "MapConv.h"
#include <stdio.h>
#include <iostream>
#include "GPS_Transform/GPS_Transform.h"

using namespace::Microsoft_MapPoint;

#ifndef constrain
#  define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#endif

char MapConv::dirPath[] = "./Map";
//char MapConv::extName[] = "bin";
int16_t MapConv::levelMin = 7;
int16_t MapConv::levelMax = 16;
bool MapConv::coordTransformEnable = false;

MapConv::MapConv()
{
    priv.level = 16;
    priv.tileSize = 256;
}

void MapConv::SetLevel(int level)
{
    priv.level = constrain(level, levelMin, levelMax);
}

void MapConv::GetMapTile(double longitude, double latitude, MapTile_t* mapTile)
{
    int32_t x, y;
    ConvertMapCoordinate(longitude, latitude, &x, &y);
    ConvertPosToTile(x, y, mapTile);
}

void MapConv::ConvertMapCoordinate(
    double longitude, double latitude,
    int32_t* mapX, int32_t* mapY
)
{
    int pixelX, pixelY;

    if (coordTransformEnable)
    {
        GPS_Transform(latitude, longitude, &latitude, &longitude);
    }

    TileSystem::LatLongToPixelXY(
        latitude,
        longitude,
        priv.level,
        &pixelX,
        &pixelY
    );

    *mapX = pixelX;
    *mapY = pixelY;
};

void MapConv::ConvertMapLevelPos(
    int32_t* destX, int32_t* destY,
    int32_t srcX, int32_t srcY, int srcLevel
)
{
    int diffLevel = srcLevel - GetLevel();
    if (diffLevel >= 0)
    {
        *destX = srcX >> diffLevel;
        *destY = srcY >> diffLevel;
    }
    else
    {
        *destX = srcX << -diffLevel;
        *destY = srcY << -diffLevel;
    }
}

int MapConv::ConvertMapPath(int32_t x, int32_t y, char* path, uint32_t len)
{
    int32_t tileX = x / priv.tileSize;
    int32_t tileY = y / priv.tileSize;

    int ret = snprintf(
                  path, len,
                  "%s/%d/%d/%d.png",
                  dirPath,
                  priv.level,
                  tileX,
                  tileY
              );
    return ret;
}

void MapConv::ConvertPosToTile(int32_t x, int32_t y, MapTile_t* mapTile)
{
    mapTile->tileX = x / priv.tileSize;
    mapTile->tileY = y / priv.tileSize;
    mapTile->subX = x % priv.tileSize;
    mapTile->subY = y % priv.tileSize;
}
