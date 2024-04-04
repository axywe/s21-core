SELECT 
    a.name AS person_name1, 
    b.name AS person_name2, 
    a.address AS common_address
FROM 
    person a
JOIN 
    person b ON a.address = b.address AND b.id < a.id
ORDER BY 
    person_name1, person_name2, common_address;
