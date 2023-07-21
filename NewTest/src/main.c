#include <genesis.h>
#include <resources.h>
#include <string.h>

#define UPLEFTIDLE 0
#define UPIDLE 1
#define LEFTIDLE 2
#define DOWNLEFTIDLE 3
#define DOWNIDLE 4

#define UPWALK 5
#define UPLEFTWALK 6
#define LEFTWALK 7
#define DOWNLEFTWALK 8
#define DOWNWALK 9

#define XENOM_UP 0
#define XENOM_UP_RIGHT 1
#define XENOM_RIGHT 2
#define XENOM_DOWN_RIGHT 3
#define XENOM_DOWN 4
#define XENOM_DEATH 5

#define LIZ_UP 0
#define LIZ_UP_RIGHT 1
#define LIZ_RIGHT 2
#define LIZ_DOWN_RIGHT 3
#define LIZ_DOWN 4
#define LIZ_DEATH 5

#define MAP_HEIGHT 28
#define MAP_WIDTH 40

#define MAX_BULLETS 11
#define MAX_ENEMIES 7

#define LEVEL_NUM 3

#define HEALTH 25


typedef u8 map[MAP_HEIGHT][MAP_WIDTH];
u8 *currentLevel;
static  u8 currentLevelIndex = 0;
map levelList;

map level1 =
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

map level2 =
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

map level3 =
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

typedef struct{u8 x;u8 y;} Point;

typedef enum
{up, upleft, upright, down, downleft, downright, left, right, death, none} moveDirection;

typedef struct
{
    Point pos;
    Point vel;
    int w;
    int h;
    int health;
    int dirIntX;
    int dirIntY;
    u16 spriteColor;
    bool moving;
    bool isShooting;
    moveDirection dir;
    Sprite *sprite;
    char name[6];
} Entity;

// typedef struct {
//     int x;
//     int y;
//     int g; // Cost to move from the start node to this node
//     int h; // Heuristic cost (estimated distance to the goal)
//     int f; // Total cost: f = g + h
//     bool walkable;
//     Node* parent; // Reference to the previous node in the path
// } Node;


// Create the grid
// Node grid[MAP_WIDTH][MAP_HEIGHT];

Entity player = {{150, 165}, {0, 0}, 32, 32, 100, 0, 0, 35, FALSE, FALSE, up, NULL, "PLAYER"};
Entity xenom[MAX_ENEMIES];
Entity lizard[MAX_ENEMIES];
Entity bullet[MAX_BULLETS];
Entity lizardBullet[MAX_BULLETS];
Entity health[HEALTH];


bool exitUnlocked = FALSE;
bool gameON = FALSE;
bool gameIsPaused = FALSE;
bool flashing = FALSE;

Point cursorPos  = {8, 10};

int i = 0;
int ticks;
int delay;
int enemiesAlive = 0;
int enemiesShouldDie = 15;

char labelTimer[7] = "TIMER:\0";
char timerStr [4] = "0";
char timer = 10;

moveDirection randomDir;

u16 palette_full[64];


// Function to calculate the heuristic cost (Manhattan distance)
// int heuristicCost(Node* current, Node* goal) 
// {
//     return abs(current->x - goal->x) + abs(current->y - goal->y);
// }

// Function to find the path using A* algorithm
// bool findPath(Node* start, Node* goal) 
// {
//     // Create two lists: openList and closedList
//     List openList;
//     List closedList;

//     // Add the start node to the openList
//     addToOpenList(start);

//     // Loop until the openList is empty
//     while (!isEmpty(openList)) 
//     {
//         // Find the node with the lowest f cost in the openList
//         Node* current = findLowestFCost(openList);

//         // Move the current node from openList to closedList
//         removeFromOpenList(current);
//         addToClosedList(current);

//         // Check if the goal node is reached
//         if (current == goal) 
//         {
//             return true;
//         }

//         // Get the neighboring nodes
//         Node* neighbors[4];
//         getNeighbors(current, neighbors);

//         // Loop through the neighbors
//         for (int i = 0; i < 4; i++) 
//         {
//             Node* neighbor = neighbors[i];

//             // Skip the neighbor if it's not walkable or already in the closedList
//             if (!neighbor->walkable || isInClosedList(neighbor)) 
//             {
//                 continue;
//             }

//             // Calculate the tentative g cost
//             int tentativeG = current->g + 1;

//             // Check if the neighbor is already in the openList
//             bool inOpenList = isInOpenList(neighbor);

//             if (!inOpenList || tentativeG < neighbor->g) 
//             {
//                 // Update the neighbor's values
//                 neighbor->g = tentativeG;
//                 neighbor->h = heuristicCost(neighbor, goal);
//                 neighbor->f = neighbor->g + neighbor->h;
//                 neighbor->parent = current;

//                 if (!inOpenList) 
//                 {
//                     // Add the neighbor to the openList
//                     addToOpenList(neighbor);
//                 }
//             }
//         }
//     }
//     // Path not found
//     return false;
// }

// // Function to reconstruct the path from the goal node to the start node
// void reconstructPath(Node* start, Node* goal) 
// {
//     Node* current = goal;

//     // Create a list to store the path
//     List path;
//     while (current != start) {
//         addToPath(path, current);
//         current = current->parent;
//     }

//     // Reverse the path
//     reversePath(path);

//     // Use the path to navigate in your game
//     // ...
// }


void showText(char s[])
{
	VDP_drawText(s, 20 - strlen(s)/2 ,10);
}

void clearText()
{
	VDP_clearText(0,10,32);
}

void swapToColor(u16 index, u16 Col, u16 defaultColor)
{
    if(flashing == TRUE)
    {    
        if(ticks % 8 == 0)
        {
            PAL_setColor(index , Col);
        }
        else if (ticks % 4 == 0)
        {
            PAL_setColor(index , defaultColor);
        }
        else if(ticks >= 30)
        {
            flashing = FALSE;
        }
    }
    else if (flashing == FALSE)
    {
        PAL_setColor(index , defaultColor);
    }
}

int collideEntities(Entity *a, Entity *b)
{
    return (a->pos.x <= b->pos.x + b->w && a->pos.x + a->w >= b->pos.x && a->pos.y <= b->pos.y + b->h && a->pos.y + a->h >= b->pos.y);
}

