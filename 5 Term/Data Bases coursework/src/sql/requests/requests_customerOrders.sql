SELECT idOrder,
       idProduct,
       OrderSum,
       OrderQuantity,
       OrderDate,
       OrderStatus,
       OrderStatusDate,
       OrderQuantity
FROM customerorder
WHERE idCustomer = $customerName