SELECT c.idCustomer, c.Name, c.Surname, c.City, c.Telephone, c.TotalSum, c.ContractDate
FROM customer c
LEFT JOIN customerorder o ON (c.idCustomer = o.idCustomer)
WHERE ( o.idOrder IS NULL )