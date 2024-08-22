from flask import Flask, render_template, request
app = Flask(__name__)
@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        # Get the text from the textbox
        user_input = request.form['text_box']
        return f"You entered: {user_input}"
    return render_template('index.html')
if __name__ == '__main__':
    app.run()