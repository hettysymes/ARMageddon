from flask import Flask, render_template, request
app = Flask(__name__)
@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        # Get the text from the textbox
        amount_spent = request.form['tb_amount_spent']
        return f"You entered: {amount_spent}"
    return render_template('index.html')
if __name__ == '__main__':
    app.run()