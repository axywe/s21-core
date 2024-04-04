SELECT DISTINCT
    person_visits.visit_date as action_date,
    person.name as person_name
FROM person_visits
LEFT JOIN person ON person.id = person_visits.person_id
JOIN person_order ON person_visits.visit_date = person_order.order_date 
    AND person_visits.person_id = person_order.person_id
ORDER BY action_date ASC, person_name DESC;