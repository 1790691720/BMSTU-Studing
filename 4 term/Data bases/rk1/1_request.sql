SELECT c.idCustomer, c.Name, c.Surname,o.idProduct, p.Name, SUM(o.OrderQuantity)
FROM customer c
JOIN customerorder o ON o.idCustomer = c.idCustomer
JOIN product p ON o.idProduct = p.idProduct
WHERE MONTH(o.OrderDate)=3 AND YEAR(o.OrderDate)=2021
GROUP BY c.idCustomer, o.idProduct