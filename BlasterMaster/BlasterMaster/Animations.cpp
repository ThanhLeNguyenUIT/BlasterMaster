#include "Animations.h"
#include <cmath>

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, int alpha, int idFrame, bool renderOneFrame, bool rev )
{
	DWORD now = GetTickCount();
	if (!renderOneFrame) {
		if (currentFrame <= -1)
		{
			currentFrame = 0;
			lastFrameTime = now;
		}
		else
		{
			DWORD t = frames[currentFrame]->GetTime();
			if (now - lastFrameTime > t)
			{
				currentFrame++;
				lastFrameTime = now;
				if (currentFrame == frames.size())
				{
					if (!rev) {
						currentFrame = 0;
					}
					else
						currentFrame = frames.size() - 1;
					isLastFrame = true;
				}

			}
			else
			{
				isLastFrame = false;
				t += now - lastFrameTime;
			}
		}
	}
	else {
		currentFrame = idFrame;
		//DebugOut(L"curFrame %d", idFrame);
	}
	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

CAnimations* CAnimations::__instance = NULL;

CAnimations* CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}
void CAnimations::LoadResources()
{
	ifstream File;
	File.open(L"text\\animations.txt");
	vector<int> ParaAni;
	ParaAni.clear();
	vector<int>::iterator it;
	int reader;
	int time;
	while (!File.eof())
	{
		File >> reader;
		if (reader > -1)
		{
			ParaAni.push_back(reader);
		}
		else
		{
			LPANIMATION ani;
			if (reader < -1)
				ani = new CAnimation(abs(reader));
			else
				ani = new CAnimation(100);
			for (auto it = ParaAni.begin(); it != ParaAni.end() - 1; ++it)
				ani->Add(*it);
			it = ParaAni.end() - 1;
			Add(*it, ani);
			ParaAni.clear();
		}
	}
	File.close();
}
void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}




