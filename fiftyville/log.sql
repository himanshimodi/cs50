-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Checking crime scene reports
SELECT *
  FROM crime_scene_reports;

-- Checking crime scene reports for specific date and street
SELECT description
  FROM crime_scene_reports
 WHERE street LIKE "HUMPHREY STREET"
   AND day = 28
   AND month = 7
   AND year = 2021;

-- Checking for interviews that mention bakeries and date match
-- Time is 10:15 am
SELECT transcript
  FROM interviews
 WHERE transcript LIKE "%bakery%"
   AND day = 28
   AND month = 7
   AND year = 2021;

-- Checking for cars in security footage of bakery within ten minutes
SELECT activity, license_plate, minute, id
  FROM bakery_security_logs
 WHERE hour = 10
   AND minute > 14
   AND minute < 26
   AND day = 28
   AND month = 7
   AND year = 2021;


-- Checking for atm transactions on morning of day of robbery
SELECT account_number, amount, transaction_type
  FROM atm_transactions
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND atm_location LIKE "%LEGGET%"
   AND transaction_type like "withdraw";

-- Checking phone records
SELECT caller, receiver, duration
  FROM phone_calls
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND duration < 61;

-- Checking flights for the next day
SELECT origin_airport_id, destination_airport_id, hour, minute, id
  FROM flights
 WHERE day = 29
   AND month = 7
   AND year = 2021
 ORDER BY hour, minute;
-- ID is 6, from fiftyville to nyc

-- Finding airports from airport ids
SELECT abbreviation, full_name, city, id
  FROM airports
 WHERE id = 4
    OR id = 8;

-- Finding list of passports and seats
SELECT passport_number, seat
  FROM passengers
 WHERE flight_id = 36;

 -- Joining data about license passport and phone to find name
 SELECT name, id
   FROM people
  WHERE phone_number in(
                        SELECT caller
                          FROM phone_calls
                         WHERE day = 28
                           AND month = 7
                           AND year = 2021
                           AND duration < 61
                        )
    AND license_plate in (SELECT license_plate
  FROM bakery_security_logs
 WHERE hour = 10
   AND minute > 14
   AND minute < 26
   AND day = 28
   AND month = 7
   AND year = 2021)
   AND phone_number IN (SELECT caller
  FROM phone_calls
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND duration < 61);

-- Finding bank account info
SELECT *
FROM bank_accounts
WHERE account_number in (SELECT account_number
  FROM atm_transactions
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND atm_location LIKE "%LEGGET%")
AND person_id in (SELECT id
   FROM people
  WHERE phone_number in(
                        SELECT caller
                          FROM phone_calls
                         WHERE day = 28
                           AND month = 7
                           AND year = 2021
                           AND duration < 61
                        )
    AND license_plate in (SELECT license_plate
  FROM bakery_security_logs
 WHERE hour = 10
   AND minute > 14
   AND minute < 26
   AND day = 28
   AND month = 7
   AND year = 2021)
   AND phone_number IN (SELECT caller
  FROM phone_calls
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND duration < 61));



-- Getting all the info
SELECT DISTINCT(people.id), people.name, people.phone_number, people.license_plate, people.passport_number
  FROM people
  JOIN passengers on people.passport_number = passengers.passport_number

  JOIN bakery_security_logs on people.license_plate = bakery_security_logs.license_plate

  JOIN phone_calls on people.phone_number = phone_calls.caller
  WHERE people.id IN(SELECT person_id
FROM bank_accounts
WHERE account_number in (SELECT account_number
  FROM atm_transactions
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND atm_location LIKE "%LEGGET%")
AND person_id in (SELECT id
   FROM people
  WHERE phone_number in(
                        SELECT caller
                          FROM phone_calls
                         WHERE day = 28
                           AND month = 7
                           AND year = 2021
                           AND duration < 61
                        )
    AND license_plate in (SELECT license_plate
  FROM bakery_security_logs
 WHERE hour = 10
   AND minute > 14
   AND minute < 26
   AND day = 28
   AND month = 7
   AND year = 2021)
   AND phone_number IN (SELECT caller
  FROM phone_calls
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND duration < 61)))
AND
people.passport_number in
(
    SELECT passport_number
  FROM passengers
 WHERE flight_id = 36
)
;



-- FInding accomplice
SELECT caller, receiver
FROM phone_calls
WHERE
caller
in
(
SELECT DISTINCT(people.phone_number)
  FROM people
  JOIN passengers on people.passport_number = passengers.passport_number

  JOIN bakery_security_logs on people.license_plate = bakery_security_logs.license_plate

  JOIN phone_calls on people.phone_number = phone_calls.caller
  WHERE people.id IN(SELECT person_id
FROM bank_accounts
WHERE account_number in (SELECT account_number
  FROM atm_transactions
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND atm_location LIKE "%LEGGET%")
AND person_id in (SELECT id
   FROM people
  WHERE phone_number in(
                        SELECT caller
                          FROM phone_calls
                         WHERE day = 28
                           AND month = 7
                           AND year = 2021
                           AND duration < 61
                        )
    AND license_plate in (SELECT license_plate
  FROM bakery_security_logs
 WHERE hour = 10
   AND minute > 14
   AND minute < 26
   AND day = 28
   AND month = 7
   AND year = 2021)
   AND phone_number IN (SELECT caller
  FROM phone_calls
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND duration < 61)))
AND
people.passport_number in
(
    SELECT passport_number
  FROM passengers
 WHERE flight_id = 36
)

)
AND day = 28
   AND month = 7
   AND year = 2021
   AND duration < 61;

-- FInd person

SELECT id, name, passport_number, phone_number
FROM people
WHERE phone_number
LIKe ("%555-8161");
