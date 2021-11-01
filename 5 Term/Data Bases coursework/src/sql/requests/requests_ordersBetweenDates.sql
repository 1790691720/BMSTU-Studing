SELECT idOrder, idCustomer,idProduct,OrderQuantity,OrderSum, OrderDate
FROM customerorder
WHERE OrderDate
BETWEEN '$dateMin' AND '$dateMax'