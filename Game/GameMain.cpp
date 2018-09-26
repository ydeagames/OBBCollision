//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   日付
//!
//! @author 制作者名 Nyarll
//! @author 制作者名 YdeaGames
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma warning (disable:4244)

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include <math.h>
#include "Vec2.h"
#include "GameUtils.h"
#include "InputManager.h"



// 定数の定義 ==============================================================



// 構造体の定義 ============================================================
typedef struct
{
	Vec2 pos;
	Vec2 size;
	float angle;
} GameObject;



// グローバル変数の定義 ====================================================

GameObject obj;


// プロトタイプ宣言 ========================================================

void InitializeGame(void);  // ゲームの初期化処理
void UpdateGame(void);      // ゲームの更新処理
void RenderGame(void);      // ゲームの描画処理
void FinalizeGame(void);    // ゲームの終了処理

void DrawBoxQuad(const GameObject* obj, UINT color, int fill);


// 関数の定義 ==============================================================

// ゲームの初期化処理
void InitializeGame(void)
{
	obj.pos = Vec2_Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	obj.size = Vec2_Create(100, 80);
}

// ゲームの更新処理
void UpdateGame(void)
{
	static const float delta = DEG_TO_RAD(1);
	obj.angle += delta;

	UpdateInputManager();
}

static BOOL BoxCollisionObj(const GameObject* obj, const Vec2* point)
{
	return BoxCollision(
		obj->pos.x,
		obj->pos.y,
		obj->size.x,
		obj->size.y,
		point->x,
		point->y,
		1,
		1
	);
}

// ゲームの描画処理
void RenderGame(void)
{
	UINT color = 0xffff0000;

	Vec2 mouse = GetMousePosition();
	Vec2 m_p = Vec2_Sub(&mouse, &obj.pos);
	Vec2 mouse_temp = Vec2_Add(&obj.pos, &Vec2_Rotate(&m_p, -obj.angle));

	if (BoxCollisionObj(&obj, &mouse_temp))
		color = 0xffffff00;

	DrawBoxQuad(&obj, color, TRUE);
}

// ゲームの終了処理
void FinalizeGame(void)
{

}


// 以下オリジナル関数 --------------------------------------------------
void DrawBoxQuad(const GameObject* obj, UINT color, int fill)
{
	Vec2 p1 = Vec2_Add(&obj->pos, &Vec2_Rotate(&Vec2_Create(- obj->size.x / 2, - obj->size.y / 2), obj->angle));
	Vec2 p2 = Vec2_Add(&obj->pos, &Vec2_Rotate(&Vec2_Create(+ obj->size.x / 2, - obj->size.y / 2), obj->angle));
	Vec2 p3 = Vec2_Add(&obj->pos, &Vec2_Rotate(&Vec2_Create(+ obj->size.x / 2, + obj->size.y / 2), obj->angle));
	Vec2 p4 = Vec2_Add(&obj->pos, &Vec2_Rotate(&Vec2_Create(- obj->size.x / 2, + obj->size.y / 2), obj->angle));

	DrawQuadrangle(
		p1.x, p1.y,
		p2.x, p2.y,
		p3.x, p3.y,
		p4.x, p4.y,
		color, fill
	);
}