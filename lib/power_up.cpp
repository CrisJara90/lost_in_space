#include "power_up.h"

/**
 * @brief The power up bitmap function converts a power up kind into a 
 * bitmap that can be used.
 * 
 * Not exposed by the header.
 * 
 * @param kind  The kind of power up you want the bitmap of
 * @return      The bitmap matching this power up kind
 */
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
    // Set the power up kind to a random power up
    result.kind = static_cast<power_up_kind>(rnd(0,4));
    result.power_up_sprite = create_sprite(power_up_bitmap(result.kind));
    // Set power up's X and Y coordinate according to parameters.
    sprite_set_x(result.power_up_sprite, x);
    sprite_set_y(result.power_up_sprite, y);
    // Set the power up to have a random velocity and random direction
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
    // Update power up sprite
    update_sprite(power_up.power_up_sprite);
    // Update its random velocity and direction each 200 clocks
    if(clock%200 == 0)
    {
        sprite_set_dx(power_up.power_up_sprite, rnd()*4-2);
        sprite_set_dy(power_up.power_up_sprite, rnd()*4-2);
    } 
}

void handle_collisions(player_data &player, power_up_data &power_up)
{
    // handle collisions
    if (sprite_collision(player.player_sprite, power_up.power_up_sprite) && !power_up.hide)
    {
        // hide power up
        power_up.hide = true;
        // update player depending on the kind of power up
        switch (power_up.kind)
        {
            case FUEL:
                if(player.fuel_pct != 1)
                    player.fuel_pct += 0.5;
                break;
            case SHIELD:
                if(player.shield != 1)
                    player.shield += 0.25;
                break;
            case HEALTH:
                if(player.health != 1)
                    player.health += 0.25;
                break;
            case AMMUNITION:
                player.ammunition += 10;
                break;
            default:
                player.score += 1;
                break;
        }
    }
}