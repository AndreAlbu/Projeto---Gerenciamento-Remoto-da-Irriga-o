#include <ESP8266WiFi.h>         //Comunicação WiFi
#include <ESP8266WebServer.h>   //Biblioteca para criação do servidor
#include <DHT.h>               //Biblioteca para o sensor de temperatura e umidade
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_Sensor.h>  

Adafruit_MCP23017 mcp; //Mapear as portas digitais multiplexada

int EstadoRele = 0;

//Em quantos porcentos os solenoides deverão ser acionados (512 -> 50%)
int nivelSensorSolo = 50;

//CONFIGURAÇÕES DE PORTAS

#define LDR     D3
#define SOLO    A0

DHT dht1(D3, DHT11);

//CONFIGURAÇÕES DE REDE
 
#define SSID_REDE  "***" 
#define SENHA_REDE "***" 

 
//CONFIGURAÇÕES THINGSPEAK

#define INTERVALO_ENVIO_THINGSPEAK 30000  
char endereco_api_thingspeak[] = "api.thingspeak.com";
String chave_escrita_thingspeak = "GGTOJWF3KGLJI5KO";  /* Chave de escrita do ThingsSpeak */
unsigned long last_connection_time;

void envia_informacoes_thingspeak(String string_dados);
void inicia_wifi(void);
void conecta_wifi(void);
void verifica_conexao_wifi(void);

//CONFIGURAÇÕES DO SERVIDOR

WiFiClient client;
ESP8266WebServer server(80);

//DECLARANDO AS FUNÇṌES
int convesorAnalogico(int valor);

int leituraSoloSensor1(); 
int leituraSoloSensor2();
int leituraSoloLDR();

float leituraSensorTemperatura();
float leituraSensorUmidade();

void ligaSolenoide();
void desligaSolenoide();


void acionamentoAutomatico();

void setup(){
  
    Serial.begin(115200);
    dht1.begin();
    mcp.begin();

    mcp.pinMode(0, OUTPUT);  //GPA0 21  Rele
    mcp.pinMode(1, OUTPUT);  //GPA1 22  Rele
    mcp.pinMode(2, OUTPUT);  //GPA2 23  Rele
    mcp.pinMode(3, OUTPUT);  //GPA3 24  Rele

    pinMode(LDR,   INPUT);
    pinMode(SOLO,  INPUT);
    
    last_connection_time = 0;

    inicia_wifi();

    server.on("/", Conectado);
    server.onNotFound(NotFound);
    server.on("/liga", ligaSolenoideHTML);
    server.on("/desliga", desligaSolenoideHTML);

    server.begin();
    Serial.println("Iniciando o servidor");
}
 
void loop(){

    int ler1 = leituraSoloSensor1(); 
    int ler2 = leituraSoloSensor2();
    int ler3 = leituraSoloLDR();
    
    float ler4 = leituraSensorTemperatura();
    float ler5 = leituraSensorUmidade();
        
    char fields_a_serem_enviados[100] = {0};
   
    if (client.connected()) {
      
        client.stop();
        Serial.println("- Desconectado do ThingSpeak");
        Serial.println();
    }
 
    verifica_conexao_wifi();
     
    if( millis() - last_connection_time > INTERVALO_ENVIO_THINGSPEAK ) {

        sprintf(fields_a_serem_enviados,"field1=%.2f&field2=%.2f&field3=%.2f&field4=%.2f&field5=%.2f&field6=%.2f", ler1, ler2, ler3, ler4, ler5, EstadoRele);
        
        envia_informacoes_thingspeak(fields_a_serem_enviados);

  
    }

    acionamentoAutomatico();

    server.handleClient();
    
    Serial.println(EstadoRele);
 
    delay(5000);
}
