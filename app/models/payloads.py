from pydantic import BaseModel

class TemperaturaPayload(BaseModel):
    temperatura: float
