cbuffer transformM
{
    matrix transform;
};

float4 main( float3 pos : POSITION ) : SV_POSITION
{
    return mul(float4(pos.x, pos.y, pos.z, 1.0f), transform);
}