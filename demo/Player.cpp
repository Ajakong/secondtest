#include"DxLib.h"
#include"Game.h"
#include"Pad.h"
#include"Object.h"
#include"Shot.h"
#include"ShotEffect.h"
#include"Laser.h"
#include"CircleShot.h"
#include "Player.h"
#include"SceneMain.h"

namespace
{
	constexpr int animDisX = 188;
	constexpr int animDisY = 112;
	constexpr float shotAngle = 8.0f;
	constexpr float dushSpeed=6.0f;
}

Player::Player(SceneMain* main) :
	m_WorldMana(main),
	m_Hp(100),
	m_velocity(0.0f, 0.0f),
	m_fireDir(0.0f, 0.0f),
	m_dir(1.0f,0.0f),
	m_size(80.0f,112.0f),
	toZeroSpeed(0.5f),
	flyingFrame(),
	m_isGroundFlag(false),
	m_isJumpFlag(true),
	m_kindOfBullet(0),
	m_rotateAngle(0)
{
	for (auto& shot : m_shot)
	{
		shot = nullptr;
	}

}

Player::~Player()
{
	

}

void Player::Init()
{
	m_handle = LoadGraph("data/image/PlayerDevil2.png");
	m_ShotGraph = LoadGraph("data/image/Shot.png");
	m_pos.x = 612.0f;
	m_pos.y = 200.0f;
	
}

void Player::PlayerMove()
{
	//ループ時の初期化処理
	m_isDushFlag = false;
	shotBulletFlag = false;
	m_fireDir.y = 0;
	m_animFrame.x = 0.0f;
	m_animFrame.y = 0.0f;
	m_playerCol.top = m_pos.y-15;
	m_playerCol.left = m_pos.x-30;
	m_playerCol.right = m_pos.x + 30;
	m_playerCol.bottom = m_pos.y + 80;

	if (m_isGroundFlag==true&&Pad::IsPress(PAD_INPUT_RIGHT))
	{
		m_velocity.x += 3.0f;
		if (Pad::IsPress(PAD_INPUT_6)&&m_isFaceDownFlag == false)//ダッシュ
		{
			m_isDushFlag = true;
		}
		
		if (m_velocity.x > dushSpeed)
		{
			m_velocity.x = dushSpeed;
		}

		m_dir.x = 1.0f;
		m_dir.y = 0.0f;
		m_isLeftFlag = false;
	}
	else if (m_isGroundFlag==true&&Pad::IsPress(PAD_INPUT_LEFT))
	{
		
		m_velocity.x -=3.0f;
		if (Pad::IsPress(PAD_INPUT_6)&&m_isFaceDownFlag==false)
		{
			m_isDushFlag = true;
		}
		if (m_velocity.x < -dushSpeed)
		{
			m_velocity.x = -dushSpeed;
		}

		m_dir.x = -1.0f;
		m_dir.y = 0.0f;
		m_isLeftFlag = true;
	}
	if (m_isLeftFlag==false&&m_isGroundFlag == false && Pad::IsPress(PAD_INPUT_2)&&m_velocity.y>=-1&&flyFlag==false)
	{
		m_isLeftFlag = false;
		m_angle = 0.0f;
		m_velocity.x = 1.5f;
		
		m_dir.x = 1.0f;
		
		m_velocity.y -= 1.6f;
	}
	else if (m_isLeftFlag == false && m_isGroundFlag == false && Pad::IsRelase(PAD_INPUT_2) && m_velocity.y >= -1 && flyFlag == false)
	{
		flyFlag = true;
	}
	if (m_isLeftFlag == true && m_isGroundFlag == false && Pad::IsPress(PAD_INPUT_2) && m_velocity.y >= -1 && flyFlag == false)
	{
		m_isLeftFlag = true;
		m_angle = 4.5f;
		m_velocity.x = -1.5f;

		m_dir.x =- 1.0f;

		m_velocity.y -= 1.6f;
	}
	else if (m_isLeftFlag == true && m_isGroundFlag == false && Pad::IsRelase(PAD_INPUT_2) && m_velocity.y >= -1 && flyFlag == false)
	{
		flyFlag = true;

	}
	if (Pad::IsPress(PAD_INPUT_UP))
	{
		m_fireDir.y -= shotAngle;
	}
	if (Pad::IsPress(PAD_INPUT_DOWN))
	{
		m_fireDir.y += shotAngle;
	}
	if (m_isJumpFlag==false&&Pad::IsPress(PAD_INPUT_2))
	{
		
		m_velocity.y = -35.0f;
		m_isGroundFlag = false;
		m_isJumpFlag = true;
		m_angle += 1.0f;
	}
	if(m_isJumpFlag==true)m_fireDir.y += shotAngle / 8;
	m_velocity.y += 2;
	//if(Pad::IsRepeat(PAD_INPUT_UP,))
	m_pos += m_velocity;
	//伏せ判定は使ったのでfalseにする
	m_isFaceDownFlag = false;
	if (m_pos.y > Game::kScreenHeight-45)
	{
		m_pos.y = Game::kScreenHeight-45;
		m_isGroundFlag = true;
		flyFlag = false;
	}
	if (m_pos.x > Game::kScreenWidth-m_size.x)
	{
		m_pos.x = Game::kScreenWidth-m_size.x;
		
	}
	if (m_pos.y < 0)
	{
		m_pos.y = 0.0f;
	}
	if (m_pos.x <0)
	{
		m_pos.x = 0.0f;
	}
	if (m_isJumpFlag == true && m_isGroundFlag == false)
	{
		m_angle += 1.0f;
	}
	if (m_isGroundFlag == true)
	{
		m_angle = 0.0f;
		m_isJumpFlag = false;
	}

	//伏せ
	if (m_isGroundFlag == true && Pad::IsPress(PAD_INPUT_DOWN))
	{
		m_animFrame.x = 7.0f;
		m_animFrame.y = 6.0f;
		m_isFaceDownFlag = true;
	}

	if (m_pos.x > Game::kScreenWidth * 6 / 8)
	{
		m_pos.x = Game::kScreenWidth * 6 / 8;
	}
}

