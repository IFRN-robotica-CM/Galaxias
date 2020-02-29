
#include <Arduino.h>
#include "ControladorSensoresDeFaixa.h"

ControladorSensoresDeFaixa::ControladorSensoresDeFaixa() {
  sensor_refletancia_esquerdo_extremo = SensorDeRefletancia(A1);
  sensor_refletancia_esquerdo_centro  = SensorDeRefletancia(A2);
  sensor_refletancia_frontal          = SensorDeRefletancia(A3);
  sensor_refletancia_central          = SensorDeRefletancia(A4);
  sensor_refletancia_direito_centro   = SensorDeRefletancia(A5);
  sensor_refletancia_direito_extremo  = SensorDeRefletancia(A6);
  sensor_refletancia_traseiro         = SensorDeRefletancia(A7);
}

void ControladorSensoresDeFaixa::lerSensoresPrincipais() {
  see = sensor_refletancia_esquerdo_extremo.ler();
  sec = sensor_refletancia_esquerdo_centro.ler();
  sf  = sensor_refletancia_frontal.ler();
  sc  = sensor_refletancia_central.ler();
  sdc = sensor_refletancia_direito_centro.ler();
  sde = sensor_refletancia_direito_extremo.ler();
}

int ControladorSensoresDeFaixa::obterSituacaoAtual() {

  lerSensoresPrincipais();

  if (sf > limite) {

    if (see > _limite and sde > _limite and sc > _limite and sec > _limite and sdc > _limite) {
      return CRUZAMENTO_TOTAL;
    }

    else if (see > _limite and sde <= limite and sc > _limite and sec > _limite) {
      delay(5);

      see = sensor_refletancia_esquerdo_extremo.ler();
      sde = sensor_refletancia_direito_extremo.ler();

      if (see > _limite and sde > _limite) {
        return CRUZAMENTO_TOTAL;
        
      }

      return CRUZAMENTO_PARA_ESQUERDA;
    }

    else if (sde > _limite and see <= limite and sc > _limite and sdc > _limite) {
      delay(5);

      see = sensor_refletancia_esquerdo_extremo.ler();
      sde = sensor_refletancia_direito_extremo.ler();

      if (see > _limite and sde > _limite) {
        return CRUZAMENTO_TOTAL;
        
      }

      return CRUZAMENTO_PARA_DIREITA;
    }

    else if (see <= limite and sde <= limite and sec > limite and sc > _limite) {
      return CURVA_SIMPLES_PARA_ESQUERDA;
    }

    else if (see <= limite and sde <= limite and sdc > limite and sc > _limite) {
      return CURVA_SIMPLES_PARA_DIREITA;
    }

    else if (see <= limite and sde <= limite and sc > _limite and sec <= limite and sdc <= limite) {
      return LINHA_RETA;
    }

  }

  else {

    if (see > _limite and sde > _limite and sc > _limite and sec > _limite and sdc > _limite) {
      return T;
    }

    else if (see > _limite and sde <= limite and sc > _limite and sec > _limite) {
      delay(5);

      see = sensor_refletancia_esquerdo_extremo.ler();
      sde = sensor_refletancia_direito_extremo.ler();

      if (see > _limite and sde > _limite) {
        return T;
        
      }

      return CURVA_DE_90_GRAUS_PARA_ESQUERDA;
    }

    else if (sde > _limite and see <= limite and sc > _limite and sdc > _limite) {
      delay(5);

      see = sensor_refletancia_esquerdo_extremo.ler();
      sde = sensor_refletancia_direito_extremo.ler();

      if (see > _limite and sde > _limite) {
        return T;
        
      }

      return CURVA_DE_90_GRAUS_PARA_ESQUERDA;
    }

    else if (see <= limite and sde <= limite and sc > _limite and sec > limite and sdc > limite) {
      return ROTATORIA;
    }

    else if (see <= limite and sde <= limite and sec > limite and sc > _limite) {
      return CURVA_SIMPLES_PARA_ESQUERDA;
    }

    else if (see <= limite and sde <= limite and sdc > limite and sc > _limite) {
      return CURVA_SIMPLES_PARA_DIREITA;
    }
  }

  return GAP;
}
