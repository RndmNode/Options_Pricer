#include "../include/monte_carlo.h"

MonteCarloPricer::MonteCarloPricer(Ticker* stock){
    ticker = stock;
    get_volatility();
}

void MonteCarloPricer::get_volatility(){
    // instantiate holder variables
    float mean;
    std::vector<float> deviation_squared;
    
    // calculate mean
    mean = (std::reduce(ticker->close_prices.begin(),ticker->close_prices.end(),0.0)) / ticker->close_prices.size();

    // calculate deviation squared
    for (int i=0; i<ticker->close_prices.size(); i++)
        deviation_squared.push_back(std::pow((mean - ticker->close_prices[i]),2.0));
    
    // calculate volatility (standard deviation)
    volatility = std::sqrt((std::reduce(deviation_squared.begin(),deviation_squared.end(),0.0)) / deviation_squared.size());
}