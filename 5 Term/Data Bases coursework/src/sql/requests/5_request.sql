SELECT idCustomer, SUM(OrderSum)
FROM customerorder
WHERE OrderStatus = $numberParam
GROUP BY idCustomer