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

	//状態別関数(ポインタで呼び出す)
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
	
	//当たり判定関数
	void OnMapCollision();
	bool OnCollision(Rect rect);

	//ゲッター
	int GetColRadius() const{ return m_collisionRadius; }
	Vec2 GetVelocity()const { return m_velocity; }
	Vec2 GetPos()const { return m_pos; }
	Vec2 GetPos(int move) { m_pos.x -= move; return m_pos; }
	Rect& GetRect() { return m_playerCol; }
	Rect& GetTopRay() { return m_topRay; }
	Rect& GetBottomRay() { return m_bottomRay; }
	
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
	Rect m_topRay;
	Rect m_bottomRay;
	//攻撃
	Vec2 m_fireDir;//照準の方向
	Vec2 m_bulletStartPos;//弾の生成位置
	//フラグ
	bool m_isGroundFlag=false;//地面と接触している
	bool m_isJumpFlag=false;//ジャンプ中を読み取るFlag
	bool m_isDushFlag=false;//ダッシュしているか
	bool m_isFaceDownFlag=false;//伏せ
	bool m_isLeftFlag=false;//左を向いてるかフラグ


	bool m_isHitFlag=false;//ダメージフラグ


	int m_animInterval=0;
	int m_animXlimit=0;
	int m_visibleLimitTime=0;//無敵時間
	int m_inputX;
	int m_inputY;

	//Die
	bool m_isEndroll;
	int m_rollCount;

	bool m_isClear=false;

	bool flyFlag=false;
	Vec2 flySpeed;//飛行時速度
	int flyingFrame=0;

	int m_collisionRadius=0;//この範囲の中でしか当たり判定を取らない
	int m_handle=0;//プレイヤーのgraphHandle;
	int m_ShotGraph=0;//弾のグラフィックハンドル
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
	

//////////*Shot関連*///////////
	//Shot* m_shot[SHOT_NUM_LIMIT];
	//Shot m_shot[SHOT_NUM_LIMIT];
	std::shared_ptr<Shot> m_shot[SHOT_NUM_LIMIT] ;
	int m_shotSoundHandle = 0;
	
	std::shared_ptr<Laser> m_laser;
	int m_laserSound = 0;

	std::shared_ptr<CircleShot> m_circleShot[SHOT_NUM_LIMIT];
	

	//弾の発射フラグ
	bool shotBulletFlag=false;
	int m_shotBulletInterval = 20;

///////////////////////////////
	


///////////*その他*////////////

	SceneMain* m_WorldMana;

///////////////////////////////

};

