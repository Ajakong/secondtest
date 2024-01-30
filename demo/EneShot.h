#pragma once
#include "Shot.h"

class EneShotEffect;

class EneShot 
{
public:
	EneShot();
	virtual ~EneShot();

	void Init();
	void Update();
	void Draw();


	//Shot�̃v���O���~���O����
	void ShotProgram(const Vec2& Spos, const Vec2& DirVec, const int& graph, std::shared_ptr<EneShotEffect> eneShotEffect, std::shared_ptr<EneShot>shotPointer);

	bool GetIsDestroy()const { return m_isDestroy; }

	bool GetShotColli(const Rect& rect);
	void OnCollision();

	void setShotBullet() { m_isVisible = false; }

	void OnDestroy() { m_isDestroy = true; m_shotEffect = nullptr; }

	void GetScreenMove(int screenmove) { m_screenMove = screenmove; }

	Vec2 GetPos() { return m_shotPos; }

	Sqhere GetCollSqhere()const { return m_collider; }
private:
	//Shot�̈ʒu���
	Vec2 m_shotPos;
	//Shot�̃x�N�g��
	Vec2 m_Velocity;
	//�x�N�g���̌���
	Vec2 m_DirVec;
	//Shot�̃O���t�B�b�N�n���h��
	int m_handle=0;
	int m_graph=0;

	Sqhere m_collider;

	int m_radius=0;

	int m_screenMove = 0;

	bool m_isVisible = true;

	bool m_isEffectFlag = false;

	bool m_isDestroy=false;

	Vec2 m_graphSize;

	Player* m_player;
	EnemyBase* m_enemy;
	std::shared_ptr<EneShot>m_myPointer;

	std::shared_ptr<EneShotEffect> m_shotEffect;
};

