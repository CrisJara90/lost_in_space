#include "player.h"
#include "splashkit.h"

/**
 * The ship bitmap function converts a ship kind into a 
 * bitmap that can be used.
 * 
 * Not exposed by the header.
 * 
 * @param kind  The kind of ship you want the bitmap of
 * @return      The bitmap matching this ship kind
 */
bitmap ship_bitmap(ship_kind kind)
{
    switch (kind)
    {
    case AQUARII:
        return bitmap_named("aquarii");
    case GLIESE:
        return bitmap_named("gliese");
    default:
        return bitmap_named("pegasi");
    }
}

player_data new_player()
{
    player_data result;

    bitmap default_bitmap = ship_bitmap(AQUARII);

    // Create the sprite with 3 layers - we can turn on and off based
    // on the ship kind selected
    result.player_sprite = create_sprite(default_bitmap);

    sprite_add_layer(result.player_sprite, ship_bitmap(GLIESE), "GLIESE");
    sprite_add_layer(result.player_sprite, ship_bitmap(PEGASI), "PEGASI");

    // Default to layer 0 = Aquarii so hide others
    sprite_hide_layer(result.player_sprite, 1);
    sprite_hide_layer(result.player_sprite, 2);

    result.kind = AQUARII;

    // Position in the centre of the initial screen
    sprite_set_x(result.player_sprite, (screen_width() - sprite_width(result.player_sprite))/2.0);
    sprite_set_y(result.player_sprite, (screen_height() - sprite_height(result.player_sprite))/2.0);

    // initialize player's fuel
    result.fuel_pct = 0.75;

    // initialize health
    result.health = 1;

    // initialize shield
    result.shield = 0;

    // initialize ammo
    result.ammunition = 0;

    // initialize score
    result.score = 0;
    
    return result;
}

void draw_player(const player_data &player_to_draw)
{
    draw_sprite(player_to_draw.player_sprite);
}

void update_player(player_data &player_to_update)
{
    // Apply movement based on rotation and velocity in the sprite
    update_sprite(player_to_update.player_sprite);
    // Test edge of screen boundaries to adjust the camera
    double left_edge = camera_x() + SCREEN_BORDER;
    double right_edge = left_edge + screen_width() - 2 * SCREEN_BORDER;
    double top_edge = camera_y() + SCREEN_BORDER;
    double bottom_edge = top_edge + screen_height() - 2 * SCREEN_BORDER;

    // Get the center of the player
    point_2d sprite_center = center_point(player_to_update.player_sprite);

    // Test if the player is outside the area and move the camera
    // the player will appear to stay still and everything else
    // will appear to move :)

    // Test top/bottom of screen
    if (sprite_center.y < top_edge)
    {
        move_camera_by(0, sprite_center.y - top_edge);
    }
    else if (sprite_center.y > bottom_edge)
    {
        move_camera_by(0, sprite_center.y - bottom_edge);
    }

    // Test left/right of screen
    if (sprite_center.x < left_edge)
    {
        move_camera_by(sprite_center.x - left_edge, 0);
    }
    else if (sprite_center.x > right_edge)
    {
        move_camera_by(sprite_center.x - right_edge, 0);
    }
}

/**
 * Switch the ship kind - will adjust which layer is hidden/shown
 */
void player_switch_to_ship(player_data &player, ship_kind target)
{
    // only do this if there is a change
    if (player.kind != target)
    {
        // show then hide layers
        sprite_show_layer(player.player_sprite, static_cast<int>(target));
        sprite_hide_layer(player.player_sprite, static_cast<int>(player.kind));

        // remember what is currently shown
        player.kind = target;
    }
}

void handle_input(player_data &player, bool &is_full_screen)
{
    // Allow the player to switch between full screen mode and normal screen.
    if(key_typed(F11_KEY))
    {
        if(!is_full_screen)
        {
            move_current_window_to(0,30);
            resize_current_window(1920, 1080);
            is_full_screen = true;
        }
        else
        {
            move_current_window_to(368, 132);
            resize_current_window(800,600);
            is_full_screen = false;
        }
    }

    // Allow the player to switch ships
    if (key_typed(NUM_1_KEY))
        player_switch_to_ship(player, AQUARII);
    if (key_typed(NUM_2_KEY))
        player_switch_to_ship(player, GLIESE);
    if (key_typed(NUM_3_KEY))
        player_switch_to_ship(player, PEGASI);

    // Handle movement - rotating left/right and moving forward/back
    //float dx = sprite_dx(player.player_sprite);
    float rotation = sprite_rotation(player.player_sprite);

    // Allow rotation with left/right keys
    if (key_down(LEFT_KEY))
        sprite_set_rotation(player.player_sprite, rotation - PLAYER_ROTATE_SPEED);
    if (key_down(RIGHT_KEY))
        sprite_set_rotation(player.player_sprite, rotation + PLAYER_ROTATE_SPEED);

    // Allow player to move forward or backwards by holding the up/down keys - Movement happens only when the key is pressed
    if (key_down(UP_KEY))
        sprite_set_dx(player.player_sprite, 2*PLAYER_SPEED);
    else if (key_down(DOWN_KEY))
        sprite_set_dx(player.player_sprite, -2*PLAYER_SPEED);
    else if (key_released(UP_KEY) || key_released(DOWN_KEY))
        sprite_set_dx(player.player_sprite, 0);
}

