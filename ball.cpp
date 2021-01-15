// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include <iostream>
#include "ball.h"
#include "geometry.h"

static ge211::Position above_block(Block const& block,
                                   Geometry const& geometry)
{
    ge211::Position position = block.top_left().right_by(block.width/2);
    return position.up_by(geometry.ball_radius + 1);
}

// It won't compile without this, so you get it for free.
Ball::Ball(Block const& paddle, Geometry const& geometry)
        : radius_   (geometry.ball_radius)
        , velocity_ (geometry.ball_velocity0)
        , center_   (above_block(paddle, geometry))
        , live_     (false)
{ }

ge211::Position Ball::top_left() const
{
    ge211::Position position = center_.up_by(radius_);
    return position.left_by(radius_);
}

bool Ball::hits_bottom(Geometry const& geometry) const
{
    return center_.down_by(radius_).y > geometry.scene_dims.height;
}

bool Ball::hits_top(Geometry const&) const
{
    return center_.up_by(radius_).y < 0;
}

bool Ball::hits_side(Geometry const& geometry) const
{
    return center_.left_by(radius_).x < 0 || center_.right_by(radius_).x > geometry.scene_dims.width;
}

Ball Ball::next() const
{
    Ball result(*this);
    result.center_.x = center_.x + velocity_.width;
    result.center_.y = center_.y + velocity_.height;
    return result;
}

bool Ball::hits_block(Block const& block) const
{
    if (center_.right_by(radius_).x < block.top_left().x) {
        return false;
    }

    if (center_.left_by(radius_).x > block.top_right().x) {
        return false;
    }

    if (center_.down_by(radius_).y < block.top_right().y) {
        return false;
    }

    if (center_.up_by(radius_).y > block.bottom_right().y ) {
        return false;
    }
    std::cout << "Hits Brick";
    return true;
}

void Ball::reflect_vertical()
{
    velocity_.height *= -1;
}

void Ball::reflect_horizontal()
{
    velocity_.width *= -1;
}

bool Ball::destroy_brick(std::vector<Block>& bricks) const
{
    for (int i = 0; i < bricks.size(); i++){
        if (hits_block(bricks[i])) {
            std::swap(bricks[i], bricks.back());
            bricks.pop_back();
            return true;
        }
    }
    return false;
}

bool operator==(Ball const& b1, Ball const& b2)
{
    return b1.radius_ == b2.radius_ && b1.center_ == b2.center_ && b1.velocity_ == b2.velocity_ && b1.live_ == b2.live_;
}

bool operator!=(Ball const& b1, Ball const& b2)
{
    return !(b1 == b2);
}