void Player::ShotIt()
{
	//Shot it!!
	switch (m_kindOfBullet)
	{
	default:
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			for (int i = 0; i < SHOT_NUM_LIMIT; i++)
			{
				if (m_shot[i] == nullptr)
				{
					
					m_shot[i] = std::make_shared<Shot>();
					m_dir.y = m_fireDir.y;
					m_shot[i]->ShotProgram(m_pos, m_dir, m_ShotGraph);
					m_WorldMana->AddShot(m_shot[i]);
					if (m_shot[i]->GetIsDestroy() == true){
						m_shot[i] = nullptr;
					}
					break;
				}
			}
		}
		break;
	case 1://マシンガン
		if (Pad::IsPress(PAD_INPUT_1)){
			for (int i = 0; i < SHOT_NUM_LIMIT; i++)
			{
				if (m_shot[i] == nullptr)
				{
					if (m_shotBulletInterval > 10)
						{
							m_shot[i] = std::make_shared<Shot>();
							m_dir.y = m_fireDir.y;
							m_shot[i]->ShotProgram(m_pos, m_dir, m_ShotGraph);
							m_WorldMana->AddShot(m_shot[i]);
							m_shotBulletInterval = 0;
							break;
						}
					
				}
			}
		}
		break;
	case 2://スプレッド
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			m_dir.y = m_fireDir.y;
			for (int a = 0; a < 4; a++)
			{
				for (int i = 0; i < SHOT_NUM_LIMIT; i++)
				{
					if (m_shot[i] == nullptr)
					{
						
						m_shot[i] = std::make_shared<Shot>();
						m_dir.y = m_dir.y + (a-1 ) * 0.5f;
						m_shot[i]->ShotProgram(m_pos, m_dir, m_ShotGraph);
						m_WorldMana->AddShot(m_shot[i]);
						m_shotBulletInterval = 0;
						break;
					}
				}
			}
		}
		break;
	case 3://視線はまるでレーザービーム
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			if (m_laser == nullptr)
			{
				m_laser = std::make_shared<Laser>();
				m_dir.y = m_fireDir.y;
				m_laser->ShotProgram(m_pos, m_dir);
				m_WorldMana->AddLaser(m_laser);
				m_shotBulletInterval = 0;
				break;
			}
		}
		break;
	case 4://サークルバレット
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			for (int i = 0; i < 3; i++)
			{
				if (m_circleShot[i] == nullptr)
				{
					m_circleShot[i] = std::make_shared<CircleShot>();
					m_dir.y = m_fireDir.y;
					m_circleShot[i]->ShotProgram(m_pos, m_dir, m_ShotGraph);
					m_WorldMana->AddCircleShot(m_circleShot[i]);
					m_shotBulletInterval = 0;
					break;
				}
			}
		}
		break;
	}
}

