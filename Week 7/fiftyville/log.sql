-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE year = 2021 AND day = 28 AND month = 7 AND street = "Humphrey Street";
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time - each of their interview transcripts mentions the bakery

SELECT * FROM interviews WHERE year = 2021 AND day = 28 AND month = 7;
-- 163|Raymond|2021|7|28|As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT * FROM airports WHERE city = 'Fiftyville';
--8|CSF|Fiftyville Regional Airport|Fiftyville

SELECT * FROM flights WHERE year = 2021 AND day = 28 AND month = 7 AND origin_airport_id = 8;
--1|8|7|2021|7|28|17|50
--6|8|5|2021|7|28|13|49
--17|8|4|2021|7|28|20|16
--34|8|5|2021|7|28|17|20
--35|8|4|2021|7|28|16|16

SELECT * FROM passengers WHERE flight_id = 6;
--6|3835860232|9A
--6|1618186613|2C
--6|7179245843|3B
--6|1682575122|4B
--6|7597790505|5D
--6|6128131458|6B
--6|6264773605|7D
--6|3642612721|8A

SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 6);
--341739|Rebecca|(891) 555-5672|6264773605|
--423393|Carol|(168) 555-6126|6128131458|81MNC9R
--505688|Jean|(695) 555-0348|1682575122|JN7K44M
--632023|Amanda|(821) 555-5262|1618186613|RS7I6A0
--745650|Sophia|(027) 555-1068|3642612721|13FNH73
--750165|Daniel|(971) 555-6468|7597790505|FLFN3W0
--780088|Nicole|(123) 555-5144|3835860232|91S1K32
--872102|Joyce||7179245843|594IBK6

SELECT * FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 6));

--1|(123) 555-5144|(007) 555-2874|2021|7|25|243
--11|(891) 555-5672|(222) 555-8026|2021|7|25|486
--13|(168) 555-6126|(618) 555-9856|2021|7|25|390
--41|(027) 555-1068|(594) 555-6254|2021|7|25|582
--94|(695) 555-0348|(095) 555-3639|2021|7|26|299
--111|(821) 555-5262|(529) 555-7276|2021|7|26|345
--119|(168) 555-6126|(869) 555-6696|2021|7|26|471
--149|(891) 555-5672|(869) 555-6696|2021|7|26|47
--159|(821) 555-5262|(839) 555-1757|2021|7|27|462
--170|(695) 555-0348|(367) 555-5533|2021|7|27|218
--176|(168) 555-6126|(037) 555-8455|2021|7|27|116
--192|(027) 555-1068|(375) 555-8161|2021|7|27|71
--232|(971) 555-6468|(267) 555-2761|2021|7|28|149
--252|(695) 555-0348|(338) 555-6650|2021|7|28|383
--282|(971) 555-6468|(258) 555-5627|2021|7|28|441
--307|(891) 555-5672|(676) 555-6554|2021|7|29|402
--320|(821) 555-5262|(130) 555-0289|2021|7|29|263
--397|(123) 555-5144|(118) 555-8106|2021|7|30|149
--440|(123) 555-5144|(901) 555-8732|2021|7|30|366
--469|(971) 555-6468|(342) 555-9260|2021|7|31|562
--471|(027) 555-1068|(717) 555-1342|2021|7|31|567

SELECT * FROM bakery_security_logs WHERE year = 2021 AND day = 28 AND month = 7;
-- bakery logs of that day

SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 6) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND day = 28 AND month = 7);

--632023|Amanda|(821) 555-5262|1618186613|RS7I6A0
--745650|Sophia|(027) 555-1068|3642612721|13FNH73
--750165|Daniel|(971) 555-6468|7597790505|FLFN3W0

SELECT * FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 6) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND day = 28 AND month = 7)) AND day = 28 AND year = 2021 AND month = 7;

--232|(971) 555-6468|(267) 555-2761|2021|7|28|149
--282|(971) 555-6468|(258) 555-5627|2021|7|28|441

SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36) AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND day = 28 AND month = 7);

--Sofia
--Taylor
--Kelsey
--Bruce