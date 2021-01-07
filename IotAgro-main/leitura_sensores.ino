//Leitura do sensor do solo 1 -> porta 0
int leituraSoloSensor1(){

  int ler_solo = 0;

  ler_solo = analogRead(SOLO);

  Serial.print("Leitura Solo 1: ");
  Serial.print(convesorAnalogico(ler_solo));
  Serial.println(" %");

  return convesorAnalogico(ler_solo);
  
}

//Leitura do sensor de solo 2 -> porta 1
int leituraSoloSensor2(){

  int ler_solo = 0;

  ler_solo = analogRead(SOLO);

  Serial.print("Leitura Solo 1: ");
  Serial.print(convesorAnalogico(ler_solo));
  Serial.println(" %");

  return convesorAnalogico(ler_solo);
  
}

//Leitura do sensor LDR (Quantidade de LUZ) -> 2
int leituraSoloLDR(){

  int lerLdr;

  lerLdr = digitalRead(LDR);

  Serial.print("LDR: ");
  Serial.print(convesorAnalogico(lerLdr));
  Serial.println(" %");

  return convesorAnalogico(lerLdr);
  
}


float leituraSensorTemperatura(){

  float ler_temperatura = 0.0;

  ler_temperatura = dht1.readTemperature();

  Serial.print("Leitura da temperatura do ar: ");
  Serial.print(ler_temperatura);
  Serial.println(" C");

  return ler_temperatura;
  
}

float leituraSensorUmidade(){

  float ler_umidade = 0.0;

  ler_umidade = dht1.readHumidity();

  Serial.print("Leitura da umidade do ar: ");
  Serial.print(ler_umidade);
  Serial.println(" %");

  return ler_umidade;
  
}



int convesorAnalogico(int valor){

   int temporario = 0;

   temporario = ((100 * (1024 - valor) / 1024));

   return temporario;
}
