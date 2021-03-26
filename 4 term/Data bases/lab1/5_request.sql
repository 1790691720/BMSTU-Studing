SELECT idCustomer, SUM(OrderSum)
FROM customerorder
WHERE OrderStatus = 1
GROUP BY idCustomer