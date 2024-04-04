-- Please find a union of pizzerias that have orders either from women or from men. Other words, you should find a set of pizzerias names have been ordered by females only and make "UNION" operation with set of pizzerias names have been ordered by males only. Please be aware with word “only” for both genders. For any SQL operators with sets don’t save duplicates (UNION, EXCEPT, INTERSECT). Please sort a result by the pizzeria name. The data sample is provided below.

-- pizzeria_name
-- Papa Johns

WITH pizzeria_gender AS (
  SELECT
    p.name AS pizzeria_name,
    pe.gender
  FROM person_order po
  JOIN menu m ON po.menu_id = m.id
  JOIN pizzeria p ON m.pizzeria_id = p.id
  JOIN person pe ON po.person_id = pe.id
),
pizzerias_with_only_women AS (
  SELECT
    pizzeria_name
  FROM pizzeria_gender
  GROUP BY pizzeria_name
  HAVING COUNT(DISTINCT gender) = 1 AND MAX(gender) = 'female'
),
pizzerias_with_only_men AS (
  SELECT
    pizzeria_name
  FROM pizzeria_gender
  GROUP BY pizzeria_name
  HAVING COUNT(DISTINCT gender) = 1 AND MAX(gender) = 'male'
)
SELECT pizzeria_name FROM pizzerias_with_only_women
UNION
SELECT pizzeria_name FROM pizzerias_with_only_men
ORDER BY pizzeria_name;
