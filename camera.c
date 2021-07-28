/*=============================================================================

		�J����[ camera.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2016/10/19
-------------------------------------------------------------------------------
	���@Update
		2016/10/19
=============================================================================*/
/*-----------------------------------------------------------------------------
						scanf ��warning�h�~ 
-----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include "main.h"
#include "input.h"
#include "camera.h"

#include "fade.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define CAMERA_NEAR ( 1.0f )	//	near
#define CAMERA_FAR ( 3000.0f )	//	far

#define SPEED ( 30.0f )	//	�����_�ړ���

#define RADIUS ( 0.05f )	//	���f�B�E�X�̑�����

#define MOVE_SPEED ( 20.0f )	//	�ړ���
#define ROT_SPEED ( 0.6f )	//	��]��

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
#ifdef _DEBUG
	LPD3DXFONT g_pFontCamera = NULL;
#endif	//	_DEBUG

float g_fLengthPolygon;	//	�Ίp��
float g_fAnglePolygon;	//	�p�x�V�[�^


D3DXVECTOR3 g_posEye( 0.0f , 60.0f , -150.0f );	//	�J����
D3DXVECTOR3 g_posAt( 0.0f , 30.0f , 0.0f );	//	�����_
D3DXVECTOR3 g_vecUp( 0.0f , 1.0f , 0.0f );	//	��̎��_

//	�r���[�s��̍쐬
D3DXMATRIX g_mtxView;

/*-----------------------------------------------------------------------------
 �֐���:	void InitCamera( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		������
-----------------------------------------------------------------------------*/
void InitCamera( void )
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

#ifdef _DEBUG
	D3DXCreateFont( pDevice ,
					18 ,	//	��������
					0 ,	//	������
					0 ,	//	�����̑���
					0 ,	//	�~�b�v�}�b�v
					FALSE ,	//	�C�^���b�N
					SHIFTJIS_CHARSET ,
					OUT_DEFAULT_PRECIS ,
					DEFAULT_QUALITY ,
					DEFAULT_PITCH ,
					"Terminal" ,
					&g_pFontCamera);