void Player::DeleteShot()
{

	if (m_laser != nullptr)
	{
		if (m_laser != nullptr)
		{
			m_laser->Update();

			if (m_laser->GetVisible() == true)
			{
				m_laser = nullptr;
			}
		}


	}

	for (int i = 0; i < SHOT_NUM_LIMIT; i++)
	{
		if (m_shot[i] != nullptr)
		{
			
			m_shot[i]->Update();
			if (m_shot[i]->GetIsDestroy())
			{
				m_shot[i] = nullptr;
				
			}
		}
	}


	for (int i = 0; i < 3; i++)
	{
		if (m_circleShot[i] != nullptr)
		{
			m_circleShot[i]->Update();
			if (m_circleShot[i]->GetIsDestroy())
			{
				m_circleShot[i] = nullptr;
			}
		}
	}

	if (Pad::IsTrigger(PAD_INPUT_3))
	{
		m_kindOfBullet++;
		if (m_kindOfBullet > 4)
		{
			m_kindOfBullet = 0;
		}
	}
	
	m_shotBulletInterval++;
}



void Player::Update()
{
	PlayerMove();

	ShotIt();

	DeleteShot();

	VelocityToZero();


}

void Player::Draw()
{
	
	

	DrawRectRotaGraph(m_pos.x, m_pos.y, 30 + animDisX*m_animFrame.x, animDisY*m_animFrame.y, animDisX, animDisY,1,m_angle+m_rotateAngle, m_handle,true,m_isLeftFlag,0);
	

	for (int i = 0; i < SHOT_NUM_LIMIT; i++)
	{
		if (m_shot[i] !=nullptr)m_shot[i]->Draw();
	}
	if (m_laser != nullptr)
	{
		m_laser->Draw();
	}
	for (int i = 0; i < 3; i++)
	{
		if (m_circleShot[i] != nullptr)m_circleShot[i]->Draw();
	}
	
}

void Player::VelocityToZero()
{
		if (m_isGroundFlag == true)
		{
			if (m_velocity.x > 0)
			{
				m_velocity.x -= 0.5f;
			}
			if (m_velocity.x < 0)
			{
				m_velocity.x += 0.5f;
			}
			if (m_isDushFlag == false)
			{
				m_velocity.x = 0.0f;
			}
		}
	
	if (m_velocity.y > 0)
	{
		m_velocity.y -= 0.5f;
	}
	if (m_velocity.y < 0)
	{
		m_velocity.y += 0.5f;
	}
}

void Player::OnDamage()
{
	m_Hp -= 10;
	if (m_Hp < 0)
	{
		m_WorldMana->GameOver();
	}
}

void Player::NeutralUpdate()
{
	//ループ時の初期化処理
	m_isDushFlag = false;
	shotBulletFlag = false;
	m_fireDir.y = 0;
	m_animFrame.x = 0.0f;
	m_animFrame.y = 0.0f;
	m_playerCol.top = m_pos.y - 15;
	m_playerCol.left = m_pos.x - 30;
	m_playerCol.right = m_pos.x + 30;
	m_playerCol.bottom = m_pos.y + 80;
}

void Player::FaceDownUpdate()
{
	//ループ時の初期化処理
	m_isDushFlag = false;
	shotBulletFlag = false;
	m_fireDir.y = 0;
	m_animFrame.x = 0.0f;
	m_animFrame.y = 0.0f;
	m_playerCol.top = m_pos.y +20;
	m_playerCol.left = m_pos.x - 30;
	m_playerCol.right = m_pos.x + 65;
	m_playerCol.bottom = m_pos.y + 80;
}

void Player::JumpingUpdate()
{
}



void Player::OnMapCollision()
{
	
	
	if(m_velocity.y>0)
	{
		m_pos.y = m_playerCol.bottom - 45;
		m_playerCol.top = m_pos.y;
		m_velocity.y = 0;
		m_isGroundFlag = true;
		flyFlag = false;
	}
	//if (m_velocity.x > 0)//マップチップの左側に衝突
	//{
	//	m_pos.x = m_playerCol.right;//今のplayer当たり判定の右側に位置を固定
	//	m_velocity.x = 0;
	//}
	//if (m_velocity.x < 0)//マップチップの左側に衝突
	//{
	//	m_pos.x = m_playerCol.left;//こっちは右側
	//	m_velocity.x = 0;
	//}
	
	
}

bool Player::OnCollision(Rect rect)
{
	
	if (m_pos.y- 112 / 2 <= rect.bottom && m_pos.y + 112/2  >= rect.top)
	{
		if (m_pos.x + 188/2  >= rect.left && m_pos.x- 188 / 2 <= rect.right)
		{
			
			
			return true;

		}
	}
	else
	{
		return false;
	}
	
}





