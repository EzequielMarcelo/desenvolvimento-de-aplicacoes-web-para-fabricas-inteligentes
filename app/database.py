import os

def get_db_path():
    return os.path.abspath(
        os.path.join(os.path.dirname(__file__), "..", "data", "database", "temperaturas.db")
    )
