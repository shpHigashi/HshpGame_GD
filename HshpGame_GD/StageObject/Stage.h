#pragma once

#include "Game.h"
#include "ObjectBlock.h"
#include "ObjectSpike.h"
#include "ObjectJumpRing.h"
#include "ObjectJumpPad.h"
#include "ObjectGravityRing.h"
#include "ObjectGoalGate.h"

class PlayerCube;

enum class StageState
{
	firstStage,
	secondStage,
	thirdStage,
	End
};

class Stage
{
public:
	Stage();
	~Stage(){}
	
	void setPlayer(PlayerCube* cube) { m_pCube = cube; }
	
	void Init();

	void SetStage();

	void Update();

	void Draw();

	bool CollisionCheck(Vec2 playerPos, int H, int W, ObjectType &object);

	bool IsUnder(Vec2 playerPos, float &tempPos, int Y, int X);

	// 各ステージのセット
	void SetSecondStage() { m_stageState = StageState::secondStage; }
	void SetThirdStage() { m_stageState = StageState::thirdStage; }

	//ステージの状態を確保
	StageState GetStageState() { return m_stageState; }

private:
	ObjectBlock m_ObjectBlock[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectSpike m_ObjectSpike[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectJumpRing m_ObjectJumpRing[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectJumpPad m_ObjectJumpPad[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectGravityRing m_ObjectGravityRing[Game::kScreenHeightNum][Game::kScreenWidthNum];
	ObjectGoalGate m_ObjectGoalGate[Game::kScreenHeightNum][Game::kScreenWidthNum];

	PlayerCube* m_pCube;

	// ステージ管理用変数
	StageState m_stageState;
	// ステージ管理用二次元配列
	int m_stage[Game::kScreenHeightNum][Game::kScreenWidthNum];
};

