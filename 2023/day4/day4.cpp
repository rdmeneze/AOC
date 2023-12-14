/**
     implementation of AoC 2023. Day 4: https://adventofcode.com/2023/day/2
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <exception>
#include <iomanip>

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

class Card {
public:
    explicit Card(int id): id(id) {}

    void addWinningNumber( const size_t number ) {
        winningNumbers.push_back(number);
        evaluate();
    }

    void addMyNumber( const size_t number ) {
        myNumbers.push_back(number);
        evaluate();
    }

    [[nodiscard]] size_t getId() const {return id;}

    [[nodiscard]] size_t getPoints() const {
        return points;
    }

    [[nodiscard]] std::string toString() const {
        std::ostringstream os;
        os << "ID: " << std::setw(4) << id << " - ";
        os << "hits: " << std::setw(4) << hits << " - ";
        os << "points: " << std::setw(4) << static_cast<uint32_t>(points) << " ";
        for(auto& num: winningNumbers) {
            os << std::setw(2) << num << " ";
        }
        os << "| ";
        for(auto& num: myNumbers) {
            os << std::setw(2) << num << " ";
        }

        return os.str();
    }

    static Card parse(const std::string &line) {
        int id;
        std::istringstream ss(line);
        std::string x;

        ss >> x;
        if (x != "Card") {
            throw std::domain_error("Invalid header tag");
        }

        ss >> x;

        try {
            id = std::stol(x);
        }
        catch(...) {
            throw std::domain_error("Invalid ID tag");
        }

        Card card(id);

        bool colon_exist = false;
        if(x[x.length()-1] == ':') {
            colon_exist = true;
        }

        if(colon_exist == false) {
            ss >> x;
            if (x == ":")
                colon_exist = true;
        }

        if ( colon_exist == false ) {
            throw std::domain_error("Invalid file format. Separator \':\' is missing");
        }

        bool separator = false;
        try {
            while(ss >> x) {
                if(separator == false) {
                    if( x == "|") {
                        separator = true;
                    }
                    else {
                        card.addWinningNumber(std::stol(x));
                    }
                }
                else {
                    card.addMyNumber(std::stol(x));
                }
            }
        }
        catch(const std::invalid_argument& e) {
            std::ostringstream oss;
            if(separator == false)
                oss << "Invalid winning number value: '";
            else
                oss << "Invalid card number value: '";
            oss << x;
            oss << "'";
            throw std::domain_error(oss.str());
        }
        catch (const std::out_of_range& e) {
            std::ostringstream oss;
            if(separator == false)
                oss << "winning number out of value range: '";
            else
                oss << "card number out of value range: '";
            oss << x;
            oss << "'";
            throw std::domain_error(oss.str());
        }
        catch(...) {
            throw std::domain_error("unknown error");
        }

        if(separator == false) {
            throw std::domain_error("Invalid file format. Separator \'|\' is missing");
        }

        return card;
    }

private:
    int id;
    size_t points{0};
    size_t hits{0};
    std::vector<std::uint32_t> winningNumbers;
    std::vector<std::uint32_t> myNumbers;

    void evaluate() {
        std::sort(winningNumbers.begin(), winningNumbers.end());

        auto verify_number = [&](const int num) {
            return std::binary_search(winningNumbers.begin(), winningNumbers.end(), num);
        };

        const size_t count = std::count_if(myNumbers.begin(), myNumbers.end(), verify_number);

        hits = count;
        points = (hits == 0) ? 0 : 1 << (hits - 1);
    }
};


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
