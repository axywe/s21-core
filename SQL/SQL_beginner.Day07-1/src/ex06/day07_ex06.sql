SELECT pz.name, COUNT(po.id) AS count_of_orders, CASE 
         WHEN ROUND(AVG(m.price), 2) = CAST(ROUND(AVG(m.price), 2) AS INTEGER) 
         THEN CAST(ROUND(AVG(m.price), 2) AS INTEGER) 
         ELSE ROUND(AVG(m.price), 2) 
       END AS average_price, MAX(m.price) AS max_price, MIN(m.price) AS min_price
FROM person p
JOIN person_order po ON po.person_id = p.id
JOIN menu m ON po.menu_id = m.id
JOIN pizzeria pz ON m.pizzeria_id = pz.id
GROUP BY pz.name
ORDER BY pz.name;
