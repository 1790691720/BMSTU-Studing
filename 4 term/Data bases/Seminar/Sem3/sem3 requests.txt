Часть 2(Простые запросы, 1 лабораторная)

3. 
SELECT Cl_id, Name 
FROM Client
WHERE MONTH(Birthday) = 3 AND DAY(Birthday) = 8;

4.
SELECT Cl_id, Name 
FROM Client
-- WHERE datediff(YEAR, Birthday, getDate()) as age > 13 AND age < 21
WHERE YEAR(CURDATE())-YEAR(Birthday) BETWEEN (14 AND 20);

5.
SELECT occupation, COUNT(Cl_id)
From Client
GROUP BY occupation;


6.
SELECT Cl_id, Tp_id, COUNT
FROM Subscriber
WHERE Cl_id BETWEEN (100 and 2000)
GROUP BY Cl_id, Tp_id;


Часть 2(Сложные запросы, 1 РК)

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


