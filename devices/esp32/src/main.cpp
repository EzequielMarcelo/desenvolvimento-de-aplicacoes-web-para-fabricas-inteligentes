#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

// Configurações da rede Wi-Fi
String ssid;
String password;

const char* api_url = "http://192.168.18.60:8000/temperatura";  //IP e porta

bool loadWiFiConfig(const char* filename = "/wifi_config.json") 
{
  if (!SPIFFS.begin(true)) 
  {
    Serial.println("Erro ao iniciar SPIFFS");
    return false;
  }

  File file = SPIFFS.open(filename);
  if (!file || file.isDirectory()) 
  {
    Serial.println("Arquivo de configuração WiFi não encontrado");
    return false;
  }

  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, file);
  
  if (err) 
  {
    Serial.print("Erro no parse do JSON: ");
    Serial.println(err.c_str());
    return false;
  }

  ssid = doc["ssid"].as<String>();
  password = doc["password"].as<String>();
  ssid.trim();
  password.trim();
  return true;
}

float getTemperatura() 
{
  return 25.0 + random(-10, 10) * 0.1;
}

void setup() 
{
  Serial.begin(115200);

  if (!loadWiFiConfig()) 
  {
    Serial.println("Não foi possível carregar configuração WiFi.");
    return;
  }

  Serial.print("Conectando-se ao WiFi: ");
  Serial.print(ssid.c_str());
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid.c_str(), password.c_str());
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  if (WiFi.status() == WL_CONNECTED) 
  {
    float temperatura = getTemperatura();

    HTTPClient http;
    http.begin(api_url);
    http.addHeader("Content-Type", "application/json");

    String json = "{\"temperatura\":" + String(temperatura, 2) + "}";

    int httpResponseCode = http.POST(json);

    Serial.print("Enviando dados: ");
    Serial.println(json);
    Serial.print("Resposta HTTP: ");
    Serial.println(httpResponseCode);

    if (httpResponseCode > 0) 
    {
      String response = http.getString();
      Serial.println("Dados enviados com sucesso para API");
    } 
    else 
      Serial.println("Erro ao enviar dados para API");

    http.end();
  } 
  else 
    Serial.println("WiFi desconectado");

  delay(10000); 
}
