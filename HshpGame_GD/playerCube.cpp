#include "playerCube.h"
#include "game.h"
#include "Stage.h"

namespace
{
    // 画像の回転速度
    constexpr float kRotaSpeed = 0.2f;

    // 画像の表示位置
    constexpr float kPlayerDrawPosX = 16.0f;
    constexpr float kPlayerDrawPosY = 34.0f;

    // ジャンプ力
    constexpr float kJumpAcc = -14.0f;

    // 重力
    constexpr float kGravity = 1.15f;
}

PlayerCube::PlayerCube() :
    pStage(nullptr)
{
}

void PlayerCube::Init(int playerHandle)
{
	m_handle = playerHandle;
	GetGraphSizeF(m_handle, &m_width, &m_height);
	
	m_isDead = false;

	m_pos.x = 0;
	m_pos.y = Game::kStageLowerLimit - (m_height / 2);

    m_vec.x = Game::kMoveSpeed;
    m_vec.y = 0;

    isMoveRight = true;
}

void PlayerCube::Update(const InputState& input)
{
    // プレイヤーの挙動の処理
    m_pos += m_vec;
    m_vec.y += kGravity;
    if(isMoveRight) m_angle += kRotaSpeed;
    else m_angle += -kRotaSpeed;

    // 地面との当たり判定
    isField = false;

    if (m_pos.y > Game::kStageLowerLimit - m_height)
    {
        m_angle = 0;
        m_pos.y = Game::kStageLowerLimit - m_height;

        m_pos.y = static_cast<float>(Game::kStageLowerLimit - m_height);    // ステージの範囲より下には行かない
        isField = true;
    }

    if (m_pos.x < 0)
    {
        m_vec.x *= -1;
        isMoveRight = true;
    }
    else if (m_pos.x  + Game::kBlockSize > Game::kScreenWidth)
    {
        m_vec.x *= -1;
        isMoveRight = false;
    }

    OnHitObject(input);

    if (input.IsPressed(InputType::jump))
    {
        if (isField)
        {
            m_vec.y = kJumpAcc;	// ジャンプ開始
        }
    }
}

void PlayerCube::OnHitObject(const InputState& input)
{
    ObjectType object;
    for (int i = 0; i < Game::kScreenHeightNum; i++)
    {
        for (int j = 0; j < Game::kScreenWidthNum; j++)
        {
            if (pStage->CollisionCheck(m_pos, i, j, object))
            {
                float tempPos = 0.0f;
                if (pStage->IsUnder(m_pos, tempPos, i, j) && object == ObjectType::Block)
                {
                    m_angle = 0.0f;
                    m_vec.y = 0.0f;
                    m_pos.y = tempPos - Game::kBlockSize;
                    isField = true;
                }
                else if (object == ObjectType::JumpRing)
                {
                    if (input.IsTriggered(InputType::jump))
                    {
                        m_vec.y = kJumpAcc;	// ジャンプ開始
                    }
                }
                else
                {
                    m_isDead = true;
                }
            }
        }
    }
}

void PlayerCube::Draw()
{
	DrawRotaGraphF(GetCenterX(), GetCenterY(), 1, m_angle, m_handle, true, false);
	//DrawBox(m_pos.x, m_pos.y, GetRight(), GetBottom(), GetColor(255, 255, 255), false);

    DrawFormatString(0, 0, 0xFFFFFF, "%f", GetBottom());
}
