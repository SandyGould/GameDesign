#include "AffineTransform.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cmath>

/**
 * Affine Transforms
 *
 */
AffineTransform::AffineTransform() {
    this->transform = this->identity();
}

/* Returns the identity matrix as an array */
matrix AffineTransform::identity() {
    matrix id;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) {
                id[i][j] = 1.0;
            } else {
                id[i][j] = 0.0;
            }
        }
    }
    return id;
}

/* Takes a point in the local coordinate system and transforms it to global space given this AffineTransform */
SDL_Point AffineTransform::transformPoint(int x, int y) {
    SDL_Point point;
    point.x = static_cast<int>(x * this->transform[0][0] + y * this->transform[0][1] + 1 * this->transform[0][2]);
    point.y = static_cast<int>(x * this->transform[1][0] + y * this->transform[1][1] + 1 * this->transform[1][2]);
    return point;
}

/* Add another transform to this one, is basically just matrix multiply */
AffineTransform& AffineTransform::concatenate(AffineTransform& at) {
    AffineTransform result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.transform[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result.transform[i][j] += this->transform[i][k] * at.transform[k][j];
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->transform[i][j] = result.transform[i][j];
        }
    }

    return *this;
}

/* Move points in the x and y direction */
AffineTransform& AffineTransform::translate(int x, int y) {
    AffineTransform temp;
    temp.transform[0][2] = x;
    temp.transform[1][2] = y;

    this->concatenate(temp);

    return *this;
}

/* rotate points by r radians */
AffineTransform& AffineTransform::rotate(double r) {
    double cos = std::cos(r);
    double sin = std::sin(r);

    AffineTransform temp;
    temp.transform[0][0] = cos;
    temp.transform[0][1] = -sin;
    temp.transform[1][0] = sin;
    temp.transform[1][1] = cos;

    this->concatenate(temp);

    return *this;
}

/* scale in the x and y direction accordingly */
AffineTransform& AffineTransform::scale(double x, double y) {
    AffineTransform temp;
    temp.transform[0][0] = x;
    temp.transform[1][1] = y;

    this->concatenate(temp);

    return *this;
}