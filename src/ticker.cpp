#include "../include/ticker.h"

// custom parse CSV line function
static std::vector<std::string> parse_line (std::string line, std::string delimiter){
    // instantiate temp variables & output
    std::vector<std::string> parsed_line;
    size_t pos = 0;
    std::string token;

    // parse line
    while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        parsed_line.push_back(token);
        line.erase(0, pos + delimiter.length());
    }

    // don't forget the last bit after the last column
    parsed_line.push_back(line);

    return parsed_line;
}

// constructor takes in the ticker symbol as 'name'
Ticker::Ticker(std::string name){
    symbol = name;
    get_CSV();
    calculate_returns();
}

// open CSV file regarding to the ticker and parse data 
void Ticker::get_CSV (){
    std::string filePath = "data/" + symbol + ".csv";

    // variable to hold parsed line info
    std::vector<std::string> parsed_line;

    // create file object and open
    std::fstream file;
    file.open(filePath, std::ios::in);

    // check if file is open
    if (file.is_open()){
        // create string object to read lines into
        std::string line;

        // read the first line that just has the header
        getline(file, line);

        // save each line if there is content
        while (getline(file, line)){
            if(line != ""){
                // get the parsed info
                parsed_line = parse_line(line, ",");

                // save the parsed info into respective object attributes
                dates.push_back(parsed_line[0]);
                open_prices.push_back(roundf(std::stof(parsed_line[1]) * 100) / 100);
                high_prices.push_back(roundf(std::stof(parsed_line[2]) * 100) / 100);
                low_prices.push_back(roundf(std::stof(parsed_line[3]) * 100) / 100);
                close_prices.push_back(roundf(std::stof(parsed_line[4]) * 100) / 100);
                adj_close_prices.push_back(roundf(std::stof(parsed_line[5]) * 100) / 100);
                volumes.push_back(std::stol(parsed_line[6]));
            }
        }
    }else{
        std::cout << "Could not open file!\n";
    }

    // close file
    file.close();

    // // trim excess space from each line
    // for (auto& i : data)
    //     for (auto& j : i)
    //         boost::algorithm::trim(j);
}

void Ticker::calculate_returns(){
    returns.push_back(0);

    // calculate daily returns
    for (int i=1; i<adj_close_prices.size(); i++){
        float ret = roundf(((adj_close_prices[i] - 
                             adj_close_prices[i-1])/
                             adj_close_prices[i-1]) * 100) / 100;
        returns.push_back(ret);
    }
}

void Ticker::print_data (int number_of_lines){
    std::cout << "\n                           " << symbol << std::endl;
    std::cout << "   Date        Open    High    Low     Close     Adj Close   Volume\n";
    std::cout << "   ----------------------------------------------------------------\n";

    for (int i=0; i<number_of_lines; i++){
        std::cout << "   ";
        std::cout << dates[i] << "  ";
        std::cout << open_prices[i] << "   ";
        std::cout << high_prices[i] << "   ";
        std::cout << low_prices[i] << "   ";
        std::cout << close_prices[i] << "    ";
        std::cout << adj_close_prices[i] << "    ";
        std::cout << volumes[i] << "   ";
        std::cout << "\n";
    }
}