float4 main(float4 pos_vertex : SV_Position) : SV_TARGET
{
    float1 length = sqrt(pow(pos_vertex.x, 2) + pow(pos_vertex.y, 2) + pow(pos_vertex.z, 2));
    float1 factor = 1.f / length;
    return float4(0.3f + 150.f * factor, 0.3f + 1.f * factor, 0.3f + 1.f * factor, 1.0f);
}