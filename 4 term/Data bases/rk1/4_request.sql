SELECT c.idCustomer, c.Name, c.Surname, c.City, c.Telephone, c.TotalSum, c.ContractDate
FROM customer c
LEFT JOIN 
(
    SELECT idOrder, idCustomer, OrderSum
    FROM customerorder
    WHERE (MONTH (customerorder.OrderDate) = 3) AND (YEAR (customerorder.OrderDate) = 2021)
) as temp
ON (temp.idCustomer = c.idCustomer)
WHERE temp.OrderSum = (SELECT MAX(OrderSum) FROM customerorder WHERE (MONTH (customerorder.OrderDate) = 3) AND (YEAR (customerorder.OrderDate) = 2021))