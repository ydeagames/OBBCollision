//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   ���t
//!
//! @author ����Җ� Nyarll
//! @author ����Җ� YdeaGames
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma warning (disable:4244)

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include <math.h>
#include "Vec2.h"
#include "GameUtils.h"
#include "InputManager.h"



// �萔�̒�` ==============================================================



// �\���̂̒�` ============================================================
typedef struct
{
	Vec2 pos;
	Vec2 size;
	float angle;
} GameObject;



// �O���[�o���ϐ��̒�` ====================================================

GameObject obj;


// �v���g�^�C�v�錾 ========================================================

void InitializeGame(void);  // �Q�[���̏���������
void UpdateGame(void);      // �Q�[���̍X�V����
void RenderGame(void);      // �Q�[���̕`�揈��
void FinalizeGame(void);    // �Q�[���̏I������

void DrawBoxQuad(const GameObject* obj, UINT color, int fill);


// �֐��̒�` ==============================================================

// �Q�[���̏���������
void InitializeGame(void)
{
	obj.pos = Vec2_Create(SCREEN_CENTER_X, SCREEN_CENTER_Y);
	obj.size = Vec2_Create(100, 80);
}

// �Q�[���̍X�V����
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

// �Q�[���̕`�揈��
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

// �Q�[���̏I������
void FinalizeGame(void)
{

}


// �ȉ��I���W�i���֐� --------------------------------------------------
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