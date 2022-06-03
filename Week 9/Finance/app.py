import os
from traceback import print_tb
from unicodedata import name
from unittest import result
from sqlalchemy import null
from datetime import datetime

from sympy import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

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
    """Show portfolio of stocks"""
    username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
    cash = int(db.execute("SELECT cash FROM users WHERE username = ?", username)[0]["cash"])
    data = db.execute("SELECT * FROM portfolio WHERE username = ?", username)
    grand_total = 0
    for item in data:
        item["price"] = lookup(item["symbol"])["price"]
        grand_total = grand_total + (int(item["price"]) * int(item["shares"]))
    return render_template("index.html", data=data, cash=cash, grand_total=grand_total + cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()        
        shares = request.form.get("shares")
        if symbol == "":
            return apology("Missing symbol", 400)
        elif shares == "":
            return apology("Missing shares", 400)
        elif int(shares) < 0:
            return apology("Shares must be a positive integer", 400)
        result = lookup(symbol)
        shares = int(shares)
        if result is not None:
            username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
            cash = int(db.execute("SELECT cash FROM users WHERE username = ?", username)[0]["cash"])
            if cash < (result["price"] * shares):
                return apology("Not enough cash", 400)
            else:
                if int(db.execute("SELECT COUNT(*) FROM portfolio WHERE username = ? AND symbol = ?", username, symbol)[0]["COUNT(*)"]) == 0:
                    db.execute("INSERT INTO portfolio (symbol, name, shares, price, username) VALUES(?, ?, ?, ?, ?)", symbol, result["name"], shares, result["price"], username)
                else:
                    current_no_shares = db.execute("SELECT shares FROM portfolio WHERE username = ? AND symbol = ?", username, symbol)[0]["shares"]
                    db.execute("UPDATE portfolio SET shares = ? WHERE username = ? AND symbol = ?", int(current_no_shares) + shares, username, symbol)
                db.execute("INSERT INTO history (symbol, name, shares, price, username, type, time) VALUES(?, ?, ?, ?, ?, ?, ?)", symbol, result["name"], shares, result["price"], username, "BUY", datetime.now())
                db.execute("UPDATE users SET cash = ? WHERE username = ?", cash - (result["price"] * shares), username)
            return redirect("/")
        else:
            return apology("Invalid symbol", 400)
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
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
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        if symbol == "":
            return apology("Missing Symbol", 400)
        result = lookup(symbol)
        if result is not None:
            data = []
            for key, value in result.items():
                data.append(value)
            return render_template("quote.html", data=1, name=data[0], price=data[1], symbol=data[2])
        else:
            return apology("Invalid symbol", 400)
    return render_template("quote.html", data=None)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if username == "" :
            return apology("username can not be blank", 403)
        elif len(db.execute('SELECT * FROM users WHERE username = ?', username)) >= 1:
            return apology("username already exists", 403)
        elif password == "" or confirmation == "":
            return apology("password or confirmation can not be blank", 403)
        elif password != confirmation:
            return apology("passwords do not match", 403)
        else:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, generate_password_hash(password))
            return redirect("/login")
    else:        
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    username = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()        
        shares = request.form.get("shares")
        cash = int(db.execute("SELECT cash FROM users WHERE username = ?", username)[0]["cash"])
        if symbol == "":
            return apology("Missing symbol", 400)
        elif shares == "":
            return apology("Missing shares", 400)
        result = lookup(symbol)
        shares = int(shares)
        if result is not None:
            if int(shares) < 0:
                return apology("Shares must be a positive integer", 400)
            elif int(db.execute("SELECT COUNT(*) FROM portfolio WHERE username = ? AND symbol = ?", username, symbol)[0]["COUNT(*)"]) == 0:
                return apology("You don't own any share of this company")
            elif int(db.execute("SELECT shares FROM portfolio WHERE username = ? AND symbol = ?", username, symbol)[0]["shares"]) < int(shares):
                return apology("Too Much Shares")
            else:
                current_no_shares = db.execute("SELECT shares FROM portfolio WHERE username = ? AND symbol = ?", username, symbol)[0]["shares"]
                db.execute("UPDATE portfolio SET shares = ? WHERE username = ? AND symbol = ?", int(current_no_shares) - shares, username, symbol)
                db.execute("INSERT INTO history (symbol, name, shares, price, username, type, time) VALUES(?, ?, ?, ?, ?, ?, ?)", symbol, result["name"], shares, result["price"], username, "SELL", datetime.now())
                db.execute("UPDATE users SET cash = ? WHERE username = ?", cash + (result["price"] * shares), username)
            return redirect('/')
        else:
            return apology("Invalid Symbol", 400)
    data = db.execute("SELECT symbol FROM portfolio WHERE username = ?", username)
    return render_template("sell.html", data=data)