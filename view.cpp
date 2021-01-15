#include "view.h"

using namespace ge211;

// You can change this or even determine it some other way:
static int const grid_size = 64;

View::View(Model const& model)
: model_(model)
{
    std::cout << (initial_window_dimensions().width - (((width - 1) * gap))) / width;
    std::cout << "\n" << initial_window_dimensions().width;

}


ge211::Position View::positionToPixels(ge211::Position position) {
    int xPos = (position.x * (dim.width + gap)) + (dim.width / 2);
    int yPos = (position.y * (dim.height + gap)) + (dim.height / 2);
    ge211::Position  position1 = {xPos, yPos};
    return position1;
}

ge211::Position View::pixelsToPosition(ge211::Position position) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int posX = j * (dim.width + gap);
            int posY = i * (dim.height + gap);
            if (position.x > posX && position.x < posX + dim.width) {
                if (position.y < posY + dim.height && position.y > posY) {
                    ge211::Position positionTemp = {j, i};
                    return positionTemp;
                }
            }
        }
    }
}

void View::draw(Sprite_set& set, ge211::Position mousePosition)
{
    // Making Rectangles
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            set.add_sprite(square_sprite, {gap + j * (gap + dim.width), gap + i * (gap + dim.height)}, 0);
        }
    }

    // Drawing Black and White at each position
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Position temp = {i, j}; // j, i?
            if (model_.operator[]({i, j}) == Player::light) {
                set.add_sprite(white_sprite, positionToPixels(temp).up_left_by({(dim.width / 3) - 6, (dim.width / 3) - 6}), 1);
                if (model_.winner() == Player::dark) {
                    set.add_sprite(loser_sprite, positionToPixels(temp).up_left_by({(dim.width / 3) - 6, (dim.width / 3) - 6}), 8);
                }
            } else if (model_.operator[]({i, j}) == Player::dark) {
                set.add_sprite(black_sprite, positionToPixels(temp).up_left_by({(dim.width / 3) - 6, (dim.width / 3) - 6}), 1);
                if (model_.winner() == Player::light) {
                    set.add_sprite(loser_sprite, positionToPixels(temp).up_left_by({(dim.width / 3) - 6, (dim.width / 3) - 6}), 8);
                }
            }
        }
    }

    // Showing available moves
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            ge211::Position tempPos = {j, i};
            Move const* theMoveP = model_.find_move(tempPos);
            if (theMoveP != nullptr) {
                Move theMove = *theMoveP;
                set.add_sprite(temp_sprite, positionToPixels(tempPos).up_left_by({(dim.width / 3) - 6, (dim.width / 3) - 6}), 2);
                if (tempPos.x == pixelsToPosition(mousePosition).x) {
                    if (tempPos.y == pixelsToPosition(mousePosition).y) {
                        for (Position position : theMove.second){
                            set.add_sprite(gained_sprite, positionToPixels(position).up_left_by({(dim.width / 3) - 6, (dim.width / 3) - 6}), 3);
                        }
                    }
                }
            }
        }
    }

    // Showing whose turn it is
    if (model_.turn() == Player::dark) {
        set.add_sprite(black_sprite, mousePosition.up_left_by({dim.width / 3, dim.width / 3}), 9);
    } else if (model_.turn() == Player::light) {
        set.add_sprite(white_sprite, mousePosition.up_left_by({dim.width / 3, dim.width / 3}), 9);
    }
}

Dimensions View::initial_window_dimensions() const
{
    // You can change this if you want:
    return grid_size * model_.board().dimensions();
}

std::string View::initial_window_title() const
{
    // You can change this if you want:
    return "Reversi";
}
