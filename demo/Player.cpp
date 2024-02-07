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
	constexpr int animDisX = 192;
	constexpr int animDisY = 112;
	constexpr float shotAngle = 8.0f;
	constexpr float dushSpeed=6.0f;
}

Player::Player(SceneMain* main,int shotSound,int damageSound,int lasersound) :
	m_WorldMana(main),
	m_pos(0,50),
	m_Hp(80),
	m_velocity(0.0f, 0.0f),
	m_fireDir(0.0f, 0.0f),
	m_dir(1.0f,0.0f),
	m_size(80.0f,112.0f),
	m_animFrame(0,0),
	toZeroSpeed(0.5f),
	flyingFrame(),
	m_isGroundFlag(false),
	m_isJumpFlag(true),
	m_isDushFlag(false),
	m_isFaceDownFlag(false),
	m_isLeftFlag(false),
	m_isScreenAdd(false),
	m_isScreenSub(false),
	flyFlag(false),
	shotBulletFlag(false),
	m_angle(0),
	m_collisionRadius(30),
	m_handle(0),
	m_kindOfBullet(0),
	m_havingweaponNumber(0),
	m_rotateAngle(0),
	m_ShotGraph(false)
{
	for (auto& shot : m_shot)
	{
		shot = nullptr;
	}
	m_playerCol.top = m_pos.y - 15;
	m_playerCol.left = m_pos.x - 30;
	m_playerCol.right = m_pos.x + 30;
	m_playerCol.bottom = m_pos.y + 80;

	m_playerUpdate = &Player::EndingUpdate;
	m_shotSoundHandle =shotSound;
	m_laserSound = lasersound;

	m_damageSound =damageSound;
}

Player::Player()://�N���A�V�[���p�̃R���X�g���N�^
	m_pos(0, 50),
	m_Hp(30),
	m_velocity(0.0f, 0.0f),
	m_fireDir(0.0f, 0.0f),
	m_dir(1.0f, 0.0f),
	m_size(80.0f, 112.0f),
	m_animFrame(0, 0),
	toZeroSpeed(0.5f),
	flyingFrame(),
	m_isGroundFlag(false),
	m_isJumpFlag(true),
	m_isDushFlag(false),
	m_isFaceDownFlag(false),
	m_isLeftFlag(false),
	m_isScreenAdd(false),
	m_isScreenSub(false),
	flyFlag(false),
	shotBulletFlag(false),
	m_angle(0),
	m_collisionRadius(30),
	m_handle(0),
	m_kindOfBullet(0),
	m_havingweaponNumber(0),
	m_rotateAngle(0),
	m_ShotGraph(false)
{
	for (auto& shot : m_shot)
	{
		shot = nullptr;
	}
	m_playerCol.top = m_pos.y - 15;
	m_playerCol.left = m_pos.x - 30;
	m_playerCol.right = m_pos.x + 30;
	m_playerCol.bottom = m_pos.y + 80;

	m_playerUpdate = &Player::StartUpdate;
	m_shotSoundHandle = LoadSoundMem("SE/shot.mp3");

	m_damageSound = LoadSoundMem("SE/PlayerDamage.mp3");

	m_animFrame.y = 1;
}

Player::~Player()
{

}

void Player::Init()
{
	m_handle = LoadGraph("data/image/PlayerDevil.png");
	m_ShotGraph = LoadGraph("data/image/Shot.png");
	m_pos.x = 50.0f;
	m_pos.y = 50.0f;
}

