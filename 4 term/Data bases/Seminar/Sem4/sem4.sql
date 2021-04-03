Сложные запросы

1.

SELECT SUB_A, SUM(price)
FROM CDR
JOIN Subscriber ON (Sub_A=Sub_id)
WHERE Cl_id=234 AND MONTH(CDR.Start_time)=3 AND YEAR(CDR.Start_time)=2016
GROUP BY Sub_id

2.

SELECT DISTINCT Cl_id, Name
FROM Client
JOIN Subscriber USING(Cl_id)
WHERE Subscriber.Balance < 0;

3.

SELECT Name, Tp_id, COUNT(Tp_id)
FROM Client
JOIN Subscriber USING Cl_id
GROUP BY Name, Tp_id

4.

SELECT Cl_id, Name,  Birthday, Occupation
FROM Clint
JOIN Subscriber USING Cl_id
WHERE Balance = ( 	
					SELECT MAX(Balance) 
					FROM Subscriber 
				)
				
5.

SELECT Sub_id
FROM Subscriber
LEFT JOIN CDR  ON (Sub_A = Sub_id)
WHERE ( id IS NULL ) 

6.

SELECT Sub_id
FROM Subscriber main
LEFT JOIN 
(
    SELECT id, Sub_A
    FROM CDR
    WHERE (MONTH (CDR.Start_time) = 3) AND (YEAR (CDR.Start_time) = 2016)
) as temp
ON (temp.Sub_A = main.Sub_id)
WHERE (id IS NULL)

7.


CREATE VIEW Price_MAX_Duration (Sub_id, lenght)
AS (
    SELECT Sub_A, SUM(lenght)
    FROM CDR
    WHERE (MONTH (CDR.Start_time) = 3) AND (YEAR (CDR.Start_time) = 2016)
	GROUP BY Sub_A
)
SELECT Sub_id
FROM Price_MAX_Duration
WHERE lenght = 
		(
			SELECT MAX(lenght)
			FROM Price_MAX_Duration
		)