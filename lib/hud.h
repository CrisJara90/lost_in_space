#ifndef HUD_H
#define HUD_H

#include "player.h"
#include "power_up.h"

#define GAP 5
#define MARGIN 10
#define LOWER_BAR_POSITION screen_height() * 0.8 
#define BAR_LENGTH 400
#define DEFAULT_FONT "roboto"
    
    

void draw_hud(player_data player, power_up_data power_up);

#endif