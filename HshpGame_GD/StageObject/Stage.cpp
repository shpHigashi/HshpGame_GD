#include "Stage.h"
#include "game.h"
#include "playerCube.h"

namespace
{
	//マップデータ
	// 1 ゴール / 2 ブロック / 3 ジャンプリング / 4 ジャンプパッド 
	// 5 スパイク / 6 グラビティリング / 7 グラビティパッド / 8  /

	// ステージ１
	int m_stage_first[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,0,0,0,0,4,0,2,0,0,0,0,0,2,2,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,5,5,0,2,0,0,0,0,0,2,0,0,0,0,0,0,2,2,2,0,0,0,0,0,3,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,3,0,0,0,0,0,0,2,2,2,2,2},
		{0,0,0,0,3,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,5,5,0,0,0,5,5,5,0,5,5,5,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0},
		{0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,4,0,0,0,0,5,0,0,0,0,4,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,5,0,4,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,1,0,5,0,0,0,2,2,2,2,2,2,2,2,2,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0},
		// ステージ地面
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
	};

	// ステージ２
	int m_stage_second[Game::kScreenHeightNum][Game::kScreenWidthNum] = {
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		// ステージ地面
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
	};
}

Stage::Stage() :
	m_pCube(nullptr),
	m_stage()
{

}

void Stage::Init(StageState stage)
{
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			m_ObjectGoalGate[i][j].Init();
			m_ObjectBlock[i][j].Init();
			m_ObjectJumpRing[i][j].Init();
			m_ObjectJumpPad[i][j].Init();
			m_ObjectSpike[i][j].Init();
			m_ObjectGravityRing[i][j].Init();
		}
	}

	SetStage(stage);
}

void Stage::SetStage(StageState stage)
{
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			if (stage == StageState::firstStage)
			{
				m_stage[i][j] = m_stage_first[i][j];
			}
			else if (stage == StageState::secondStage)
			{
				m_stage[i][j] = m_stage_second[i][j];
			}

			float blockPosX, blockPosY;
			blockPosX = j * Game::kBlockSize;
			blockPosY = i * Game::kBlockSize;

			if (m_stage[i][j] == 1) m_ObjectGoalGate[i][j].SetPos(blockPosX, blockPosY);
			if (m_stage[i][j] == 2) m_ObjectBlock[i][j].SetPos(blockPosX, blockPosY);
			if (m_stage[i][j] == 3) m_ObjectJumpRing[i][j].SetPos(blockPosX, blockPosY);
			if (m_stage[i][j] == 4) m_ObjectJumpPad[i][j].SetPos(blockPosX, blockPosY);
			if (m_stage[i][j] == 5) m_ObjectSpike[i][j].SetPos(blockPosX, blockPosY);
			if (m_stage[i][j] == 6) m_ObjectGravityRing[i][j].SetPos(blockPosX, blockPosY);
		}
	}
}

void Stage::Update()
{	
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			m_ObjectJumpRing[i][j].Update();
			m_ObjectGravityRing[i][j].Update();
		}
	}
}

void Stage::Draw()
{
	for (int i = 0; i < Game::kScreenHeightNum; i++)
	{
		for (int j = 0; j < Game::kScreenWidthNum; j++)
		{
			int drawPosX = 0, drawPosY = 0;
			drawPosX = static_cast<int>(j * Game::kBlockSize);
			drawPosY = static_cast<int>(i * Game::kBlockSize);
			
			// デバック用白線
			DrawBox(drawPosX, drawPosY, drawPosX + static_cast<int>(Game::kBlockSize), drawPosY + static_cast<int>(Game::kBlockSize), 0xFFFFFF, false);

			// ステージギミックの描画
			if (m_stage[i][j] == 1) m_ObjectGoalGate[i][j].Draw();
			if (m_stage[i][j] == 2) m_ObjectBlock[i][j].Draw();
			if (m_stage[i][j] == 3) m_ObjectJumpRing[i][j].Draw();
			if (m_stage[i][j] == 4) m_ObjectJumpPad[i][j].Draw();
			if (m_stage[i][j] == 5) m_ObjectSpike[i][j].Draw();
			if (m_stage[i][j] == 6) m_ObjectGravityRing[i][j].Draw();
		}
	}
}

