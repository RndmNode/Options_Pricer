#include "../include/monte_carlo.h"

MonteCarloPricer::MonteCarloPricer (Ticker* ticker, Ticker* benchmark){
    m_ticker = ticker;
    m_benchmark = benchmark;
    plot_simulation();
}

// getting volatility via standard deviation
float MonteCarloPricer::get_volatility (Ticker* t){
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

// function used for threaded simulation returns a set to be merged with other sets to create the entire simulation
static inline std::set<std::vector<float>> simulation_thread (int num_sims, int num_days, float s0, float nu, float sig, float dt){
    std::set<std::vector<float>> partial_sim;
    float price_today = s0;
    float S;    // price one step in the future

    // random number generation
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<float> random_n(0, 1);

    // simulate
    for(int i=0; i<num_sims; i++){
        // push back today's price to start the simulation
        std::vector<float> sim;
        s0 = price_today;
        sim.push_back(s0);

        // simulate all days till expiry
        for(int j=0; j<num_days; j++){
            // simulate price for "tomorrow"
            S = s0 * exp(nu + sig*sqrt(dt)*random_n(generator));
            sim.push_back(S);
            // reset "today"
            s0 = sim.back();
        }
        partial_sim.insert(sim);
    }
    return partial_sim;
}

// static inline int square (int a, int b){
//     return a * b;
// }

void MonteCarloPricer::simulate (int num_sims, int days_to_expiry, bool threaded){
    /*
    Function to generate sample paths for assets assuming geometric brownian motion

    Inputs:
        s0 = stock price today
        S = stock price at one time step in the future
        mu = expected return
        sig = volatility
        dt = size of time steps (1/365 = 1 day)
        steps = number of time steps to calculate (days to expiry)
        num_sims = number of simulation paths to generate
    */

    float s0;
    float S;
    // expected return in this instance is calculated as mean return on data
    float mu = (std::reduce(m_ticker->returns.begin(),m_ticker->returns.end(),0.0)) / m_ticker->returns.size();
    float sig = get_volatility(m_ticker);
    float dt = 1.0f/365.0f;

    // calculate drift
    float nu = mu - sig*sig/2;

    if (!threaded){
        // random number generation
        unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::normal_distribution<float> random_n(0, 1);
        
        // simulate
        for(int i=0; i<num_sims; i++){
            // push back today's price to start the simulation
            std::vector<float> sim;
            s0 = m_ticker->adj_close_prices.back();
            sim.push_back(s0);

            // simulate all days till expiry
            for(int j=0; j<days_to_expiry; j++){
                // simulate price for "tomorrow"
                S = s0 * exp(nu + sig*sqrt(dt)*random_n(generator));
                sim.push_back(S);
                // reset "today"
                s0 = sim.back();
            }
            sim_paths.insert(sim);
        }
    }else{ // multithreaded
        // vector of the threads
        std::vector<std::future<std::set<std::vector<float>>>> futures;
        // std::vector<std::future<int>> futures;
        s0 = m_ticker->adj_close_prices.back();

        int threads = 1000;
        // create all threads to allow for concurrent simulations
        for (int i=0; i<50; i++){
            // std::future f = std::async(std::launch::async, simulation_thread, num_sims/5, days_to_expiry, s0, nu, sig, dt);
            futures.push_back(std::async(std::launch::async, simulation_thread, num_sims/threads, days_to_expiry, s0, nu, sig, dt));
        }

        // merge all sim paths into the main sim path
        for (auto & future : futures){
            sim_paths.merge(future.get());
        }
    }
}

#include <chrono>

void MonteCarloPricer::plot_simulation (){

    int num_sims = 100000;

    // start simulation timer ---------------
    printf("Starting non-threaded\n");
    auto start = std::chrono::high_resolution_clock::now();
    simulate(num_sims, 50, false);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration1 = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time for one thread: " << duration1.count() << std::endl;

    // end simulation timer ---------------
    printf("Starting threaded\n");
    start = std::chrono::high_resolution_clock::now();
    simulate(num_sims, 50, true);
    stop = std::chrono::high_resolution_clock::now();
    auto duration2 = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time for multi-threads: " << duration2.count() << std::endl;

    std::cout << "Time saved (micros): " << duration1.count() - duration2.count() << std::endl;
    std::cout << "Time saved (%): " << (1.0f - ((float) duration2.count() / (float) duration1.count())) * 100.0f << std::endl;

    // matplot::plot(sim_paths);
    // matplot::title(m_ticker->symbol);
    // matplot::xlabel("Days");
    // matplot::ylabel("Stock Price");
    // matplot::show();
}