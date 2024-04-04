COMMENT ON TABLE person_discounts IS 'Stores discount information for persons based on their order history with specific pizzerias. This table helps in personalizing discounts for customers to enhance loyalty and customer satisfaction.';

COMMENT ON COLUMN person_discounts.id IS 'Unique identifier for each discount entry.';
COMMENT ON COLUMN person_discounts.person_id IS 'Identifier for the person to whom the discount applies. References the person table.';
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Identifier for the pizzeria where the discount can be applied. References the pizzeria table.';
COMMENT ON COLUMN person_discounts.discount IS 'The discount amount that the person gets. It is stored as a percentage value ranging from 0 to 100.';

COMMENT ON CONSTRAINT ch_nn_person_id ON person_discounts IS 'Ensures that the person_id cannot be NULL.';
COMMENT ON CONSTRAINT ch_nn_pizzeria_id ON person_discounts IS 'Ensures that the pizzeria_id cannot be NULL.';
COMMENT ON CONSTRAINT ch_nn_discount ON person_discounts IS 'Ensures that the discount cannot be NULL.';
COMMENT ON CONSTRAINT ch_range_discount ON person_discounts IS 'Ensures that the discount value is between 0 and 100.';
