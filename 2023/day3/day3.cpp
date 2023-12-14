/**
     implementation of AoC 2023. Day 2: https://adventofcode.com/2023/day/2
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <array>
#include <cstdint>
#include <map>
#include <algorithm>
#include <numeric>

constexpr char dot{'.'};
constexpr char gear{'*'};

using Pos = std::array<std::uint32_t, 2>;
using SymbolMap = std::map<Pos, char>;
using NumberMap = std::map<Pos, std::vector<std::uint32_t>>;

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


int main(int argc, char** argv){
    std::cout << "Advent of Code: day3\n";


    std::vector<std::string> fileMirror{};
    if (argc != 2){
        std::cerr << "usage error\n";
        return 1;
    }

    if( readFile(argv[1], fileMirror) == false ){
        return 1;
    }

    const Pos dim{ static_cast<unsigned int>(fileMirror.size()), static_cast<unsigned int>(fileMirror[0].size()) };
    fileMirror.insert(fileMirror.begin(), std::string(dim[1], dot));

    std::transform(fileMirror.begin(), fileMirror.end(), fileMirror.begin(), [](auto& row) { return dot + std::move(row) + dot; });


    SymbolMap symbols;
    NumberMap numbers;
    for (uint32_t i = 1; i < dim[0] + 1; ++i) {
        std::vector<char> number;
        std::vector<Pos> adjs;
        for (uint32_t j = 1; j < dim[1] + 2; ++j) {
            if (std::isdigit(fileMirror[i][j])) {
                if (number.empty()) {
                    adjs.push_back({i - 1, j - 1});
                    adjs.push_back({i, j - 1});
                    adjs.push_back({i + 1, j - 1});
                }
                number.push_back(fileMirror[i][j]);
                adjs.push_back({i - 1, j});
                adjs.push_back({i + 1, j});
            } else {
                if (!number.empty()) {
                    adjs.push_back({i - 1, j});
                    adjs.push_back({i, j});
                    adjs.push_back({i + 1, j});
                    uint32_t n{};
                    for (const auto c : number) {
                        n *= 10;
                        n += c - '0';
                    }
                    for (const auto& adj : adjs) {
                        if (auto it = numbers.find(adj); it != numbers.end()) {
                            it->second.push_back(n);
                        } else {
                            numbers[adj] = std::vector<uint32_t>{n};
                        }
                    }
                    number.clear();
                    adjs.clear();
                }
                if (dot != fileMirror[i][j]) {
                    symbols[{i, j}] = fileMirror[i][j];
                }
            }
        }
    }

    {  // Part 1
        uint64_t sum{};
        for (const auto& [pos, _] : symbols) {
            if (const auto it = numbers.find(pos); it != numbers.end()) {
                // Assumption: Each number is adjacent to not more than one symbol
                sum += std::accumulate(it->second.cbegin(), it->second.cend(), uint64_t{0});
            }
        }
        std::cout << sum << std::endl;
    }
    {  // Part 2
        uint64_t sum{};
        for (const auto& [pos, symbol] : symbols) {
            if (gear != symbol) {
                continue;
            }
            if (const auto it = numbers.find(pos); it != numbers.end() && 2 == it->second.size()) {
                sum += it->second[0] * it->second[1];
            }
        }
        std::cout << sum << std::endl;
    }

    return 0;
}
