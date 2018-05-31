#include "core/Application.h"
#include <iostream>
#include "Particule.h"




using namespace std;

#define drawOneLine(x1,y1,x2,y2) glBegin(GL_LINES); glVertex2f((x1),(y1)) ; glVertex2f((x2),(y2)) ; glEnd();

class Simulator: public Application
{
private:
    Program* program = NULL; // Prog pour le rendu
     Program* program2 = NULL; 
    Program* compute = NULL; // Prog pour le calcule //Avec les des prog on creer pipline de rendu et de calcule 
    Renderer* renderer = NULL; //le rendu est dans le buffer
    Renderer* cube = NULL;
    Computer* computer = NULL;
    Buffer* lines = NULL;
    Buffer* velocities = NULL;
    Particule *p=NULL;
    int nbParticule=64;
    
public:

    Simulator(int argc, char* argv[]);
    void update(int time); // methode qui met a jour les particules avec une temps de frame
    void render(); //methode de rendu
    void setup(); //libere la mémoire
    void teardown();
};

Simulator::Simulator(int argc, char* argv[]) : Application(argc, argv) {}

void Simulator::update(int elapsedTime)
{
	//appel le compute sheader, les calcule sont separer en morceau, la on a qu 1 morceau (les morceaux sont a des pos x,y,z)
    computer->compute(1, 1, 1);
}

void Simulator::render()
{
	//simple de faire des rendu avec des points
    // on indique le nombre de point qui va etre renderer
     renderer->render(PRIMITIVE_POINTS, nbParticule);
     cube->render(PRIMITIVE_LINES, 24);
}



void Simulator::setup()
{   
// dessin des lignes
float lineVec[] = {
// ligne haut 
    -10,4,0,
    10,4,0,

//ligne bas
    -10,-1,0,
    10,-0.2,0,

//ligne droite
    -10,4,0,
    -10,-1.1,0,

 //ligne gauche
    10,4,0,
    10,0,0,
    
// ligne diag g b
    10,0,12,
   10,0,0,

//ligne diag g h
    10,4,0,
    9,4,9,

//ligne b diag d
    -10,-1,0,
    -20,-0,4,

//ligne b diag d
    -10,4,0,
    -20,4,4,

//ligne x d
    -20,-0,4,
    -20,4,4,

//ligne x h
    9,4,9,
    -20,4,4,

//ligne x g
    9,4,9,
    9,0.5,9,

//ligne x b
    -20,0,4,
    9,0.5,9,

};

lines = new Buffer(lineVec, sizeof(lineVec));
//def couleur de fenetre - gris claire
    setClearColor(0.95f, 0.95f, 0.95f, 1.0f);

    p = new Particule(nbParticule); //Creation de l'objet Particule
    int taille = p->size_();
    program = new Program();
    program->addShader(Shader::fromFile("shaders/perspective.vert")); //Sert a afficher, on a besoin de 2 sheader vertex et fragment, 
	//ils sont créer a partir de l extension .vert .frag
    program->addShader(Shader::fromFile("shaders/black.frag"));
    program->link();


    program2 = new Program();
    program2->addShader(Shader::fromFile("shaders/perspective.vert")); //Sert a afficher, on a besoin de 2 sheader vertex et fragment, 
	//ils sont créer a partir de l extension .vert .frag
    program2->addShader(Shader::fromFile("shaders/lineColors.frag"));
    program2->link();

	//a partir d un rendu on creer un renderer, il faut encore ajouter des données d'entrer donc le plus simple c'est de faire comme sa
	// on porrait avoir un renderer par objet
    renderer = program->createRenderer();
    cube = program2->createRenderer();

	//doit mentionner le nom du vertexsheader et donnees buffer des particules, et l'organisation dans la structure
    renderer->setVertexData("vertex", p->getParticuleBuff(), TYPE_FLOAT, 0, 3, taille);
    cube->setVertexData("vertex", lines, TYPE_FLOAT, 0, 3, (sizeof(float)*3));


	//pr faire le rendu on a besoin de 2 matrice vu et perception-projection
    mat4 projection = perspective(90.0f, 640.0/480.0, 0.1, 500);
    // dans le lookat le 
    //1ere argu: la camera deplace autour du point centre change de cadrage
    // le 2eme: c'est pour la position de l'axe y de la camera
    //le 3 eme: c'est pour la profondeur de champ, au plus la valeur est petite au plus on dezomme
    mat4 view = lookat(vec3(-30, 5, -17), vec3(0, 5, 0), vec3(0, 10, 0));

	//nom de variable des sheader
    renderer->setMatrix("projectionMatrix", projection);
    renderer->setMatrix("modelViewMatrix", view);

    cube->setMatrix("projectionMatrix", projection);
    cube->setMatrix("modelViewMatrix", view);

	//prog pour mettre a jour
    compute = new Program();
    compute->addShader(Shader::fromFile("shaders/gravity.comp"));
    compute->link();

	//on peut avoir pluieurs prog de calcule
    computer = compute->createComputer();
    computer->setData(1, p->getParticuleBuff());


}

void Simulator::teardown()
{
   
}

int main(int argc, char** argv)
{
    try 
    {
        Simulator app = Simulator(argc, argv); 
	    return app.run();
    }
	catch(Exception e)
    {
        cout << e.getMessage() << endl;
        return 1;
    }
}