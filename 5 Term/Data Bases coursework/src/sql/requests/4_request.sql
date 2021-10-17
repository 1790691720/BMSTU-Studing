SELECT idCustomer, Telephone
FROM customer
WHERE Telephone LIKE '%$telephoneLike%'
