#include "PlayerStats.h"
#include "UIHelpers.h"


void PlayerStats::Draw()
{
	const float t = m_pTimer->GetTime();
	
	//Get a width that is 100 + sin(t)
	float width = 100.0f + sin(t * 5.0f) * 50.0f;
	printf("%f\n", width);
	
	UIHelpers::DrawRectangle(Vector2(100.0, 100.0), Vector2(width, 50.0), Vector4(1.0, 0.0, 0.0, 1.0));
	UIHelpers::DrawSprite(eSprite::Health_Pip, Vector2(100.0, 100.0));
}