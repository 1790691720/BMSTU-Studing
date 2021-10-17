SELECT *
FROM customer
WHERE YEAR(ContractDate) = $year AND MONTH(ContractDate) = $year