void killEntity(Entity *e)
{
    e->health = 0;
    SPR_setVisibility(e->sprite, HIDDEN);
}

void reviveEntity(Entity *e, int HP)
{
    e->health = HP;
    SPR_setVisibility(e->sprite, VISIBLE);
}

int checkCollisions(s16 x, s16 y, u8 width, u8 height, Entity *e)
{
    s16 y_tile = y >> 3;
    s16 x_tile = x >> 3;

    u8 player_width = width;
    u8 player_height = height;

    s16 leftTile = x_tile;
    s16 rightTile = x_tile + player_width;
    s16 topTile = y_tile;
    s16 bottomTile = y_tile + player_height;

    for (s16 i = leftTile; i <= rightTile; i++)
    {
        for (s16 j = topTile; j <= bottomTile; j++)
        {
            if (levelList[j][i] == 0)
            {
                return 0;
            }
            else if (levelList[j][i] == 2)
            {
                return 2;
            }
        }
    }
    return 1;
}


void spawnPlayer()
{
    SPR_init();
    player.sprite = SPR_addSprite(&Soldier, player.pos.x, player.pos.y, TILE_ATTR(PAL2, 0, FALSE, FALSE));
    PAL_setPalette(PAL2, Soldier.palette->data, DMA);
    SPR_update();
}

void movePlayer()
{
    player.pos.x += player.vel.x;
    player.pos.y += player.vel.y;

    switch (player.dir)
    {
        case up:

            player.dirIntX = 0;
            player.dirIntY = -1;

            if (player.moving == TRUE)
            {
                player.vel.y = -1;
                player.vel.x = 0;
                SPR_setHFlip(player.sprite, FALSE);
                SPR_setAnim(player.sprite, UPWALK);
            }
            else if (player.moving == FALSE)
            {

                SPR_setAnim(player.sprite, UPIDLE);
            }

            break;

        case down:

            player.dirIntX = 0;
            player.dirIntY = 1;

            if (player.moving == TRUE)
            {
                player.vel.y = 1;
                player.vel.x = 0;
                SPR_setHFlip(player.sprite, FALSE);
                SPR_setAnim(player.sprite, DOWNWALK);
            }
            else if (player.moving == FALSE)
            {
                SPR_setAnim(player.sprite, DOWNIDLE);
            }
            break;

        case left:

            player.dirIntX = -1;
            player.dirIntY = 0;

            if (player.moving == TRUE)
            {
                player.vel.y = 0;
                player.vel.x = -1;
                SPR_setAnim(player.sprite, LEFTWALK);
                SPR_setHFlip(player.sprite, FALSE);
            }
            else if (player.moving == FALSE)
            {
                SPR_setHFlip(player.sprite, FALSE);
                SPR_setAnim(player.sprite, LEFTIDLE);
            }
            break;

        case right:

            player.dirIntX = 1;
            player.dirIntY = 0;

            if (player.moving == TRUE)
            {
                player.vel.y = 0;
                player.vel.x = 1;
                SPR_setAnim(player.sprite, LEFTWALK);
                SPR_setHFlip(player.sprite, TRUE);
            }
            else if (player.moving == FALSE)
            {
                SPR_setHFlip(player.sprite, TRUE);
                SPR_setAnim(player.sprite, LEFTIDLE);
            }
            break;

        case upleft:

            player.dirIntX = -1;
            player.dirIntY = -1;

            if (player.moving == TRUE)
            {
                player.vel.y = -1;
                player.vel.x = -1;
                SPR_setAnim(player.sprite, UPLEFTWALK);
                SPR_setHFlip(player.sprite, FALSE);
            }
            else if (player.moving == FALSE)
            {
                SPR_setHFlip(player.sprite, FALSE);
                SPR_setAnim(player.sprite, UPLEFTIDLE);
            }
            break;

        case upright:

            player.dirIntX = 1;
            player.dirIntY = -1;

            if (player.moving == TRUE)
            {
                player.vel.y = -1;
                player.vel.x = 1;
                SPR_setAnim(player.sprite, UPLEFTWALK);
                SPR_setHFlip(player.sprite, TRUE);
            }
            else if (player.moving == FALSE)
            {
                SPR_setHFlip(player.sprite, TRUE);
                SPR_setAnim(player.sprite, UPLEFTIDLE);
            }
            break;

        case downleft:

            player.dirIntX = -1;
            player.dirIntY = 1;

            if (player.moving == TRUE)
            {
                player.vel.y = 1;
                player.vel.x = -1;
                SPR_setAnim(player.sprite, DOWNLEFTWALK);
                SPR_setHFlip(player.sprite, FALSE);
            }
            else if (player.moving == FALSE)
            {

                SPR_setHFlip(player.sprite, FALSE);
                SPR_setAnim(player.sprite, DOWNIDLE);
            }
            break;

        case downright:

            player.dirIntX = 1;
            player.dirIntY = 1;

            if (player.moving == TRUE)
            {
                player.vel.y = 1;
                player.vel.x = 1;
                SPR_setAnim(player.sprite, DOWNLEFTWALK);
                SPR_setHFlip(player.sprite, TRUE);
            }
            else if (player.moving == FALSE)
            {
                SPR_setHFlip(player.sprite, TRUE);
                SPR_setAnim(player.sprite, DOWNIDLE);
            }
            break;

        default:
            break;
    }

    if (checkCollisions(player.pos.x + player.dirIntX, player.pos.y + player.dirIntY, 4, 4, &player) == 0)
    {
        player.moving = FALSE;
    }
    
    if (player.moving == FALSE)
    {
        player.vel.x = 0;
        player.vel.y = 0;
        player.dirIntX = 0;
        player.dirIntY = 0;
    }
    SPR_setPosition(player.sprite, player.pos.x, player.pos.y);
}


void randomDirection()
{
    int randDir = random()%4;
        switch(randDir)
        {
            case 0:
            randomDir = up;
            break;

            case 1:
            randomDir = down;
            break;

            case 2:
            randomDir = left;
            break;

            case 3:
            randomDir = right;
            break;
        }
}


