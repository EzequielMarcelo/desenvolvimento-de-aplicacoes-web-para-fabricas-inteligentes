#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Configurações da rede Wi-Fi
const char* ssid = "WIFI-TESTE";
const char* password = "12345678";

const char* api_url = "http://192.168.18.60:8000/temperatura";  //IP e porta

// Função para simular temperatura
float getTemperatura() 
{
  return 25.0 + random(-10, 10) * 0.1;
}

void setup() 
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);

  Serial.print("Conectando-se ao WiFi");
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
