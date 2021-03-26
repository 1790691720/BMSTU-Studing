SELECT idCustomer, MAX(OrderSum)
FROM customerorder
GROUP BY idCustomer