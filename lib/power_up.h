#ifndef POWER_UP
#define POWER_UP

#include <splashkit.h>

using namespace std;

enum power_up_kind
{
    FUEL,
    SHIELD,
    HEALTH,
    AMMUNITION,
    COINS
};

struct power_up_data
{
    power_up_kind kind;
    sprite power_up_sprite;
    bool hide;
};

power_up_data new_power_up(double x, double y);

void draw_power_up(const power_up_data &power_up);

void update_power_up(power_up_data &power_up, int clock);

#endif