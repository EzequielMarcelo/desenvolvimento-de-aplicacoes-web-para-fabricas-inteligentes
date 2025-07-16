from fastapi import APIRouter
from app.models.payloads import TemperaturaPayload
from app.services.temperatura import salvar_temperatura, listar_temperaturas

router = APIRouter()

@router.post("/temperatura")
async def receber_temperatura(payload: TemperaturaPayload):
    salvar_temperatura(payload.temperatura)
    return {"status": "ok"}

@router.get("/temperatura")
def get_temperaturas():
    return listar_temperaturas()
