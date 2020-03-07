
#include <Arduino.h>
#include "ControladorSensoresDeFaixa.h"

ControladorSensoresDeFaixa::ControladorSensoresDeFaixa() {
  sensor_esquerdo_extremo = SensorDeRefletancia(A1);
  sensor_esquerdo_centro  = SensorDeRefletancia(A2);
  sensor_frontal          = SensorDeRefletancia(A3);
  sensor_central          = SensorDeRefletancia(A4);
  sensor_direito_centro   = SensorDeRefletancia(A5);
  sensor_direito_extremo  = SensorDeRefletancia(A6);
  sensor_traseiro         = SensorDeRefletancia(A7);
}

void ControladorSensoresDeFaixa::lerSensoresPrincipais() {
  see = sensor_esquerdo_extremo.ler();
  sec = sensor_esquerdo_centro.ler();
  sf  = sensor_frontal.ler();
  sc  = sensor_central.ler();
  sdc = sensor_direito_centro.ler();
  sde = sensor_direito_extremo.ler();
}

int ControladorSensoresDeFaixa::lerSensorFrontal() {
  return sensor_frontal.ler();
}

int ControladorSensoresDeFaixa::lerSensorTraseiro() {
  return sensor_traseiro.ler();
}

int ControladorSensoresDeFaixa::obterSituacaoAtual() {

  lerSensoresPrincipais();

  if (sf > 250) {

    if (see > _limite and sde > _limite and sc > _limite and sec > _limite and sdc > _limite) {
      situacao_atual = CRUZAMENTO_TOTAL;
      return CRUZAMENTO_TOTAL;
    }

    else if (see > _limite and sde <= limite and sc > _limite and sec > _limite) {
      delay(5);

      see = sensor_esquerdo_extremo.ler();
      sde = sensor_direito_extremo.ler();

      if (see > _limite and sde > _limite) {
        situacao_atual = CRUZAMENTO_TOTAL;
        return CRUZAMENTO_TOTAL;
      }
      
      situacao_atual = CRUZAMENTO_PARA_ESQUERDA;
      return CRUZAMENTO_PARA_ESQUERDA;
    }

    else if (sde > _limite and see <= limite and sc > _limite and sdc > _limite) {
      delay(5);

      see = sensor_esquerdo_extremo.ler();
      sde = sensor_direito_extremo.ler();

      if (see > _limite and sde > _limite) {
        situacao_atual = CRUZAMENTO_TOTAL;
        return CRUZAMENTO_TOTAL;      
      }

      situacao_atual = CRUZAMENTO_PARA_DIREITA;
      return CRUZAMENTO_PARA_DIREITA;
    }

    else if (see <= limite and sde <= limite and sec > limite and sc > _limite) {
      situacao_atual = CURVA_SIMPLES_PARA_ESQUERDA;
      return CURVA_SIMPLES_PARA_ESQUERDA;
    }

    else if (see <= limite and sde <= limite and sdc > limite and sc > _limite) {
      situacao_atual = CURVA_SIMPLES_PARA_DIREITA;
      return CURVA_SIMPLES_PARA_DIREITA;
    }

    else if (see <= limite and sde <= limite and sc > _limite and sec <= limite and sdc <= limite) {
      situacao_atual = LINHA_RETA;
      return LINHA_RETA;
    }

  }

  else {

    if (see > _limite and sde > _limite and sc > _limite and sec > _limite and sdc > _limite) {
      situacao_atual = T;
      return T;
    }

    else if (see > _limite and sde <= limite and sc > _limite and sec > _limite) {
      delay(5);

      see = sensor_esquerdo_extremo.ler();
      sde = sensor_direito_extremo.ler();

      if (see > _limite and sde > _limite) {
        situacao_atual = T;
        return T;
      }

      situacao_atual = CURVA_DE_90_GRAUS_PARA_ESQUERDA;
      return CURVA_DE_90_GRAUS_PARA_ESQUERDA;
    }

    else if (sde > _limite and see <= limite and sc > _limite and sdc > _limite) {
      delay(5);

      see = sensor_esquerdo_extremo.ler();
      sde = sensor_direito_extremo.ler();

      if (see > _limite and sde > _limite) {
        situacao_atual = T;
        return T;
      }

      situacao_atual = CURVA_DE_90_GRAUS_PARA_DIREITA;
      return CURVA_DE_90_GRAUS_PARA_DIREITA;
    }

    else if (see <= limite and sde <= limite and sc > _limite and sec > limite and sdc > limite) {
      situacao_atual = ROTATORIA;
      return ROTATORIA;
    }

    else if (see <= limite and sde <= limite and sec > limite and sc > _limite) {
      situacao_atual = CURVA_SIMPLES_PARA_ESQUERDA;
      return CURVA_SIMPLES_PARA_ESQUERDA;
    }

    else if (see <= limite and sde <= limite and sdc > limite and sc > _limite) {
      situacao_atual = CURVA_SIMPLES_PARA_DIREITA;
      return CURVA_SIMPLES_PARA_DIREITA;
    }

    else if (see <= limite and sde <= limite and sdc <= limite and sc <= _limite) {
      situacao_atual = GAP;
      return GAP;
    }
  }

  situacao_atual = SITUACAO_NAO_IMPORTANTE;
  return SITUACAO_NAO_IMPORTANTE;
}

void ControladorSensoresDeFaixa::mostrarResultados() {
  Serial.print(F("    "));
  Serial.print(see);
  Serial.print(F("    "));
  Serial.print(sec);
  Serial.print(F("    "));
  Serial.print(sf);
  Serial.print(F("    "));
  Serial.print(sc);
  Serial.print(F("    "));
  Serial.print(sdc);
  Serial.print(F("    "));
  Serial.print(sde);
  Serial.print(F("    "));

  switch (situacao_atual) {
    case CRUZAMENTO_TOTAL:
      Serial.println(F("CRUZAMENTO_TOTAL"));
      break;
    case CRUZAMENTO_PARA_ESQUERDA:
      Serial.println(F("CRUZAMENTO_PARA_ESQUERDA"));
      break;
    case CRUZAMENTO_PARA_DIREITA:
      Serial.println(F("CRUZAMENTO_PARA_DIREITA"));
      break;
    case CURVA_SIMPLES_PARA_ESQUERDA:
      Serial.println(F("CURVA_SIMPLES_PARA_ESQUERDA"));
      break;
    case CURVA_SIMPLES_PARA_DIREITA:
      Serial.println(F("CURVA_SIMPLES_PARA_DIREITA"));
      break;
    case LINHA_RETA:
      Serial.println(F("LINHA_RETA"));
      break;
    case CURVA_DE_90_GRAUS_PARA_ESQUERDA:
      Serial.println(F("CURVA_DE_90_GRAUS_PARA_ESQUERDA"));
      break;
    case CURVA_DE_90_GRAUS_PARA_DIREITA:
      Serial.println(F("CURVA_DE_90_GRAUS_PARA_DIREITA"));
      break;
    case T:
      Serial.println(F("T"));
      break;
    case ROTATORIA:
      Serial.println(F("ROTATORIA"));
      break;
    case GAP:
      Serial.println(F("GAP"));
      break;
    case SITUACAO_NAO_IMPORTANTE:
      Serial.println(F("SITUACAO_NAO_IMPORTANTE"));
      break;
    default:
    break;
  }

}
