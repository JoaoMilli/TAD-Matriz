/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   matriz.c
 * Author: joao
 * 
 * Created on 22 de março de 2020, 18:22
 */

#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

struct matriz{
    int nlinhas;
    int ncolunas;
    int** pointer;
};

Matriz* inicializaMatriz (int nlinhas, int ncolunas){
    
    Matriz* mat;
    
    if(nlinhas < 0 || ncolunas < 0){
        return mat;
    }   
    mat = (Matriz*) malloc (sizeof(Matriz));
    
    if(mat == NULL) return mat;
    
    mat-> pointer = (int**) malloc (sizeof(int*) * nlinhas);
    
    if(mat-> pointer == NULL){
        free(mat);
        return mat;
    }    
    int i, count = 0;
    
    for(i=0; i < nlinhas; i++){
        mat-> pointer[i] = (int*) malloc (sizeof(int) * ncolunas);
        if(mat-> pointer[i] == NULL){
            while(count > 0){
                free(mat-> pointer[count]);
                count--;
            }
            free(mat);
            return mat;
        }
        count++;
    }   
    mat-> ncolunas = ncolunas;
    mat-> nlinhas = nlinhas;
    
    return mat;
    
}

void modificaElemento (Matriz* mat, int linha, int coluna, int elem){
    
    if((mat == NULL) || (mat-> ncolunas < 1) || (mat-> nlinhas < 1)) return;  
    if(linha > (mat-> nlinhas - 1) || coluna > (mat-> ncolunas - 1)) return;
    
    mat-> pointer[linha][coluna] = elem;
    
}

int recuperaElemento(Matriz* mat, int linha, int coluna){
    
    if((mat == NULL) || (mat-> ncolunas < 1) || (mat-> nlinhas < 1)) return 0;  
    if(linha > (mat-> nlinhas - 1) || coluna > (mat-> ncolunas - 1)) return 0;
    
    return (mat-> pointer[linha][coluna]);
}

int recuperaNColunas (Matriz* mat){
    
    if(mat == NULL) return 0;
    
    return (mat-> ncolunas);
}

int recuperaNLinhas (Matriz* mat){
    
    if(mat == NULL) return 0;
    
    return (mat-> nlinhas);
}

Matriz* transposta (Matriz* mat){
    
    if(mat == NULL) return mat;
    
    Matriz* tmat;
    
    tmat = inicializaMatriz (mat-> ncolunas, mat-> nlinhas);
    
    if(tmat == NULL){
        return tmat;
    }
    
    int i, j;
    for(i=0; i < (mat-> nlinhas); i++){
        for(j=0; j < (mat-> ncolunas); j++){
            tmat-> pointer[j][i] = mat-> pointer[i][j];
        }
    }
    
    return tmat;
}

Matriz* multiplicacao (Matriz* mat1, Matriz* mat2){
    
    if(mat1 == NULL) return mat1;
    if(mat2 == NULL) return mat2;
    
    if((mat1-> nlinhas) != (mat2-> ncolunas)) return mat1;
    
    Matriz* mtmat;
    
    mtmat = inicializaMatriz (mat1-> nlinhas, mat2-> ncolunas);
    
    if(mtmat == NULL){
        return mtmat;
    }
    int i, j, k, num = 0;
    
    for(k=0; k < (mat2-> ncolunas); k++){
        for(i=0; i < (mat1-> nlinhas); i++){
            for(j=0; j < (mat1 -> ncolunas); j++){
                num = num + (mat1-> pointer[i][j] * mat2-> pointer[j][k]);
            }
            mtmat-> pointer[i][k] = num;
            num = 0;
        }
    }
    return mtmat;
}

void imprimeMatriz(Matriz* mat){
    
    if(mat == NULL) return;
    
    int i, j, l, c, elem;
    l = mat-> nlinhas;
    c = mat-> ncolunas;
    
    for(i=0; i < l; i++){
        for(j=0; j < c; j++){
            elem = mat-> pointer[i][j];
            printf(" %d", elem);
        }
        printf("\n");
    }
}

void destroiMatriz(Matriz* mat){
    
    if(mat == NULL) return;
    
    int i;
    
    if(mat-> pointer != NULL){
        for(i=0; i < mat-> nlinhas; i++){
            free(mat-> pointer[i]);
        }
        free(mat-> pointer);
    }
    free(mat);
}