
# # for greater simplicity install our package
# # https://github.com/twelvedata/twelvedata-python
import json

import requests
from dotenv import load_dotenv
import os
from datetime import datetime

load_dotenv()
api_key = os.getenv('TWELVE_DATA_API_KEY')
print(api_key)

response = requests.get()
dictt = json.loads(response.text)
with open("data.json", 'w') as f:
    json.dump(dictt, f, indent=2)

def get_price_at_date(symbol, date, api_key):
    next_date = date + datetime.timedelta(days=1)
    request_data_format = "%Y-%m-%d %H:%M:%S"
    date_str = date.strftime(request_data_format)
    next_date_str = next_date.strftime(request_data_format)
    request_str = f"https://api.twelvedata.com/time_series?apikey={api_key}&interval=1day&symbol={symbol}&start_date={date_str}&format=JSON&end_date={next_date_str}"
    response = requests.get(request_str)
    data = json.loads(response.text)

inp_date = "2024-08-20"
date = datetime.strptime(inp_date, "%Y-%m-%d")
get_price_at_date("ARM", date)

# for greater simplicity install our package
# https://github.com/twelvedata/twelvedata-python
    