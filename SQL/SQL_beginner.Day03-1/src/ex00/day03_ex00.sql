-- Please write a SQL statement which returns a list of pizza names, pizza prices, pizzerias names and dates of visit for Kate and for prices in range from 800 to 1000 rubles. Please sort by pizza, price and pizzeria names. Take a look at the sample of data below.

-- pizza_name	price	pizzeria_name	visit_date
-- cheese pizza	950	DinoPizza	2022-01-04
-- pepperoni pizza	800	Best Pizza	2022-01-03
-- pepperoni pizza	800	DinoPizza	2022-01-04
-- ...	...	...	...

SELECT pizza_name, price, pi.name, visit_date FROM menu m
JOIN pizzeria pi ON m.pizzeria_id = pi.id
JOIN person_visits pv ON pv.pizzeria_id = m.pizzeria_id
JOIN person p ON pv.person_id = p.id
WHERE p.name = 'Kate' AND price BETWEEN 800 AND 1000
ORDER BY pizza_name, price, pi.name;