#include "game.h"

class HowToStage;

enum class PlayerState
{
	Cube,
};

class HowToPlayer
{
public:
	HowToPlayer() :
		m_playerState(PlayerState::Cube),
		m_pHStage(nullptr),
		m_updateFunc(&HowToPlayer::CubeNormalUpdate),
		m_pos(),
		m_vec(),
		m_lastPos(),
		m_hPlayer(-1),
		m_hWaveBurner(-1),
		m_hDeathEffect(-1),
		m_hDeathSound(-1),
		m_playerScale(0.0),
		m_effectHeight(0),
		m_effectWidth(0),
		m_angle(0.0f),
		m_lastAngle(),
		m_countFrame(0),
		m_deathCountFrame(0),
		m_waveDelay(0),
		m_isMoveRight(true),
		m_isRevGravity(false),
		m_isDashRingEnabled(false),
		m_isField(false),
		m_isStageClear(false),
		m_isDead(false)
	{}
	virtual ~HowToPlayer() {}

	void SetStage(HowToStage* stage) { m_pHStage = stage; }

	// プレイヤーの初期化
	void Init(int playerHandle, int waveBurner, int playerDeathEffect, int hDeathSound, bool isPrac);

	// プレイヤーのスポーン位置をセット
	void SetSpawnPos(bool isPrac);

	// メンバ関数ポインタの中身を変更
	void ChangeUpdateType();
	// プレイヤーの更新処理
	void Update(const InputState& input);

	// オブジェクトと当たった時の処理
	void OnHitObject(const InputState& input);

	// プレイヤーの描画処理
	void Draw();

	// プレイヤーの移動時のエフェクト
	void DrawMoveEffect();

	// 右移動するかどうかの設定
	void SetMoveRight(bool isRight) { m_isMoveRight = isRight; }
	// 右移動するかどうか取得
	bool IsMoveRight() const { return m_isMoveRight; }

	// 重力反転しているかを取得
	bool IsRevGravity() const { return m_isRevGravity; }

	// 画面スクロール時の横移動の切り替え
	void SetPlayerVec(int scroll);
	// 横方向のベクトル削除
	void DeleteVecX() { m_vec.x = 0.0f; }

	// プレイヤーの現在の状態を取得
	PlayerState GetPlayerState() const { return m_playerState; }

	// 四方向の取得
	float GetLeft() const { return m_pos.x; }
	float GetTop() const { return m_pos.y; }
	float GetRight() const { return m_pos.x + Game::kBlockSize; }
	float GetBottom() const { return m_pos.y + Game::kBlockSize; }

	// プレイヤーの中心座標取得
	float GetCenterX() const { return m_pos.x + (Game::kBlockSize / 2); }	// キューブの中心
	float GetCenterY() const { return m_pos.y + (Game::kBlockSize / 2); }

	// クリアしたかどうかを取得
	bool IsStageClear() const { return m_isStageClear; }
	// 死亡判定を true にする
	void SetDead() { m_isDead = true; }
	// 死亡判定を取得
	bool IsDead() const { return m_isDead; }

	// プレイヤーの座標取得
	Vec2 GetPos() const { return m_pos; }

private:
	// 現在のプレイヤーの状態
	PlayerState m_playerState;

	// ステージのポインタ
	HowToStage* m_pHStage;

	// キューブの通常時の更新処理
	void CubeNormalUpdate(const InputState& input);
	// キューブの重力反転時の更新処理
	void CubeRevGravityUpdate(const InputState& input);
	// プレイヤー死亡時の更新処理
	void GoalUpdate(const InputState& input);

	using m_tUpdateFunc = void (HowToPlayer::*) (const InputState& input);
	m_tUpdateFunc m_updateFunc = nullptr;

private:
	// プレイヤー座標
	Vec2 m_pos;
	// 移動量
	Vec2 m_vec;

	Vec2 m_lastPos[5];

	// 画像データ
	int m_hPlayer;
	int m_hWaveBurner;
	int m_hDeathEffect;

	// 音データ
	int m_hDeathSound;

	// プレイヤーのサイズ
	double m_playerScale;

	// エフェクト画像サイズ
	float m_effectHeight;
	float m_effectWidth;
	// 画像表示角度
	double m_angle;
	double m_lastAngle[5];

	// フレーム数をカウント
	int m_countFrame;
	int m_deathCountFrame;
	int m_waveDelay;

	// 移動方向
	bool m_isMoveRight;
	// 重力方向
	bool m_isRevGravity;
	// ダッシュリング用の判定
	bool m_isDashRingEnabled;
	// 地面との当たり判定用変数
	bool m_isField;

	// ゴール判定
	bool m_isStageClear;
	// 死亡判定
	bool m_isDead;
};
