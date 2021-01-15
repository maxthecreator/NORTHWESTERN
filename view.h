#pragma once

#include "model.h"

#include <string>

class View
{
public:
    explicit View(Model const&);

    // You will probably want to add arguments here so that the
    // controller can communicate UI state (such as a mouse or
    // cursor position):
    void draw(ge211::Sprite_set& set, ge211::Position mousePosition);

    ge211::Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    void on_mouse_up(ge211::Mouse_button, ge211::Position);

    ge211::Position pixelsToPosition(ge211::Position position);

    ge211::Position positionToPixels(ge211::Position position);

    void game_is_over(ge211::Sprite_set& set, Player loser);

private:

    Model const& model_;
    ge211::Dimensions dim = {(initial_window_dimensions().width - (((width - 1) * gap))) / width,
                             (initial_window_dimensions().height - (((height - 1) * gap))) / height};

    ge211::Color const tileColor {0, 250, 154};
    ge211::Color const blackColor {0, 0, 0};
    ge211::Color const whiteColor {255, 255, 255};
    ge211::Color const greyColor {105, 105, 105};
    ge211::Color const tempColor {42, 42, 245};
    ge211::Color const gainedColor {255, 0, 0};

    ge211::Rectangle_sprite const
            square_sprite {dim, tileColor};

    ge211::Circle_sprite const
            black_sprite {dim.width / 3, blackColor}; //dim.width /3

    ge211::Circle_sprite const
            white_sprite {dim.width / 3, whiteColor};

    ge211::Circle_sprite const
            loser_sprite {dim.width / 3, greyColor};

    ge211::Circle_sprite const
            temp_sprite {dim.width / 3, tempColor};
    ge211::Circle_sprite const
            gained_sprite {dim.width / 3, gainedColor};

    static int const height = 8;
    static int const width = 8;
    static int const gap = 5;


};

