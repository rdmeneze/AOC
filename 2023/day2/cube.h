//
// Created by rdias on 12/12/23.
//

#pragma once

#include <string>
#include <stdexcept>
#include <array>
#include <algorithm>

class Cube {
public:
    explicit Cube( std::string_view type ) {
        const int ret = setType(type);
        if(ret != 0 ){
            throw std::runtime_error("type is not a valid cube type");
        }
    };

    [[nodiscard]] std::string getType( ) const { return cubeType; }

private:
    static constexpr  std::array<std::string_view, 3> cubeTypes {"red", "green", "blue"};
    std::string cubeType;

    int setType( const std::string_view newType ) {
        int ret = 1;
        const auto index = std::find(cubeTypes.begin(), cubeTypes.end(), newType);

        cubeType = "";
        if(index != std::end(cubeTypes)) {
            cubeType = newType.data();
            ret = 0;
        }
        return ret;
    }
};