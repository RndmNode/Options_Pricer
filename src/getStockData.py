import pandas as pd

from api import API_KEY

# return list of tickers from what is in the txt file
def get_tickers():
    tickers = []
    with open('tickers.txt') as f:
        for line in f:
            tickers.append(line.strip())
    f.close()

    return tickers

# uses api to get latest stock performance
def get_data(ticker):
    data = pd.read_csv('https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol='+ticker+'&apikey=' + API_KEY+'&datatype=csv')
    data.to_csv('data/'+ticker+'.csv')

# go go gadget, run
def main():
    tickers = get_tickers()

    for ticker in tickers:
        get_data(ticker)

if __name__ == "__main__":
    main()