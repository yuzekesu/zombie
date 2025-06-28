cbuffer something
{
    float4 colors[6];
};

float4 main( uint unique_id : SV_PrimitiveID ) : SV_TARGET
{
    return colors[unique_id / 2];
}