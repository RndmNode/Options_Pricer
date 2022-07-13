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
        std::vector<std::vector<std::string>> data;
        void print_data(int number_of_lines);
    private:
        void get_CSV();
};

#endif /* TICKER_H */