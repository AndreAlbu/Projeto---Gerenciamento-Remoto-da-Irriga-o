int solo();

void acionamentoAutomatico(){

  int leituraSolo = solo();
  
  if(leituraSolo > 900){

    digitalWrite(RELE, HIGH);

    Serial.println("Ligando Solenoide");
    
  }

  else{

    digitalWrite(RELE, LOW);

    Serial.println("Desligando Solenoide");

  }
  
}

String estadoRele(){

  int leituraSolo = solo();

  if(leituraSolo > 900){

    return EstadoRele = "ON";
  }

  else{

    return EstadoRele = "OFF";
  }
}

int estadoReleThings(){

  int leituraSolo = solo();

  if(leituraSolo > 900){

    return 1;
  }

  else{

    return 0;
  }
}
