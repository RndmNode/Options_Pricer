#include "../include/monte_carlo.h"

MonteCarloPricer::MonteCarloPricer(Ticker* ticker, Ticker* benchmark){
    m_ticker = ticker;
    m_benchmark = benchmark;
    get_beta();
}

float MonteCarloPricer::get_volatility(Ticker* t){
    // instantiate holder variables
    float mean;
    std::vector<float> deviation_squared;

    // calculate mean daily returns
    mean = (std::reduce(t->returns.begin(),t->returns.end(),0.0)) / t->returns.size();

    // calculate deviation squared on t->returns
    for (int i=0; i<t->returns.size(); i++)
        deviation_squared.push_back(std::pow((mean - t->returns[i]),2.0));
    
    // calculate standard deviation
    float ticker_std_dev = roundf(std::sqrt((std::reduce(deviation_squared.begin(),
                                                        deviation_squared.end(), 0.0)) / 
                                                        deviation_squared.size()) * 100) / 100;
    return ticker_std_dev;
}

float MonteCarloPricer::get_correlation_coefficient(float ticker_std_dev, float bench_std_dev){
    float correlation;
    float ticker_mean;
    float bench_mean;
    float covariance;

    // get mean daily returns
    ticker_mean = (std::reduce(m_ticker->returns.begin(),m_ticker->returns.end(),0.0)) / m_ticker->returns.size();
    bench_mean = (std::reduce(m_benchmark->returns.begin(),m_benchmark->returns.end(),0.0)) / m_benchmark->returns.size();

    // calculate covariance
    float running_sum;
    for (int i=0; i<m_ticker->returns.size(); i++){
        running_sum += (m_ticker->returns[i] - ticker_mean) * 
                       (m_benchmark->returns[i] - bench_mean);
    }
    covariance = (running_sum / (m_ticker->returns.size() - 1));

    // calculate correlation
    correlation = covariance / (ticker_std_dev * bench_std_dev);

    return correlation;
}

void MonteCarloPricer::get_beta(){
    float ticker_std_dev = get_volatility(m_ticker);
    float bench_std_dev = get_volatility(m_benchmark);

    float correlation = get_correlation_coefficient(ticker_std_dev, bench_std_dev);

    m_beta = roundf((correlation * (ticker_std_dev/ bench_std_dev)) * 100) / 100;
}