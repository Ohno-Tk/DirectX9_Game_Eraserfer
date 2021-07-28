/*=============================================================================

		���ꑝ�₷�G[ Enemy1.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/02/22
-------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <time.h>
#include "main.h"
#include "Enemy1.h"
#include "Born.h"
#include "HelpNumber.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define MODEL_NAME "data/MODEL/Player/Player.x"

#define MAX_MAT ( 8 )	//	���f���̍ő�}�e���A����

#define SET_FRAME ( 325 )

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
LPD3DXMESH g_pMeshEnemy1;	//	���b�V���C���^�[�t�F�[�X�|�C���^

LPD3DXBUFFER g_pBufferMatEnemy1;	//	�}�e���A�����

DWORD g_nNumMatEnemy1;	//	�}�e���A����

LPDIRECT3DTEXTURE9 g_pTextureEnemy1[ MAX_MAT ] = { NULL };//	�e�N�X�`���C���^�[�t�F�[�X

D3DXMATERIAL* pMatEnemy1;	//	�}�e���A���|�C���^

ENEMY g_Enemy1;	//	�\����

int g_Frame;

/*-----------------------------------------------------------------------------
 �֐���:	void InitEnemy1( void )
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void InitEnemy1( void )
{

	//	���݂̎������擾
	srand((unsigned)time(NULL));


	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	HRESULT hr;

	hr = D3DXLoadMeshFromX( MODEL_NAME ,			//	�t�@�C����
							D3DXMESH_MANAGED,
							pDevice,				//	�f�o�C�X
							NULL,					//	�אڃo�b�t�@
							&g_pBufferMatEnemy1,		//	�}�e���A�������i�[
							NULL,
							&g_nNumMatEnemy1,		//	�}�e���A����
							&g_pMeshEnemy1 );		//	���b�V��

	//	���f���̃G���[�`�F�b�N
	if( FAILED( hr ) )
	{

		MessageBox( NULL , "[ Enemy1.cpp ]\n MODEL_NAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	�}�e���A�����̃|�C���^�Ƃ��ăo�b�t�@�̃A�h���X���擾
	pMatEnemy1 = ( D3DXMATERIAL* )g_pBufferMatEnemy1 -> GetBufferPointer();

	for( int i = 0 ; i < ( int )g_nNumMatEnemy1 ; i++ )
	{
		if( pMatEnemy1[ i ].pTextureFilename != NULL )
		{

			//	�e�N�X�`���̃G���[�`�F�b�N
			if( FAILED( D3DXCreateTextureFromFile( pDevice , pMatEnemy1[ i ].pTextureFilename , &g_pTextureEnemy1[ i ]  ) ) )
			{
				MessageBox( NULL , "���f���̉摜�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

			}	//	end of if

		}	//	end of if

	}	//	end of for


	//	�\���̏�����
	g_Enemy1.World.Pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Enemy1.World.Rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Enemy1.World.Scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	g_Enemy1.Use = true;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitEnemy1( void )
 ����:		
 �߂�l:	
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitEnemy1( void )
{

	if( g_pMeshEnemy1 != NULL )	//	���b�V���C���^�[�t�F�[�X�|�C���^
	{

		g_pMeshEnemy1 -> Release();
		g_pMeshEnemy1 = NULL;

	}	//	end of if

	if( g_pBufferMatEnemy1 != NULL )	//	�}�e���A�����J��
	{

		g_pBufferMatEnemy1 -> Release();
		g_pBufferMatEnemy1 = NULL;

	}	//	end of if

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UpdataEnemy1( void )
 ����:		
 �߂�l:	
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateEnemy1( void )
{

	if( g_Enemy1.Use == true )
	{

		int *Number = GetHelpNumber();

		if( g_Frame == SET_FRAME && *Number != MAX_BORN )
		{
		
			SetBorn( D3DXVECTOR3( rand()%500 - 400 , 0.0f , rand()%500 - 400 ) );

			*Number += 1;

			g_Frame = 0;
		
		}


		g_Frame++;

	}

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawEnemy1( void )
 ����:		
 �߂�l:	
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawEnemy1( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	���݃f�o�C�X�ɐݒ肳��Ă���}�e���A�����̎擾
	D3DMATERIAL9 matDef;
	pDevice -> GetMaterial( &matDef );


	if( g_Enemy1.Use == true)
	{

		//	�t�s��Ȃ��̃��[���h���W�ϊ�
		SetWorld( g_Enemy1.World.Pos , g_Enemy1.World.Rot , g_Enemy1.World.Scl );


		for( int i = 0 ; i < ( int )g_nNumMatEnemy1 ; i++ )
		{
			//	�f�o�C�X�Ƀ}�e���A����ݒ�
			pDevice -> SetMaterial( &pMatEnemy1[ i ].MatD3D );

			//	�e�N�X�`���ݒ�
			pDevice -> SetTexture( 0 , g_pTextureEnemy1[ i ] );


			//	�`��
			g_pMeshEnemy1 -> DrawSubset( i );

		}	//	end of for

	}	//	end of if

	pDevice -> SetMaterial( &matDef );

}	//	end of func

ENEMY *GetEnemy1( void )
{

	return &g_Enemy1;

}