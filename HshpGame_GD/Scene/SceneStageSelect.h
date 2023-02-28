#pragma once
#include "SceneBase.h"
#include "InputState.h"
#include "game.h"

class SceneMain;
class SceneManager;
class SceneTitle;

class SceneStageSelect : public SceneBase
{
public:
	SceneStageSelect() :
		m_updateFunc(&SceneStageSelect::SceneStartUpdate),
		m_selectPos(0),
		m_textTimer(0),
		m_fadeCount(0),
		m_isEnd(false),
		m_hBg(-1),
		m_textScroll(0),
		m_scroll(0),
		m_scrollAcc(0),
		m_pMain(nullptr),
		m_pManager(nullptr),
		m_pTitle(nullptr)
	{
	}
	virtual ~SceneStageSelect() {}

	void SetMain(SceneMain* main) { m_pMain = main; }
	void SetManager(SceneManager* manager) { m_pManager = manager; }
	void SetTitle(SceneTitle* title) { m_pTitle = title; }

	// 初期化
	virtual void Init(bool& isPrac);

	// 終了処理
	void End();

	// 更新処理
	void Update(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);
	// 描画
	void Draw();

	// m_isEnd を取得
	bool IsEnd() const { return m_isEnd; }

	int GetScroll()const { return m_scroll; }

private:
	using m_tUpdateFunc = void (SceneStageSelect::*) (const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);
	m_tUpdateFunc m_updateFunc = nullptr;

	void NormalUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);

	void SceneStartUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);

	void SceneEndUpdate(const InputState& input, bool& isGameEnd, NextSceneState& nextScene, bool& isPrac);
private:
	// メニュー選択
	int m_selectPos;

	int m_textTimer;

	int m_fadeCount;
	// タイトル表示を終えるかどうか
	bool m_isEnd;

	// 画像データ
	int m_hBg;

	int m_textScroll;

	int m_scroll;
	int m_scrollAcc;

	SceneMain* m_pMain;
	SceneManager* m_pManager;
	SceneTitle* m_pTitle;
};