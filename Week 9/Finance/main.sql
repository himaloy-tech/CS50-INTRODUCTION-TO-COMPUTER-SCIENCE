CREATE TABLE history(
    id INTEGER,
    symbol TEXT,
    name TEXT,
    shares INTEGER,
    price DECIMAL(7, 3),
    username TEXT,
    time TEXT,
    PRIMARY KEY(id)
);

CREATE TABLE portfolio(
    id INTEGER,
    symbol TEXT,
    name TEXT,
    shares INTEGER,
    price DECIMAL(7, 3),
    username TEXT,
    PRIMARY KEY(id)
);