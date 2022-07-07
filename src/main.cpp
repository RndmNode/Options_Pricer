#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string/trim.hpp>

std::vector<std::string> get_tickers(){
    // output
    std::vector<std::string> ticker_list;

    // create file object and open
    std::fstream file;
    file.open("tickers.txt", std::ios::in);

    // check if file is open
    if (file.is_open()){
        // create string object to read lines into
        std::string line;
        // save each line if there is content
        while (getline(file, line)){
            if(line != "")
                ticker_list.push_back(line);
        }
    }

    // close file
    file.close();

    // trim excess space from each line
    for (auto& i : ticker_list){
        boost::algorithm::trim(i);
    }

    return ticker_list;
}

std::vector<std::string> parse_line(std::string line, std::string delimiter){
    // instantiate temp variables
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

std::vector<std::vector<std::string>> get_CSV(std::string ticker){
    std::string filePath = "data/" + ticker + ".csv";
    std::vector<std::vector<std::string>> data;

    // create file object and open
    std::fstream file;
    file.open(filePath, std::ios::in);

    // check if file is open
    if (file.is_open()){
        // create string object to read lines into
        std::string line;
        std::vector<std::string> parsed_line;

        // save each line if there is content
        while (getline(file, line)){
            if(line != ""){
                parsed_line = parse_line(line, ",");
                data.push_back(parsed_line);
            }
        }
    }

    // trim excess space from each line
    for (auto& i : data){
        for (auto& j : i){
            boost::algorithm::trim(j);
        }
    }

    // close file
    file.close();

    return data;
}

int main (){
    std::vector<std::string> tickers = get_tickers();
    std::vector<std::vector<std::string>> data = get_CSV(tickers[0]);

    for (int i=0; i<10; i++){
        for (int j=0; j < data[i].size(); j++){
            std::cout << data[i][j] << "  ";
        }
        std::cout << "\n";
    }

    return 0;
}