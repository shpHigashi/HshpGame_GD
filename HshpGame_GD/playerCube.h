#include "game.h"
#include "player.h"

class ObjectBlock;

class PlayerCube :
    public Player
{
public:
	PlayerCube();
	virtual ~PlayerCube() {}

	void setObject(ObjectBlock* Object) { pObject = Object; }

	// プレイヤーの初期化
	void Init(int playerHandle);

	// プレイヤーの更新処理
	void Update(const InputState& input);
	// プレイヤーの描画処理
	void Draw();

private:
	ObjectBlock* pObject;
};
