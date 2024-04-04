CREATE INDEX IF NOT EXISTS idx_person_name ON person (UPPER(name));
SET enable_seqscan = off;
EXPLAIN ANALYZE
SELECT upper(p.name) FROM person p WHERE upper(p.name) = 'ANNA';

SELECT upper(p.name) FROM person p WHERE upper(p.name) = 'ANNA';