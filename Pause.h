/*=============================================================================

		�|�[�Y[ Pause.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/01/14
-------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	��d�C���N���[�h�h�~
-----------------------------------------------------------------------------*/
#ifndef _PAUSE_H_
#define _PAUSE_H_

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
void InitPause( void );		//	�|�[�Y�̏�����
void UninitPause( void );	//	�|�[�Y�̏I��
void UpdatePause( void );	//	�|�[�Y�̍X�V
void DrawPause( void );		//	�|�[�Y�̕`��

bool *GetPauseFlag( void );	//	�|�[�Y�t���O���̎擾

#endif