SELECT c.idCustomer, c.Name, c.Surname, c.City, c.Telephone, c.TotalSum, c.ContractDate
FROM customer c
LEFT JOIN 
(
    SELECT idOrder, idCustomer
    FROM customerorder
    WHERE (MONTH (customerorder.OrderDate) = 1) AND (YEAR (customerorder.OrderDate) = 2021)
) as temp
ON (temp.idCustomer = c.idCustomer)
WHERE (idOrder IS NULL)