//GLOBALS
Texture2D shaderTexture;
SamplerState SampleType;

//BUFFERS
cbuffer LightBuffer
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 lightDirection;
	float specularPower;
	float4 specularColor;
};
cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};
cbuffer CameraBuffer
{
	float3 cameraPosition;
	float padding;
}

//INPUT
struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};
struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 viewDirection : TEXCOORD1;
};

//PIXEL SHADER
float4 PS(PixelInputType input) : SV_TARGET
{
	float4 textureColor;
	float3 lightDir;
	float lightIntensity;
	float4 color;
	float3 reflection;
	float4 specular;

	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = shaderTexture.Sample(SampleType, input.tex);

	// Set the default color to the ambient light value for all pixels
	color = ambientColor;

	// Initialize the specular color.
	specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// Invert the light direction for calculations.
	lightDir = -lightDirection;

	// Calculate the amount of light on this pixel.
	lightIntensity = saturate(dot(input.normal, lightDir));

	//Calculate if N dot L > 0.  If it is, then add the diffuse color to the ambient color
	if (lightIntensity > 0.0f)
	{
		// Determine the final diffuse color based on the diffuse color and the amount of light intensity.
		color += (diffuseColor * lightIntensity);

		// Saturate the ambient and diffuse colors.
		color = saturate(color);

		// Calculate the reflection vector.
		reflection = normalize(2 * lightIntensity * input.normal - lightDir);

		// Determine the amount of specular light
		specular = pow(saturate(dot(reflection, input.viewDirection)), specularPower);
	}

	// Multiply the texture pixel and the final diffuse color to get the final pixel color result.
	color = color * textureColor;

	//Make sure to saturate since combination could have been more than 1.
	//Add the specular component to the last output color.
	color = saturate(color + specular);

	return color;
}

//VERTEX SHADER
PixelInputType VS(VertexInputType input)
{
	PixelInputType output;
	float4 worldPosition;

	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;

	// Calculate the normal vector against the world matrix only.
	output.normal = mul(input.normal, (float3x3)worldMatrix);

	// Normalize the normal vector.
	output.normal = normalize(output.normal);

	// Calculate the position of the vertex in the world.
	worldPosition = mul(input.position, worldMatrix);

	// Determine the viewing direction based on the position of the camera and the position of the vertex in the world.
	output.viewDirection = cameraPosition.xyz - worldPosition.xyz;

	// Normalize the viewing direction vector.
	output.viewDirection = normalize(output.viewDirection);

	return output;
}