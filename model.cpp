// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include <iostream>
#include "model.h"

Model::Model(Geometry const& geometry)
        : geometry_(geometry)
        , paddle_(Block::from_top_left(geometry_.paddle_top_left0(),
                                       geometry_.paddle_dims_))
        , ball_(paddle_, geometry_)
{
    for (int i = 0; i < geometry_.brick_rows; i++) {
        for (int j = 0; j < geometry_.brick_cols; j++) {
            Block block;
            block.width = geometry_.brick_dims().width;
            block.height = geometry_.brick_dims().height;
            block.x = geometry_.side_margin + j*(geometry_.brick_spacing.width + geometry_.brick_dims().width);
            block.y = geometry_.top_margin + i*(geometry_.brick_spacing.height + geometry_.brick_dims().height);
            bricks_.push_back(block);
        }
    }
}

// Freebie.
void Model::launch()
{
    ball_.live_ = true;
}

void Model::paddle_to(int x)
{
    paddle_.x = x;
    if (!ball_.live_) {
        Ball ball(paddle_, geometry_);
        ball_ = ball;
    }
}

void Model::update(int boost)
{
    Ball ball = ball_.next();
    if (ball_.live_) {
        if (ball.hits_bottom(geometry_)) {
            ball_.live_ = false;
            std::cout << ("Triggered Hits Bottom\n");
            return;
        }
        if (ball.hits_top(geometry_)) {
            ball_.reflect_vertical();
            std::cout << ("Triggered Hits Top\n");
        }
        if (ball.hits_side(geometry_)) {
            ball_.reflect_horizontal();
            std::cout << ("Triggered Hits Side\n");
        }
        if (ball.destroy_brick(bricks_)) {
            ball_.reflect_horizontal();
            ball_.reflect_vertical();
            std::cout << ("Triggered Destroy Brick\n");
        }
        if (ball.hits_block(paddle_)) {
            ball_.reflect_vertical();
            ball_.velocity_.width += boost;
            std::cout << ("Triggered Hits Block (Paddle)\n");
        }
        ball_ = ball_.next();
    }


}


