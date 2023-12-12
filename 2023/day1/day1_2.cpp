#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <array>
#include <algorithm>

int main(void)
{
    std::cout << "advent of code - day one\n";
    std::string fileName = "input.txt";

    std::ifstream inFile(fileName);

    if( inFile.good())
    {
        std::array<char, 1024> s{0};
        std::uint64_t sum = 0;
        const std::string decimals_numbers = "0123456789";
        const std::array<std::string_view, 10> decimals_texts = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
        while(!inFile.eof())
        {
            inFile.getline(&s[0], s.size());
            std::string txt{s.data()};

            size_t first_pos;
            size_t last_pos;

            bool isFirstDigitNumber{false};
            bool isLastDigitNumber{false};

            std::string first_str_digit;
            std::string last_str_digit;

            size_t first_dig_pos = txt.find_first_of( decimals_numbers );
            size_t last_dig_pos = txt.find_last_of( decimals_numbers );

            char first_char_digit = (first_dig_pos != std::string::npos)?txt[first_dig_pos]: 0;
            char last_char_digit = (last_dig_pos != std::string::npos) ? txt[last_dig_pos]: 0;

            size_t first_str_pos = std::string::npos;
            size_t last_str_pos = std::string::npos;

            for(const auto& decimal_text : decimals_texts) {
                size_t pos = txt.find( decimal_text );
                if(static_cast<int>(pos) != std::string::npos){
                    if(first_str_pos == std::string::npos) {
                        first_str_pos = pos;
                        first_str_digit = decimal_text;
                    }
                    else {
                        if( pos < first_str_pos ) {
                            first_str_pos = pos;
                            first_str_digit = decimal_text;
                        }
                    }
                }
            }

            for(const auto& decimal_text : decimals_texts){
                size_t pos = txt.rfind( decimal_text );
                if(static_cast<int>(pos) > static_cast<int>(last_str_pos)) {
                    last_str_pos = pos;
                    last_str_digit = decimal_text;
                }
            }

            if(first_dig_pos != std::string::npos && first_str_pos != std::string::npos){
                if(first_dig_pos < first_str_pos) {
                    // is a digit
                    isFirstDigitNumber = true;
                    first_pos = first_dig_pos;
                }
                else {
                    first_pos = first_str_pos;
                }
            } 
            else{
                if(first_dig_pos == std::string::npos) {
                    first_pos = first_str_pos;
                }
                else {
                    isFirstDigitNumber = true;
                    first_pos = first_dig_pos;
                }
            }

            if(last_dig_pos != std::string::npos && last_str_pos != std::string::npos){
                if(last_dig_pos > last_str_pos) {
                    last_pos = last_dig_pos;
                    isLastDigitNumber = true;
                }
                else {
                    last_pos = last_str_pos;
                }
            }
            else{
                if(last_dig_pos == std::string::npos) {
                    last_pos = last_str_pos;
                }
                else {
                    isLastDigitNumber = true;
                    last_pos = last_dig_pos;
                }
            }

            char cval[] = {'0','0', 0};

            if(isFirstDigitNumber) {
                cval[0] = first_char_digit;
            }
            else {
                auto index = std::find( std::begin(decimals_texts), std::end(decimals_texts), first_str_digit );
                cval[0] = std::distance(std::begin(decimals_texts), index)+'0';
            }

            if(isLastDigitNumber) {
                cval[1] = last_char_digit;
            }
            else {
                auto index = std::find( std::begin(decimals_texts), std::end(decimals_texts), last_str_digit );
                cval[1] = std::distance(std::begin(decimals_texts), index)+'0';
            }

            int val = std::atoi(cval);

            sum += val;
        }
        std::cout << "sum is " << sum << "\n";
    } 
    return 0;
}
