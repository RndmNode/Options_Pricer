#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string/trim.hpp>

std::vector<std::string> get_tickers(){
    std::vector<std::string> ticker_list;
    // create file object and open
    std::fstream file;
    file.open("tickers.txt", std::ios::in);

    // check if file is open
    if (file.is_open()){
        // create string object to read lines into
        std::string line;
        // save each line if there is content
        while (getline(file, line)){
            if(line != "")
                ticker_list.push_back(line);
        }
    }

    // close file
    file.close();

    // trim excess space from each line
    for (auto& i : ticker_list){
        boost::algorithm::trim(i);
    }

    return ticker_list;
}

int main (){
    std::vector<std::string> tickers = get_tickers();

    return 0;
}