#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "ticker.h"

#include <time.h>
#include <numeric>
#include <cmath>
#include <random>
#include <thread>
#include <future>
#include <set>
#include <matplot/matplot.h>

// class for monte carlo method of option pricing
class MonteCarloPricer{
    public:
        MonteCarloPricer(Ticker* ticker, Ticker* benchmark);
        ~MonteCarloPricer(){};
        void plot_simulation();
    private:
        // attributes
        Ticker* m_ticker;
        Ticker* m_benchmark;
        std::set<std::vector<float>> sim_paths;

        // methods
        float get_volatility(Ticker* t);
        float get_correlation_coefficient(float ticker_std_dev, float bench_std_dev);
        void get_beta();
        void simulate(int num_sims, int days_to_expiry, bool threaded);
        // int square (int num);
};

#endif /* MONTECARLO_H */