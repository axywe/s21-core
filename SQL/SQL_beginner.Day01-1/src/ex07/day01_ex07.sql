SELECT o.order_date, CONCAT(p.name, ' (age:', p.age, ')') AS person_information
FROM person_order o
JOIN person p ON o.person_id = p.id
ORDER BY o.order_date ASC, p.name ASC;
