#version 450 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture sampler
uniform sampler2D ourTexture1;

// Variaveis uniform com parâmetros para os exercicios
uniform int code;

void main()
{
    color = texture(ourTexture1, TexCoord);// * vec4(ourColor, 1.0);

    //Lembre-se: canais de cor está normalizado (entre 0.0 e 1.0)
    

    if (code == 1) //R
    { 
       color = vec4(color.r,color.r,color.r,color.a);
    }

    if (code == 2) //G
    { 
       color = vec4(color.g,color.g,color.g,color.a);
    }

    if (code == 3) //B
    { 
       color = vec4(color.b,color.b,color.b,color.a);
    }
    else
    {
    }


}