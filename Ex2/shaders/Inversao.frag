#version 450 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture sampler
uniform sampler2D ourTexture1;



void main()
{
    color = texture(ourTexture1, TexCoord);// * vec4(ourColor, 1.0);

    //Lembre-se: canais de cor est� normalizado (entre 0.0 e 1.0)
    //exercicio 4: inversao

    color = vec4(1.0 - color.rgb ,color.a);
    
}