#ifndef BUTTON_H
#define BUTTON_H

#include "splashkit.h"

using namespace std;

/**
 * @brief Button data structure used to abstract the idea of button
 * 
 * @field text             The text the button is going to have 
 * @field clickable_space  The space of the button that when clicked triggers the functionality
 */
struct button_data
{
    string text;
    rectangle clickable_space;
};

/**
 * @brief Check if the player clicked the button or not
 * 
 * @param m_position    Mouse position
 * @param button        Button data
 * @return true         If the button's clickable space was clicked
 * @return false        If the button's clickable space has not been clicked
 */
bool button_clicked(const point_2d &m_position, const button_data &button);

/**
 * @brief Draw a button on screen according to button's data
 * 
 * @param button  The button to be drawn
 */
void draw_button(const button_data &button);

/**
 * @brief  Create a new button according to the parameters
 * 
 * @param x              X coordinate of the button
 * @param y              Y coordinate of the button
 * @param width          Button's width
 * @param height         Button's height
 * @param text           Button's inner text
 * @return               button_data struct
 */
button_data new_button(double x, double y, double width, double height, const string &text);

#endif