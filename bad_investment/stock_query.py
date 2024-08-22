import json
import requests
from dotenv import load_dotenv
import os
from datetime import timedelta, datetime
import time

# Load the API Key
load_dotenv()
API_KEY = os.getenv('TWELVE_DATA_API_KEY')

# Get the price of a stock (symbol) at a given date (date)
def get_price_at_date(symbol, date):
    DAYS_TO_CHECK = 10
    TIMES_TO_CHECK_EACH_DAY = 2
    for _ in range(DAYS_TO_CHECK):
        for _ in range(TIMES_TO_CHECK_EACH_DAY):
            next_date = date + timedelta(days=1)
            request_data_format = "%Y-%m-%d"
            date_str = date.strftime(request_data_format)
            next_date_str = next_date.strftime(request_data_format)
            print(f"INFO:finding {symbol} stock between {date_str} and {next_date_str}")
            request_str = f"https://api.twelvedata.com/time_series?apikey={API_KEY}&interval=1day&symbol={symbol}&start_date={date_str} 00:00:00&format=JSON&end_date={next_date_str} 00:00:00"
            response = requests.get(request_str)
            data = json.loads(response.text)
            if data["status"] == "ok":
                return {"price": float(data["values"][0]["close"]), "date": date, "success": True}
            time.sleep(0.1)
        date -= timedelta(days=1)
    return {"price": "", "date": "", "success": False}

# Calculate the profit
def calculate_profit(symbol, price_bought, date_bought):
    # Get price of stock at time of buy
    old_price_res = get_price_at_date(symbol, date_bought)
    if not old_price_res["success"]:
        return {"profit": "", "success": False}
    old_price = old_price_res["price"]
    # Get number of stock bought
    num_stock = price_bought/old_price
    # Get price of stock now
    now_price_res = get_price_at_date(symbol, datetime.today())
    if not now_price_res["success"]:
        return {"profit": "", "success": False}
    now_price = now_price_res["price"]
    # Return profit
    return {"profit": num_stock*(now_price - old_price), "success": True}

    