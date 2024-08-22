
# for greater simplicity install our package
# https://github.com/twelvedata/twelvedata-python
import json

import requests
from dotenv import load_dotenv
import os

load_dotenv()
api_key = os.get_env('TWELVE_DATA_API_KEY')
response = requests.get(f"https://api.twelvedata.com/time_series?{api_key}&interval=1min&symbol=ARM")
dict = json.loads(response.text)
for d in dict:
    print(d)