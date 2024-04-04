SELECT menu.pizza_name
FROM menu
WHERE NOT EXISTS (
    SELECT 1
    FROM menu AS m
    WHERE m.pizza_name = menu.pizza_name AND m.id < menu.id
)
ORDER BY menu.pizza_name DESC;
