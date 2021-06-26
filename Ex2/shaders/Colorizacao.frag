#version 450 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture sampler
uniform sampler2D ourTexture1;
uniform vec3 corColorizadora;


void main()
{
    color = texture(ourTexture1, TexCoord);// * vec4(ourColor, 1.0);

    //Lembre-se: canais de cor está normalizado (entre 0.0 e 1.0)
    //exercicio 3: Colorização

    color = color + vec4(corColorizadora,0.0);
    
}