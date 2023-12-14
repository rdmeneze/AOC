/**
     implementation of AoC 2023. Day 4: https://adventofcode.com/2023/day/2
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <numeric>
#include <exception>
#include <iomanip>
#include "card/card.h"

static bool readFile(const std::string& fileName, std::vector<std::string>& lines){
    std::ifstream in{fileName};
    if(!in.good()){
        std::cerr << "Cannot open file " << fileName << "\n";
        return false;
    }

    while(!in.eof()){
        std::string str;
        std::getline(in, str);
        lines.push_back(str);
    }

    in.close();
    return true;
}



int main(const int argc, const char** argv){
    std::cout << "Advent of Code: day4\n";

    if (argc != 2){
        std::cerr << "usage error\n";
        return 1;
    }

    std::vector<std::string> fileMirror{};
    if( readFile(argv[1], fileMirror) == false ){
        return 1;
    }

    std::vector<Card> cardList{};
    for( auto&line: fileMirror) {
        try {
            Card card = Card::parse(line);

            std::cout << card.toString() << "\n";
            cardList.push_back(card);
        }
        catch( const std::exception& e ) {
            std::cerr << e.what() << "\n";
            return 1;
        }
    }

    std::cout << "number of cards: " << cardList.size() << "\n";

    uint32_t totalPoints = 0;
    totalPoints = std::accumulate(cardList.begin(),
        cardList.end(),
        0,
        [](const uint32_t sum, const Card& card) {return sum + card.getPoints();});

    std::cout << "points: " << totalPoints << "\n";

    return 0;
}
