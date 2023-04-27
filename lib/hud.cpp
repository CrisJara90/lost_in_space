#include "splashkit.h"
#include "hud.h"
#include <iostream>

using namespace std;

void draw_hud(player_data player, power_up_data power_up)
{
    // HUD
    // HUD will have the score and location
    int hud_x = 0;
    int hud_y = 0;
    int hud_height = 70;
    int hud_width = 350;
    //location
    string location_text = "LOCATION: " + to_string(center_point(player.player_sprite).x) + ", " + to_string(center_point(player.player_sprite).y);
    int location_text_font_size = 15;
    double location_h = text_height(location_text, DEFAULT_FONT, location_text_font_size);
    double location_w = text_width(location_text, DEFAULT_FONT, location_text_font_size);
    double location_x = GAP;
    double location_y = GAP;
    //score
    string score_text = "SCORE: " + to_string(player.score);
    int score_text_font_size = 20;
    double score_x = GAP;
    double score_y = location_y + location_h + GAP;
    double score_h = text_height(score_text, DEFAULT_FONT, score_text_font_size);


    //shield icon
    double shield_icon_x = MARGIN;
    double shield_icon_y = LOWER_BAR_POSITION;
    double shield_icon_h = bitmap_height("shield-icon");
    double shield_icon_w = bitmap_width("shield-icon");
    //shield bar
    double shield_bar_x = MARGIN + shield_icon_w;
    double shield_bar_y = LOWER_BAR_POSITION;
    double shield_bar_h = shield_icon_h;
    double shield_bar_w = BAR_LENGTH;


    // Ammo
    double ammo_icon_x = screen_width() - bitmap_width("ammo-icon") - MARGIN;
    double ammo_icon_y = shield_bar_y;
    double ammo_icon_w = bitmap_width("ammo-icon"); // ammo icon is a square so width is equal to heigth

    string ammo_text = to_string(player.ammunition);
    //int ammo_text_font_size = 100*ammo_icon_w/55; // if full screen
    int ammo_text_font_size = 50*ammo_icon_w/55;
    double ammo_text_x = ammo_icon_x - text_width(ammo_text, "roboto", ammo_text_font_size);
    double ammo_text_y = ammo_icon_y;


    // health icon
    double health_icon_x = MARGIN;
    double health_icon_y = shield_bar_y + shield_icon_h + GAP;
    double health_icon_h = bitmap_height("health-icon");
    double health_icon_w = bitmap_width("health-icon");
    // health bar
    double health_bar_x = MARGIN + health_icon_w;
    double health_bar_y = shield_bar_y + shield_bar_h + GAP;
    double health_bar_h = health_icon_h;
    double health_bar_w = BAR_LENGTH; // 100 of health 1 of health is 5px


    // fuel icon
    double fuel_icon_x = MARGIN;
    double fuel_icon_y = health_bar_y + health_icon_h + GAP;
    double fuel_icon_h = bitmap_height("fuel-icon");
    double fuel_icon_w = bitmap_width("fuel-icon");
    // fuel bar
    double fuel_bar_x = fuel_icon_x + fuel_icon_w;
    double fuel_bar_y = fuel_icon_y;
    double fuel_bar_h = fuel_icon_h;
    double fuel_bar_w = BAR_LENGTH;


    // Draw HUD
    fill_rectangle(COLOR_DARK_BLUE, hud_x, hud_y, hud_width, hud_height, option_to_screen());
    //Draw Score
    draw_text(score_text, COLOR_WHITE, DEFAULT_FONT, score_text_font_size, score_x, score_y, option_to_screen());
    //Draw Location
    draw_text(location_text, COLOR_WHITE, DEFAULT_FONT, location_text_font_size, location_x, location_y, option_to_screen());


    // Draw fuel icon and bar
    draw_bitmap("fuel-icon", fuel_icon_x, fuel_icon_y, option_to_screen());
    fill_rectangle(COLOR_DARK_GRAY, fuel_bar_x+GAP, fuel_bar_y, fuel_bar_w, fuel_bar_h,  option_to_screen()); // empty bar
    fill_rectangle(COLOR_LIGHT_GOLDENROD_YELLOW, fuel_bar_x+GAP, fuel_bar_y, fuel_bar_w * player.fuel_pct, fuel_bar_h,  option_to_screen());
    //draw_bitmap("empty", fuel_bar_x+GAP, fuel_bar_y, option_to_screen());
    // (THERE IS AN ERROR HERE!) 
    //int part_width = static_cast<int>(bitmap_width("fuel-bar") * player.fuel_pct);
    //draw_bitmap("fuel-bar", 40, , option_part_bmp(0, 0, part_width, bitmap_height("fuel-bar"), option_to_screen()));


    // Draw shield icon and bar
    draw_bitmap("shield-icon", shield_icon_x, shield_icon_y, option_to_screen());
    fill_rectangle(COLOR_DARK_GRAY, shield_bar_x+GAP, shield_bar_y, shield_bar_w, shield_bar_h,  option_to_screen()); // empty bar
    fill_rectangle(COLOR_LIGHT_BLUE, shield_bar_x+GAP, shield_bar_y, shield_bar_w * player.shield, shield_bar_h,  option_to_screen());
    
    
    // Draw health icon and bar
    draw_bitmap("health-icon", health_icon_x, health_icon_y, option_to_screen());
    fill_rectangle(COLOR_DARK_GRAY, health_bar_x+GAP, health_bar_y, health_bar_w, health_bar_h,  option_to_screen()); // empty bar
    fill_rectangle(COLOR_LIGHT_GREEN, health_bar_x+GAP, health_bar_y, health_bar_w * player.health, health_bar_h,  option_to_screen());

    
    // Draw Ammo
    draw_bitmap("ammo-icon", ammo_icon_x, ammo_icon_y, option_scale_bmp(0.5, 0.5, option_to_screen()));
    draw_text(ammo_text, COLOR_WHITE, DEFAULT_FONT, ammo_text_font_size, ammo_text_x, ammo_text_y, option_to_screen()); 

}
