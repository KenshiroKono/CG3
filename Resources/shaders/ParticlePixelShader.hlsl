#include "ParticleShaderHeader.hlsli"

Texture2D<float4> tex : register(t0);  // 0番スロットに設定されたテクスチャ
SamplerState smp : register(s0);      // 0番スロットに設定されたサンプラー

float4 main(GSOutput input) : SV_TARGET
{

	return tex.Sample(smp, input.uv)*float4(0.5f,1.0f,1.0f,1.0f);
	//return float4(1, 1, 1, 1);
}