void Player::PlayerMove()
{
	//���[�v���̏���������
	m_isDushFlag = false;
	shotBulletFlag = false;
	m_fireDir.y = 0;
	
	m_animFrame.y = 0.0f;
	m_playerCol.top = m_pos.y-15;
	m_playerCol.left = m_pos.x-30;
	m_playerCol.right = m_pos.x + 30;
	m_playerCol.bottom = m_pos.y + 40;

	
	if (m_isGroundFlag==true&&Pad::IsPress(PAD_INPUT_RIGHT))
	{
		m_velocity.x += 3.0f;
		if (Pad::IsPress(PAD_INPUT_6)&&m_isFaceDownFlag == false)//�_�b�V��
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
	//��������͎g�����̂�false�ɂ���
	m_isFaceDownFlag = false;
	if (m_isJumpFlag == true && m_isGroundFlag == false)
	{
		m_angle += 1.0f;
	}
	if (m_isGroundFlag == true)
	{
		m_angle = 0.0f;
		m_isJumpFlag = false;
	}
	//����
	if (m_isGroundFlag == true && Pad::IsPress(PAD_INPUT_DOWN))
	{
		m_animFrame.x = 7.0f;
		m_animFrame.y = 6.0f;
		m_isFaceDownFlag = true;
	}
	if (m_pos.x > Game::kScreenWidth * 6.0f / 8.0f)
	{
		m_pos.x = Game::kScreenWidth * 6.0f / 8.0f;
	}
	m_animInterval++;
}

void Player::ShotIt()
{
	GetJoypadAnalogInput(&m_inputX, &m_inputY, DX_INPUT_PAD1);
	if(m_fireDir.x!=0)
	{
		m_fireDir.x = m_inputX;
		
	}
	
	m_fireDir.y = m_inputY;
	if (abs(m_fireDir.x )<0.3f)
	{
		if (m_isLeftFlag)m_fireDir.x = -1;
		else m_fireDir.x = 1;
	}
	m_fireDir.Normalize();

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
					if (m_shotBulletInterval > 30)
					{
						m_shot[i] = std::make_shared<Shot>();
						m_dir = m_fireDir;
						m_shot[i]->ShotProgram(m_pos, m_dir, m_ShotGraph);
						PlaySoundMem(m_shotSoundHandle, DX_PLAYTYPE_BACK);
						m_WorldMana->AddShot(m_shot[i]);
						m_shotBulletInterval = 0;
						if (m_shot[i]->GetIsDestroy() == true) {
							m_shot[i] = nullptr;
						}
						break;
					}
				}
			}
		}
		break;
	case 1://�}�V���K��
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
						PlaySoundMem(m_shotSoundHandle, DX_PLAYTYPE_BACK);
						m_WorldMana->AddShot(m_shot[i]);
						m_shotBulletInterval = 0;
						break;
					}
					
				}
			}
		}
		break;
	case 2://�X�v���b�h
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			m_dir.y = m_fireDir.y;
			if (m_shotBulletInterval > 30)
			{
				for (int a = 0; a < 4; a++)
				{
					for (int i = 0; i < SHOT_NUM_LIMIT; i++)
					{
						if (m_shot[i] == nullptr)
						{
							m_shot[i] = std::make_shared<Shot>();
							m_dir.y = m_dir.y + (a - 1) * 0.5f;
							m_shot[i]->ShotProgram(m_pos, m_dir, m_ShotGraph);
							PlaySoundMem(m_shotSoundHandle, DX_PLAYTYPE_BACK);
							m_WorldMana->AddShot(m_shot[i]);
							m_shotBulletInterval = 0;
							break;
						}
					}
				}
			}
		}
		break;
	case 3://�����͂܂�Ń��[�U�[�r�[��
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			if (m_laser == nullptr)
			{
				if (m_shotBulletInterval > 50)
				{
					m_laser = std::make_shared<Laser>();
					m_dir.y = m_fireDir.y;
					m_laser->ShotProgram(m_pos, m_dir);
					PlaySoundMem(m_laserSound,DX_PLAYTYPE_BACK);
					m_WorldMana->AddLaser(m_laser);
					m_shotBulletInterval = 0;
					break;
				}
				
			}
		}
		break;
	case 4://�T�[�N���o���b�g
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
				m_laser.reset();
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
				m_shot[i].reset();
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
				m_circleShot[i].reset();
			}
		}
	}
	if (Pad::IsTrigger(PAD_INPUT_3))
	{
		
		if (m_kindOfBullet==0)
		{
			m_kindOfBullet = m_havingweaponNumber;
		}
		else
		{
			m_kindOfBullet = 0;
		}
	}
	m_shotBulletInterval++;
}

void Player::Update()
{

	m_velocity.y += 2;//�d��

	//���[�v���̏���������
	m_isDushFlag = false;
	shotBulletFlag = false;
	m_fireDir.y = 0;
	
	(this->*m_playerUpdate)();//��ԑJ��

	/*if (m_pos.y > Game::kScreenHeight - 45)
	{
		m_pos.y = Game::kScreenHeight - 45;
		m_isGroundFlag = true;
		flyFlag = false;
	}
	if (m_pos.x > Game::kScreenWidth - m_size.x)
	{
		m_pos.x = Game::kScreenWidth - m_size.x;
	}
	if (m_pos.y < 0)
	{
		m_pos.y = 0.0f;
	}
	if (m_pos.x < 0)
	{
		m_pos.x = 0.0f;
	}*/
	if (m_pos.y >= 1080)
	{
		
		m_playerUpdate = &Player::DieUpdate;
		
	}

	m_visibleLimitTime++;//���G���Ԑ����͏�ɉ��Z���Ă���

	if (!m_isGroundFlag)
	{
		m_playerUpdate = &Player::JumpingUpdate;
	}

	DeleteShot();
	VelocityToZero();
}

