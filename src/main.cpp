#include "../include/monte_carlo.h"

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
        
        // create new Ticker if there is a new line with content
        while (getline(file, line)){
            if(line != "")
                boost::algorithm::trim(line);
                tickers.push_back(new Ticker(line));
        }
    }
    // close file
    file.close();
}

void plot_tickers(Ticker* ticker){
    // std::vector<int> x = ticker->dates;
    std::vector<float> y = ticker->close_prices;

    matplot::plot(y);
    matplot::title(ticker->symbol);
    matplot::show();
}

int add ( int a ){
    return a + 1;
}

int main (){
    get_tickers();

    MonteCarloPricer monte(tickers[1], tickers[0]);

    return 0;
}