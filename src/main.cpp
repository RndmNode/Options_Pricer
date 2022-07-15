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

    std::vector<int> x = tickers[0]->ticks;
    std::vector<float> y = tickers[0]->close_prices;

    matplot::plot(x, y);
    matplot::title(tickers[0]->symbol);
    matplot::show();

    return 0;
}