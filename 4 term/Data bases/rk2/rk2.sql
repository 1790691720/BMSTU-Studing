CREATE PROCEDURE `updateStatus` (inputDate DATE)
BEGIN
	DECLARE idO INT;
	DECLARE done INT DEFAULT 0;
	DECLARE temp CURSOR FOR
	SELECT idOrder
    FROM customerorder
    WHERE (OrderStatus = 1) AND ((OrderDate - inputDate) > 3);
	
	DECLARE CONTINUE handler FOR SQLSTATE('02000')
	SET done = 1;
	
	OPEN temp;
	
	WHILE done = 0 DO
		FETCH temp INTO idO;
		UPDATE customerorder 
        SET OrderStatus = 3, OrderStatusDate = inputDate
		WHERE idOrder= idO;
	END WHILE;
	CLOSE temp;
END