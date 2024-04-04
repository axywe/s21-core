WITH date_series AS (
  SELECT generate_series('2022-01-01'::date, '2022-01-10'::date, '1 day'::interval)::date AS missing_date
),
visited_dates AS (
  SELECT DISTINCT visit_date::date FROM person_visits
  WHERE (person_id = 1 OR person_id = 2) AND visit_date BETWEEN '2022-01-01' AND '2022-01-10'
)
SELECT d.missing_date
FROM date_series d
LEFT JOIN visited_dates v ON d.missing_date = v.visit_date
WHERE v.visit_date IS NULL
ORDER BY d.missing_date ASC;
