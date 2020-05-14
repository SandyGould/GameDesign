#pragma once

#include <SDL2/SDL.h>
#include <array>

using matrix = std::array<std::array<double, 3>, 3>;

class AffineTransform {
public:
    AffineTransform();
    SDL_Point transformPoint(int x, int y);
    AffineTransform& translate(int x, int y);
    AffineTransform& rotate(double r);
    AffineTransform& scale(double x, double y);

    AffineTransform& concatenate(AffineTransform& at);

private:
    matrix transform;

    static matrix identity();
};
