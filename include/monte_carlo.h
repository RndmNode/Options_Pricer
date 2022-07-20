#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "ticker.h"
#include <numeric>
#include <cmath>
#include <thread>

// class for monte carlo method of option pricing
class MonteCarloPricer{
    public:
        MonteCarloPricer(Ticker* ticker, Ticker* benchmark);
        ~MonteCarloPricer(){};
        float m_beta;
    private:
        // attributes
        Ticker* m_ticker;
        Ticker* m_benchmark;
        float m_correlation;
        // float m_beta;

        // methods
        float get_volatility(Ticker* t);
        float get_correlation_coefficient(float ticker_std_dev, float bench_std_dev);
        void get_beta();
};

#endif /* MONTECARLO_H */