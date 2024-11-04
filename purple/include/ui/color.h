#pragma once

#include "glm/vec4.hpp"

namespace purple{
    enum Color{
        Transparent,
        Black,
        White,
        Red,
        Green,
        Blue,
    };

    glm::vec4 ConverColorValue(Color color);
}

