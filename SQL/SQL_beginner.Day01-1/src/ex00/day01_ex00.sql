SELECT menu.id, menu.pizza_name as object_name
FROM menu
UNION ALL
SELECT person.id, person.name as object_name
FROM person
ORDER BY id, object_name;
