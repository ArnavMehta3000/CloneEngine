struct VSOutput
{
    noperspective float4 Position : SV_Position;
    noperspective float2 UV :  TEXCOORD;
}

VSOutput FullScreenTriangleVS(int uint VertexId : SV_VertexID)
{
    VSOutput output{}

    output.Position = float4(0, 0, 0, 1);
    output.UV = float2(0, 0);
    
    return output;
}