#version 430 
in vec3 frontColor;
out vec3 Fragment;
void main()
{
	//recois la couleur et l'applique au sheaders
    //Fragment = vec4(gl_FragCoord.z, gl_FragCoord.z, gl_FragCoord.z, 1.0);
    Fragment = frontColor;
}