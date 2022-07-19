import pandas as pd
import yfinance as yf

# return list of tickers from what is in the txt file
def get_tickers():
    tickers = []
    with open('tickers.txt') as f:
        for line in f:
            tickers.append(line.strip())
    f.close()

    return tickers

# uses api to get latest stock performance
def get_CSV(ticker):
    data = yf.download(ticker, period="100d")
    data.to_csv('data/'+ticker+'.csv')

# go go gadget, run
def main():
    tickers = get_tickers()

    for ticker in tickers:
        get_CSV(ticker)

if __name__ == "__main__":
    main()