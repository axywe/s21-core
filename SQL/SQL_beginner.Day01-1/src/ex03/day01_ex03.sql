SELECT DISTINCT
    person_visits.visit_date as action_date,
    person_visits.person_id
FROM person_visits, person_order 
WHERE person_visits.visit_date = person_order.order_date 
    AND person_visits.person_id = person_order.person_id 
ORDER BY action_date ASC, person_id DESC;