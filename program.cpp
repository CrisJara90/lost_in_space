#include "splashkit.h"
#include "lib/game.h"

/**
 * Load the game images, sounds, etc.
 */
void load_resources()
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

/**
 * Entry point.
 * 
 * Manages the initialisation of data, the event loop, and quitting.
 */

int main()
{
    open_window("Lost In Space", 800, 600);
    
    load_resources();

    player_data player;
    player = new_player();

    power_up_data power_up;
    power_up = new_power_up(100, 100);
    
    /* Draw Welcome Page */
    bitmap title = bitmap_named("game_title");

    // Set up button structure
    button_data start_button;
    double start_button_width = 150;
    double start_button_height = 80;
    double start_button_x = screen_width()/2 - start_button_width/2;
    double start_button_y = screen_height()/2 + bitmap_height(title);
    start_button = new_button(start_button_x, start_button_y, start_button_width, start_button_height, "START");
       
    // Display welcome screen until the start button is clicked   
    while(!button_clicked(mouse_position(), start_button) && !quit_requested())
    {
        clear_screen(COLOR_BLACK);
        // Handle input to check if the start button was clicked
        process_events();
        // Draw title
        draw_bitmap(title, screen_width()/2 - bitmap_width(title)/2, screen_height()/2 - bitmap_height(title)/2);
        // Draw button
        draw_button(start_button);
        refresh_screen(60);
    }

    int clock=0;
    // game main loop
    while ( !quit_requested() )
    {
        // Handle input to adjust player movement
        process_events();
        handle_input(player);

        // Perform movement and update the camera
        update_player(player);

        update_power_up(power_up, clock);

        // Redraw everything
        clear_screen(COLOR_BLACK);

        // including something stationary - it doesn't move
        fill_rectangle(COLOR_WHITE, 400, 400, 10, 10);

        // as well as the player who can move
        draw_player(player);

        if(!power_up.hide)
            draw_power_up(power_up);

        // Draw HUD
        draw_hud(player, power_up);

        // handle collisions
        if (sprite_collision(player.player_sprite, power_up.power_up_sprite) && !power_up.hide)
        {
            // hide power up
            power_up.hide = true;
            // update player depending on the power up
            switch (power_up.kind)
            {
                case FUEL:
                    if(player.fuel_pct != 1)
                        player.fuel_pct += 0.5;
                    write_line("fuel " + to_string(player.fuel_pct));
                    break;
                case SHIELD:
                    if(player.shield != 1)
                        player.shield += 0.25;
                    write("shield ");
                    write_line(player.shield);
                    break;
                case HEALTH:
                    if(player.health != 1)
                        player.health += 0.25;
                    write("health ");
                    write_line(player.health);
                    break;
                case AMMUNITION:
                    player.ammunition += 10;
                    write("ammunition ");
                    write_line(player.ammunition);
                    break;
                default:
                    write("score ");
                    player.score += 1;
                    write_line(player.score);
                    break;
            }
        }
    

        refresh_screen(60);
        clock++;
    }

    return 0;
}