void Player::CollisionUpdate()
{
	m_playerCol.top = m_pos.y - 15;
	m_playerCol.left = m_pos.x - 30;
	m_playerCol.right = m_pos.x + 30;
	m_playerCol.bottom = m_pos.y + 45;
}

void Player::Draw()
{
	if(m_visibleLimitTime<110)
	{
		if (m_visibleLimitTime % 5 == 1)
		{
			DrawRectRotaGraph(m_pos.x, m_pos.y,  animDisX * m_animFrame.x, animDisY * m_animFrame.y, animDisX, animDisY, 1, m_angle + m_rotateAngle, m_handle, true, m_isLeftFlag, 0);
			
		}
	}
	else
	{
		DrawRectRotaGraph(m_pos.x, m_pos.y,animDisX * m_animFrame.x, animDisY * m_animFrame.y, animDisX, animDisY, 1, m_angle + m_rotateAngle, m_handle, true, m_isLeftFlag, 0);
	}
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
	DrawFormatString(100, 300,0xffffff,"InVisibleTime:%d", m_visibleLimitTime);
	
	DrawBox(m_pos.x-m_collisionRadius, m_pos.y-m_collisionRadius, m_pos.x+m_collisionRadius, m_pos.y+m_collisionRadius, 0xff00ff, false);
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

bool Player::OnDamage()
{
	
	if (m_visibleLimitTime < 120||m_Hp<=0)
	{
		return false;
	}
	m_visibleLimitTime = 0;
	StartJoypadVibration(DX_INPUT_PAD1, 200, 500);
	PlaySoundMem(m_damageSound, DX_PLAYTYPE_BACK);
	m_velocity.x -= m_dir.x*10;

	m_velocity.y = -35.0f;
	m_isGroundFlag = false;
	m_isJumpFlag = true;
	m_angle += 1.0f;
	m_playerUpdate = &Player::JumpingUpdate;
	
	m_pos += m_velocity;
	m_visibleLimitTime = 0;
	m_isHitFlag = true;
	m_Hp -= 10;
	return true;
}

bool Player::OnDamage(float hitDir)
{
	if (m_visibleLimitTime < 120 || m_Hp <= 0)
	{
		return false;
	}
	m_visibleLimitTime = 0;
	StartJoypadVibration(DX_INPUT_PAD1, 200,500);
	PlaySoundMem(m_damageSound, DX_PLAYTYPE_BACK);
	m_velocity.x -=hitDir * 10;

	m_velocity.y = -35.0f;
	m_isGroundFlag = false;
	m_isJumpFlag = true;
	m_angle += 1.0f;
	m_playerUpdate = &Player::JumpingUpdate;

	m_pos += m_velocity;
	
	m_isHitFlag = true;
	m_Hp -= 10;
	return true;
	return false;
}

void Player::ToDie()
{
	if (m_Hp <= 0)
	{
		
		if (m_isGroundFlag == true)
		{
			m_WorldMana->EnemyDelete();

			m_visibleLimitTime = 100;//���������ۂ̖��G���Ԃ�ׂ�

			m_playerCol.top = -500;
			m_playerCol.left = -500;
			m_playerCol.right = -500;
			m_playerCol.bottom = -500;

			m_angle = 0;
			m_animFrame.x = 0;
			
			m_playerUpdate = &Player::DieUpdate;
		}
	}
}

void Player::OnClear()
{
	if(!m_isClear)
	{
		if (m_isGroundFlag == true)
		{
			m_WorldMana->EnemyDelete();

			m_visibleLimitTime = 100;//���������ۂ̖��G���Ԃ�ׂ�

			m_playerCol.top = -500;
			m_playerCol.left = -500;
			m_playerCol.right = -500;
			m_playerCol.bottom = -500;
			m_angle = 0;

			m_animFrame.x = 0;
			m_animFrame.y = 3;
			m_isClear = true;
			m_playerUpdate = &Player::ClearUpdate;
		}
	}
	
}

void Player::GetNewWeapon(int weaponNum)
{
	m_havingweaponNumber = weaponNum;
	m_kindOfBullet = weaponNum;
}

void Player::StartUpdate()
{
	CollisionUpdate();

	m_pos.x += 2;
	m_velocity.y+= 0.5f;
	m_angle += 1.0f;
	m_pos.y += m_velocity.y;
	if(m_isGroundFlag==true)
	{
		m_playerUpdate = &Player::IdleUpdate;
	}
}

void Player::IdleUpdate()
{
	m_animFrame.y = 0.0f;

	CollisionUpdate();

	m_angle = 0;
	if (m_animInterval >= 6)
	{
		m_animFrame.x++;
		if (m_animFrame.x >= 14)
		{
			m_animFrame.x = 0;
		}
		m_animInterval = 0;
	}
	if (m_isGroundFlag == true && Pad::IsPress(PAD_INPUT_RIGHT))
	{
		m_isLeftFlag = false;
		m_playerUpdate = &Player::WalkingUpdate;
	}
	if (m_isGroundFlag == true && Pad::IsPress(PAD_INPUT_LEFT))
	{
		m_isLeftFlag = true;
		m_playerUpdate = &Player::WalkingUpdate;
	}
	/*if (m_isLeftFlag == false && m_isGroundFlag == false && Pad::IsPress(PAD_INPUT_2) && m_velocity.y >= -1 && flyFlag == false)
	{
		m_angle = 0.0f;	
		m_playerUpdate = &Player::FlyingUpdate;
	}
	if (m_isLeftFlag == true && m_isGroundFlag == false && Pad::IsPress(PAD_INPUT_2) && m_velocity.y >= -1 && flyFlag == false)
	{
		m_angle = 4.5f;	
		m_playerUpdate = &Player::FlyingUpdate;
	}*/
	if (Pad::IsTrigger(PAD_INPUT_2))
	{
		
		m_velocity.y = -35.0f;
		m_isGroundFlag = false;
		m_isJumpFlag = true;
		m_angle += 1.0f;
		m_playerUpdate = &Player::JumpingUpdate;
	}
	m_animInterval++;

	//Die
	ToDie();

	ShotIt();
}

void Player::WalkingUpdate()
{
	CollisionUpdate();

	//���[�v���̏���������
	m_isDushFlag = false;
	shotBulletFlag = false;
	m_fireDir.y = 0;

	m_velocity.y += 2;
	//if(Pad::IsRepeat(PAD_INPUT_UP,))
	m_pos += m_velocity;
	//��������͎g�����̂�false�ɂ���
	m_isFaceDownFlag = false;
	m_animInterval++;

	if (m_isGroundFlag == true && Pad::IsPress(PAD_INPUT_RIGHT))
	{
		m_velocity.x += 3.0f;
		m_isDushFlag = true;
		if (Pad::IsPress(PAD_INPUT_6))//�_�b�V��
		{
			
		}
		if (m_velocity.x > dushSpeed)
		{
			m_velocity.x = dushSpeed;
		}
		
		m_dir.x = 1.0f;
		m_dir.y = 0.0f;
		m_isLeftFlag = false;

		ShotIt();
	}
	else if (m_isGroundFlag == true && Pad::IsPress(PAD_INPUT_LEFT))
	{
		m_velocity.x -= 3.0f;
		m_isDushFlag = true;
		if (Pad::IsPress(PAD_INPUT_6))
		{
			
		}
		if (m_velocity.x < -dushSpeed)
		{
			m_velocity.x = -dushSpeed;
		}
		
		m_dir.x = -1.0f;
		m_dir.y = 0.0f;
		m_isLeftFlag = true;
		ShotIt();
	}
	else
	{
		m_playerUpdate = &Player::IdleUpdate;
	}
	if (Pad::IsTrigger(PAD_INPUT_2))
	{
		m_playerUpdate = &Player::JumpingUpdate;
		m_velocity.y = -35.0f;
		m_isGroundFlag = false;
		m_isJumpFlag = true;
		m_angle += 1.0f;
	}

	m_animFrame.y = 1;
	if (m_animInterval >= 6)
	{
		m_animFrame.x++;
		if (m_animFrame.x >= 11)
		{
			m_animFrame.x = 0;
		}
		m_animInterval = 0;
	}

	//Die
	ToDie();

	
	ShotIt();
}

void Player::NeutralUpdate()
{
	//���[�v���̏���������
	m_isDushFlag = false;
	shotBulletFlag = false;
	m_fireDir.y = 0;
	m_animFrame.x = 0.0f;
	m_animFrame.y = 0.0f;
	m_playerCol.top = m_pos.y - 15;
	m_playerCol.left = m_pos.x - 20;
	m_playerCol.right = m_pos.x + 20;
	m_playerCol.bottom = m_pos.y + 50;

	PlayerMove();
}

void Player::FaceDownUpdate()
{
	CollisionUpdate();

	if (m_isJumpFlag == false && Pad::IsTrigger(PAD_INPUT_2))
	{
		m_playerUpdate = &Player::JumpingUpdate;
		m_velocity.y = -35.0f;
		m_isGroundFlag = false;
		m_isJumpFlag = true;
		m_angle += 1.0f;
	}

	//Die
	ToDie();

	ShotIt();
}

void Player::JumpingUpdate()
{
	CollisionUpdate();
	
	m_fireDir.y += shotAngle / 8;
	m_angle += 1.0f;
	
	if (m_isGroundFlag == true)
	{
		m_angle = 0.0f;
		m_isJumpFlag = false;
		m_playerUpdate = &Player::IdleUpdate;
	}
	/*if (m_isLeftFlag == false && m_isGroundFlag == false && Pad::IsPress(PAD_INPUT_2) && m_velocity.y >= -1 && flyFlag == false)
	{
		m_angle = 0.0f;
		m_playerUpdate = &Player::FlyingUpdate;
	}
	if (m_isLeftFlag == true && m_isGroundFlag == false && Pad::IsPress(PAD_INPUT_2) && m_velocity.y >= -1 && flyFlag == false)
	{
		m_angle = 4.5f;
		m_playerUpdate = &Player::FlyingUpdate;
	}*/
	m_pos += m_velocity;

	//Die
	ToDie();

	ShotIt();
}

void Player::FlyingUpdate()
{
	CollisionUpdate();

	if (!m_isLeftFlag)
	{
		m_velocity.x = -1.5f;
		m_dir.x = -1.0f;
		m_velocity.y -= 1.6f;
	}
	if (m_isLeftFlag)
	{
		m_velocity.x = 1.5f;
		m_dir.x = 1.0f;
		m_velocity.y -= 1.6f;
	}

	//Die
	ToDie();
	ShotIt();
}

void Player::DieUpdate()
{
	
	if (m_animInterval >= 20)
	{
		m_animFrame.y = 6;
		m_animFrame.x++;
		if (m_animFrame.x >= 10)
		{
			m_animFrame.x = 10;
		}
		m_animInterval = 0;
	}
	if(m_animFrame.x >= 10)
	{
		m_pos.y--;
		m_WorldMana->GameOver();
	}
	m_animInterval++;
}

void Player::ClearUpdate()
{
	if (m_animInterval >= 6)
	{
		m_animFrame.x++;
		if(m_animFrame.y==3)
		{
			if (m_animFrame.x >= 5)
			{
				m_animFrame.x = 0;
				m_animFrame.y = 4;
			}
		}
		else if (m_animFrame.y == 4)
		{
			if (m_animFrame.x >= 8)
			{
				m_WorldMana->GameOver();
			}
		}
		m_animInterval = 0;
	}
	
	m_animInterval++;
}

void Player::EndingStartUpdate()
{
	CollisionUpdate();

	m_pos.x += 2;
	m_velocity.y += 0.5f;
	m_angle += 1.0f;
	m_pos.y += m_velocity.y;
	if (m_isGroundFlag == true)
	{
		m_playerUpdate = &Player::EndingUpdate;
	}
}

void Player::EndingUpdate()
{
	CollisionUpdate();

	//���[�v���̏���������
	m_isDushFlag = false;
	shotBulletFlag = false;
	m_fireDir.y = 0;
	m_velocity.y += 2;
	//if(Pad::IsRepeat(PAD_INPUT_UP,))
	m_pos += m_velocity;
	//��������͎g�����̂�false�ɂ���
	m_isFaceDownFlag = false;
	m_animInterval++;

	if (m_isGroundFlag == true)
	{
		m_velocity.x += 3.0f;
		m_isDushFlag = true;

		m_dir.x = 1.0f;
		m_dir.y = 0.0f;
		m_isLeftFlag = false;
	}
	
	m_animFrame.y = 1;
	if (m_animInterval >= 6)
	{
		m_animFrame.x++;
		if (m_animFrame.x >= 11)
		{
			m_animFrame.x = 0;
		}
		m_animInterval = 0;
	}

	ShotIt();
	//Die
	ToDie();

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
	//if (m_velocity.x > 0)//�}�b�v�`�b�v�̍����ɏՓ�
	//{
	//	m_pos.x = m_playerCol.right;//����player�����蔻��̉E���Ɉʒu���Œ�
	//	m_velocity.x = 0;
	//}
	//if (m_velocity.x < 0)//�}�b�v�`�b�v�̍����ɏՓ�
	//{
	//	m_pos.x = m_playerCol.left;//�������͉E��
	//	m_velocity.x = 0;
	//}
}

bool Player::OnCollision(Rect rect)
{
	if (m_playerCol.right >= rect.left && m_playerCol.left <= rect.right)
	{
		if (m_playerCol.top <= rect.bottom && m_playerCol.bottom >= rect.top)
		{
			
			return true;
		}
	}
	
	
	return false;
	
}





