#include "../include/ticker.h"
#include <matplot/matplot.h>

// global object to hold all tickers and their data
std::vector<Ticker *> tickers;

// get tickers requested from tickers.txt file and fill the global tickers vector
void get_tickers (){
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
                boost::algorithm::trim(line);
                tickers.push_back(new Ticker(line));
        }
    }
    // close file
    file.close();
}

int main (){
    get_tickers();

    std::vector<int> x = {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10};
    std::vector<int> y = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    matplot::plot(x, y);
    matplot::show();

    return 0;
}