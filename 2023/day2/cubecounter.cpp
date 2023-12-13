//
// Created by rdias on 12/12/23.
//

#include "cubecounter.h"

CubeCounter::CubeCounter( std::string_view type ) : cube(type), counter(0){
};

size_t CubeCounter::getCounter() const {
    return counter;
}

void CubeCounter::addCounter(size_t value) {
    counter += value;
}

std::string CubeCounter::getType() const {
    return cube.getType();
}
