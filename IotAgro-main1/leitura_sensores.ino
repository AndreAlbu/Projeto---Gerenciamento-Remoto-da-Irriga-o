int solo(){

  int ler_solo = 0;

  ler_solo = analogRead(SOLO);

  Serial.print("Leitura Solo: ");
  Serial.print(ler_solo);
  Serial.println(" %");

  return ler_solo;
  
}

float temperatura_DHT11(){

  float ler_temperatura = 0;

  ler_temperatura = dht1.readTemperature();

  Serial.print("Leitura da temperatura do ar: ");
  Serial.print(ler_temperatura);
  Serial.println(" C");

  return ler_temperatura;
  
}

float umidade_DHT11(){

  float ler_umidade = 0.0;

  ler_umidade = dht1.readHumidity();

  Serial.print("Leitura da umidade do ar: ");
  Serial.print(ler_umidade);
  Serial.println(" %");

  return ler_umidade;
  
}

float temperatura_DHT11_Externo(){

  float ler_temperatura = 0;

  ler_temperatura = dht2.readTemperature();

  Serial.print("Leitura da temperatura do ar EXTERNA: ");
  Serial.print(ler_temperatura);
  Serial.println(" C");

  return ler_temperatura;
  
}

float umidade_DHT11_Externo(){

  float ler_umidade = 0.0;

  ler_umidade = dht2.readHumidity();

  Serial.print("Leitura da umidade do ar EXTERNA: ");
  Serial.print(ler_umidade);
  Serial.println(" %");

  return ler_umidade;
  
}

int chuva(){
  
  int lerChuva = -1;

  lerChuva = digitalRead(CHUVA);

  if(lerChuva == 0){

    Serial.println("Chuvendo!");

    return lerChuva;
  }

  else if(lerChuva == 1){

    Serial.println("Normal!!");
    
    return lerChuva;
  }
  
}

int ldr(){

  int lerLdr = -1;

  lerLdr = digitalRead(LDR);

  if(lerLdr == 0){

    Serial.println("Recendo Luz!");

    return lerLdr;
  }

  else if(lerLdr == 1){

    Serial.println("Sem Luz!");

    return lerLdr;
  }
}
