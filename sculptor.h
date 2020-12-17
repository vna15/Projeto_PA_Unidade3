#ifndef SCULPTOR_H
#define SCULPTOR_H

#include <iostream>

/**
 * @brief O Voxel struct armazena os elementos necessários para criação de um bloco.
 *
 * @details O struct armazena, de forma dinâmica, as cores RGB, o índice de transparência alpha e a ativação, ou não, de um bloco.
 */
struct Voxel {
  float r,g,b; // Colors
  float a;
// Transparency
  bool isOn; // Included or not
};

/**
 * @brief A classe Sculptor serve para criar os voxels alocados dinamicamente.
 */
class Sculptor {
protected:
    /**
   * @brief v é o voxel.
   */
  Voxel ***v;
  // 3D matrix
  /**
   * @brief nx é o numero de voxels na direção x.
   * @brief ny é o número de voxels na direção y.
   * @brief nz é o número de voxels na direção z.
   */
  int nx,ny,nz; // Dimensions
  /**
   * @brief r, g e b são as cores RGB que o voxel(bloco) assume.
   * @brief a é a transpaência do bloco;
   */
  float r,g,b,a; // Current drawing color
public:
  /**
   * @brief Sculptor é o construtor da classe
   * @param _nx é o número de voxels a serem criados na direção x.
   * @param _ny é o número de voxels a serem criados na direção y.
   * @param _nz é o número de voxels a serem criados na direção z.
   */
  Sculptor(int _nx, int _ny, int _nz);
  ~Sculptor();
  /**
   * @brief setColor é a função para registrar as cores do voxel.
   * @param r é a taxa, entre 0 e 1, de cor vermelho que o voxel deve registrar.
   * @param g é a taxa, entre 0 e 1, de cor verde que o voxel deve registrar.
   * @param b é a taxa, entre 0 e 1, de cor azul que o voxel deve registrar.
   * @param alpha é a taxa, entre 0 e 1, de transparência que o voxel deve registrar.
   */
  void setColor(float r, float g, float b, float alpha);
  /**
   * @brief putVoxel é a funcão que cria o bloco.
   * @param x é a coordenada x do bloco.
   * @param y é a coordenada y do bloco.
   * @param z é a coordenada z do bloco.
   */
  void putVoxel(int x, int y, int z);
  /**
   * @brief cutVoxel é a função que inativa o bloco.
   * @details O bloco de coordenadas XYZ é desativado.
   */
  void cutVoxel(int x, int y, int z);
  /**
   * @brief putBox é uma função que cria um objeto retangular.
   * @param x0 é a coordenada incial na direção x.
   * @param x1 é a coordenada final na direção x.
   * @param y0 é a coordenada incial na direção y.
   * @param y1 é a coordenada final na direção y.
   * @param z0 é a coordenada incial na direção z.
   * @param z1 é a coordenada final na direção z.
   */
  void putBox(int x0, int x1, int y0, int y1, int z0, int z1);
  /**
   * @brief cutBox é a função que inativa um objeto retangular.
   * @details Dada as coordenadas iniciais e finais, o objeto é desativado.
   */
  void cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
  /**
   * @brief putSphere é uma função que cria um objeto esférico.
   * @param xcenter é a coordenada do centro da esfera na direção x.
   * @param ycenter é a coordenada do centro da esfera na direção y.
   * @param zcenter é a coordenada do centro da esfera na direção z.
   * @param radius é o raio da esfera.
   */
  void putSphere(int xcenter, int ycenter, int zcenter, int radius);
  /**
   * @brief cutSphere é a função que inativa um objeto esférico.
   * @details Dada as coordenadas do centro da esfera e o seu raio, o obejteo é desativado.
   */
  void cutSphere(int xcenter, int ycenter, int zcenter, int radius);
  /**
   * @brief putEllipsoid é a função que cria um objeto na forma de uma elipsoide.
   * @param xcenter é a coordenada do centro da elipsoide na direção x.
   * @param ycenter é a coordenada do centro da elipsoide na direção y.
   * @param zcenter é a coordenada do centro da elipsoide na direção z.
   * @param rx é o raio na direção x.
   * @param ry é o raio na direção y.
   * @param rz é o raio na direção z.
   */
  void putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  /**
   * @brief cutEllipsoid é a função que inativa um objeto na forma de uma elipsoide.
   * @details Dada as coordenadas do centro da elipsoide e os raios em cada direção, o objeto é desativado.
   */
  void cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
  /**
   * @brief writeOFF é a função que cria um arquivo.
   * @param filename é o nome do arquivo a ser criado.
   * @details Essa função serve para o usuário criar um arquivo .OFF que contém os elementos necessários para ser rodado em ferramentas de visualização.
   */
  void writeOFF(char* filename);

};

#endif // SCULPTOR_H

