SELECT *
FROM product
WHERE PricePerUnit = (SELECT MAX(PricePerUnit) FROM product)