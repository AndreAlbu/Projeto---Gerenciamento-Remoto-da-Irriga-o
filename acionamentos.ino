void acionamentoAutomatico(){

   leituraSoloSensor1(); 
   leituraSoloSensor2();
   leituraSoloLDR();
  
   leituraSensorTemperatura();
   leituraSensorUmidade();
   
  if(EstadoRele == 1){
    
    ligaSolenoide();
  }

  else if(EstadoRele == 0){

    desligaSolenoide();
  }
  
  if(leituraSoloSensor1() > nivelSensorSolo || leituraSoloSensor2() > nivelSensorSolo || EstadoRele == 1){

     ligaSolenoide();
    
  }

  else if(leituraSoloSensor1() < nivelSensorSolo || leituraSoloSensor2() < nivelSensorSolo || EstadoRele == 0){

    desligaSolenoide();
  }
  
}

//Ao ser chamada ligará todos os solenoides
void ligaSolenoide(){

  Serial.println("Ligando solenoides");
  
  mcp.digitalWrite(0, HIGH);
  mcp.digitalWrite(1, HIGH);
  mcp.digitalWrite(2, HIGH);
  mcp.digitalWrite(3, HIGH);
}

//Ao ser chamada desligará todos os solenoides
void desligaSolenoide(){

  Serial.println("Desligando solenoides");
  
  mcp.digitalWrite(0, LOW);
  mcp.digitalWrite(1, LOW);
  mcp.digitalWrite(2, LOW);
  mcp.digitalWrite(3, LOW);
}
