# Desenvolvimento de Aplicações Web para Fábricas Inteligentes: Explorando o Potencial do Python e dos Dispositivos da Internet das Coisas (IoT)

<p align="center"><img src="docs/imagens/diagrama-geral-do-projeto.jpg" height="400"></p>

Este projeto de Iniciação Científica, desenvolvido no Instituto Federal do Espírito Santo (IFES), busca explorar como tecnologias modernas podem 
transformar processos industriais, com foco no conceito de fábricas inteligentes. A proposta integra dispositivos IoT e soluções baseadas em Python 
para criar sistemas escaláveis, eficientes e alinhados às demandas da Indústria 4.0.

## Objetivo
O principal objetivo do projeto é investigar e demonstrar como a combinação de ferramentas e frameworks em Python, juntamente com dispositivos IoT 
como o ESP32, pode:
- Automatizar processos industriais: Criar sistemas que integram sensores e atuadores para controle e monitoramento em tempo real.
- Otimizar recursos e eficiência: Aplicar tecnologias para melhorar a produtividade e reduzir custos operacionais.
- Promover escalabilidade: Construir soluções flexíveis que atendam a diferentes demandas industriais.
- Aumentar a conectividade: Implementar protocolos modernos de comunicação (como MQTT e HTTP) para uma integração fluida entre sistemas.

## Resultados Esperados
- Desenvolvimento de uma API robusta para comunicação com dispositivos IoT.
- Criação de firmware otimizado para ESP32, responsável por capturar e enviar dados de sensores.
- Um sistema funcional capaz de exemplificar aplicações práticas em fábricas inteligentes, como monitoramento ambiental, controle de máquinas 
ou análise de eficiência.

# Desenvolvimento do Projeto

# 🌡️ Sistema de Monitoramento de Temperatura com ESP32, FastAPI e Streamlit

O sistema escolhido realiza a leitura de temperatura via ESP32, envia os dados para uma API desenvolvida com FastAPI e exibe os dados em tempo real em um dashboard interativo feito com Streamlit.

>💡 Instale todas as dependências necessárias:
```bash
# Criar o ambiente virtual
python -m venv .venv
# Ativar o ambiente virtual
.venv\Scripts\Activate.ps1
# Instalar as dependências
pip install -r requirements.txt 
```

---

## 📟 1. ESP32 – Leitura e Envio de Temperatura

### 📁 Estrutura Esperada
O código do ESP32 está na pasta `devices/esp32`, foi desenvolvido utilizando o PlatformIO, e o Wi-Fi é configurado via arquivo:

```
devices/esp32
├── data/
│   ├── wifi_config.json
├── include/
├── lib/
├── src/
│   ├── main.cpp
├── test/
├── platformio.ini

```

### 📄 `wifi_config.json`
```json
{
  "ssid": "NOME_DA_REDE",
  "password": "SENHA_DA_REDE"
}
```

### 🔧 Como usar
1. Abra a pasta devices/esp32 com VS Code.
2. Altere o conteúdo de `wifi_config.json` com o nome e senha da sua rede.
3. Compile e envie o código para o ESP32.
4. Envie o arquivo wifi_config.json para o ESP32 com `pio run --target uploadfs`.
5. O ESP32 se conectará ao Wi-Fi e enviará leituras de temperatura (em JSON via POST) para a API a cada 10 segundos.

---

## 🧠 2. API – FastAPI

### 📁 Estrutura Esperada
```
Backend/
├── app/
│   ├── __init__.py
│   ├── main.py
│   ├── api/
│   │   └── routes.py
│   └── models/
│       └── payloads.py
```

### ▶️ Como rodar
1. Abra a pasta raiz do projeto com VS Code:

2. Rode a API com Uvicorn:
```bash
uvicorn app.main:app --host 0.0.0.0 --port 8000 
```

3. A API estará disponível em `http://localhost:8000`.

### 🔗 Endpoints
- `POST /temperatura`: Recebe dados do ESP32.
- `GET /temperatura`: Retorna as leituras salvas (simuladas ou armazenadas).

---

## 📊 3. Frontend – Streamlit

### 📁 Estrutura Esperada
```
Frontend/
├── streamlit/
│   └── main.py
```

### ▶️ Como rodar o dashboard
1. Abra a pasta raiz do projeto com VS Code:

2. Execute o Streamlit:
```bash
streamlit run frontend/streamlit/main.py 
```

3. Acesse `http://localhost:8501` no navegador.

---

## 📡 Comunicação entre os Componentes

```
ESP32 → (POST) → FastAPI → (GET) → Streamlit
```

---

## ✅ Requisitos

### 📦 Python
- Python 3.10+
- FastAPI
- Uvicorn
- Requests
- Streamlit

### 🔌 Arduino/ESP32
- Placa ESP32 instalada
- Biblioteca `WiFi.h`
- Biblioteca `HTTPClient.h`
- JSON embutido para configuração
