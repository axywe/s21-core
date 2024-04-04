SELECT p.name AS person_name, m.pizza_name, pz.name AS pizzeria_name
FROM person p
JOIN person_order po ON p.id = po.person_id
JOIN menu m ON po.menu_id = m.id
JOIN pizzeria pz ON m.pizzeria_id = pz.id
ORDER BY p.name, m.pizza_name, pz.name ASC;
