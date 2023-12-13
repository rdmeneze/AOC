//
// Created by rdias on 12/12/23.
//

#pragma once

#include <string>
#include "cube.h"

class CubeCounter {
public:
    explicit CubeCounter( std::string_view type );

    [[nodiscard]] std::string getType() const;

    [[nodiscard]] size_t getCounter() const;

    void addCounter(size_t value);

private:
    Cube cube;
    size_t counter;
};

