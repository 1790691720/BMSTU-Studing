SELECT OrderStatus, COUNT(OrderStatus)
FROM customerorder
WHERE (TO_DAYS(CURDATE())-TO_DAYS(OrderDate))<5
GROUP BY OrderStatus