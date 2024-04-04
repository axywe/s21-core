SELECT p.name, COUNT(*) AS count_visits
FROM person_visits
JOIN person p ON person_visits.person_id = p.id
GROUP BY p.name
HAVING COUNT(*) > 3