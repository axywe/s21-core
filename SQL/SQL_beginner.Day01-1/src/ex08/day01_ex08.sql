SELECT o.order_date, CONCAT(p.name, ' (age:', p.age, ')') AS person_information
FROM person_order o
NATURAL JOIN (
    SELECT id AS person_id, name, age
    FROM person
) p
ORDER BY o.order_date ASC, p.name ASC;
