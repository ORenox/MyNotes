![[Pasted image 20260918093600.png]]

Después de escribir los modelos ejecutas:

```python
python manage.py makemigrations
```

Django genera algo parecido a esto (automáticamente):

```python
Migrations for 'machines':
  0001_initial.py

  Create model Machine
  Create model Sensor
  Create model Measurement
```

Luego:

```python
python manage.py migrate
```

Y PostgreSQL crea:

```sql
CREATE TABLE machine (...);

CREATE TABLE sensor (...);

CREATE TABLE measurement (...);

ALTER TABLE sensor
ADD CONSTRAINT ...
FOREIGN KEY (machine_id)
REFERENCES machine(id);
```

Tú no escribes ese SQL.