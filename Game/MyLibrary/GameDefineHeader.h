#pragma once

//���b�Z�[�W�{�b�N�X
#define MSG(m)	{	MessageBox(NULL,m,"Message Info",MB_OK);}
#define EXIT	{	MSG("�Q�[�����I�����܂�") PostQuitMessage(0);}

#define PI (3.141592653589793238)
#define DEG_TO_RAD(DEG)	((DEG) * (PI / 180.0))
#define RAD_TO_DEG(RAD)	((RAD) * (180.0 / PI))