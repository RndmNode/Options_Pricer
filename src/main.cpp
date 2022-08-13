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

void run (){
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::normal_distribution<float> random_n(0, 1);

    std::cout << "some Normal-distributed(0.0,1.0) results:" << std::endl;
    for (int i=0; i<10; ++i)
        std::cout << random_n(generator) << std::endl;

}

int main (){
    get_tickers();

    MonteCarloPricer monte(tickers[1], tickers[0]);
    // run();

    return 0;
}