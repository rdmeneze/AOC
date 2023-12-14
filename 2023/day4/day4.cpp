/**
     implementation of AoC 2023. Day 4: https://adventofcode.com/2023/day/2
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#include <cstdint>
#include <map>
#include <algorithm>
#include <numeric>
#include <sstream>



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

//using Card = std::array<std::vector<std::string>, 2> ;

class Card {
public:
    explicit Card(int id): id(id) {}

    void addWinningNumber( const size_t number ) {
        winningNumbers.push_back(number);
        points = validate();
    }

    void addMyNumber( const size_t number ) {
        myNumbers.push_back(number);
        points = validate();
    }

    [[nodiscard]] size_t getId() const {return id;}

    [[nodiscard]] size_t getPoints() const {
        return points;
    }

    static Card parse(const std::string &line) {
        int id;
        std::istringstream ss(line);
        std::string x;

        ss >> x;
        if (x != "Card") {
            return Card{-1};
        }

        ss >> id;
        Card card(id);
        ss.ignore(1);
        bool separator = false;
        while(ss >> x) {
            if(separator == false) {
                if( x == "|") {
                    separator = true;
                }
                else {
                    card.addWinningNumber(std::atoi(x.c_str()));
                }
            }
            else {
                card.addMyNumber(std::atoi(x.c_str()));
            }
        }

        return card;
    }

private:
    int id;
    size_t points{0};
    std::vector<std::uint32_t> winningNumbers;
    std::vector<std::uint32_t> myNumbers;

    size_t validate() {
        std::sort(winningNumbers.begin(), winningNumbers.end());
        std::sort(myNumbers.begin(), myNumbers.end());

        auto verify_number = [&](int num) {
            return std::binary_search(winningNumbers.begin(), winningNumbers.end(), num);
        };

        size_t count = std::count_if(myNumbers.begin(),
            myNumbers.end(), verify_number);

        return (1<<(count - 1));
    }
};


int main(int argc, char** argv){
    std::cout << "Advent of Code: day4\n";

    std::vector<std::string> fileMirror{};
    if (argc != 2){
        std::cerr << "usage error\n";
        return 1;
    }

    if( readFile(argv[1], fileMirror) == false ){
        return 1;
    }

    std::vector<Card> cardList{};
    for( auto&line: fileMirror) {
        Card card = Card::parse(line);
        if(card.getId() == -1) {
            std::cerr << "error reading cards file\n";
            return 1;
        }
        cardList.push_back(card);
    }

    int64_t totalPoints = 0;
    /*std::accumulate(cardList.begin(),
        cardList.end(),
        0,
        [](int64_t sum, const Card& card) {return sum + (int64_t)card.getPoints();});
*/
    for(auto& card: cardList) {
        totalPoints += static_cast<int64_t>(card.getPoints());
    }

    std::cout << "points: " << totalPoints << "\n";

    return 0;
}
