
# # for greater simplicity install our package
# # https://github.com/twelvedata/twelvedata-python
import json

import requests
from dotenv import load_dotenv
import os
from datetime import timedelta, datetime

load_dotenv()
API_KEY = os.getenv('TWELVE_DATA_API_KEY')

def get_price_at_date(symbol, date):
    for i in range(10):
        next_date = date + timedelta(days=1)
        request_data_format = "%Y-%m-%d %H:%M:%S"
        date_str = date.strftime(request_data_format)
        next_date_str = next_date.strftime(request_data_format)
        print(f"INFO:finding ${symbol} stock between {date_str} and {next_date_str}")
        request_str = f"https://api.twelvedata.com/time_series?apikey={API_KEY}&interval=1day&symbol={symbol}&start_date={date_str}&format=JSON&end_date={next_date_str}"
        response = requests.get(request_str)
        data = json.loads(response.text)
        if data["status"] == "ok":
            return {"price": float(data["values"][0]["close"]), "date": date, "success": True}
        date -= timedelta(days=1)
    return {"price": "", "date": "", "success": False}

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

    