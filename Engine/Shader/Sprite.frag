#version 450 core

out vec4 FragColor;
  
in vec3 Color;
in vec2 TexCoord;

uniform bool useTexture;
uniform sampler2D mainTexture;

void main()
{
    if (useTexture) 
    {
        vec4 textureColor = texture(mainTexture, TexCoord);

        // Combine the texture color with the uniform color (using multiplication for blending)
        vec4 finalColor = textureColor * vec4(Color, 1.0);

        // Output the final color
        FragColor = finalColor;
    }
    else 
    {
        FragColor = vec4(Color, 1.0);
    }
}