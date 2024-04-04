SELECT po.person_id
FROM person_order po
WHERE po.order_date = '2022-01-07'
EXCEPT ALL
SELECT pv.person_id
FROM person_visits pv
WHERE pv.visit_date = '2022-01-07';