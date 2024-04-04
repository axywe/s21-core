-- SQL Syntax Patten	Please use “insert-select” pattern
-- INSERT INTO ... SELECT ...	
-- Denied	
-- SQL Syntax Patten	- Don’t use direct numbers for identifiers of Primary Key, and menu
-- Don’t use window functions like ROW_NUMBER( )
-- Don’t use atomic INSERT statements |
-- Please register new orders from all persons for “greek pizza” on 25th of February 2022. Warning: this exercise will probably be the cause of changing data in the wrong way. Actually, you can restore the initial database model with data from the link in the “Rules of the day” section and replay script from Exercises 07 , 08 ,09 , 10 and 11.

INSERT INTO person_order (id, person_id, menu_id, order_date)
SELECT (SELECT COALESCE(MAX(id), 0) FROM person_order) + row_number() OVER (ORDER BY p.id, m.id) AS id,
       p.id AS person_id,
       m.id AS menu_id,
       '2022-02-25' AS order_date
FROM person p
CROSS JOIN menu m
JOIN pizzeria pz ON pz.id = m.pizzeria_id
WHERE m.pizza_name = 'greek pizza';

SELECT * FROM person_order;