// プレイヤーとオブジェクトの当たり判定チェック
bool Stage::CollisionCheck(Vec2 playerPos, int H, int W, ObjectType &object)
{
	if (m_stage[H][W] == 0) return false;

	// 当たっている場合、trueを返す
	// ブロックの当たり判定
	if (m_ObjectBlock[H][W].GetRight() >= playerPos.x &&
		playerPos.x + Game::kBlockSize >= m_ObjectBlock[H][W].GetLeft() &&
		m_ObjectBlock[H][W].GetBottom() >= playerPos.y &&
		playerPos.y + Game::kBlockSize >= m_ObjectBlock[H][W].GetTop())
	{
		object = ObjectType::Block;
		return true;
	}
	// ジャンプリングの当たり判定
	if (m_ObjectJumpRing[H][W].GetRight() >= playerPos.x &&
		playerPos.x + Game::kBlockSize >= m_ObjectJumpRing[H][W].GetLeft() &&
		m_ObjectJumpRing[H][W].GetBottom() >= playerPos.y &&
		playerPos.y + Game::kBlockSize >= m_ObjectJumpRing[H][W].GetTop())
	{
		object = ObjectType::JumpRing;
		return true;
	}
	// ジャンプパッドの当たり判定
	if (m_ObjectJumpPad[H][W].GetRight() - 5 > playerPos.x &&
		playerPos.x + Game::kBlockSize > m_ObjectJumpPad[H][W].GetLeft() + 5 &&
		m_ObjectJumpPad[H][W].GetBottom() > playerPos.y &&
		playerPos.y + Game::kBlockSize > m_ObjectJumpPad[H][W].GetTop() + Game::kBlockSize - (Game::kBlockSize / 4))
	{
		object = ObjectType::JumpPad;
		return true;
	}
	// スパイクの当たり判定
	if (m_ObjectSpike[H][W].GetRight() > playerPos.x &&
		playerPos.x + Game::kBlockSize > m_ObjectSpike[H][W].GetLeft() &&
		m_ObjectSpike[H][W].GetBottom() > playerPos.y &&
		playerPos.y + Game::kBlockSize > m_ObjectSpike[H][W].GetTop())
	{
		object = ObjectType::Spike;
		return true;
	}
	// グラビティリングの当たり判定
	if (m_ObjectGravityRing[H][W].GetRight() >= playerPos.x &&
		playerPos.x + Game::kBlockSize >= m_ObjectGravityRing[H][W].GetLeft() &&
		m_ObjectGravityRing[H][W].GetBottom() >= playerPos.y &&
		playerPos.y + Game::kBlockSize >= m_ObjectGravityRing[H][W].GetTop())
	{
		object = ObjectType::GravityRing;
		return true;
	}
	// ゴールゲートの判定
	if (m_ObjectGoalGate[H][W].GetRight() >= playerPos.x &&
		playerPos.x + Game::kBlockSize >= m_ObjectGoalGate[H][W].GetLeft() &&
		m_ObjectGoalGate[H][W].GetBottom() >= playerPos.y &&
		playerPos.y + Game::kBlockSize >= m_ObjectGoalGate[H][W].GetTop())
	{
		object = ObjectType::GoalGate;
		return true;
	}

	// 当たっていない場合、falseを返す
	return false;
}

// オブジェクトがプレイヤーの下にあるかどうか
bool Stage::IsUnder(Vec2 playerPos, float &tempPos,  int H, int W)
{	
	// ブロックが存在する場合
	if(m_stage[H][W] == 2)
	{
		if (!m_pCube->IsRevGravity())
		{
			// プレイヤーの中心、ブロックの上面での判定
			// 下にある場合、trueを返す
			if (m_ObjectBlock[H][W].GetPos().y > playerPos.y + (Game::kBlockSize / 2))
			{
				// ブロックの座標を代入
				tempPos = m_ObjectBlock[H][W].GetPos().y;
				return true;
			}
		}
		else
		{
			if (m_ObjectBlock[H][W].GetPos().y < playerPos.y + (Game::kBlockSize / 2))
			{
				// ブロックの座標を代入
				tempPos = m_ObjectBlock[H][W].GetPos().y + Game::kBlockSize;
				return true;
			}
		}
	}
	
	// 下ではない場合、falseを返す
	return false;
}
