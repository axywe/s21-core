SELECT DISTINCT p.name
FROM person p
JOIN person_order po ON po.person_id = p.id
WHERE p.id IN (SELECT DISTINCT person_id
               FROM person_order)
ORDER BY p.name;