-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE year = 2021 AND day = 28 AND month = 7 AND street = "Humphrey Street";
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time - each of their interview transcripts mentions the bakery

SELECT * FROM interviews WHERE year = 2021 AND day = 28 AND month = 7  AND transcripts LIKE "%bakery%";
--161|Ruth|2021|7|28|Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
--162|Eugene|2021|7|28|I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
--163|Raymond|2021|7|28|As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT * FROM bakery_security_logs WHERE year = 2021 AND day = 28 and month = 7 AND hour = 10 AND minute >= 15 AND minute <= 30;

--260|2021|7|28|10|16|exit|5P2BI95
--261|2021|7|28|10|18|exit|94KL13X
--262|2021|7|28|10|18|exit|6P58WS2
--263|2021|7|28|10|19|exit|4328GD8
--264|2021|7|28|10|20|exit|G412CB7
--265|2021|7|28|10|21|exit|L93JTIZ
--266|2021|7|28|10|23|exit|322W7JE
--267|2021|7|28|10|23|exit|0NTHK55

SELECT * FROM atm_transactions WHERE year = 2021 AND day = 28 AND month = 7 AND atm_location = "Leggett Street" AND transaction_type = 'withdraw';
--246|28500762|2021|7|28|Leggett Street|withdraw|48
--264|28296815|2021|7|28|Leggett Street|withdraw|20
--266|76054385|2021|7|28|Leggett Street|withdraw|60
--267|49610011|2021|7|28|Leggett Street|withdraw|50
--269|16153065|2021|7|28|Leggett Street|withdraw|80
--288|25506511|2021|7|28|Leggett Street|withdraw|20
--313|81061156|2021|7|28|Leggett Street|withdraw|30
--336|26013199|2021|7|28|Leggett Street|withdraw|35

SELECT * FROM phone_calls WHERE day = 28 AND year = 2021 AND month = 7 AND duration <= 60;
--221|(130) 555-0289|(996) 555-8899|2021|7|28|51
--224|(499) 555-9472|(892) 555-8872|2021|7|28|36
--233|(367) 555-5533|(375) 555-8161|2021|7|28|45
--234|(609) 555-5876|(389) 555-5198|2021|7|28|60
--251|(499) 555-9472|(717) 555-1342|2021|7|28|50
--254|(286) 555-6063|(676) 555-6554|2021|7|28|43
--255|(770) 555-1861|(725) 555-3243|2021|7|28|49
--261|(031) 555-6622|(910) 555-3251|2021|7|28|38
--279|(826) 555-1652|(066) 555-9701|2021|7|28|55
--281|(338) 555-6650|(704) 555-2131|2021|7|28|54

SELECT * FROM airports WHERE city = "Fiftyville";
--8|CSF|Fiftyville Regional Airport|Fiftyville

SELECT id FROM flights WHERE day = 29 AND month = 7 and year = 2021 AND origin_airport_id = 8 ORDER BY hour ASC LIMIT 1;
--36

SELECT passport_number FROM passengers WHERE flight_id = 8;
--9172951504
--5310124622
--5806941094
--9852889341
--3699913849
--2996517496

SELECT name FROM people WHERE phone_number IN (SELECT phone_number FROM phone_calls WHERE day = 28 AND year = 2021 AND month = 7 AND duration <= 60) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE day = 29 AND month = 7 and year = 2021 AND origin_airport_id = 8 ORDER BY hour ASC LIMIT 1)) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND day = 28 and month = 7 AND hour = 10 AND minute >= 15 AND minute <= 30);
--Sofia
--Luca
--Kelsey
--Bruce

SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND day = 28 AND month = 7 AND atm_location = "Leggett Street" AND transaction_type = 'withdraw');
--686048
--514354
--458378
--395717
--396669
--467400
--449774
--438727

SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND day = 28 AND month = 7 AND atm_location = "Leggett Street" AND transaction_type = 'withdraw'));
--Kenny
--Iman
--Benista
--Taylor
--Brooke
--Luca
--Diana
--Bruce

SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day = 28 AND year = 2021 AND month = 7 AND duration <= 60);
--Kenny
--Sofia
--Benista
--Taylor
--Diana
--Kelsey
--Kathryn
--Bruce
--Carina

--Bruce is the suspect because his name is present in all the checks.

-- DESTINATION

SELECT destination_airport_id FROM flights WHERE id = (SELECT id FROM flights WHERE day = 29 AND month = 7 and year = 2021 AND origin_airport_id = 8 ORDER BY hour ASC LIMIT 1);
--4

SELECT city FROM airports WHERE id = 4;
--New York City

-- City escaped is New York City

--ACCOMPLICE
SELECT phone_number FROM people WHERE name = 'Bruce';
--(367) 555-5533

SELECT receIver FROM phone_calls WHERE day = 28 AND year = 2021 AND month = 7 AND duration <= 60 AND caller = '(367) 555-5533';
--(375) 555-8161

SELECT name FROM people WHERE phone_number = '(375) 555-8161';
--Robin

-- ACCOMPLICE name is Robin