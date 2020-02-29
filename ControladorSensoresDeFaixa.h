
#ifndef ControladorSensoresDeFaixa_h
#define ControladorSensoresDeFaixa_h

#include <Arduino.h>
#include "CosmosNV2.h"

#define CRUZAMENTO_TOTAL                1
#define CRUZAMENTO_PARA_ESQUERDA        2
#define CRUZAMENTO_PARA_DIREITA         3
#define CURVA_SIMPLES_PARA_ESQUERDA     4
#define CURVA_SIMPLES_PARA_DIREITA      5
#define LINHA_RETA                      6
#define T                               7
#define CURVA_DE_90_GRAUS_PARA_ESQUERDA 8
#define CURVA_DE_90_GRAUS_PARA_DIREITA  9
#define ROTATORIA                       10
#define GAP                             11

class ControladorSensoresDeFaixa
{
  public:
    ControladorSensoresDeFaixa();
    int obterSituacaoAtual();
    SensorDeRefletancia sensor_refletancia_frontal;
    SensorDeRefletancia sensor_refletancia_traseiro;
  private:
    void lerSensoresPrincipais();

    int see = 0;
    int sec = 0;
    int sf  = 0;
    int sc  = 0;
    int sdc = 0;
    int sde = 0;

    const int _limite = 500;
    const int  limite = 150;

    SensorDeRefletancia sensor_refletancia_esquerdo_extremo;
    SensorDeRefletancia sensor_refletancia_esquerdo_centro;
    SensorDeRefletancia sensor_refletancia_central;
    SensorDeRefletancia sensor_refletancia_direito_centro;
    SensorDeRefletancia sensor_refletancia_direito_extremo;
};

#endif