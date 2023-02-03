#pragma once

enum class InputType
{
	enter, // 次へ行くボタン
	space,
	pause, // ポーズボタン
	right,	// 右
	left,	// 左
	up,		// 上
	down,	// 下
	jump,
	retry,
	end
};

class InputState
{
private:
	char keyMouseState[256];
	char lastKeyMouseState[256];
	char keyState[256];
	char lastKeyState[256];

public:
	bool IsTriggered(InputType type)const;
	bool IsPressed(InputType type)const;
	void Update();
};