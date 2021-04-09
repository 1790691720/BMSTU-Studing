CREATE VIEW OrderQuntityTable (idCustomer, Quntity)
AS (
    SELECT idCustomer, COUNT(idCustomer)
    FROM customerorder
    WHERE (MONTH (customerorder.OrderDate) = 3) AND (YEAR (customerorder.OrderDate) = 2021)
	GROUP BY idCustomer
);
SELECT *
FROM OrderQuntityTable q
JOIN customer c ON c.idCustomer = q.idCustomer
WHERE Quntity = 
		(
			SELECT MAX(Quntity)
			FROM OrderQuntityTable
		)
        
