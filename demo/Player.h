#pragma once
#include<iostream>
#include<vector>
#include<memory>
#include"Vec2.h"
#include"Object.h"
#include"Rect.h"

namespace
{
	constexpr int SHOT_NUM_LIMIT = 100;
};

class SceneMain;
class Shot;
class Laser;
class CircleShot;

class Player : public Object
{
	
public:
	//using Shot = std::shared_ptr<Shot>;

	Player(SceneMain* main, int shotSound, int damageSound, int lasersound);
	Player();
	~Player();

	void Init();
	void PlayerMove();
	void ShotIt();
	void DeleteShot();
	void Update();
	void CollisionUpdate();
	void Draw();
	void VelocityToZero();
	bool OnDamage();
	bool OnDamage(float hitDir);

	void ToDie();

	void OnClear();


	void GetNewWeapon(int weaponNum);

	//��ԕʊ֐�(�|�C���^�ŌĂяo��)
	void StartUpdate();
	void IdleUpdate();
	void WalkingUpdate();
	void NeutralUpdate();
	void FaceDownUpdate();
	void JumpingUpdate();
	void FlyingUpdate();
	void DieUpdate();
	void ClearUpdate();

	void EndingStartUpdate();
	void EndingUpdate();
	
	//�����蔻��֐�
	void OnMapCollision();
	bool OnCollision(Rect rect);

	//�Q�b�^�[
	int GetColRadius() const{ return m_collisionRadius; }
	Vec2 GetVelocity()const { return m_velocity; }
	Vec2 GetPos()const { return m_pos; }
	Vec2 GetPos(int move) { m_pos.x -= move; return m_pos; }
	Rect& GetRect() { return m_playerCol; }
	Rect& GetTopRay() { return m_topRay; }
	Rect& GetBottomRay() { return m_bottomRay; }
	
	//�}�b�v�i�s
	void screenAdd() { m_isScreenAdd = true; }
	void screenSub() { m_isScreenSub = true; }

	//�����o�֐��|�C���^
	using playerState_t = void(Player::*)();
	playerState_t m_playerUpdate;

private:
	/*�����o�ϐ�*/
	//Pos
	Vec2 m_pos;//���W
	Vec2 m_size;//�T�C�Y
	Vec2 m_velocity;//���x
	Vec2 m_dir;//����
	Vec2 m_animFrame;//�A�j���[�V�����t���[��
	Rect m_playerCol;
	Rect m_topRay;
	Rect m_bottomRay;
	//�U��
	Vec2 m_fireDir;//�Ə��̕���
	Vec2 m_bulletStartPos;//�e�̐����ʒu
	//�t���O
	bool m_isGroundFlag=false;//�n�ʂƐڐG���Ă���
	bool m_isJumpFlag=false;//�W�����v����ǂݎ��Flag
	bool m_isDushFlag=false;//�_�b�V�����Ă��邩
	bool m_isFaceDownFlag=false;//����
	bool m_isLeftFlag=false;//���������Ă邩�t���O


	bool m_isHitFlag=false;//�_���[�W�t���O


	int m_animInterval=0;
	int m_animXlimit=0;
	int m_visibleLimitTime=0;//���G����
	int m_inputX;
	int m_inputY;

	//Die
	bool m_isEndroll;
	int m_rollCount;

	bool m_isClear=false;

	bool flyFlag=false;
	Vec2 flySpeed;//��s�����x
	int flyingFrame=0;

	int m_collisionRadius=0;//���͈̔͂̒��ł��������蔻������Ȃ�
	int m_handle=0;//�v���C���[��graphHandle;
	int m_ShotGraph=0;//�e�̃O���t�B�b�N�n���h��
	int m_kindOfBullet=0;
	int m_havingweaponNumber = 0;
	int m_Hp=0;

	float m_angle=0.0f;
	float m_rotateAngle=0.0f;
	float toZeroSpeed=0.0f;

	bool m_isScreenAdd=false;
	bool m_isScreenSub=false;

	

	int m_damageSound = 0;



/////////////////////////////////	
	

//////////*Shot�֘A*///////////
	//Shot* m_shot[SHOT_NUM_LIMIT];
	//Shot m_shot[SHOT_NUM_LIMIT];
	std::shared_ptr<Shot> m_shot[SHOT_NUM_LIMIT] ;
	int m_shotSoundHandle = 0;
	
	std::shared_ptr<Laser> m_laser;
	int m_laserSound = 0;

	std::shared_ptr<CircleShot> m_circleShot[SHOT_NUM_LIMIT];
	

	//�e�̔��˃t���O
	bool shotBulletFlag=false;
	int m_shotBulletInterval = 20;

///////////////////////////////
	


///////////*���̑�*////////////

	SceneMain* m_WorldMana;

///////////////////////////////

};

