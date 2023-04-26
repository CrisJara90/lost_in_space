#ifndef BUTTON_H
#define BUTTON_H

#include "splashkit.h"

using namespace std;

struct button_data
{
    string text;
    rectangle clickable_space;
};

bool button_clicked(const point_2d &m_position, const button_data &button);

void draw_button(const button_data &button);

button_data new_button(double x, double y, double width, double height, const string &text);

#endif