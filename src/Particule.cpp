#include "Particule.h"
#include <fstream>
#include <sstream>
#include <iostream>


Particule::Particule(int nb)
{
  
this->nb=nb;

Part pp[this->nb];
int i =0;

for(int j=0;j<4;j++){
        for (int k=0;k<4;k++){
            for (int l = 0;l<4;l++){
                pp[i] = Part(vec3(10-(j*0.5),k,l),vec3(1,0,0));
                i++;
            }
           
        }
    }

this->particules = new Buffer(pp, sizeof(pp));

}

int Particule::size_(){

    return sizeof(Part);

}


Particule::~Particule()
{
    
}

Buffer* Particule::getParticuleBuff(){

    return this->particules;

}
