SELECT *
FROM customerorder
WHERE TO_DAYS(CURDATE())-TO_DAYS(OrderDate)<$lastDays