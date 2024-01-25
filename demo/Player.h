#pragma once
#include<iostream>
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

	Player(SceneMain* main);
	~Player();

	void Init();
	void PlayerMove();
	void ShotIt();
	void DeleteShot();
	void Update();
	void Draw();
	void VelocityToZero();
	void OnDamage();

	//状態別関数(ポインタで呼び出す)
	void NeutralUpdate();
	void FaceDownUpdate();
	void JumpingUpdate();
	//ダッシュはいらん(その状態になった際できないことやできることがあるのが状態別関数の条件)

	//当たり判定関数
	void OnMapCollision();
	bool OnCollision(Rect rect);

	//ゲッター
	int GetColRadius() const{ return m_collisionRadius; }
	Vec2 GetVelocity()const { return m_velocity; }
	Vec2 GetPos()const { return m_pos; }
	Vec2 GetPos(int move) { m_pos.x -= move; return m_pos; }
	Rect& GetRect() { return m_playerCol; }
	
	//マップ進行
	void screenAdd() { m_isScreenAdd = true; }
	void screenSub() { m_isScreenSub = true; }

	//メンバ関数ポインタ
	using playerState_t = void(Player::*)();
	playerState_t m_playerUpdate;


private:
	/*メンバ変数*/
	//Pos
	Vec2 m_pos;//座標
	Vec2 m_size;//サイズ
	Vec2 m_velocity;//速度
	Vec2 m_dir;//向き
	Vec2 m_animFrame;//アニメーションフレーム
	Rect m_playerCol;
	//攻撃
	Vec2 m_fireDir;//照準の方向
	Vec2 m_bulletStartPos;//弾の生成位置
	//フラグ
	bool m_isGroundFlag;//地面と接触している
	bool m_isJumpFlag;//ジャンプ中を読み取るFlag
	bool m_isDushFlag;//ダッシュしているか
	bool m_isFaceDownFlag;//伏せ
	bool m_isLeftFlag;//左を向いてるかフラグ



	bool flyFlag;

	Vec2 flySpeed;//飛行時速度

	int flyingFrame;

	int m_collisionRadius;//この範囲の中でしか当たり判定を取らない
	
	int m_handle;//プレイヤーのgraphHandle;
	
	int m_ShotGraph;//弾のグラフィックハンドル

	int m_kindOfBullet;

	int m_Hp;

	float m_angle;
	float m_rotateAngle;

	float toZeroSpeed;

	bool m_isScreenAdd;
	bool m_isScreenSub;


/////////////////////////////////	
	

//////////*Shot関連*///////////
	//Shot* m_shot[SHOT_NUM_LIMIT];
	//Shot m_shot[SHOT_NUM_LIMIT];
	std::shared_ptr<Shot> m_shot[SHOT_NUM_LIMIT] ;

	
	std::shared_ptr<Laser> m_laser;
	std::shared_ptr<CircleShot> m_circleShot[3];


	//弾の発射フラグ
	bool shotBulletFlag;

	int m_shotBulletInterval = 20;

///////////////////////////////
	


///////////*その他*////////////

	SceneMain* m_WorldMana;

///////////////////////////////

};

