/**
     implementation of AoC 2023. Day 2: https://adventofcode.com/2023/day/2
 */

#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>
#include <sstream>
#include <map>
#include "cubecounter.h"

std::vector<std::string> getBlocks(std::string_view play) {
    std::vector<std::string> blocks;
    std::istringstream iss(play.data());
    std::string token;

    while(std::getline(iss, token, ';')) {
        blocks.push_back(token);
    }

    return blocks;
}

std::vector<CubeCounter> getCubeCounters( std::string_view block ) {
    std::istringstream iss(block.data());
    std::string token;
    std::vector<CubeCounter> counters;

    while(std::getline(iss, token, ',')) {
        std::istringstream ss(token);
        size_t counter;
        std::string type;

        ss >> counter >> type;
        CubeCounter cc(type);
        cc.addCounter(counter);
        counters.push_back(cc);
    }

    return counters;
}

struct Game {
    size_t id{0};
    std::vector<CubeCounter> counters;

    [[nodiscard]] std::string toString() const {
        std::ostringstream os;
        os << "ID: " << id << " " << "Plays: ";
        for( auto& cubeCounter : counters) {
            os << cubeCounter.getType() << " | " << cubeCounter.getCounter() << " | ";
        }
        return os.str();
    }

    [[nodiscard]] size_t getCount(std::string_view type) const {
        size_t ret = 0;
        if(exist(type)) {
            for(auto& counter : counters) {
                if(counter.getType() == type) {
                    ret = counter.getCounter();
                    break;
                }
            }
        }
        return ret;
    }

    [[nodiscard]] bool exist(const std::string_view type) const {
        for(auto& counter : counters) {
            if(counter.getType() == type) {
                return true;
            }
        }
        return false;
    }

    void update(const std::string_view type, const size_t count) {
        if(exist(type)) {
            for(auto& counter : counters) {
                if(counter.getType() == type) {
                    counter.addCounter(count);
                    break;
                }
            }
        }
        else {
            CubeCounter counter(type);
            counter.addCounter(count);
            counters.push_back(counter);
        }
    }

    void insert( const std::string_view type, const size_t count ) {
        CubeCounter counter(type);
        counter.addCounter(count);
        counters.push_back(counter);
    }
};

Game parseGame( std::string_view game ) {
    // format: Game 1: 7 blue, 6 green, 3 red; 3 red, 5 green, 1 blue; 1 red, 5 green, 8 blue; 3 red, 1 green, 5 blue

    Game gameData;
    std::istringstream ss(game.data());
    size_t id;
    std::string header;

    ss >> header >> id;
    if (header != "Game") {
        return {0};
    }
    gameData.id = id;

    const size_t firstToken = game.find_first_of(':');
    if( firstToken == std::string::npos ) {
        return {0};
    }

    std::string_view boardData = game.substr(firstToken+1 );

    std::vector<std::string> blocks = getBlocks(boardData);

    for( auto& block : blocks ) {
        auto counter = getCubeCounters(block);
        for(auto& cube : counter) {
            gameData.insert(cube.getType(), cube.getCounter());
        }
    }

    return gameData;
}

static std::string& readLine( std::ifstream& fin ){
    static std::string line;
    std::array<char, 1024> buf{};

    if( fin.good() ){
        fin.getline( &buf[0], buf.size() );
        line = buf.data();
    }
    return line;
}


int main(int argc, char** argv){
    std::cout << "Advent of Code - day two \n";

    if( argc != 2 ) {
        return 0;
    }

    std::string fileName = argv[1];
    std::ifstream inFile(fileName);
    std::vector<Game> board;

    while( !inFile.eof() ) {
        std::string line = readLine(inFile);

        Game game = parseGame(line);
        std::cout << "Game data: " << game.toString() << "\n";

        board.push_back(game);
    }

    std::cout << "===============================================\n";

    // apply the restrictions
    std::map<std::string, size_t> limits{
    {"red", 12},
    {"green", 13},
    {"blue", 14},
    };

    size_t gameCount = 0;
    for( auto& game : board) {
        bool consider = true;

        for( auto& cubeCounter : game.counters ) {
            auto n = cubeCounter.getCounter();
            auto c = cubeCounter.getType();

            if(n > limits[c]) {
                consider = false;
            }
        }
        if( consider) {
            gameCount += game.id;
        }
    }

    std::cout << "Sum Game ID: " << gameCount << "\n";

    return 0;
}
