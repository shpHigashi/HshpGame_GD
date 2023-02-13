#include "SceneTitle.h"
#include <DxLib.h>
#include "game.h"
#include "SceneManager.h"
#include "SceneMain.h"

namespace
{
	// タイトルメッセージ
	const char* const kGameTitle = "SquareJumper";
	const char* const kTitleMessage = "ENTER to Select";

	// メニューメッセージ
	const char* const kChallengeModeText = "WtfChallengeMode";
	const char* const kStageSelectText = "StageSelect";
	const char* const kHelpText = "How to Play";
	const char* const kRankText = "Ranking";
	const char* const kGameEndText = "Exit";

	// メニューの選択項目の数
	constexpr int kMenuMax = 5;

	// メニューのサイズ
	constexpr int kLeftMenuX = Game::kScreenWidthHalf - 200;
	constexpr int kMenuY = Game::kScreenHeightHalf - 100;

	constexpr int kMenuW = 400;
	constexpr int kMenuH = 60;
}

// 初期化
void SceneTitle::Init()
{
	// 画像データの読み込み
	// ゲームタイトル
	m_hBg = LoadGraph("imagedata/GDbg.jpg");

	// シーン終了に false を代入
	m_isEnd = false;

	m_textScroll = -Game::kScreenWidth;
	m_selectPos = 0;
	m_textTimer = 10;
	m_scroll = 0;
	m_scrollAcc = 7;
	m_fadeCount = 0;

	m_scroll = m_pStageSelect->GetScroll();

	m_updateFunc = &SceneTitle::SceneStartUpdate;
	if (m_pManager->GetLastScene() != SceneManager::kSceneStageSelect)
	{
		m_fadeCount = 255;
		m_textScroll = 0;
	}
}

// 終了処理
void SceneTitle::End()
{
	DeleteGraph(m_hBg);
}

// 更新処理
void SceneTitle::Update(const InputState& input, bool &isGameEnd, NextSceneState &nextScene, bool& isPrac)
{	
	if (m_textTimer > 1000) m_textTimer = 10;

	(this->*m_updateFunc)(input, isGameEnd, nextScene, isPrac);
}

// 描画処理
void SceneTitle::Draw()
{
	int bgX = 0, bgY = 0, bgW = Game::kScreenWidth, bgH = Game::kScreenHeight;
	bgX -= m_scroll, bgW -= m_scroll;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 75);
	DrawExtendGraph(bgX, bgY, bgW, bgH, m_hBg, true);
	DrawExtendGraph(bgX + Game::kScreenWidth, bgY, bgW + Game::kScreenWidth, bgH, m_hBg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(60);
	DrawString((Game::kScreenWidth / 2) - GetDrawStringWidth(kGameTitle, 6) + m_textScroll, Game::kScreenHeight / 4, kGameTitle, 0xff4500);

	// フォントサイズの設定
	SetFontSize(30);
	if (m_textTimer > 0)
	{		
		if ((m_textTimer / 10) % 4 != 0)
		{
			// タイトルのテキストを表示
			DrawString(Game::kScreenWidth / 2 - GetDrawStringWidth(kTitleMessage, 7) + m_textScroll, Game::kScreenHeightHalf + 300, kTitleMessage, 0xffffff);
		}

		m_textTimer++;
	}

	int menuX = kLeftMenuX, menuY = kMenuY, menuW = kLeftMenuX + kMenuW, menuH = kMenuY + kMenuH;
	
	for (int i = 0; i < kMenuMax; i++)
	{
		menuY = kMenuY + (kMenuH * i) + 10;
		DrawBox(menuX + m_textScroll, menuY, menuW + m_textScroll, menuH + (kMenuH * i), 0xffffff, false);

		// フォントサイズの設定
		SetFontSize(20);

		menuY = menuY + (kMenuH / 2) - 15;

		if (i == 0) DrawString(menuX + 20 + m_textScroll, menuY, kChallengeModeText, 0xffffff);
		if (i == 1) DrawString(menuX + 20 + m_textScroll, menuY, kStageSelectText, 0xffffff);
		if (i == 2) DrawString(menuX + 20 + m_textScroll, menuY, kHelpText, 0xffffff);
		if (i == 3) DrawString(menuX + 20 + m_textScroll, menuY, kRankText, 0xffffff);
		if (i == 4) DrawString(menuX + 20 + m_textScroll, menuY, kGameEndText, 0xffffff);
	}

	menuY = kMenuY + (kMenuH * m_selectPos) + 10;
	DrawBox(menuX + m_textScroll, menuY, menuW + m_textScroll, menuH + (kMenuH * m_selectPos), 0xff0000, false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeCount);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTitle::NormalUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac)
{
	if (m_scroll > Game::kScreenWidth)
	{
		m_scroll = 0;
	}

	m_scroll += m_scrollAcc;

	if (input.IsTriggered(InputType::escape))
	{
		isGameEnd = true;
		return;
	}

	// キー入力があった場合、シーン終了を true にする
	if (input.IsTriggered(InputType::enter))
	{
		switch (m_selectPos)
		{
		case 0:
			m_updateFunc = &SceneTitle::SceneEndUpdate;
			nextScene = NextSceneState::nextGameMain;
			isPrac = false;
			return;
		case 1:
			m_updateFunc = &SceneTitle::SceneEndUpdate;
			nextScene = NextSceneState::nextStageSelect;
			isPrac = true;
			return;
		case 2:
			m_updateFunc = &SceneTitle::SceneEndUpdate;
			nextScene = NextSceneState::nextHelp;
			return;
		case 3:
			m_updateFunc = &SceneTitle::SceneEndUpdate;
			nextScene = NextSceneState::nextRanking;
			return;
		case 4:
			isGameEnd = true;
			return;
		default:
			break;
		}
	}

	if (input.IsTriggered(InputType::down))
	{
		m_selectPos++;
	}
	if (input.IsTriggered(InputType::up))
	{
		m_selectPos--;
	}

	if (m_selectPos > 4) m_selectPos = 0;
	if (m_selectPos < 0) m_selectPos = 4;
}

void SceneTitle::SceneStartUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac)
{
	if (m_scroll > Game::kScreenWidth)
	{
		m_scroll = 0;
	}

	m_scroll += m_scrollAcc;
	
	if (m_pManager->GetLastScene() == SceneManager::kSceneStageSelect)
	{
		m_textScroll += 100;

		if (m_textScroll > 0)
		{
			m_textScroll = 0;
			m_updateFunc = &SceneTitle::NormalUpdate;
		}
	}
	else
	{
		m_fadeCount -= 5;

		if (m_fadeCount < 0)
		{
			m_fadeCount = 0;
			m_updateFunc = &SceneTitle::NormalUpdate;
		}
	}
}

void SceneTitle::SceneEndUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac)
{
	if (m_scroll > Game::kScreenWidth)
	{
		m_scroll = 0;
	}

	if (nextScene == NextSceneState::nextStageSelect)
	{
		m_textScroll -= 100;

		if (m_textScroll < -Game::kScreenWidth)
		{
			m_isEnd = true;
		}
	}
	else
	{
		m_fadeCount += 5;

		if (m_fadeCount > 255)
		{
			m_isEnd = true;
		}
	}

	m_scroll += m_scrollAcc;
}
