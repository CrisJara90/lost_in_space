#include "splashkit.h"
#include "button.h"

bool button_clicked(const point_2d &m_position, const button_data &button)
{
    // if m_position inside button, then button clicked
    if(mouse_clicked(LEFT_BUTTON))
    {
        return point_in_rectangle(m_position, button.clickable_space);
    }
    return false;
}

void draw_button(const button_data &button)
{
    int font_size = 40; 
    int text_w = text_width(button.text, "roboto", font_size);
    int text_h = text_height(button.text, "roboto", font_size);
    double offset_x = (button.clickable_space.width - text_w)/2.0;
    double offset_y = (button.clickable_space.height - text_h)/2.0;

    draw_rectangle(COLOR_WHITE_SMOKE, button.clickable_space);
    fill_rectangle(COLOR_WHITE_SMOKE, button.clickable_space);
    draw_text(button.text, COLOR_BLACK, "roboto", font_size, button.clickable_space.x+offset_x, button.clickable_space.y+offset_y);
    return;
}

button_data new_button(double x, double y, double width, double height, const string &text)
{
    button_data result;
    result.clickable_space = rectangle_from(x, y, width, height);
    result.text = text;
    return result;
}