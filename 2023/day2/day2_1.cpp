/**
     implementation of AoC 2023. Day 2: https://adventofcode.com/2023/day/2
 */

#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <sstream>

class Cube {
public:
    size_t getCounter() const {return counter;}
    std::string_view getType( ){ return cubeType; }

    explicit Cube( std::string& type, const size_t instacesCounter = 0 ) {
        int ret = setType(type);
        if(ret!=0) {
            throw std::runtime_error("type is not a valid cube type");
        }

        counter = instacesCounter;
    };


private:
    static constexpr  std::array<std::string_view, 3> cubeTypes {"red", "green", "blue"};
    std::string_view cubeType;
    size_t counter;

    int setType( std::string& newType ) {
        // add a verification
        int ret = 1;
        const auto index = std::find(std::begin(cubeTypes), std::end(cubeTypes), newType);

        cubeType = "";
        if(index != std::end(cubeTypes)) {
            cubeType = newType;
            ret = 0;
        }
        return ret;
    }
};


std::vector<std::string> getBlocks(std::string_view game) {
    std::vector<std::string> blocks;
    std::istringstream iss(game.data());
    std::string token;

    while(std::getline(iss, token, ';')) {
        blocks.push_back(token);
    }

    return blocks;
}
/*
std::vector<Cube>& parseGame( std::string game ) {
    // format: Game 1: 7 blue, 6 green, 3 red; 3 red, 5 green, 1 blue; 1 red, 5 green, 8 blue; 3 red, 1 green, 5 blue


    return [];
}
*/

static std::string& readLine( std::ifstream& fin ){
    static std::string line;
    std::array<char, 1024> buf{};

    if( fin.good() ){
        fin.getline( &buf[0], buf.size() );
        line = buf.data();
    }
    return line;
}




int main(void){

    std::cout << "Advent of Code - day two \n";

    constexpr std::string_view fileName = "input_1.txt";

    std::ifstream inFile(fileName.data());

    while( !inFile.eof() ) {
        std::string line = readLine(inFile);
        std::cout << line << std::endl;

        std::vector<std::string> blocks = getBlocks(line);
        for(auto& block : blocks) {
            std::cout << block << "\n";
        }
    }


    return 0;
}
