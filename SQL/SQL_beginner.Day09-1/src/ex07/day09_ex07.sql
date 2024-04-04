CREATE OR REPLACE FUNCTION func_minimum(arr FLOAT[])
RETURNS FLOAT AS $$
BEGIN
    RETURN (SELECT MIN(a) FROM unnest(arr) AS dt(a));
END;
$$ LANGUAGE plpgsql;

SELECT func_minimum(VARIADIC arr => ARRAY[-10.0, -1.0, 5.0, 4.4]);
