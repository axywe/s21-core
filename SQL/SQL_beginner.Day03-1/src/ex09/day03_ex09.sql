-- Please register new visits into Dominos restaurant from Denis and Irina on 24th of February 2022. Warning: this exercise will probably be the cause of changing data in the wrong way. Actually, you can restore the initial database model with data from the link in the “Rules of the day” section and replay script from Exercises 07 and 08..

INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
VALUES
((SELECT MAX(id) + 1 FROM person_visits), (SELECT id FROM person WHERE name = 'Denis'), 2, '2022-02-24'),
((SELECT MAX(id) + 2 FROM person_visits), (SELECT id FROM person WHERE name = 'Irina'), 2, '2022-02-24');

SELECT * FROM person_visits;