/*============================================================================*/
/* ICSF13 - 2026-2 - TRABALHO 1                                               */
/*----------------------------------------------------------------------------*/
/* Diego Soares                                                               */
/*============================================================================*/

#include <math.h>
#include <float.h>
#include "trabalho1.h"

int calculaInterseccao (int n_retangulos){
    // Declara as variáveis das coordenadas do primeiro retângulo
    int xSE, ySE;
    int xID, yID;

    // Declara a versão atual para fazer as comparações
    int xSE_atual, ySE_atual;
    int xID_atual, yID_atual;

    // Declaração do i
    int i;

    // Testando se a quantidade de retângulos é válida
    if (n_retangulos <= 0)
        return 0;

    // Inicialização das variáveis
    xSE = pegaXSE(0);
    ySE = pegaYSE(0);
    xID = pegaXID(0);
    yID = pegaYID(0);

    // Testa o primeiro
    if (xSE >= xID || yID >= ySE)
        return 0;

    // Iteração pela quantidade de retângulos
    for (i = 1; i < n_retangulos; i++){
        // Pega os valores do retângulo i
        xSE_atual = pegaXSE(i);
        ySE_atual = pegaYSE(i);
        xID_atual = pegaXID(i);
        yID_atual = pegaYID(i);

        // Verifica a interseção no ponto superior esquerdo
        if (xSE < xSE_atual)
            xSE = xSE_atual;
        if (ySE > ySE_atual)
            ySE = ySE_atual;

        // Verifica a interseção no ponto inferior direito
        if (xID > xID_atual)
            xID = xID_atual;
        if (yID < yID_atual)
            yID = yID_atual;

        // Verificação se a largura ou a altura é 0
        if (xSE >= xID || yID >= ySE)
            return 0;
    }

    // Retorna a área
    return (xID - xSE) * (ySE - yID);
}

unsigned int encontraParMaisProximo (int n_retangulos){
    // Declara a distância, índices e centros
    float distancia, menorDistancia = FLT_MAX;
    float xCi, yCi, xCj, yCj;
    int id1 = 0, id2 = 0;
    int i, j;

    // Testando se a quantidade de retângulos é válida
    if (n_retangulos < 2)
        return 0;

    // Iteração pelos pares de retângulos
    for (i = 0; i < n_retangulos - 1; i++){
        // Coordenadas e centro do retângulo i
        xCi = (pegaXSE(i) + pegaXID(i)) / 2.0;
        yCi = (pegaYSE(i) + pegaYID(i)) / 2.0;

        for (j = i + 1; j < n_retangulos; j++){
            // Coordenadas e centro do retângulo j
            xCj = (pegaXSE(j) + pegaXID(j)) / 2.0;
            yCj = (pegaYSE(j) + pegaYID(j)) / 2.0;

            // Calcula os catetos
            dx = xCi - xCj;
            dy = yCi - yCj;

            // Calcula a distância entre os dois centros
            distancia = sqrt(dx * dx + dy * dy);

            if (distancia < menorDistancia){
                menorDistancia = distancia;

                // i é sempre menor que j
                id1 = i;
                id2 = j;
            }
        }
    }

    // Retorna os índices
    return (id1 << 16) | id2;
}
