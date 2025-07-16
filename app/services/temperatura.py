from datetime import datetime
from app.database import get_db_path
import sqlite3
import pandas as pd

def salvar_temperatura(valor: float):
    conn = sqlite3.connect(get_db_path())
    c = conn.cursor()
    c.execute("CREATE TABLE IF NOT EXISTS temperatura (timestamp TEXT, valor REAL)")
    c.execute("INSERT INTO temperatura VALUES (?, ?)", (datetime.now().isoformat(), valor))
    conn.commit()
    conn.close()

def listar_temperaturas():
    conn = sqlite3.connect(get_db_path())
    df = pd.read_sql_query("SELECT * FROM temperatura ORDER BY timestamp DESC LIMIT 40", conn)
    conn.close()
    return df.to_dict(orient="records")
