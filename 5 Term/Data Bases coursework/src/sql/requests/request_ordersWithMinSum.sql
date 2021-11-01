SELECT idOrder, idCustomer,idProduct,OrderQuantity,OrderSum, OrderDate
FROM customerorder
WHERE OrderSum >= $sumMin