#endif	//	_DEBUG


	//	������

	g_fLengthPolygon = -g_posEye.z;

	g_fAnglePolygon = 0;


	//	���̃��[�h�̎擾
	MODE *Mode = GetNextMode();

	if( *Mode == MODE_TITLE )
	{

		g_posEye = D3DXVECTOR3( 0.0f , 1100.0f , -1.0f );	//	�J����
		g_posAt = D3DXVECTOR3( 0.0f , 30.0f , 0.0f );	//	�����_

	}	//	end of if

	else if( *Mode == MODE_GAME )
	{

		g_posEye = D3DXVECTOR3( 0.0f , 150.0f , -1000.0f );	//	�J����
		g_posAt = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );	//	�����_

	}	//	end of if

	else if( *Mode == MODE_RESULT )
	{

		g_posEye = D3DXVECTOR3( 0.0f , 1100.0f , -1.0f );	//	�J����
		g_posAt = D3DXVECTOR3( 0.0f , 30.0f , 0.0f );	//	�����_

	}	//	end of if


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitCamera( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitCamera( void )
{
#ifdef _DEBUG

	if( g_pFontCamera != NULL )	//	�t�H���g�|�C���^�J��
	{
		g_pFontCamera -> Release();
		g_pFontCamera = NULL;

	}	//	end of if

#endif	//	_DEBUG

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UpdateCamera( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateCamera( void )
{

#if 0

	//	���_�ړ�
	if( GetKeyboardPress( DIK_W ) )
	{
		g_posEye.x += sin( -g_fAnglePolygon ) * MOVE_SPEED;
		g_posEye.z += cos( -g_fAnglePolygon ) * MOVE_SPEED;

		g_posAt.x += sin( -g_fAnglePolygon ) * MOVE_SPEED;
		g_posAt.z += cos( -g_fAnglePolygon ) * MOVE_SPEED;

	}	//	end of if

	if( GetKeyboardPress( DIK_S ) )
	{
		g_posEye.x -= sin( -g_fAnglePolygon ) * MOVE_SPEED;
		g_posEye.z -= cos( -g_fAnglePolygon ) * MOVE_SPEED;

		g_posAt.x -= sin( -g_fAnglePolygon ) * MOVE_SPEED;
		g_posAt.z -= cos( -g_fAnglePolygon ) * MOVE_SPEED;

	}	//	end of if

	if( GetKeyboardPress( DIK_A ) )
	{
		g_posEye.x -= cos( g_fAnglePolygon ) * MOVE_SPEED;
		g_posEye.z -= sin( g_fAnglePolygon ) * MOVE_SPEED;

		g_posAt.x -= cos( g_fAnglePolygon ) * MOVE_SPEED;
		g_posAt.z -= sin( g_fAnglePolygon ) * MOVE_SPEED;

	}	//	end of if

	if( GetKeyboardPress( DIK_D ) )
	{
		g_posEye.x += cos( g_fAnglePolygon ) * MOVE_SPEED;
		g_posEye.z += sin( g_fAnglePolygon ) * MOVE_SPEED;

		g_posAt.x += cos( g_fAnglePolygon ) * MOVE_SPEED;
		g_posAt.z += sin( g_fAnglePolygon ) * MOVE_SPEED;

	}	//	end of if

	

	//	�����_����
	if( GetKeyboardPress( DIK_Q ) )
	{

		g_posAt.x = g_fLengthPolygon * cos( g_fAnglePolygon + D3DX_PI * 0.5f ) + g_posEye.x;
		g_posAt.z = g_fLengthPolygon * sin( g_fAnglePolygon + D3DX_PI * 0.5f ) + g_posEye.z;

		g_fAnglePolygon += RADIUS;

	}	//	end of if

	else if( GetKeyboardPress( DIK_E ) )
	{

		g_posAt.x = g_fLengthPolygon * cos( g_fAnglePolygon + D3DX_PI * 0.5f ) + g_posEye.x;
		g_posAt.z = g_fLengthPolygon * sin( g_fAnglePolygon + D3DX_PI * 0.5f ) + g_posEye.z;

		g_fAnglePolygon -= RADIUS;

	}	//	end of if


	//	���_����
	if( GetKeyboardPress( DIK_Z ) )
	{

		g_posEye.x = g_fLengthPolygon * cos( g_fAnglePolygon + D3DX_PI * 1.5f ) + g_posAt.x;
		g_posEye.z = g_fLengthPolygon * sin( g_fAnglePolygon + D3DX_PI * 1.5f ) + g_posAt.z;

		g_fAnglePolygon -= RADIUS;

	}	//	end of if

	else if( GetKeyboardPress( DIK_C ) )
	{

		g_posEye.x = g_fLengthPolygon * cos( g_fAnglePolygon + D3DX_PI * 1.5f ) + g_posAt.x;
		g_posEye.z = g_fLengthPolygon * sin( g_fAnglePolygon + D3DX_PI * 1.5f ) + g_posAt.z;

		g_fAnglePolygon += RADIUS;

	}	//	end of if

	//	�����_�ړ�
	if( GetKeyboardPress( DIK_T ) )
	{
		g_posAt.y += SPEED;

	}	//	end of if

	else if( GetKeyboardPress( DIK_B ) )
	{
		g_posAt.y -= SPEED;

	}	//	end of if

	//	�J�����ړ�
	if( GetKeyboardPress( DIK_Y ) )
	{
		g_posEye.y += SPEED;

	}	//	end of if

	else if( GetKeyboardPress( DIK_N ) )
	{
		g_posEye.y -= SPEED;

	}	//	end of if

#endif
/*
	//	���̃��[�h�̎擾
	MODE *Mode = GetNextMode();

	bool *FadeFlag = GetFadeFlag();

	if( *Mode == MODE_TITLE && *FadeFlag == false )
	{

		g_posEye.x = g_fLengthPolygon * cos( g_fAnglePolygon + D3DX_PI * 1.5f ) + g_posAt.x;
		g_posEye.z = g_fLengthPolygon * sin( g_fAnglePolygon + D3DX_PI * 1.5f ) + g_posAt.z;

		g_fAnglePolygon += 0.01f;

	}	//	end of if
*/

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawCamera( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawCamera( void )
{

#ifdef _DEBUG

//	DebugCamera();

#endif

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	���[���h���W�ϊ�
	//	���[���h�}�g���N�X�̍쐬
	D3DXMATRIX mtxWorld;

	D3DXMatrixIdentity( &mtxWorld );	//	�s���P�ʍs��ɂ���

	//	�f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	pDevice -> SetTransform( D3DTS_WORLD , &mtxWorld );

	//	�r���[���W�ϊ�
	D3DXMatrixLookAtLH( &g_mtxView , &g_posEye , &g_posAt , &g_vecUp );

	//	�f�o�C�X�Ƀr���[�ϊ��s���ݒ�
	pDevice -> SetTransform( D3DTS_VIEW , &g_mtxView );

	//	�v���W�F�N�V�����ϊ�
	//	�v���W�F�N�V�����s��̍쐬
	D3DXMATRIX mtxProj;

#if 0
	//	�p�[�X�y�N�e�B�u�s��
	D3DXMatrixPerspectiveFovLH( &mtxProj ,
								D3DX_PI / 3.0f ,	//	��p
								( float )SCREEN_WIDTH / ( SCREEN_HEIGHT / 2 ) ,	//	�A�X�y�N�g��
								CAMERA_NEAR ,	//	near	�l����0�ȉ��ɂ��Ȃ�
								CAMERA_FAR );	//	far

#endif

	//	�p�[�X�y�N�e�B�u�s��
	D3DXMatrixPerspectiveFovLH( &mtxProj ,
								D3DX_PI / 3.0f ,	//	��p
								( float )SCREEN_WIDTH / SCREEN_HEIGHT ,	//	�A�X�y�N�g��
								CAMERA_NEAR ,	//	near	�l����0�ȉ��ɂ��Ȃ�
								CAMERA_FAR );	//	far

	//	�f�o�C�X�Ƀv���W�F�N�V�����ϊ��s���ݒ�
	pDevice -> SetTransform( D3DTS_PROJECTION , &mtxProj );


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void SetCamera( D3DXVECTOR3 Pos )
 ����:		D3DXVECTOR3 Pos		���W
 �߂�l:	�Ȃ�
 ����:		�J�����̃Z�b�g
-----------------------------------------------------------------------------*/
void SetCamera( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot , float Rot2 )
{

	//posAt.x = sinf( D3DXToRadian( Rot.y + 180 ) ) * Move.x + Pos.x;
	//posAt.y = Pos.y + 20.0f;
	//posAt.z = cosf( D3DXToRadian( Rot.y + 180 ) ) * Move.z + Pos.z;

	//g_posAt.x = Pos.x;
	//g_posAt.y = Pos.y + 20.0f;
	//g_posAt.z = Pos.z;


	//g_posEye.x = Pos.x;
	//g_posEye.y = 30.0f;
	//g_posEye.z = g_posAt.z - 100.0f;




	g_posAt.x = Pos.x;
	g_posAt.y = Pos.y + 20.0f;
	g_posAt.z = Pos.z;

	g_posEye.x = sinf( D3DXToRadian( Rot2 ) ) * 50.0f + Pos.x;
	g_posEye.y = Pos.y + 40.0f;
	g_posEye.z = cosf( D3DXToRadian( Rot2 ) ) * 50.0f + Pos.z;



}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	D3DXMATRIX *GetView( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�r���[�s��̏��擾
-----------------------------------------------------------------------------*/
D3DXMATRIX GetView( void )
{
	return g_mtxView;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DebugCamera( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�J�����̕����\��
-----------------------------------------------------------------------------*/
#ifdef _DEBUG
void DebugCamera( void )
{
	int Height = 15;
	D3DXCOLOR Color = D3DXCOLOR( 255 , 255 , 255 , 255 );

	RECT rect00 = { 0 , Height , SCREEN_WIDTH , SCREEN_HEIGHT };
	RECT rect01 = { 0 , Height + 15 , SCREEN_WIDTH , SCREEN_HEIGHT };
	RECT rect02 = { 0 , Height + 45 , SCREEN_WIDTH , SCREEN_HEIGHT };

	char aStr00[ 256 ] , aStr01[ 256 ] , aStr02[ 256 ];

	sprintf( &aStr00[ 0 ] , "[ �J�������W ] ( %f : %f : %f )" , g_posEye.x , g_posEye.y , g_posEye.z );
	sprintf( &aStr01[ 0 ] , "[ �����_���W ] ( %f : %f : %f )" , g_posAt.x , g_posAt.y , g_posAt.z );
	sprintf( &aStr02[ 0 ] , "*** �J�������� ***" );

	g_pFontCamera -> DrawText( NULL ,
						&aStr00[ 0 ] ,
						-1 ,
						&rect00 ,
						DT_LEFT ,
						Color );

	g_pFontCamera -> DrawText( NULL ,
						&aStr01[ 0 ] ,
						-1 ,
						&rect01 ,
						DT_LEFT ,
						Color );

	g_pFontCamera -> DrawText( NULL ,
						&aStr02[ 0 ] ,
						-1 ,
						&rect02 ,
						DT_LEFT ,
						Color );


}	//	end of func

#endif	//	_DEBUG