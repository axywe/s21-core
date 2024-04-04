-- Please find pizzerias that have been visited more often by women or by men. For any SQL operators with sets save duplicates (UNION ALL, EXCEPT ALL, INTERSECT ALL constructions). Please sort a result by the pizzeria name. The data sample is provided below.

-- pizzeria_name
-- Best Pizza
-- Dominos
-- ...

WITH visit_counts AS (
    SELECT
        p.name AS pizzeria_name,
        pe.gender,
        COUNT(*) AS visit_count
    FROM person_visits pv
    JOIN pizzeria p ON pv.pizzeria_id = p.id
    JOIN person pe ON pv.person_id = pe.id
    GROUP BY p.name, pe.gender
),
gender_visit_diff AS (
    SELECT
        vc1.pizzeria_name
    FROM visit_counts vc1
    LEFT JOIN visit_counts vc2 ON vc1.pizzeria_name = vc2.pizzeria_name AND vc2.gender = 'male'
    WHERE vc1.gender = 'female' AND COALESCE(vc1.visit_count, 0) > COALESCE(vc2.visit_count, 0)
    UNION ALL
    SELECT
        vc1.pizzeria_name
    FROM visit_counts vc1
    LEFT JOIN visit_counts vc2 ON vc1.pizzeria_name = vc2.pizzeria_name AND vc2.gender = 'female'
    WHERE vc1.gender = 'male' AND COALESCE(vc1.visit_count, 0) > COALESCE(vc2.visit_count, 0)
)
SELECT *
FROM gender_visit_diff
ORDER BY pizzeria_name;
