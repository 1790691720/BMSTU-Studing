SELECT idProduct, Name, ActualQuantity, FixationDate, ReservedProduct, RevervationDate
FROM product
WHERE ActualQuantity <= $quantityProduct
