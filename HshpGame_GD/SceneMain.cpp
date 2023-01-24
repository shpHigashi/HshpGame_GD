#include "game.h"
#include "SceneMain.h"

namespace
{
	// 敵出現用の遅延時間
	constexpr int kSpawnDelay = 100;
	// ゲームの制限時間
	constexpr int kGameMaxTime = 1800;	
	// 死亡時の遅延
	constexpr int kGameOverDelay = 30;

	// 制限時間表示位置
	constexpr int kTimerPositionX = Game::kScreenWidthHalf - 30;
	constexpr int kTimerPositionY = Game::kStageLowerLimit + 25;

	// RGB初期値用
	constexpr int kSetColor = 255;
}

SceneMain::SceneMain() :
	countAttempt(0)
{
	m_hPlayerGraphic = -1;

	m_gameTimeRemaining = kGameMaxTime;
	m_GameOverDelay = kGameOverDelay;

	m_isGameClear = false;
	m_isEnd = false; 
}
SceneMain::~SceneMain()
{
}

// 初期化
void SceneMain::init()
{
	// 画像データの読み込み
	m_hPlayerGraphic = LoadGraph("imagedata/PlayerCubeMini.png");
	// プレイヤー初期化 
	m_cPlayer.Init(m_hPlayerGraphic);
	m_cPlayer.setStage(&m_Stage);

	m_Stage.Init();
	m_Stage.setPlayer(&m_cPlayer);

	// 各時間用変数の初期化
	m_gameTimeRemaining = kGameMaxTime;
	m_GameOverDelay = kGameOverDelay;

	// シーン終了、ゲームクリアを false に初期化
	m_isGameClear = false;
	m_isEnd = false;
}

// 終了処理
void SceneMain::end()
{
	// 画像データの削除
	DeleteGraph(m_hPlayerGraphic);
}

// 毎フレームの処理
void SceneMain::update(const InputState& input)
{	
	if (input.IsTriggered(InputType::enter))
	{
		countAttempt = 0;
		m_isEnd = true;
	}
	
	// Rキーを押すとゲームリトライ
	if (input.IsTriggered(InputType::retry))
	{
		init();
		countAttempt++;
	}

	// プレイヤーの死亡判定が true の場合
	if (m_cPlayer.IsDead())
	{
		if (m_GameOverDelay < 0)
		{
			init();
			countAttempt++;
			return;
		}
		// ゲームオーバー遅延を1フレームごとに減少させる
		m_GameOverDelay--;
		return;
	}

	m_Stage.Update();

	// プレイヤーの更新処理
	m_cPlayer.NormalUpdate(input);
}

// 毎フレームの描画
void SceneMain::draw()
{
	m_Stage.Draw();

	// プレイヤーの描画
	m_cPlayer.Draw();

	// フォントサイズ設定
	SetFontSize(Game::kFontSize);
	
	DrawFormatString(0, 50, 0xffffff, "Attempt : %d", countAttempt);
}
