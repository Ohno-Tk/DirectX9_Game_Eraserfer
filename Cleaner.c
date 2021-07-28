/*=============================================================================

		�������N���[�i�[[ Cleaner.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/02/23
-------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "Cleaner.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define MODEL_NAME "data/MODEL/�������N���[�i�[.x"

#define MAX_MAT ( 3 )	//	���f���̍ő�}�e���A����

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
LPD3DXMESH g_pMeshCleaner;	//	���b�V���C���^�[�t�F�[�X�|�C���^

LPD3DXBUFFER g_pBufferMatCleaner;	//	�}�e���A�����

DWORD g_nNumMatCleaner;	//	�}�e���A����

LPDIRECT3DTEXTURE9 g_pTextureCleaner[ MAX_MAT ] = { NULL };//	�e�N�X�`���C���^�[�t�F�[�X

D3DXMATERIAL* pMatCleaner;	//	�}�e���A���|�C���^

CLEANER g_Cleaner;	//	�\����

/*-----------------------------------------------------------------------------
 �֐���:	void InitCleaner( void )
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void InitCleaner( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	HRESULT hr;

	hr = D3DXLoadMeshFromX( MODEL_NAME ,			//	�t�@�C����
							D3DXMESH_MANAGED,
							pDevice,				//	�f�o�C�X
							NULL,					//	�אڃo�b�t�@
							&g_pBufferMatCleaner,		//	�}�e���A�������i�[
							NULL,
							&g_nNumMatCleaner,		//	�}�e���A����
							&g_pMeshCleaner );		//	���b�V��

	//	���f���̃G���[�`�F�b�N
	if( FAILED( hr ) )
	{

		MessageBox( NULL , "[ Cleaner.cpp ]\n MODEL_NAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	�}�e���A�����̃|�C���^�Ƃ��ăo�b�t�@�̃A�h���X���擾
	pMatCleaner = ( D3DXMATERIAL* )g_pBufferMatCleaner -> GetBufferPointer();

	for( int i = 0 ; i < ( int )g_nNumMatCleaner ; i++ )
	{
		if( pMatCleaner[ i ].pTextureFilename != NULL )
		{

			//	�e�N�X�`���̃G���[�`�F�b�N
			if( FAILED( D3DXCreateTextureFromFile( pDevice , pMatCleaner[ i ].pTextureFilename , &g_pTextureCleaner[ i ]  ) ) )
			{
				MessageBox( NULL , "���f���̉摜�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

			}	//	end of if

		}	//	end of if

	}	//	end of for


	//	�\���̏�����
	g_Cleaner.World.Pos = D3DXVECTOR3( 780.0f , 50.0f , -860.0f );
	g_Cleaner.World.Rot = D3DXVECTOR3( 270.0f , 0.0f , 180.0f );
	g_Cleaner.World.Scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
	g_Cleaner.Radius = 120.0f;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitCleaner( void )
 ����:		
 �߂�l:	
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitCleaner( void )
{

	if( g_pMeshCleaner != NULL )	//	���b�V���C���^�[�t�F�[�X�|�C���^
	{

		g_pMeshCleaner -> Release();
		g_pMeshCleaner = NULL;

	}	//	end of if

	if( g_pBufferMatCleaner != NULL )	//	�}�e���A�����J��
	{

		g_pBufferMatCleaner -> Release();
		g_pBufferMatCleaner = NULL;

	}	//	end of if

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UpdataCleaner( void )
 ����:		
 �߂�l:	
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateCleaner( void )
{
}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawCleaner( void )
 ����:		
 �߂�l:	
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawCleaner( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	���݃f�o�C�X�ɐݒ肳��Ă���}�e���A�����̎擾
	D3DMATERIAL9 matDef;
	pDevice -> GetMaterial( &matDef );



	//	�t�s��Ȃ��̃��[���h���W�ϊ�
	SetWorld( g_Cleaner.World.Pos , g_Cleaner.World.Rot , g_Cleaner.World.Scl );


	for( int i = 0 ; i < ( int )g_nNumMatCleaner ; i++ )
	{
		//	�f�o�C�X�Ƀ}�e���A����ݒ�
		pDevice -> SetMaterial( &pMatCleaner[ i ].MatD3D );

		//	�e�N�X�`���ݒ�
		pDevice -> SetTexture( 0 , g_pTextureCleaner[ i ] );


		//	�`��
		g_pMeshCleaner -> DrawSubset( i );

	}	//	end of for


	pDevice -> SetMaterial( &matDef );

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	CLEANER *GetCleaner( void )
 ����:		
 �߂�l:	return &g_Cleaner;
 ����:		�������N���[�i�[���̎擾
-----------------------------------------------------------------------------*/
CLEANER *GetCleaner( void )
{

	return &g_Cleaner;

}	//	end of func