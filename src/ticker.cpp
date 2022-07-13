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
}

// open CSV file regarding to the ticker and parse data 
void Ticker::get_CSV (){
    std::string filePath = "data/" + symbol + ".csv";

    // create file object and open
    std::fstream file;
    file.open(filePath, std::ios::in);

    // check if file is open
    if (file.is_open()){
        // create string object to read lines into
        std::string line;

        // save each line if there is content
        while (getline(file, line)){
            if(line != "")
                data.push_back(parse_line(line, ","));
        }
    }else{
        std::cout << "Could not open file!\n";
    }

    // close file
    file.close();

    // trim excess space from each line
    for (auto& i : data)
        for (auto& j : i)
            boost::algorithm::trim(j);
}

void Ticker::print_data (int number_of_lines){
    std::cout << "\n" << symbol << std::endl;

    for (int i=0; i<number_of_lines; i++){
        for (auto& j : data[i]){
            std::cout << j << "  ";
        }
        std::cout << "\n";
    }
}