void changeHealthBar()
{
    int textPosX = 2;
    
    for(int i = 0; i < player.health/10; i++) 
    {    
        textPosX ++;  
        //VDP_setTextPalette(PAL1);
        VDP_drawText("|",textPosX,25);
        //SPR_addSprite(&Health, textPosX, 215, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    } 
    

}

void spawnBullets()
{
    Entity *b = bullet;
    for (i = 0; i < MAX_BULLETS; i++)
    {
        b->pos.x = 0;
        b->pos.y = 0;
        b->w = 8;
        b->h = 8;
        b->health = 1;
        b->sprite = SPR_addSprite(&Bullet, bullet[i].pos.x, bullet[i].pos.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
        PAL_setPalette(PAL1, Bullet.palette->data, DMA);
        sprintf(b->name, "Bu%d", i);
        b++;
    }
}

void positionBullets()
{
    u16 i = 0;
    Entity *b;
    Entity *e;
    Entity *l;
    int j = 0;

    for (i = 0; i < MAX_BULLETS; i++)
    {
        b = &bullet[i];

        b->pos.x += b->vel.x;
        b->pos.y += b->vel.y;

        for (j = 0; j < MAX_ENEMIES; j++)
        {
            e = &xenom[j];
            l = &lizard[j];
            if (checkCollisions(b->pos.x, b->pos.y, 1, 1, b) == 0 || (collideEntities(b, e) && e->health > 0 && b->health > 0))
            {
                b->health = 0;
                killEntity(b);
                swapToColor(e->spriteColor,RGB24_TO_VDPCOLOR(0xaf0a09),e->spriteColor);
                swapToColor(50,RGB24_TO_VDPCOLOR(0xaf0a09),49);
                break;
            }
            else
            {
                SPR_setPosition(b->sprite, b->pos.x, b->pos.y);
            }

            if (collideEntities(b, l) && l->health > 0 && b->health > 0)
            {
                b->health = 0;
                //killEntity(b);
                swapToColor(l->spriteColor,RGB24_TO_VDPCOLOR(0xaf0a09),l->spriteColor);
                swapToColor(18,RGB24_TO_VDPCOLOR(0xaf0a09),18);
                break;
            }
            else
            {
                SPR_setPosition(b->sprite, b->pos.x, b->pos.y);
            }
        }
    }
}

void shootBullet(Entity Shooter)
{
    u16 i = 0;
    Entity *b;

    for (i = 0; i < MAX_BULLETS; i++)
    {
        b = &bullet[i];
        if (b->health == 0 && Shooter.health > 0)
        {
            switch (Shooter.dir)
            {
            case up:
                b->pos.x = Shooter.pos.x + 16;
                b->pos.y = Shooter.pos.y;
                b->vel.y = -3;
                b->vel.x = 0;
                SPR_setVFlip(b->sprite, FALSE);
                break;

            case down:
                b->vel.y = 3;
                b->vel.x = 0;
                b->pos.x = Shooter.pos.x + 6;
                b->pos.y = Shooter.pos.y + 24;
                SPR_setVFlip(b->sprite, TRUE);
                break;

            case right:
                b->pos.x = Shooter.pos.x + 24;
                b->pos.y = Shooter.pos.y + 16;
                b->vel.y = 0;
                b->vel.x = 3;
                break;

            case left:
                b->pos.x = Shooter.pos.x;
                b->pos.y = Shooter.pos.y + 16;
                b->vel.y = 0;
                b->vel.x = -3;
                break;

            case upleft:
                b->pos.x = Shooter.pos.x;
                b->pos.y = Shooter.pos.y;
                b->vel.y = -3;
                b->vel.x = -3;
                SPR_setVFlip(b->sprite, TRUE);
                break;

            case upright:
                b->pos.x = Shooter.pos.x + 32;
                b->pos.y = Shooter.pos.y;
                b->vel.y = -3;
                b->vel.x = 3;
                SPR_setVFlip(b->sprite, FALSE);
                break;

            case downleft:
                b->pos.x = Shooter.pos.x;
                b->pos.y = Shooter.pos.y + 32;
                b->vel.y = 3;
                b->vel.x = -3;
                SPR_setVFlip(b->sprite, TRUE);
                break;

            case downright:
                b->pos.x = Shooter.pos.x + 32;
                b->pos.y = Shooter.pos.y + 32;
                b->vel.y = 3;
                b->vel.x = 3;
                SPR_setVFlip(b->sprite, FALSE);
                break;

            case none:
                break;
            case death:
                break;

            default:
                break;
            }
            reviveEntity(b, 1);
            SPR_setPosition(b->sprite, b->pos.x, b->pos.y);
            break;
        }
    }
}

void plrShooting(int fireRate)
{
    if (ticks % fireRate == 0)
    {
        if (player.isShooting == TRUE)
        {
            shootBullet(player);
        }
        else if (player.isShooting == FALSE)
        {
        }
    }
}






void xenomSpawner(Entity *e, int enemyCount)
{
    //enemiesAlive = 0;
    int randX;
    int randY; 
    randX = random()%200;
    randY = random()%200;
    for (i = 0; i < enemyCount; i++)
    {
        e = &xenom[i];
        e->pos.x = randX + random()%150;
        e->pos.y = randY + random()%150;
        e->w = 32;
        e->h = 32;
        e->health = 1;
        e->dir = up;
        e->spriteColor = 49;
        
        if(checkCollisions(e->pos.x, e->pos.y, 4, 4, e) == 1 )
        {
            e->sprite = SPR_addSprite(&Xenom, e->pos.x, e->pos.y, TILE_ATTR(PAL3, 0, FALSE, FALSE));
            PAL_setPalette(PAL3, Xenom.palette->data, DMA);
            sprintf(e->name, "En%d", i);
            e++;
            enemiesAlive++;
        }
        else if (checkCollisions(e->pos.x, e->pos.y, 4, 4, e) == 0)
        {
            randX = random()%200;
            randY = random()%200;
            i--;
        }
        
    }
}

void xenmoState(Entity *e)
{
    for (i = 0; i <= MAX_ENEMIES; i++)
    {
        e = &xenom[i];
        e->pos.x += e->vel.x;
        e->pos.y += e->vel.y;

        switch (e->dir)
        {
            e = &xenom[i];
            case up:
                
                e->moving = TRUE;
                e->dirIntX = 0;
                e->dirIntY = -1;
                e->vel.y = -1;
                e->vel.x = 0;
                SPR_setAnim(e->sprite, XENOM_UP);

                break;

            case down:

                e->moving = TRUE;
                player.dirIntX = 0;
                player.dirIntY = 1;
                e->vel.y = 1;
                e->vel.x = 0;
                SPR_setAnim(e->sprite, XENOM_DOWN);

                break;

            case left:

                e->moving = TRUE;
                player.dirIntX = -1;
                player.dirIntY = 0;
                e->vel.y = 0;
                e->vel.x = -1;
                SPR_setHFlip(e->sprite, TRUE);
                SPR_setAnim(e->sprite, XENOM_RIGHT);

                break;

            case right:

                e->moving = TRUE;
                player.dirIntX = 1;
                player.dirIntY = 0;
                e->vel.y = 0;
                e->vel.x = 1;
                SPR_setHFlip(e->sprite, FALSE);
                SPR_setAnim(e->sprite, XENOM_RIGHT);

                break;

            case upleft:
                player.dirIntX = 0;
                player.dirIntY = -1;

                e->moving = TRUE;
                e->vel.y = -1;
                e->vel.x = -1;
                SPR_setHFlip(e->sprite, TRUE);
                SPR_setAnim(e->sprite, XENOM_UP_RIGHT);

                break;

            case upright:

                e->moving = TRUE;
                e->vel.y = -1;
                e->vel.x = 1;
                SPR_setHFlip(e->sprite, FALSE);
                SPR_setAnim(e->sprite, XENOM_UP_RIGHT);

                break;

            case downleft:

                e->moving = TRUE;
                e->vel.y = 1;
                e->vel.x = -1;
                SPR_setHFlip(e->sprite, TRUE);
                SPR_setAnim(e->sprite, XENOM_DOWN_RIGHT);

                if (e->health > 0 && e->moving == FALSE)
                {
                    e->dir = left;
                }
                break;

            case downright:
            player.dirIntX = 0;
            player.dirIntY = -1;

                e->moving = TRUE;
                e->vel.y = 1;
                e->vel.x = 1;
                SPR_setHFlip(e->sprite, FALSE);
                SPR_setAnim(e->sprite, XENOM_DOWN_RIGHT);

                break;

            case none:
                break;

            case death:
                e->moving = FALSE;
                e->vel.x = 0;
                e->vel.y = 0;
                e->health = 0;
                delay++;

                SPR_setAnim(e->sprite, XENOM_DEATH);
                if (delay % 29 == 0)
                {
                    killEntity(e);
                    delay = 0;
                }
                break;

            default:
                break;
        }

        if (checkCollisions(e->pos.x + e->dirIntX * 4, e->pos.y + e->dirIntY * 4, 4, 4, e) == 0)
        {
            e->moving = FALSE;
        }

        if (e->moving == FALSE)
        {
            e->vel.x = 0;
            e->vel.y = 0;
            e->dirIntX = 0;
            e->dirIntY = 0;
        }
        SPR_setPosition(e->sprite, e->pos.x, e->pos.y);
    }
}

void enemyAI(Entity *e)
{

    for (i = 0; i < MAX_ENEMIES; i++)
    {
        e = &xenom[i];
        
     if((e->pos.x > player.pos.x - 34 && e->pos.x < player.pos.x + 50) && (e->pos.y > player.pos.y - 34 && e->pos.y < player.pos.y + 50))
     {
        
    
        if (e->pos.y  > player.pos.y + player.h && e->health > 0)
        {    
            e->dir = up;
            
            if(checkCollisions(e->pos.x , e->pos.y - 4, 4,4 ,e) == 0 &&  checkCollisions(e->pos.x - 4 , e->pos.y, 4,4 ,e) == 1)
            {
                e->dir = left;
            }
            else if(checkCollisions(e->pos.x , e->pos.y - 4, 4,4 ,e) == 0 &&  checkCollisions(e->pos.x + 4 , e->pos.y, 4,4 ,e) == 1 )
            {
                e->dir = right;
            }

        }
        else if (e->pos.y + e->h < player.pos.y  && e->health > 0 )
        {    
            e->dir = down;

            if(checkCollisions(e->pos.x , e->pos.y + 4, 4,4 ,e) == 0  && checkCollisions(e->pos.x - 4 , e->pos.y, 4,4 ,e) == 1)
            {
                e->dir = left;
            }
            else if(checkCollisions(e->pos.x , e->pos.y + 4, 4,4 ,e) == 0 && player.pos.x > e->pos.x && checkCollisions(e->pos.x + 4 , e->pos.y, 4,4 ,e) == 1)
            {
                 e->dir = right;
            }  
        }
        else if (e->pos.x + e->w < player.pos.x && e->health > 0 && e->health > 0)
        {      
            e->dir = right;

            if(checkCollisions(e->pos.x + 4, e->pos.y, 4,4 ,e) == 0 && player.pos.y < e->pos.y && checkCollisions(e->pos.x , e->pos.y - 4, 4,4 ,e) == 1)
            {
                e->dir = up;
            }
            else if(checkCollisions(e->pos.x + 4, e->pos.y, 4,4 ,e) == 0 && player.pos.y > e->pos.y && checkCollisions(e->pos.x , e->pos.y + 4, 4,4 ,e) == 1)
            {
                e->dir = down;
            }
        }
        else if (e->pos.x > player.pos.x + player.w && e->health > 0 && e->health > 0)
        { 
            e->dir = left;

            if(checkCollisions(e->pos.x - 4, e->pos.y, 4,4 ,e) == 0  && player.pos.y < e->pos.y && checkCollisions(e->pos.x  , e->pos.y - 4, 4,4 ,e) == 1)
            {
                e->dir = up;
                
            }
            else if(checkCollisions(e->pos.x - 4, e->pos.y, 4,4 ,e) == 0 && player.pos.y > e->pos.y && checkCollisions(e->pos.x  , e->pos.y + 4, 4,4 ,e) == 1)
            {
                e->dir = down;
            }
        }
        


         if(e->pos.x + e->w < player.pos.x  && e->pos.y + e->h < player.pos.y && e->health > 0 &&  checkCollisions(e->pos.x + 1 , e->pos.y + 1, 4, 4, e))
        {
                e->dir = downright;
        }
        else if(e->pos.x > player.pos.x + player.w && e->pos.y + e->h < player.pos.y && e->health > 0 &&  checkCollisions(e->pos.x - 1, e->pos.y + 1, 4, 4, e))
        {
                e->dir = downleft;
        }
        else if(e->pos.x + e->w < player.pos.x && e->pos.y > player.pos.y + player.h && e->health > 0 &&  checkCollisions(e->pos.x + 1 , e->pos.y - 1, 4, 4, e))
        {
                e->dir = upright;
        }
        else if(e->pos.x > player.pos.x + player.w && e->pos.y > player.pos.y + player.h && e->health > 0 &&  checkCollisions(e->pos.x - 1  , e->pos.y - 1, 4, 4, e))
        {
                e->dir = upleft;
        }
     }
    else
    {
        randomDirection();
        if(checkCollisions(e->pos.x , e->pos.y - 4, 4,4 ,e) == 0 && e->dir == up)
        {
            e->dir = randomDir;
        }
        else if (checkCollisions(e->pos.x , e->pos.y + 4, 4,4 ,e) == 0 && e->dir == down)
        {
            e->dir = randomDir;
        }
        
        if (checkCollisions(e->pos.x - 4 , e->pos.y, 4,4 ,e) == 0 && e->dir == left)
        {
            e->dir = randomDir;
        }
        else if (checkCollisions(e->pos.x + 4 , e->pos.y, 4,4 ,e) == 0 && e->dir == right)
        {
            e->dir = randomDir;
        }

        if (collideEntities(e, &player))
        {
            e->vel.x = 0;
            e->vel.y = 0;
            if(e->health > 0 && ticks == 10)
            {
                player.health -=4;
            }
        }

    }

        

    }
}



void lizardSpawner(Entity *e, int enemyCount)
{
    //enemiesAlive = 0;
    int randX;
    int randY; 
    randX = random()%200;
    randY = random()%200;
    for (i = 0; i < enemyCount; i++)
    {
        e = &lizard[i];
        e->pos.x = randX + random()%150;
        e->pos.y = randY + random()%150;
        e->w = 32;
        e->h = 32;
        e->health = 2;
        e->dir = up;
        e->spriteColor = 17;
        
        if(checkCollisions(e->pos.x, e->pos.y, 4, 4, e) == 1 )
        {
            e->sprite = SPR_addSprite(&Lizard, e->pos.x, e->pos.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
            PAL_setPalette(PAL1, Lizard.palette->data, DMA);
            sprintf(e->name, "En%d", i);
            e++;
            enemiesAlive++;
        }
        else if (checkCollisions(e->pos.x, e->pos.y, 4, 4, e) == 0)
        {
            randX = random()%200;
            randY = random()%200;
            i--;
        }   
    }
}




void spawnLizardBullets()
{
    Entity *b = lizardBullet;
    for (i = 0; i < MAX_BULLETS; i++)
    {
        b->pos.x = 0;
        b->pos.y = 0;
        b->w = 8;
        b->h = 8;
        b->health = 1;
        b->sprite = SPR_addSprite(&LizardBullet, lizardBullet[i].pos.x, lizardBullet[i].pos.y, TILE_ATTR(PAL1, 0, FALSE, FALSE));
        PAL_setPalette(PAL1, LizardBullet.palette->data, DMA);
        sprintf(b->name, "LizBu%d", i);
        b++;
    }
}

void lizPositionBullets()
{
    u16 i = 0;
    Entity *b;
    Entity *p = &player;
    int j = 0;

    for (i = 0; i < MAX_BULLETS; i++)
    {
        b = &lizardBullet[i];

        b->pos.x += b->vel.x;
        b->pos.y += b->vel.y;

        for (j = 0; j < MAX_ENEMIES; j++)
        {
            if (checkCollisions(b->pos.x, b->pos.y, 1, 1, b) == 0 || (collideEntities(b, p) && p->health > 0 && b->health > 0))
            {
                b->health = 0;
                killEntity(b);
                swapToColor(p->spriteColor,RGB24_TO_VDPCOLOR(0xaf0a09),p->spriteColor);
                break;
            }
            else
            {
                SPR_setPosition(b->sprite, b->pos.x, b->pos.y);
            }
        }
    }
}

void lizShootBullet(Entity Shooter)
{
    u16 i = 0;
    Entity *b;

    for ( i = 0; i < MAX_BULLETS; i++)
    {
        b = &lizardBullet[i];
        if (b->health == 0 && Shooter.health > 0)
        {
            switch (Shooter.dir)
            {
            case up:
                b->pos.x = Shooter.pos.x + 16;
                b->pos.y = Shooter.pos.y;
                b->vel.y = -3;
                b->vel.x = 0;
                break;

            case down:
                b->vel.y = 3;
                b->vel.x = 0;
                b->pos.x = Shooter.pos.x + 16;
                b->pos.y = Shooter.pos.y + 24;
                break;

            case right:
                b->pos.x = Shooter.pos.x + 24;
                b->pos.y = Shooter.pos.y + 16;
                b->vel.y = 0;
                b->vel.x = 3;
                break;

            case left:
                b->pos.x = Shooter.pos.x;
                b->pos.y = Shooter.pos.y + 16;
                b->vel.y = 0;
                b->vel.x = -3;
                break;

            case upleft:
                b->pos.x = Shooter.pos.x;
                b->pos.y = Shooter.pos.y;
                b->vel.y = -3;
                b->vel.x = -3;
                break;

            case upright:
                b->pos.x = Shooter.pos.x + 32;
                b->pos.y = Shooter.pos.y;
                b->vel.y = -3;
                b->vel.x = 3;
                break;

            case downleft:
                b->pos.x = Shooter.pos.x;
                b->pos.y = Shooter.pos.y + 32;
                b->vel.y = 3;
                b->vel.x = -3;
                SPR_setVFlip(b->sprite, TRUE);
                break;

            case downright:
                b->pos.x = Shooter.pos.x + 32;
                b->pos.y = Shooter.pos.y + 32;
                b->vel.y = 3;
                b->vel.x = 3;
                break;

            case none:
                break;
            case death:
                break;

            default:
                break;
            }
            reviveEntity(b, 1);
            SPR_setPosition(b->sprite, b->pos.x, b->pos.y);
            break;
        }
    }
}

void lizardState(Entity *e)
{
    for (i = 0; i <= MAX_ENEMIES; i++)
    {
        e = &lizard[i];
        e->pos.x += e->vel.x;
        e->pos.y += e->vel.y;

        switch (e->dir)
        {
            e = &lizard[i];
            case up:
                
                e->moving = TRUE;
                e->dirIntX = 0;
                e->dirIntY = -1;
                e->vel.y = -1;
                e->vel.x = 0;
                SPR_setAnim(e->sprite, LIZ_UP);

                break;

            case down:

                e->moving = TRUE;
                player.dirIntX = 0;
                player.dirIntY = 1;
                e->vel.y = 1;
                e->vel.x = 0;
                SPR_setAnim(e->sprite, LIZ_DOWN);

                break;

            case left:

                e->moving = TRUE;
                player.dirIntX = -1;
                player.dirIntY = 0;
                e->vel.y = 0;
                e->vel.x = -1;
                SPR_setHFlip(e->sprite, TRUE);
                SPR_setAnim(e->sprite, LIZ_RIGHT);

                break;

            case right:

                e->moving = TRUE;
                player.dirIntX = 1;
                player.dirIntY = 0;
                e->vel.y = 0;
                e->vel.x = 1;
                SPR_setHFlip(e->sprite, FALSE);
                SPR_setAnim(e->sprite, LIZ_RIGHT);

                break;

            case upleft:
                player.dirIntX = 0;
                player.dirIntY = -1;

                e->moving = TRUE;
                e->vel.y = -1;
                e->vel.x = -1;
                SPR_setHFlip(e->sprite, TRUE);
                SPR_setAnim(e->sprite, LIZ_UP_RIGHT);

                break;

            case upright:

                e->moving = TRUE;
                e->vel.y = -1;
                e->vel.x = 1;
                SPR_setHFlip(e->sprite, FALSE);
                SPR_setAnim(e->sprite, LIZ_UP_RIGHT);

                break;

            case downleft:

                e->moving = TRUE;
                e->vel.y = 1;
                e->vel.x = -1;
                SPR_setHFlip(e->sprite, TRUE);
                SPR_setAnim(e->sprite, LIZ_DOWN_RIGHT);

                if (e->health > 0 && e->moving == FALSE)
                {
                    e->dir = left;
                }
                break;

            case downright:
            player.dirIntX = 0;
            player.dirIntY = -1;

                e->moving = TRUE;
                e->vel.y = 1;
                e->vel.x = 1;
                SPR_setHFlip(e->sprite, FALSE);
                SPR_setAnim(e->sprite, LIZ_DOWN_RIGHT);

                break;

            case none:
                break;

            case death:
                e->moving = FALSE;
                e->vel.x = 0;
                e->vel.y = 0;
                e->health = 0;
                delay++;

                SPR_setAnim(e->sprite, LIZ_DEATH);
                if (delay % 29 == 0)
                {
                    killEntity(e);
                    delay = 0;
                }
                break;

            default:
                break;
        }

        if (checkCollisions(e->pos.x + e->dirIntX * 4, e->pos.y + e->dirIntY * 4, 4, 4, e) == 0)
        {
            e->moving = FALSE;
        }

        if (e->moving == FALSE)
        {
            e->vel.x = 0;
            e->vel.y = 0;
            e->dirIntX = 0;
            e->dirIntY = 0;
        }
        SPR_setPosition(e->sprite, e->pos.x, e->pos.y);
    }
}

void enemyAI_LIZ(Entity *e)
{
    for (i = 0; i < MAX_ENEMIES; i++)
    {
        
        e = &lizard[i];
        randomDirection();
        if((e->pos.x > player.pos.x - 34 && e->pos.x < player.pos.x + 50) && (e->pos.y > player.pos.y - 34 && e->pos.y < player.pos.y + 50))
        {
            if(e->pos.y == player.pos.y)
            {
                //e->moving = FALSE;
                if(player.pos.x > e->pos.x )
                {
                    e->dir = right;
                    if(checkCollisions(e->pos.x + 4 , e->pos.y, 4,4 ,e) == 0)
                    {
                        e->dir = up;
                    }
                }
                else if(player.pos.x < e->pos.x)
                {
                e->dir = left;
                if(checkCollisions(e->pos.x - 4 , e->pos.y, 4,4 ,e) == 0)
                    {
                        e->dir = up;
                    }
                }
            }

        
            if (e->pos.y  > player.pos.y + player.h && e->health > 0)
            {    
                e->dir = up;
                
                if(checkCollisions(e->pos.x , e->pos.y - 4, 4,4 ,e) == 0 &&  checkCollisions(e->pos.x - 4 , e->pos.y, 4,4 ,e) == 1)
                {
                    e->dir = left;
                }
                else if(checkCollisions(e->pos.x , e->pos.y - 4, 4,4 ,e) == 0 &&  checkCollisions(e->pos.x + 4 , e->pos.y, 4,4 ,e) == 1 )
                {
                    e->dir = right;
                }

            }
            else if (e->pos.y + e->h < player.pos.y  && e->health > 0 )
            {    
                e->dir = down;

                if(checkCollisions(e->pos.x , e->pos.y + 4, 4,4 ,e) == 0  && checkCollisions(e->pos.x - 4 , e->pos.y, 4,4 ,e) == 1)
                {
                    e->dir = left;
                }
                else if(checkCollisions(e->pos.x , e->pos.y + 4, 4,4 ,e) == 0 && player.pos.x > e->pos.x && checkCollisions(e->pos.x + 4 , e->pos.y, 4,4 ,e) == 1)
                {
                    e->dir = right;
                }  
            }
            else if (e->pos.x + e->w < player.pos.x && e->health > 0 && e->health > 0)
            {      
                e->dir = right;

                if(checkCollisions(e->pos.x + 4, e->pos.y, 4,4 ,e) == 0 && player.pos.y < e->pos.y && checkCollisions(e->pos.x , e->pos.y - 4, 4,4 ,e) == 1)
                {
                    e->dir = up;
                }
                else if(checkCollisions(e->pos.x + 4, e->pos.y, 4,4 ,e) == 0 && player.pos.y > e->pos.y && checkCollisions(e->pos.x , e->pos.y + 4, 4,4 ,e) == 1)
                {
                    e->dir = down;
                }
            }
            else if (e->pos.x > player.pos.x + player.w && e->health > 0 && e->health > 0)
            { 
                e->dir = left;

                if(checkCollisions(e->pos.x - 4, e->pos.y, 4,4 ,e) == 0   && checkCollisions(e->pos.x  , e->pos.y - 4, 4,4 ,e) == 1)
                {
                    e->dir = up;
                }
                else if(checkCollisions(e->pos.x - 4, e->pos.y, 4,4 ,e) == 0 && player.pos.y > e->pos.y && checkCollisions(e->pos.x  , e->pos.y + 4, 4,4 ,e) == 1)
                {
                    e->dir = down;
                }
            }

            
            if(e->pos.x + e->w < player.pos.x  && e->pos.y + e->h < player.pos.y && e->health > 0 &&  checkCollisions(e->pos.x + 1 , e->pos.y + 1, 4, 4, e))
            {
                    e->dir = downright;
            }
            else if(e->pos.x > player.pos.x + player.w && e->pos.y + e->h < player.pos.y && e->health > 0 &&  checkCollisions(e->pos.x - 1, e->pos.y + 1, 4, 4, e))
            {
                    e->dir = downleft;
            }
            else if(e->pos.x + e->w < player.pos.x && e->pos.y > player.pos.y + player.h && e->health > 0 &&  checkCollisions(e->pos.x + 1 , e->pos.y - 1, 4, 4, e))
            {
                    e->dir = upright;
            }
            else if(e->pos.x > player.pos.x + player.w && e->pos.y > player.pos.y + player.h && e->health > 0 &&  checkCollisions(e->pos.x - 1  , e->pos.y - 1, 4, 4, e))
            {
                    e->dir = upleft;
            }

            if(ticks % 60 == 0 && e->health > 0)
            {
                lizShootBullet(lizard[i]);
            }
        }
    else
    {
        if(checkCollisions(e->pos.x , e->pos.y - 4, 4,4 ,e) == 0 && e->dir == up)
        {
            
            e->dir = randomDir;
        }
        else if (checkCollisions(e->pos.x , e->pos.y + 4, 4,4 ,e) == 0 && e->dir == down)
        {
            e->dir = randomDir;
        }
        
        if (checkCollisions(e->pos.x - 4 , e->pos.y, 4,4 ,e) == 0 && e->dir == left)
        {
            e->dir = randomDir;
        }
        else if (checkCollisions(e->pos.x + 4 , e->pos.y, 4,4 ,e) == 0 && e->dir == right)
        {
            e->dir = randomDir;
        }
    }
        
        if (collideEntities(e, &player))
        {
            e->vel.x = 0;
            e->vel.y = 0;
        } 

        // if(player.pos.x <= e->pos.x + 50 && player.pos.x >= e->pos.x - 50 && player.pos.y <= e->pos.y + 50 && player.pos.y >= e->pos.y - 50)
        // {
            
        // }
    }
}



void startGame()
{
    if(gameON == TRUE)
    {
        SPR_init();
        VDP_clearPlane(BG_A,FALSE);

        if(currentLevelIndex == 0)
        VDP_drawImage(BG_B, &LVL, 0, 0);

        spawnPlayer();
        spawnBullets();
        spawnLizardBullets();
    
        xenomSpawner(xenom,3);
        lizardSpawner(lizard,3);
        SPR_update();


        SPR_update();
    }
}

void clearLevel()
{
    VDP_clearPlane(BG_B, TRUE);
    VDP_clearSprites();
    VDP_clearPlane(BG_A, TRUE);
    exitUnlocked = FALSE;
}


void loadLevel()
{
    
    u8 i = 0;
    u8 j = 0;

    for (i = 0; i < MAP_HEIGHT; i++)
    {
        for (j = 0; j < MAP_WIDTH; j++)
        {
            switch (currentLevelIndex)
            {
                case 0:
                    levelList[i][j] = level1[i][j]; 
                    enemiesShouldDie = 5;
                    break;
                case 1:
                    levelList[i][j] = level2[i][j];
                    enemiesShouldDie = 5;
                    break;
                case 2:
                    levelList[i][j] = level3[i][j];
                    enemiesShouldDie = 5;
                    break;
                
                    default:
                    currentLevelIndex--;
                        break;
            }
            
        }      
    }           
}

void changeLevelIndex()
{
    if (exitUnlocked == TRUE && checkCollisions(player.pos.x, player.pos.y, 4, 4, &player) == 2)
    {
        exitUnlocked = FALSE;
        currentLevelIndex ++;
        enemiesAlive = 0;

        loadLevel();
        startGame();
        PAL_fadeIn(0,63, palette_full, 10, FALSE);
        waitMs(1000); 
        PAL_fadeOut(0, 63, 10, FALSE);
        if(currentLevelIndex == 0)
        {
            VDP_clearPlane(BG_B,TRUE);
            VDP_drawImage(BG_B, &LVL, 0, 0);
            
        }
        else if(currentLevelIndex == 1)
        {
            VDP_clearPlane(BG_B,TRUE);
            VDP_drawImage(BG_B, &LVL1, 0, 0);
        }
        else if(currentLevelIndex == 2)
        {
            VDP_clearPlane(BG_B,TRUE);
            VDP_drawImage(BG_B, &LVL2, 0, 0);
        }
        spawnPlayer();
        spawnBullets();
        spawnLizardBullets();
        xenomSpawner(xenom,3);
        lizardSpawner(lizard,3);
        
        
    }
}

void showMainMenu()
{
    switch (gameON)
    {
        case FALSE:
            cursorPos.x = 8;
            VDP_drawText(">",cursorPos.x,cursorPos.y);
            VDP_drawText("START",10,10);
            VDP_drawText("EXIT",10,11);
            VDP_drawText("Press Start to select!!",10,25);
            break;

        case TRUE:
            break;
        
        default:
            break;
    }
    
    
}

void isColliding()
{
    Entity *e;
    Entity *l;
    Entity *b;
    Entity *lB;
    int i = 0;
    int j = 0;

    for (i = 0; i < MAX_BULLETS; i++)
    {
        b = &bullet[i];
        lB = &lizardBullet[i];
        
        if (lB->health > 0)
        {
            if (collideEntities(lB, &player))
            {
                player.health-=4;
                break;
            }
        }

        if (b->health > 0)
        {
            for (j = 0; j < MAX_ENEMIES; j++)
            {
                e = &xenom[j];
                l = &lizard[j];
                if (e->health > 0)
                {
                    if (collideEntities(b, e))
                    {
                        e->health--;
                        flashing = TRUE;

                        if (e->health < 1)
                        {
                            e->dir = death;
                            e--;
                            enemiesAlive--;
                            enemiesShouldDie--;
                            
                        }
                        break;
                    }
                }

                if(l->health > 0)
                {
                    if (collideEntities(b, l))
                    {
                        l->health--;
                        flashing = TRUE;

                        if (l->health < 1)
                        {
                            l->dir = death;
                            l--;
                            enemiesAlive--;
                            enemiesShouldDie--;
                        }
                        break;
                    }
                }

            }
        }
    }
}

void updateTimerDisplay()
{
    VDP_clearTextArea(21,13,2,1);
	sprintf(timerStr,"%d",timer);
	VDP_drawText(timerStr,21,13);
}

void gameOver()
{
    int timerTicks;

    if(player.health <=0)
    {
        VDP_clearSprites();
        VDP_drawImage(BG_B, &GameOver, 0, 0);
        VDP_drawText("GAME OVER",15,12);
        VDP_drawText(labelTimer,15,13);
        timerTicks++;

        if(ticks == 20 && timer > 0)
        {
            updateTimerDisplay();
            timer --;
            ticks = 0;           
        }
        else if(timer <= 0)
        {
            timer = 10;
            reviveEntity(&player,10);
            VDP_clearPlane(BG_A,TRUE);
            gameON = FALSE;
            showMainMenu();
        }
        
        
        
    }
}

void myJoyHandler(u16 joy, u16 changed, u16 state)
{
    if (joy == JOY_1)
    {
        if(gameON == TRUE)
        {
            if (state & BUTTON_UP)
            {
                player.moving = TRUE;

                if (state & BUTTON_LEFT)
                {
                    player.dir = upleft;
                    player.moving = TRUE;
                }
                else if (state & BUTTON_RIGHT)
                {
                    player.dir = upright;
                    player.moving = TRUE;
                }
                else
                {
                    player.dir = up;
                }
            }
            else if (state & BUTTON_DOWN)
            {

                player.moving = TRUE;

                if (state & BUTTON_LEFT)
                {
                    player.dir = downleft;
                    player.moving = TRUE;
                }
                else if (state & BUTTON_RIGHT)
                {
                    player.dir = downright;
                    player.moving = TRUE;
                }
                else
                {
                    player.dir = down;
                }
            }
            else if (state & BUTTON_LEFT)
            {
                player.dir = left;
                player.moving = TRUE;
            }
            else if (state & BUTTON_RIGHT)
            {
                player.dir = right;
                player.moving = TRUE;
            }
            else
            {
                player.moving = FALSE;
            }

            if (state & BUTTON_A)
            {
                if(player.isShooting == FALSE)
                {
                    shootBullet(player);
                }
                player.isShooting = TRUE;
            }
            else
            {
                player.isShooting = FALSE;
            }


              if(state &  BUTTON_START)
             {
                switch (gameIsPaused)
                {
                    case 0:
                    gameIsPaused ++;

                        break;

                    case 1:
                        gameIsPaused --;
                        break;
                    
                    default:
                        break;
                }
             }

        }


        if(gameON == FALSE)
        {
            if(state & BUTTON_START)
            {
                switch (cursorPos.y)
                {
                    case 10:
                        gameON = TRUE;
                        startGame();
                        break;
                    case 11:
                    
                        break;

                    default:
                        break;
                }  
            }
            else if(state & BUTTON_UP && cursorPos.y > 10)
            {
                VDP_clearText(8,cursorPos.y,1);
                cursorPos.y--;
            }
            else if(state & BUTTON_DOWN && cursorPos.y < 11)
            {
                VDP_clearText(8,cursorPos.y,1);
                cursorPos.y++;
            }
        }

        if (gameON == TRUE && player.health <=0 && timer>=0)
        {
            if(state & BUTTON_START)
            {
                 VDP_clearPlane(BG_A, FALSE);
                 VDP_clearPlane(BG_B, FALSE);
                 reviveEntity(&player,10);
                 changeLevelIndex();
                 startGame();
            }
        }
    }
}



int main()
{
    JOY_init();
    JOY_setEventHandler(myJoyHandler);
    loadLevel();
    VDP_setTextPlane(BG_A);


    while (1)
    {
        
        if (delay == 60)
        {
            delay = 0;
        }

        ticks++;
        if (ticks == 60)
        {
            VDP_clearPlane(BG_A,FALSE);
            ticks = 0;
        }
                
        if(gameIsPaused == 1)
        {
        
        }

        showMainMenu();

        if(player.health <= 0)
        {

        }
        
        if(gameON == TRUE && gameIsPaused == 0)
        {
            
            if (enemiesShouldDie <= 0)
            {
                exitUnlocked = TRUE;
            }
            // else if(enemiesAlive <=1 && enemiesShouldDie > 0)
            // {
            //     xenomSpawner(xenom,enemiesShouldDie%2);
            //     lizardSpawner(lizard,enemiesShouldDie%2);
            // }
           
            
            xenmoState(xenom);
            lizardState(lizard);
            enemyAI(xenom);
            enemyAI_LIZ(lizard);

            changeLevelIndex();
            movePlayer();
            plrShooting(15);
            isColliding(&bullet, &xenom);
            positionBullets();
            lizPositionBullets();
            
            changeHealthBar();
            gameOver();

            

            SPR_update();
        }
        SYS_doVBlankProcess();
    }
    return (0);
}
