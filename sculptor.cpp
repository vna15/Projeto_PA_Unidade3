#include "sculptor.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <cstdlib>

using namespace std;


Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
      nx = _nx;
      ny = _ny;
      nz = _nz;


      v = new Voxel**[nx];
      for(int i=0;i<nx;i++){
          v[i] = new Voxel*[ny];
          for(int j=0;j<ny;j++){
              v[i][j] = new Voxel[nz];
          }
      }

}

Sculptor::~Sculptor()
{
    if(nx == 0 || ny == 0|| nz == 0){
         return;
    }
   delete[] v[0][0];
   delete[] v[0];
   delete[] v;
}

void Sculptor::setColor(float r, float g, float b, float alpha)
{
         this -> r=r;

         this -> g=g;

         this -> b=b;

         a=alpha;
}

void Sculptor::putVoxel(int x, int y, int z)
{
     v[x][y][z].isOn = true;
     v[x][y][z].r = r;
     v[x][y][z].g = g;
     v[x][y][z].b = b;
     v[x][y][z].a = a;

}

void Sculptor::cutVoxel(int x, int y, int z)
{
     v[x][y][z].isOn = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
     for(int i=x0;i<=x1;i++){
         for(int j=y0;j<=y1;j++){
             for(int k=z0;k<=z1;k++){
                 putVoxel(i,j,k);
             }
         }
     }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
    for(int i=x0;i<=x1;i++){
        for(int j=y0;j<=y1;j++){
            for(int k=z0;k<=z1;k++){
                cutVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    for(int i=xcenter-radius;i<=xcenter+radius;i++){
        for(int j=ycenter-radius;j<=ycenter+radius;j++){
            for(int k=zcenter-radius;k<=zcenter+radius;k++){
                if((pow(i-xcenter,2) + pow(j-ycenter,2) + pow(k-zcenter,2))<=(pow(radius,2))){
                    putVoxel(i,j,k);
                }
            }
       }
   }



}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
    for(int i=xcenter-radius;i<=xcenter+radius;i++){
        for(int j=ycenter-radius;j<=ycenter+radius;j++){
            for(int k=zcenter-radius;k<=zcenter+radius;k++){
                if((pow(i-xcenter,2) + pow(j-ycenter,2) + pow(k-zcenter,2))<=(pow(radius,2))){
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
      for(int i=xcenter-rx;i<=xcenter+rx;i++){
          for(int j=ycenter-ry;j<=ycenter+ry;j++){
              for(int k=zcenter-rz;k<=zcenter+rz;k++){
                  if((pow(i-xcenter,2)/pow(rx,2)) + (pow(j-ycenter,2)/pow(ry,2)) + (pow(k-zcenter,2)/pow(rz,2)) <= 1){
                      putVoxel(i,j,k);
                  }
              }
          }
      }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
    for(int i=xcenter-rx;i<=xcenter+rx;i++){
        for(int j=ycenter-ry;j<=ycenter+ry;j++){
            for(int k=zcenter-rz;k<=zcenter+rz;k++){
                if((pow(i-xcenter,2)/pow(rx,2)) + (pow(j-ycenter,2)/pow(ry,2)) + (pow(k-zcenter,2)/pow(rz,2)) <= 1){
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::writeOFF(char* filename)
{
      std::ofstream fout;
      std::fixed(fout);
      char *nomeArq;
            nomeArq = filename;
            fout.open(nomeArq);

      if(!fout.is_open()){
          exit(0);
      }

      fout << "OFF\n";

      int numBlocosON = nx*ny*nz;

      for(int i=0;i<nx;i++){
          for(int j=0;j<ny;j++){
              for(int k=0;k<nz;k++){
                  if(v[i][j][k].isOn==false){
                      numBlocosON--;
                  }
              }
          }
      }

      fout << numBlocosON*8 << " " << numBlocosON*6 << " " << 0 << endl;

           for(int i=0;i<nx;i++){
                for(int j=0;j<ny;j++){
                    for(int k=0;k<nz;k++){
                        if(v[i][j][k].isOn==false){

                        }else{
                            fout << k-0.5 << " " << j+0.5 << " " << i-0.5 << endl;
                            fout << k-0.5 << " " << j-0.5 << " " << i-0.5 << endl;
                            fout << k+0.5 << " " << j-0.5 << " " << i-0.5 << endl;
                            fout << k+0.5 << " " << j+0.5 << " " << i-0.5 << endl;
                            fout << k-0.5 << " " << j+0.5 << " " << i+0.5 << endl;
                            fout << k-0.5 << " " << j-0.5 << " " << i+0.5 << endl;
                            fout << k+0.5 << " " << j-0.5 << " " << i+0.5 << endl;
                            fout << k+0.5 << " " << j+0.5 << " " << i+0.5 << endl;
                        }
                    }
                }
            }

           int cont = 0;
           for(int i=0;i<nx;i++){
                for(int j=0;j<ny;j++){
                    for(int k=0;k<nz;k++){
                        if(v[i][j][k].isOn==false){

                        }else{
                            int pv = 8*cont;
                            fout << "4" << " " << pv << " " << pv+3 << " " << pv+2 << " " << pv+1 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                            fout << "4" << " " << pv+4 << " " << pv+5 << " " << pv+6 << " " << pv+7 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                            fout << "4" << " " << pv << " " << pv+1 << " " << pv+5 << " " << pv+4 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                            fout << "4" << " " << pv << " " << pv+4 << " " << pv+7 << " " << pv+3 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                            fout << "4" << " " << pv+3 << " " << pv+7 << " " << pv+6 << " " << pv+2 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                            fout << "4" << " " << pv+1 << " " << pv+2 << " " << pv+6 << " " << pv+5 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                            cont++;
                        }
                    }
                }
            }


            fout.close();


}







