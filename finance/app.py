import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# API KEY = pk_4ec0a267d5f54759a46b4f262e9a272c


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    user_id = session["user_id"]

    totality = 0
    rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)
    money1 = rows[0]
    money = money1["cash"]

    stock_dict = indexer()
    return_dict = {}
    for symbol, shares in stock_dict.items():
        pricer = lookup(symbol)
        price = float(pricer["price"])
        name = pricer["name"]
        total = price * shares
        totality += total
        return_dict[symbol] = (symbol, name, shares, price, total)

    return render_template("index.html", return_dict=return_dict, totality=totality, money=money)

    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            number = float(request.form.get("shares"))
        except:
            return apology("Invalid Number Of Shares")
        my_dict = lookup(symbol)
        time = datetime.now()
        if my_dict == None:
            return apology("Symbol doesn't exist")
        if number < 1 or (number % 1 != 0):
            return apology("Invalid Number Of Shares")

        else:
            price = my_dict["price"]
            name = my_dict["name"]
            number = int(number)
        user_id = session["user_id"]
        rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)
        money1 = rows[0]
        money = money1["cash"]
        if (price * number) > money:
            return apology("Not Enough Money")
        else:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", (money - (price * number)), user_id)
            db.execute("INSERT INTO transactions(symbol, name, price, shares, user_id, time, type) VALUES (?, ?, ?, ?, ?, ?, ?)",
                       symbol, name, price, number, user_id, time, "buy")
            return redirect("/")
    else:
        return render_template("buy.html")
    return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    dic_list = db.execute(
        "SELECT transaction_id, symbol, name, price, shares, time, type FROM transactions WHERE user_id = ?", user_id)
    return render_template("history.html", dic_list=dic_list)
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote_dict = lookup(symbol)
        if quote_dict == None:
            return apology("Invalid Symbol")
        return render_template("quoted.html", quote_dict=quote_dict)
    return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not request.form.get("username"):
            return apology("must provide username", 400)
        elif not request.form.get("password"):
            return apology("must provide password", 400)
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation", 400)
        rows = db.execute("SELECT username FROM users WHERE username = ?", username)
        if len(rows) != 0:
            return apology("username already taken", 400)
        if (confirmation != password):
            return apology("password and confirmation dont match", 400)
        hash = generate_password_hash(password)
        db.execute("INSERT INTO users(username, hash) VALUES (?, ?)", username, hash)
        return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "GET":
        symb_list = []
        symb_dicr = indexer()
        for i in symb_dicr:
            symb_list.append(i)

        return render_template("sell.html", symb_list=symb_list)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        numb = int(request.form.get("shares"))
        time = datetime.now()
        money1 = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        money2 = money1[0]
        money = money2["cash"]
        stock_dict = indexer()
        if symbol not in stock_dict:
            return apology("you dont have this stock")
        if numb > stock_dict[symbol]:
            return apology("You do not have that many shares")
        my_dict = lookup(symbol)
        price = my_dict["price"]
        name = my_dict["name"]
        total = price * numb
        db.execute("UPDATE users SET cash = ? WHERE id = ?", (money + total), user_id)
        db.execute("INSERT INTO transactions(symbol, name, price, shares, user_id, time, type) VALUES (?, ?, ?, ?, ?, ?, ?)",
                   symbol, name, price, numb, user_id, time, "sell")

    return redirect("/")

    return apology("TODO")


def indexer():
    user_id = session["user_id"]

    stock_dict = {}
    # Database query
    dict_list = db.execute("SELECT shares, symbol, type FROM transactions WHERE user_id = ?", user_id)
    for transaction in dict_list:
        # Get number symbol and buy or sell
        shares = int(transaction["shares"])
        symb = transaction["symbol"]
        type = transaction["type"]

        # Check if buy or sell
        if type == "buy":
            stock_dict[symb] = stock_dict.setdefault(symb, 0) + shares
        else:
            stock_dict[symb] -= shares
            if stock_dict[symb] == 0:
                del stock_dict[symb]
    return stock_dict

    '''
    old index func
    def index():
    user_id = session["user_id"]
    counter = 0

    stock_list = []
    symb_list = []
    dict_list = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
    for transaction in dict_list:
        my_dict = {}
        shares = transaction["shares"]
        symb = transaction["symbol"]
        name = transaction["name"]
        price1 = lookup(symb)
        price = price1["price"]

        if symb not in symb_list:
            my_dict["symb"] = symb
            my_dict["name"] = name
            my_dict["price"] = price
            my_dict["number"] = 0
            symb_list.append(symb)
            if transaction["type"] == "buy":
                my_dict["number"] += shares
            else:
                my_dict["number"] -= shares
            stock_list.append(my_dict)
        else:
            for dict in stock_list:
                if dict["symb"] == symb:
                     if transaction["type"] == "buy":
                        dict["number"] += shares
                     else:
                        dict["number"] -= shares

    for dicts in stock_list:

        if dicts["number"] == 0:
            stock_list.pop(counter)
        counter += 1







    return render_template("index.html", stock_list = stock_list)

    '''
    # Index Function is too slow
    # Tryb speeding it up
    # try reducing the loops
    # Use dict if possible instead of dicts a

