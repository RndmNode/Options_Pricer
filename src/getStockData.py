import pandas as pd

from api import API_KEY

tickers = [
    "TSLA",
    "IBM",
    "AAPL",
    "F",
    "MSFT"
]

def get_data(ticker):
    data = pd.read_csv('https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol='+ticker+'&apikey=' + API_KEY+'&datatype=csv')
    data.to_csv('data/'+ticker+'.csv')

def main():
    for ticker in tickers:
        get_data(ticker)

if __name__ == "__main__":
    main()