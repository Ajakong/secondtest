#pragma once
#include "Shot.h"
#include<vector>

class EneShotEffect;

class EneShot 
{
public:
	EneShot(const Vec2& Spos, const Vec2& DirVec, const int& graph, const Player* p_player);
	virtual ~EneShot();

	void Init();
	void Update();
	void Draw(int screenMove);


	//Shot�̃v���O���~���O����
	void ShotProgram();

	bool GetIsDestroy()const { return m_isDestroy; }

	bool GetShotColli();
	void OnCollision();

	void setShotBullet() { m_isVisible = false; }

	void OnDestroy();

	void CollisionUpdate();

	void OnHit();


	Vec2 GetPos() { return m_shotPos; }

private:
	//Shot�̈ʒu���
	Vec2 m_shotPos;
	//Shot�̑��x�x�N�g��
	Vec2 m_Velocity;
	
	Vec2 m_dis;

	//Shot�̃O���t�B�b�N�n���h��
	int m_handle=0;

	int m_radius=0;//���a

	int m_screenMove = 0;

	bool m_isVisible = true;

	bool m_isEffectFlag = false;

	bool m_isDestroy=false;

	const Player* m_player;

	//std::vector<std::shared_ptr<EneShotEffect>> m_shotEffect;
};

