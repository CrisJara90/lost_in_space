#ifndef LOST_IN_SPACE_PLAYER
#define LOST_IN_SPACE_PLAYER

#include "splashkit.h"

using namespace std;

#define PLAYER_SPEED 1.5
#define PLAYER_ROTATE_SPEED 3
#define SCREEN_BORDER 100

/**
 * Different options for the kind of ship.
 * Adjusts the image used.
 */
enum ship_kind
{
    AQUARII,
    GLIESE,
    PEGASI
};

/**
 * The player data keeps track of all of the information related to the player.
 * 
 * @field   player_sprite   The player's sprite - used to track position and movement
 * @field   score           The current score for the player
 * @field   kind            Current kind of player ship
 * @field   fuel_pct        Current amount of fuel of player. Goes from 0 to 1 
 * @field   shield          Current amount of shield the player has. Goes from 0 to 1
 * @field   health          Current amount of health the players. Goes from 0 to 1
 * @field   ammunition      Current number of bullets the player has.
 */
struct player_data
{
    sprite      player_sprite;
    int         score;
    ship_kind   kind;
    float fuel_pct;
    float shield;
    float health;
    int ammunition;
};

/**
 * Creates a new player in the centre of the screen with the default ship.
 * 
 * @returns     The new player data
 */
player_data new_player();

/**
 * Draws the player to the screen. 
 * 
 * @param player_to_draw    The player to draw to the screen
 */
void draw_player(const player_data &player_to_draw);

/**
 * Actions a step update of the player - moving them and adjusting the camera.
 * 
 * @param player_to_update      The player being updated
 */
void update_player(player_data &player_to_update);

/**
 * Read user input and update the player based on this interaction.
 * 
 * @param player    The player to update
 */
void handle_input(player_data &player, bool &is_full_screen);

#endif 