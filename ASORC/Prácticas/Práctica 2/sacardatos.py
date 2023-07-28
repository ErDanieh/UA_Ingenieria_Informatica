# Module Imports
import mariadb
import sys

# Connect to MariaDB Platform
try:
    conn = mariadb.connect(
        user="daniel",
        password="270301",
        host="192.168.56.222",
        port=3306,
        database="asorc"

    )
except mariadb.Error as e:
    print(f"Error connecting to MariaDB Platform: {e}")
    sys.exit(1)

# Get Cursor
cur = conn.cursor()

cur.execute(
    "SELECT * from alumnos")

# Print Result-set
for (first_name) in cur:
    print(f"Dato: {first_name}")