from flask import Flask, render_template, request
from datetime import datetime
from stock_query import calculate_profit

app = Flask(__name__)
@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        stock_symbol = request.form['stock_symbol']
        price_bought = float(request.form['price_bought'])
        date_bought = datetime.strptime(request.form['date_bought'], "%Y-%m-%d")
        res = calculate_profit(stock_symbol, price_bought, date_bought)
        profit_msg = ""
        old = ""
        new = ""
        stock = ""
        if res["success"]:
            profit = res["profit"]
            if (profit >= 0):
                profit_msg = f"Your PROFIT is: {profit:.2f} USD"
            else:
                profit_msg = f"Your LOSS is: {-profit:.2f} USD"
            old = f"Old price: {res['old_price']:.2f} USD"
            new = f"New price: {res['now_price']:.2f} USD"
            stock = f"Number of stocks bought: {res['num_stock']:.2f}"
        else:
            profit_msg = "ERROR: could not find the price at this date in our system :("
        return render_template('index.html', profit_msg=profit_msg, old=old, new=new, stock=stock)
    return render_template('index.html', profit_msg="", old="", new="", stock="")
if __name__ == '__main__':
    app.run()