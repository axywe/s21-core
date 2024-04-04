SELECT 
    COALESCE(p.name, '-') AS person_name,
    pv.visit_date,
    COALESCE(pi.name, '-') AS pizzeria_name
FROM 
    (SELECT id, name FROM person) p
LEFT JOIN person_visits pv ON p.id = pv.person_id AND pv.visit_date BETWEEN '2022-01-01' AND '2022-01-03'
LEFT JOIN pizzeria pi ON pv.pizzeria_id = pi.id
FULL OUTER JOIN 
    (SELECT id, name FROM pizzeria) pi2 ON pi.id = pi2.id
AND pv.visit_date BETWEEN '2022-01-01' AND '2022-01-03'
ORDER BY person_name, pv.visit_date, pizzeria_name;
