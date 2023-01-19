#pragma once

#include "Game.h"
#include "ObjectBlock.h"

namespace
{
	constexpr int kBlockMax = 30;
}

class Stage
{
public:
	Stage();
	~Stage(){}

	void Init();
	
	void Update();

	void Draw();

	bool CollisionCheck(Vec2 playerPos);

	//bool IsHit() { return isHit; }
private:
	//bool isHit;
	
	// �u���b�N���W
	Vec2 m_pos[kBlockMax];
	Vec2 m_vec;
	
	//int m_stage[40];

	ObjectBlock m_Object;
};
