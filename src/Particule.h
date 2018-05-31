#ifndef PARTICULE_H
#define PARTICULE_H

#include "core/vmath.h"
#include "string"
#include "core/opengl.h"
#include <vector>
#include "core/Buffer.h"

using namespace std;
using namespace vmath;

struct Part
{
    vec4 position;
    vec4 velocity;
    Part(vec3 pos, vec3 vel)
    {
        position = vec4(pos[0], pos[1], pos[2], 1.0f);
        velocity = vec4(vel[0], vel[1], vel[2], 1.0f);
    }
    Part()
    {
        position = vec4(0, 0, 0, 1.0f);
        velocity = vec4(0, 0, 0, 1.0f);
    }

};

class Particule
{
private:
    int nb;
    Buffer* particules;
public:
    Particule(int nb);
    ~Particule();
    int size_();
    Buffer* getParticuleBuff();
    
};

#endif