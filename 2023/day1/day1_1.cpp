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
        std::array<char, 1024> s;
        std::uint64_t sum = 0;
        const std::string decimals = "0123456789";
        while(!inFile.eof())
        {
            inFile.getline(&s[0], s.size());
            std::string txt{s.data()};

            size_t first_pos = txt.find_first_of( decimals );
            size_t last_pos = txt.find_last_of(  decimals );

            int val = 0;
            char cval[] = {'0','0', 0};
            if( first_pos != std::string::npos)
            {
                cval[0] = s[first_pos];
            }
            if( last_pos != std::string::npos)
            {
                cval[1] = s[last_pos];
            }

            val = std::atoi(cval);

            //std::cout << val << "\n";
            sum += val;
        }
        std::cout << "sum is " << sum << "\n";
    } 
    return 0;
}