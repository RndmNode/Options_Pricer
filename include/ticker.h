#ifndef TICKER_H
#define TICKER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string/trim.hpp>

// class to hold each ticker's information
class Ticker{
    public:
        Ticker(std::string name);
        ~Ticker(){};
        std::string symbol;
        std::vector<int> ticks;
        std::vector<std::string> dates;
        std::vector<float> open_prices;
        std::vector<float> high_prices;
        std::vector<float> low_prices;
        std::vector<float> close_prices;
        std::vector<long> volumes;
        void print_data(int number_of_lines);
    private:
        void get_CSV();
};

#endif /* TICKER_H */