SELECT menu.pizza_name as object_name
FROM menu
UNION ALL
SELECT person.name as object_name
FROM person
ORDER BY object_name