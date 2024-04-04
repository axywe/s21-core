CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop INTEGER DEFAULT 10)
RETURNS TABLE(fibonacci_number BIGINT) AS $$
DECLARE
    a BIGINT := 0;
    b BIGINT := 1;
    fib BIGINT := 0;
BEGIN
    IF pstop <= 0 THEN
        RETURN;
    END IF;

    -- Always start with first Fibonacci number
    fibonacci_number := a;
    RETURN NEXT;

    FOR i IN 1..pstop LOOP
        fib := a + b;
        EXIT WHEN fib >= pstop;
        fibonacci_number := fib;
        RETURN NEXT;
        a := b;
        b := fib;
    END LOOP;
END;
$$ LANGUAGE plpgsql;

select * from fnc_fibonacci(100);
select * from fnc_fibonacci();