-- Please use SQL statement from Exercise #01 and show pizza names from pizzeria which are not ordered by anyone, including corresponding prices also. The result should be sorted by pizza name and price. The sample of output data is presented below.

-- pizza_name	price	pizzeria_name
-- cheese pizza	700	Papa Johns
-- cheese pizza	780	DoDo Pizza
-- ...	...	...

SELECT m.pizza_name, m.price, pi.name FROM menu m 
JOIN pizzeria pi ON m.pizzeria_id = pi.id
WHERE m.id NOT IN (SELECT menu_id FROM person_order)
ORDER BY m.pizza_name, m.price;
