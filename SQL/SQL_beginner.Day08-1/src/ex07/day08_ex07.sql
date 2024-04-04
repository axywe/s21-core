-- Session #1:
BEGIN TRANSACTION;
UPDATE pizzeria SET rating = 5 WHERE id = 1;

-- Session #2:
BEGIN TRANSACTION;
UPDATE pizzeria SET rating = 4 WHERE id = 2;

-- Session #1:
UPDATE pizzeria SET rating = 5 WHERE id = 2;

-- Session #2:
UPDATE pizzeria SET rating = 4 WHERE id = 1;