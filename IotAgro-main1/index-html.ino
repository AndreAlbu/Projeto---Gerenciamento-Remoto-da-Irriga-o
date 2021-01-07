float leituraTemperatura, leituraUmidade;
int leituraSolo;

float temperatura_DHT11();
float umidade_DHT11();
int solo();

void NotFound(){
  
  server.send(404, "text/plain", "Not found");
  
}

void Ligar(){
  
    Serial.println("Ligando Bomba");
    botao1 = "on";
    digitalWrite(RELE, HIGH);
  
}

void estado(){
  
  String header;

  if (header.indexOf("GET /5/on") >= 0) {
              
   
 
  } else if (header.indexOf("GET /5/off") >= 0) {
    
    Serial.println("Desligando Bomba");
    botao1 = "off";
    digitalWrite(RELE, LOW);
  
  } 
}

void Conectado() {
  
  leituraTemperatura = temperatura_DHT11_Externo();
  leituraUmidade = umidade_DHT11_Externo();
  leituraSolo = solo();
  
  server.send(200, "text/html", SendHTML(leituraTemperatura, leituraUmidade, leituraSolo)); 
}


String SendHTML(float leituraTemperatura,float leituraUmidade, int leituraSolo){
  
  String ptr = "<!DOCTYPE html>";
  
  ptr +="<html lang/'pt-br'/>";
  ptr +="<head>";
  ptr +="<title>IoTAGRO</title>";
  ptr +="<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  ptr +="<meta charset=\"UTF-8\" name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">";
  ptr +="<link href='https://fonts.googleapis.com/css?family=Open+Sans:300,400,600' rel='stylesheet'>";
  
  ptr +="<style>";
  
  ptr +="html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #444444;}";
  ptr +="body{margin: 0px;} ";
  ptr +="h1 {margin: 50px auto 30px;} ";
  ptr +=".side-by-side{display: table-cell;vertical-align: middle;position: relative;}";
  ptr +=".text{font-weight: 600;font-size: 19px;width: 200px;}";
  ptr +=".reading{font-weight: 300;font-size: 50px;padding-right: 25px;}";
  ptr +=".temperature .reading{color: #F29C1F;}";
  ptr +=".humidity .reading{color: #3B97D3;}";
  ptr +=".pressure .reading{color: #26B99A;}";
  ptr +=".superscript{font-size: 17px;font-weight: 600;position: absolute;top: 10px;}";
  ptr +=".data{padding: 10px;}";
  ptr +=".container{display: table;margin: 0 auto;}";
  ptr +=".icon{width:65px}";
  ptr +=".a .btn-ar {width: 50%;height: 50px ;border: hidden;margin-bottom: 15px;border-radius: 20px;font-size: 16px;color: gainsboro; box-shadow: 2px 4px 2px darkgray;background-color: #aedd94;;}";
  ptr +=".btn-luzes, .btn-ar {width: 50%;height: 50px ;border: hidden;margin-bottom: 15px;border-radius: 20px;font-size: 16px;color: gainsboro; box-shadow: 2px 4px 2px darkgray;background-color: #800000;}";
  ptr +=".btn-luzes2, .btn-ar2 {width: 50%;height: 50px ;border: hidden;margin-bottom: 15px;border-radius: 20px;font-size: 16px;color: gainsboro; box-shadow: 2px 4px 2px darkgray;background-color: #00FF00;}";
  ptr +="</style>";
  
  ptr +="</head>";
  
  ptr +="<body>";
  
  ptr +="<h1>IoT AGRO IFCE</h1>";

  ptr +="<h1>Bomba</h1>";
  ptr +="<p>Estado: ";
  ptr +=EstadoRele;
  ptr +="</p>";

  if (botao1 == "off") {
              
    ptr += "<p><a href=\"/ligar\"><button class=\"btn-luzes\">Bomba</button></a></p>";
    
  } else {
      
    ptr += "<p><a href=\"/5/off\"><button class=\"button btn-luzes2\">Bomba</button></a></p>";
  } 
  
  
  ptr +="<div class='container'>";
  ptr +="<div class='data temperature'>";
  ptr +="<div class='side-by-side icon'>";
  ptr +="<svg enable-background='new 0 0 19.438 54.003'height=54.003px id=Layer_1 version=1.1 viewBox='0 0 19.438 54.003'width=19.438px x=0px xml:space=preserve xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink y=0px><g><path d='M11.976,8.82v-2h4.084V6.063C16.06,2.715,13.345,0,9.996,0H9.313C5.965,0,3.252,2.715,3.252,6.063v30.982";
  ptr +="C1.261,38.825,0,41.403,0,44.286c0,5.367,4.351,9.718,9.719,9.718c5.368,0,9.719-4.351,9.719-9.718";
  ptr +="c0-2.943-1.312-5.574-3.378-7.355V18.436h-3.914v-2h3.914v-2.808h-4.084v-2h4.084V8.82H11.976z M15.302,44.833";
  ptr +="c0,3.083-2.5,5.583-5.583,5.583s-5.583-2.5-5.583-5.583c0-2.279,1.368-4.236,3.326-5.104V24.257C7.462,23.01,8.472,22,9.719,22";
  ptr +="s2.257,1.01,2.257,2.257V39.73C13.934,40.597,15.302,42.554,15.302,44.833z'fill=#F29C21 /></g></svg>";
  ptr +="</div>";
  ptr +="<div class='side-by-side text'>Temperatura</div>";
  ptr +="<div class='side-by-side reading'>";
  ptr +=(int)leituraTemperatura;
  ptr +="<span class='superscript'>&deg;C</span></div>";
  ptr +="</div>";

  
  ptr +="<div class='data humidity'>";
  ptr +="<div class='side-by-side icon'>";
  ptr +="<svg enable-background='new 0 0 29.235 40.64'height=40.64px id=Layer_1 version=1.1 viewBox='0 0 29.235 40.64'width=29.235px x=0px xml:space=preserve xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink y=0px><path d='M14.618,0C14.618,0,0,17.95,0,26.022C0,34.096,6.544,40.64,14.618,40.64s14.617-6.544,14.617-14.617";
  ptr +="C29.235,17.95,14.618,0,14.618,0z M13.667,37.135c-5.604,0-10.162-4.56-10.162-10.162c0-0.787,0.638-1.426,1.426-1.426";
  ptr +="c0.787,0,1.425,0.639,1.425,1.426c0,4.031,3.28,7.312,7.311,7.312c0.787,0,1.425,0.638,1.425,1.425";
  ptr +="C15.093,36.497,14.455,37.135,13.667,37.135z'fill=#3C97D3 /></svg>";
  ptr +="</div>";
  ptr +="<div class='side-by-side text'>Umidade</div>";
  ptr +="<div class='side-by-side reading'>";
  ptr +=(int)leituraUmidade;
  ptr +="<span class='superscript'>%</span></div>";
  ptr +="</div>";



  
  ptr +="<div class='data pressure'>";
  ptr +="<div class='side-by-side icon'>";
  ptr +="<svg enable-background='new 0 0 29.235 40.64'height=40.64px id=Layer_1 version=1.1 viewBox='0 0 29.235 40.64'width=29.235px x=0px xml:space=preserve xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink y=0px><path d='M14.618,0C14.618,0,0,17.95,0,26.022C0,34.096,6.544,40.64,14.618,40.64s14.617-6.544,14.617-14.617";
  ptr +="C29.235,17.95,14.618,0,14.618,0z M13.667,37.135c-5.604,0-10.162-4.56-10.162-10.162c0-0.787,0.638-1.426,1.426-1.426";
  ptr +="c0.787,0,1.425,0.639,1.425,1.426c0,4.031,3.28,7.312,7.311,7.312c0.787,0,1.425,0.638,1.425,1.425";
  ptr +="C15.093,36.497,14.455,37.135,13.667,37.135z'fill=#3C97D3 /></svg>";
  ptr +="</div>";
  ptr +="<div class='side-by-side text'>Solo</div>";
  ptr +="<div class='side-by-side reading'>";
  ptr +=(int)leituraSolo;
  ptr +="<span class='superscript'>%</span></div>";
  ptr +="</div>";

  ptr += "<div class = 'things'>";
  ptr += "<a href='https://thingspeak.com/channels/1193749/'>Análise Completa</a>";
  ptr += "</div>";
  
  ptr +="</div>"; //DIV CONTEINER
  
  ptr +="</body>";
  ptr +="</html>";
  return ptr;
}
