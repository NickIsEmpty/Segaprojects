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

#define MAP_HEIGHT 28
#define MAP_WIDTH 40

#define MAX_BULLETS 11
#define MAX_ENEMIES 3

#define LEVEL_NUM 3


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
        {0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
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
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

typedef struct
{
    u8 x;
    u8 y;
} Point;

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

Entity player = {{150, 165}, {0, 0}, 32, 32, 100, 0, 0, 0, FALSE, FALSE, up, NULL, "PLAYER"};
Entity xenom[MAX_ENEMIES];
Entity bullet[MAX_BULLETS];

bool exitUnlocked = FALSE;
bool gameON = FALSE;
bool gameIsPaused = FALSE;
bool flashing = FALSE;

Point cursorPos  = {8, 10};

int i = 0;
int ticks;
int delay;
int enemiesAlive = 0;

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
    int j = 0;
    int a = 0;
    for (i = 0; i < MAX_BULLETS; i++)
    {
        b = &bullet[i];

        b->pos.x += b->vel.x;
        b->pos.y += b->vel.y;

        for (j = 0; j < MAX_ENEMIES; j++)
        {
            e = &xenom[j];
            if (checkCollisions(b->pos.x, b->pos.y, 1, 1, b) == 0 || (collideEntities(b, e) && e->health > 0 && b->health > 0))
            {
                b->health = 0;
                killEntity(b);
                swapToColor(e->spriteColor,RGB24_TO_VDPCOLOR(0xaf0a09),e->spriteColor);
                swapToColor(50,RGB24_TO_VDPCOLOR(0xaf0a09),49);
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
            switch (player.dir)
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
    if (ticks % fireRate == 1)
    {
        if (player.isShooting == TRUE)
        {
            shootBullet(player);
            ticks = 1;
        }
        else if (player.isShooting == FALSE)
        {
        }
    }
}


void enemySpawner(Entity *e)
{
    enemiesAlive = 0;
    int randX;
    int randY; 
    randX = random()%200;
    randY = random()%200;
    for (i = 0; i < MAX_ENEMIES; i++)
    {
        e = &xenom[i];
        e->pos.x = randX + random()%150;
        e->pos.y = randY + random()%150;
        e->w = 32;
        e->h = 32;
        e->health = 2;
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

void enemyState(Entity *e)
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

        if (checkCollisions(e->pos.x + e->dirIntX, e->pos.y + e->dirIntY, 4, 4, e) == 0)
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
        if (e->pos.y + e->h < player.pos.y && e->health > 0)
        {
            e->dir = down;
        }
        else if (e->pos.y > player.pos.y + player.h && e->health > 0)
        {
            e->dir = up;
        }
        else if (e->pos.x + e->w < player.pos.x && e->health > 0)
        {
            e->dir = right;
        }
        else if (e->pos.x > player.pos.x + player.w && e->health > 0)
        {
            e->dir = left;
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

        if (collideEntities(e, &player))
        {
            e->vel.x = 0;
            e->vel.y = 0;
        }
    }
}


void startGame()
{
    if(gameON == TRUE)
    {
        VDP_drawImage(BG_A, &LVL, 0, 0);

        SPR_init();

        spawnPlayer();

        spawnBullets();
        enemySpawner(xenom);

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
                    break;
                case 1:
                    levelList[i][j] = level2[i][j];
                    break;
                case 2:
                    levelList[i][j] = level3[i][j];
                    break;
                
                    default:
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
        
        loadLevel();
        startGame();
        
        if(currentLevelIndex == 0 )
        {
            VDP_drawImage(BG_A, &LVL, 0, 0);
        }
        else if(currentLevelIndex == 1)
        {
            VDP_drawImage(BG_A, &LVL1, 0, 0);
        }
        else if(currentLevelIndex == 2)
        {
            VDP_drawImage(BG_A, &LVL, 0, 0);
        }
        spawnPlayer();
        spawnBullets();
        enemySpawner(xenom);
        
        
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
    Entity *b;
    int i = 0;
    int j = 0;

    for (i = 0; i < MAX_BULLETS; i++)
    {
        b = &bullet[i];
        if (b->health > 0)
        {
            for (j = 0; j < MAX_ENEMIES; j++)
            {
                e = &xenom[j];
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
                        }
                        break;
                    }
                }
            }
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
        else
        {

        }
    }
}

int main()
{
    JOY_init();
    JOY_setEventHandler(myJoyHandler);
    
    loadLevel();

    while (1)
    {
        
        if (delay == 60)
        {
            delay = 0;
        }

        ticks++;
        if (ticks == 60)
        {
            ticks = 0;
        }
                
        if(gameIsPaused == 1)
        {

        }

        showMainMenu();
        
        if(gameON == TRUE && gameIsPaused == 0)
        {
            
            if (enemiesAlive == 0)
            {
                exitUnlocked = TRUE;
            }
           
            enemyState(xenom);
            enemyAI(xenom);

            changeLevelIndex();
            movePlayer();
            plrShooting(15);
            isColliding(&bullet, &xenom);
            positionBullets();
            SPR_update();
        }
        SYS_doVBlankProcess();
    }
    return (0);
}
