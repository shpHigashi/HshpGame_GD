//#include "game.h"
//#include "player.h"
//
//class Stage;
//
//class PlayerShip :
//	public Player
//{
//public:
//	PlayerShip();
//	virtual ~PlayerShip() {}
//
//	void setStage(Stage* stage) { m_pStage = stage; }
//
//	// プレイヤーの初期化
//	void Init(int playerHandle, int playerDeathEffect);
//
//	// プレイヤーの更新処理
//	void Update(const InputState& input);
//
//	// オブジェクトと当たった時の処理
//	void OnHitObject(const InputState& input);
//
//	// プレイヤーの描画処理
//	void Draw();
//private:
//	// ステージのポインタ
//	Stage* m_pStage;
//
//	// 通常時の更新処理
//	void NormalUpdate(const InputState& input);
//	// 重力反転時の更新処理
//	void RevGravityUpdate(const InputState& input);
//	// プレイヤー死亡時の更新処理
//	void DeadUpdate(const InputState& input);
//
//	using m_tUpdateFunc = void (PlayerShip::*) (const InputState& input);
//	m_tUpdateFunc m_updateFunc = nullptr;
//};
