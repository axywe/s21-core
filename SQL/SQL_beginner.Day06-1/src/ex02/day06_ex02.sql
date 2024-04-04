SELECT p.name, pizza_name, price, CAST(price - price * discount / 100 AS DECIMAL(10,0)) AS discount_price, pz.name as pizzeria_name
FROM person_order
JOIN menu ON person_order.menu_id = menu.id
JOIN person_discounts ON person_order.person_id = person_discounts.person_id AND menu.pizzeria_id = person_discounts.pizzeria_id
JOIN person p ON person_order.person_id = p.id
JOIN pizzeria pz ON menu.pizzeria_id = pz.id
ORDER BY p.name, pz.name;