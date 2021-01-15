#include "controller.h"

using namespace ge211;

Controller::Controller(int size)
        : Controller(size, size)
{ }

Controller::Controller(int width, int height)
        : model_(width, height)
        , view_(model_)
        , position_(position_)

{ }

void Controller::draw(Sprite_set& sprites)
{
    view_.draw(sprites, position_);

}

void Controller::on_mouse_up(ge211::Mouse_button, ge211::Position position) {
    position_ = position;
    std::cout << "X: " << position.x << '\n';
    std::cout << "Y: " << position.y << '\n';
    std::cout << "Pos X: " << view_.pixelsToPosition(position).x << '\n';
    std::cout << "Pos Y: " << view_.pixelsToPosition(position).y << '\n';
    Move const* movep = model_.find_move(view_.pixelsToPosition(position));
    if (!movep || model_.is_game_over()){
        return;
    }
    else {
        model_.play_move(view_.pixelsToPosition(position));
    }
}

void Controller::on_mouse_move(ge211::Position position) {
    position_ = position;
}

Dimensions Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

