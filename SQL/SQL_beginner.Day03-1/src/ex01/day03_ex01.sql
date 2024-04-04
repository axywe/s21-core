-- Please find all menu identifiers which are not ordered by anyone. The result should be sorted by identifiers. The sample of output data is presented below.

-- menu_id
-- 5
-- 10
-- ...

SELECT id FROM menu
WHERE id NOT IN (SELECT menu_id FROM person_order)