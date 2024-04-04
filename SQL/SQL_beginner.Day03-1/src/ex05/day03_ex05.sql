-- Please write a SQL statement which returns a list of pizzerias which Andrey visited but did not make any orders. Please order by the pizzeria name. The sample of data is provided below.

-- pizzeria_name
-- Pizza Hut

SELECT p.name
FROM pizzeria p
JOIN person_visits pv ON p.id = pv.pizzeria_id
LEFT JOIN person_order po ON pv.person_id = po.person_id AND pv.pizzeria_id IN (SELECT m.pizzeria_id FROM menu m WHERE m.id = po.menu_id)
JOIN person pe ON pv.person_id = pe.id AND pe.name = 'Andrey'
WHERE po.id IS NULL
ORDER BY p.name;
