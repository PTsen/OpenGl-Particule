#version 430                  
//Calcule l'eclarage sur le pos de la lumiere
                                                                            
in vec3 vertexPos; //recois pose des vertex
in vec3 vertexNormal; // recois les normal de vertex, vect perpen a un somet de face = c'est la somme des toutes les normal 
//des 4 qui sont lier au point puis on normalise utilse pour l eclairage
//en calculant 3 faces opengl peut deja faire une interpolation des couleur
out vec3 frontColor;                                                             
uniform mat4 projectionMatrix;                                                                             
uniform mat4 modelMatrix; // faut tourner
uniform mat4 viewMatrix;// pos de camere
uniform vec3 lightPosition; // pos de lumiere

void main() {

    mat3 normalMatrix; 
	vec3 normal, lightDir;
    vec4 vertex;
	vec3 diffuse;
	float NdotL;

    normalMatrix = transpose(inverse(mat3(viewMatrix * modelMatrix))); // calculer l'orientation des normal dans l espace camera
	//en gardant les perpendiculaires (important de garder sinon sa marche pas)

	normal = normalize(normalMatrix * vertexNormal);
	
	
//calcule pos des vertex dans camera
    vertex = viewMatrix * modelMatrix * vec4( vertexPos.x, vertexPos.y, vertexPos.z, 1 );

//calcule vecteru vers la lumiere
	lightDir = normalize(mat3(viewMatrix) * lightPosition - vertexPos.xyz);
	
//calcule prod scalair entre normal et la lumiere ( vu que 2 vecteur) vecA*vecB = |vecA|*|VecB|*cos et on veut le cos
	NdotL = max(dot(normal, lightDir), 0.0);

//NdotL = dot(normal, lightDir);

//couleur qui est diffuser blanc
	diffuse = vec3(1.0, 1.0, 1.0);
	frontColor =  NdotL * diffuse;

	gl_Position = projectionMatrix * vertex;
}