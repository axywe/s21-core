--  Session #1:
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
SHOW TRANSACTION ISOLATION LEVEL; --  REPEATABLE READ
BEGIN;

--  Session #2:
BEGIN;
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';

--  Session #1:
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';

--  Session #1:
UPDATE pizzeria SET rating = 4 WHERE name = 'Pizza Hut';

--  Session #2:
UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';

--  Session #1:
COMMIT;

--  Session #2:
COMMIT;

--  Session #1:
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';

--  Session #2:
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';