#include "splashkit.h"
#include "power_up.h"

bitmap power_up_bitmap(power_up_kind kind)
{
    switch (kind)
    {
    case FUEL:
        return bitmap_named("fuel");
    case SHIELD:
        return bitmap_named("shield");
    case HEALTH:
        return bitmap_named("heart");
    case AMMUNITION:
        return bitmap_named("bullet");
    default:
        return bitmap_named("gold_coin");
    }
}


power_up_data new_power_up(double x, double y)
{
    power_up_data result;
    result.hide = false;
    result.kind = static_cast<power_up_kind>(rnd(0,4));
    result.power_up_sprite = create_sprite(power_up_bitmap(result.kind));
    sprite_set_x(result.power_up_sprite, x);
    sprite_set_y(result.power_up_sprite, y);

    sprite_set_dx(result.power_up_sprite, rnd()*4-2);
    sprite_set_dy(result.power_up_sprite, rnd()*4-2);

    return result;
}

void draw_power_up(const power_up_data &power_up)
{
    draw_sprite(power_up.power_up_sprite);
}

void update_power_up(power_up_data &power_up, int clock)
{
    update_sprite(power_up.power_up_sprite);
    if(clock%200 == 0)
    {
        sprite_set_dx(power_up.power_up_sprite, rnd()*4-2);
        sprite_set_dy(power_up.power_up_sprite, rnd()*4-2);
    } 
}