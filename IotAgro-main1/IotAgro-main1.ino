#include <ESP8266WiFi.h>         //Comunicação WiFi
#include <ESP8266WebServer.h>   //Biblioteca para criação do servidor
#include <DHT.h>               //Biblioteca para o sensor de temperatura e umidade
#include <Wire.h>
#include <Adafruit_Sensor.h>  //Biblioteca para o sensor de temperatura e umidade

//CONFIGURAÇÕES DE PORTAS

#define RELE    D0
#define CHUVA   D2
#define LDR     D3
#define SOLO    A0

DHT dht1(D1, DHT11);
DHT dht2(D5, DHT11);

String botao1 = "off";
String botao2 = "off";
String EstadoRele = "off";


//CONFIGURAÇÕES DE REDE
 
#define SSID_REDE  "POUSADANSCONCEICAO" 
#define SENHA_REDE "pousadadoseuluiz" 

 
//CONFIGURAÇÕES THINGSPEAK

#define INTERVALO_ENVIO_THINGSPEAK 30000  
char endereco_api_thingspeak[] = "api.thingspeak.com";
String chave_escrita_thingspeak = "AVLEJVQDC85IVXCX";  /* Chave de escrita do ThingsSpeak */
unsigned long last_connection_time;

void envia_informacoes_thingspeak(String string_dados);
void inicia_wifi(void);
void conecta_wifi(void);
void verifica_conexao_wifi(void);

//CONFIGURAÇÕES DO SERVIDOR

WiFiClient client;
ESP8266WebServer server(80);

//DECLARANDO AS FUNÇṌES

int solo();
int chuva();
int ldr();
float temperatura_DHT11();
float umidade_DHT11();
float temperatura_DHT11_Externo();
float umidade_DHT11_Externo();
int estadoReleThings();
void acionamentoAutomatico();

void setup(){
  
    Serial.begin(115200);

    pinMode(CHUVA, INPUT);
    pinMode(LDR,   INPUT);
    pinMode(SOLO,  INPUT);
    pinMode(RELE,  OUTPUT);
    dht1.begin();
    dht2.begin();
    
    last_connection_time = 0;

    inicia_wifi();

    server.on("/", Conectado);
    server.onNotFound(NotFound);
    server.on("/ligar", Ligar);

    server.begin();
    Serial.println("Iniciando o servidor");
}
 
void loop(){

    float leituraSolo = solo(); 
    float leituraChuva = chuva(); 
    float leituraLdr = ldr(); 
    float leituraTemperatura = temperatura_DHT11(); 
    float leituraUmidade = umidade_DHT11();
    float leituraTemperaturaExterna = temperatura_DHT11_Externo();
    float leituraUmidadeExterna = umidade_DHT11_Externo();
    float rele = estadoReleThings();
    
    acionamentoAutomatico();
      
    char fields_a_serem_enviados[100] = {0};
   
    if (client.connected()) {
      
        client.stop();
        Serial.println("- Desconectado do ThingSpeak");
        Serial.println();
    }
 
    verifica_conexao_wifi();
     
    if( millis() - last_connection_time > INTERVALO_ENVIO_THINGSPEAK ) {

        sprintf(fields_a_serem_enviados,"field1=%.2f&field2=%.2f&field3=%.2f&field4=%.2f&field5=%.2f&field6=%.2f&field7=%.2f&field8=%.2f", 
                                         leituraTemperatura,leituraUmidade,leituraSolo,leituraChuva,leituraLdr,leituraTemperaturaExterna,leituraUmidadeExterna);
        
        envia_informacoes_thingspeak(fields_a_serem_enviados);

  
    }

    server.handleClient();
 
    delay(5000);
}
