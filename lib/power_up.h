#ifndef POWER_UP
#define POWER_UP

#include <splashkit.h>
#include "player.h"

using namespace std;

/**
 * @brief Different options for the kind of power up
 * Adjusts the image used
 */
enum power_up_kind
{
    FUEL,
    SHIELD,
    HEALTH,
    AMMUNITION,
    COINS
};

/**
 * @brief The power_up_data struct keeps track of all the information related to the power up
 * 
 * @field kind             Current kind of power up
 * @field power_up_sprite  Power up's sprite - used to track position, movement
 * @field hide             Current state of the power up - used to check if it has been collided or not.
 */
struct power_up_data
{
    power_up_kind kind;
    sprite power_up_sprite;
    bool hide;
};

/**
 * @brief Creates a new power up at position (x,y) on the screen.
 * 
 * @param x  X screen coordinate
 * @param y  Y screen coordinate
 * @return   The new power_up data 
 */
power_up_data new_power_up(double x, double y);

/**
 * @brief Draws power up to the screen
 * 
 * @param power_up The power up to drawn to the screen
 */
void draw_power_up(const power_up_data &power_up);

/**
 * @brief Actions a step update of the power up - adjusting its movement every 200 clocks.
 * 
 * @param power_up   The player being updated
 * @param clock      clock used to keep track of the time during program execution
 */
void update_power_up(power_up_data &power_up, int clock);


/**
 * @brief Handles the collision between the player's ship and any power up. If they collide, the power up dissapears
 * and the player information is updated according to the kind of power up.
 * 
 * @param player    The player to track the collision of
 * @param power_up  The power up to track the collision of
 */
void handle_collisions(player_data &player, power_up_data &power_up);

#endif