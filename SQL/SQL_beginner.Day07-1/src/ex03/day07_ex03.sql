WITH visits AS (
    SELECT pizzeria.name, COUNT(*) AS visit_count
    FROM person_visits
    JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
    GROUP BY pizzeria.name
),
orders AS (
    SELECT pizzeria.name, COUNT(*) AS order_count
    FROM person_order
    JOIN menu ON person_order.menu_id = menu.id
    JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
    GROUP BY pizzeria.name
),
combined AS (
    SELECT v.name, COALESCE(v.visit_count, 0) AS visit_count, COALESCE(o.order_count, 0) AS order_count
    FROM visits v
    FULL OUTER JOIN orders o ON v.name = o.name
)
SELECT name, (visit_count + order_count) AS total_count
FROM combined
ORDER BY total_count DESC, name ASC;
