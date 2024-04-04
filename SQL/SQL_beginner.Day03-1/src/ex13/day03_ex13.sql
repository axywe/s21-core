-- Please write 2 SQL (DML) statements that delete all new orders from exercise #12 based on order date. Then delete “greek pizza” from the menu. Warning: this exercise will probably be the cause of changing data in the wrong way. Actually, you can restore the initial database model with data from the link in the “Rules of the day” section and replay script from Exercises 07 , 08 ,09 , 10 , 11, 12 and 13.

DELETE FROM person_order
WHERE order_date = '2022-02-25';

SELECT * FROM person_order;

DELETE FROM menu
WHERE pizza_name = 'greek pizza';

SELECT * FROM menu;