#ifndef HUD_H
#define HUD_H

#include "player.h"
#include "power_up.h"

#define GAP 5
#define MARGIN 10
#define LOWER_SECTION_HUD screen_height() * 0.8 
#define BAR_LENGTH 400
#define DEFAULT_FONT "roboto"

/**
 * @brief Draw the entire HUD according to player's data
 * 
 * @param player     Current player data - Used to update the HUD according to the players new data
 */
void draw_hud(const player_data &player);

#endif