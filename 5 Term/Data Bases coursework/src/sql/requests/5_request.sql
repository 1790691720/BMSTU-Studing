SELECT idCustomer, SUM(OrderSum)
FROM customerorder
WHERE OrderStatus = $orderStatus
GROUP BY idCustomer