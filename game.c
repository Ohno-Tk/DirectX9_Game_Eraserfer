/*=============================================================================

		�Q�[��[ game.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2016/12/15
-------------------------------------------------------------------------------
	���@Update
=============================================================================*/
/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "game.h"

#include "camera.h"
#include "MeshField.h"
#include "MeshWall.h"
#include "skydome.h"
#include "Shadow.h"
#include "Player.h"
#include "Enemy1.h"
#include "Cleaner.h"
#include "Born.h"
#include "JumpRamp.h"
#include "Help.h"
#include "Particle.h"

#include "HelpNumber.h"
#include "Gauge.h"
#include "CountDown.h"
#include "Pause.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	��
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�\����
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�v���g�^�C�v�錾
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 �֐���:	void InitGame( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		������
-----------------------------------------------------------------------------*/
void InitGame( void )
{

	InitCamera();	//	�J�����̏�����

	InitMeshField();		//	���b�V���t�B�[���h�̏�����

	InitMeshWall();		//	���b�V���E�H�[���̏�����

	InitSkydome();		//	�X�J�C�h�[���̏�����

	InitShadow();	//	�e�̏�����

	InitHelpNumber();

	InitHelp();		//	�w���v�̏�����

	InitBorn();		//	�����l�̏�����

	InitPlayer();		//	�v���C���[�̏�����

	InitEnemy1();	//	���ꑝ�₷�G�̏�����

	InitCleaner();	//	�������N���[�i�[�̏�����

	InitJumpRamp();		//	�W�����v��̏�����

	InitParticle();		//	�p�[�e�B�N���̏�����

	InitCountDown();		//	�J�E���g�_�E���̏�����

	InitGauge();		//	�Q�[�W�̏�����

	InitPause();		//	�|�[�Y�̏�����


	//	���y�Đ�
	PlaySound( SOUND_LABEL_BGM_GAME );

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitGame( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitGame( void )
{

	UninitMeshField();		//	���b�V���t�B�[���h�̏I��

	UninitMeshWall();	//	���b�V���E�H�[���̏I��

	UninitSkydome();		//	�X�J�C�h�[���̏I��

	UninitShadow();	//	�e�̏I��

	UninitPlayer();	//	�v���C���[�̏I��

	UninitEnemy1();	//	���ꑝ�₷�G�̏I��

	UninitCleaner();	//	�������N���[�i�[�̏I��

	UninitBorn();	//	�����l�̏I��

	UninitJumpRamp();	//	�W�����v��̏I��

	UninitHelp();	//	�w���v�̏I��

	UninitParticle();	//	�p�[�e�B�N���̏I��

	UninitHelpNumber();

	UninitGauge();	//	�Q�[�W�̏I��

	UninitCountDown();	//	�J�E���g�_�E���̏I��

	UninitPause();	//	�|�[�Y�̏I��


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UpdateGame( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateGame( void )
{

	//	�X�^�[�g�������̏��擾
	bool *Start = GetStart();


	//	�|�[�Y�t���O���̎擾
	bool *Pause = GetPauseFlag();

	int *HelpNumber = GetHelpNumber();


	if( *Start == true && *Pause == false )
	{

		UpdateMeshField();		//	���b�V���t�B�[���h�̍X�V

		UpdateMeshWall();	//	���b�V���E�H�[���̍X�V

		UpdateSkydome();		//	�X�J�C�h�[���̍X�V

		UpdateShadow();	//	�e�̍X�V

		UpdatePlayer();	//	�v���C���[�̍X�V

		UpdateEnemy1();	//	���ꑝ�₷�G�̍X�V

		UpdateCleaner();	//	�������N���[�i�[�̍X�V

		UpdateBorn();	//	�����l�̍X�V

		UpdateJumpRamp();	//	�W�����v��̍X�V

		UpdateHelp();	//	�w���v�̍X�V

		UpdateParticle();	//	�p�[�e�B�N���̍X�V

		UpdateHelpNumber();

		UpdateGauge();	//	�Q�[�W�̍X�V

	}	//	end of if

	UpdateCountDown();	//	�J�E���g�_�E���̍X�V

	UpdatePause();	//	�|�[�Y�̍X�V



	ENEMY *Enemy = GetEnemy1();

	//	��ʑJ��
	if( *HelpNumber <= 0  )
	{

		*HelpNumber = 0;

		Enemy -> Use = false;


		SetFade( FADE_OUT , MODE_RESULT );

		//	���Ԗڂ̉����~�߂�
		StopSound( SOUND_LABEL_BGM_GAME );

	}

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawGame( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawGame( void )
{

	DrawMeshField();		//	���b�V���t�B�[���h�̕`��

	DrawSkydome();		//	�X�J�C�h�[���̕`��

	DrawMeshWall();		//	���b�V���E�H�[���̕`��

	DrawShadow();	//	�e�̕`��

	DrawPlayer();		//	�v���C���[�̕`��

//	DrawEnemy1();	//	���ꑝ�₷�G�̕`��

	DrawCleaner();	//	�������N���[�i�[�̕`��

	DrawBorn();		//	�����l�̕`��

//	DrawJumpRamp();		//	�W�����v��̕`��

	DrawHelp();		//	�w���v�̕`��

	DrawParticle();		//	�p�[�e�B�N���̕`��

	DrawHelpNumber();

	DrawGauge();		//	�Q�[�W�̕`��

	DrawCountDown();		//	�J�E���g�_�E���̕`��

	DrawPause();		//	�|�[�Y�̕`��


}	//	end of func