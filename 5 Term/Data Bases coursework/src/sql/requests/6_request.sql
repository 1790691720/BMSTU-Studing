SELECT idCustomer, MAX(OrderSum)
FROM customerorder
WHERE YEAR(OrderDate) = $year AND OrderStatus=$orderStatus
GROUP BY idCustomer
