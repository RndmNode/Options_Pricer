#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "ticker.h"
#include <numeric>
#include <cmath>
#include <thread>

// class for monte carlo method of option pricing
class MonteCarloPricer{
    public:
        MonteCarloPricer(Ticker* stock);
        ~MonteCarloPricer(){};
    private:
        // attributes
        Ticker* ticker;
        float volatility;

        // methods
        void get_volatility();
};

#endif /* MONTECARLO_H */