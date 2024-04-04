SELECT 
    (SELECT p.name FROM person p WHERE p.id = po.person_id) AS NAME
FROM 
    person_order po
WHERE 
    EXISTS (
        SELECT 1 FROM menu m 
        WHERE m.id = po.menu_id 
        AND m.id IN (13, 14, 18)
    )
    AND po.order_date = '2022-01-07';
