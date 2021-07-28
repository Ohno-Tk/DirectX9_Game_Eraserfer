/*=============================================================================

		���b�V���E�H�[��[ MeshWall.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2016/11/09
-------------------------------------------------------------------------------
	���@Update
		2016/11/09
=============================================================================*/
/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "MeshWall.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/MeshWall.jpg"

#define MAX_WALL ( 4 )	//	�ǂ̍ő吔

#define WALL_WIDTH ( 10 )	//	���̖���
#define WALL_HEIGHT ( 1 )	//	�c�̖���

#define WIDTH_ONE_SIZE ( 175 )	//	����1�ӂ̑傫��
#define HEIGHT_ONE_SIZE ( 20 )	//	�c��1�ӂ̑傫��

#define WALL_POSITON ( WALL_WIDTH * WIDTH_ONE_SIZE / 2 )	//	�ǂ̈ʒu

#define VERTEX ( ( ( 2 + 2 * WALL_WIDTH ) * WALL_HEIGHT + ( WALL_HEIGHT - 1 ) * 2 ) )	//	���_��

/*-----------------------------------------------------------------------------
	��
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�\����
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�v���g�^�C�v�錾
-----------------------------------------------------------------------------*/

//	���_�̍쐬
HRESULT MakeVertexMeshWall( LPDIRECT3DDEVICE9 pDevice , UINT NumBlock_X , UINT NumBlock_Y , float SizeBlock_X , float SizeBlock_Y );

//	�ǂ̃Z�b�g
void SetWall( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot );

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferMeshWall = NULL;	//	���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBufferMeshWall = NULL;	//	�C���f�b�N�X�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^�̃A�h���X
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;//	�e�N�X�`���C���^�[�t�F�[�X

MESHWALL g_MeshWall[ MAX_WALL ];	//	���b�V���E�H�[���\����

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT InitMeshWall( void )
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void InitMeshWall( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�e�N�X�`���̃G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureMeshWall  ) ) )
	{
		MessageBox( NULL , "[ MeshWall.cpp ]\n POLYGON00_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	���_�̍쐬
	MakeVertexMeshWall( pDevice , WALL_WIDTH , WALL_HEIGHT , WIDTH_ONE_SIZE , HEIGHT_ONE_SIZE );


	//	�\���̏�����
	for( int Cnt = 0 ; Cnt < MAX_WALL ; Cnt++ )
	{
		//	���W
		g_MeshWall[ Cnt ].World.Pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	�g�嗦
		g_MeshWall[ Cnt ].World.Scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//	��]��
		g_MeshWall[ Cnt ].World.Rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	�g�p�t���O
		g_MeshWall[ Cnt ].Use = false;

	}	//	end of for


	//	�ǂ̃Z�b�g

	//	��O�̕�
	SetWall( D3DXVECTOR3( 0.0f , 0.0f , -870.0f ) , D3DXVECTOR3( 0.0f , 180.0f , 0.0f ) );


	//�E�̕�
	SetWall( D3DXVECTOR3( 870.0f , 0.0f , 0.0f ) , D3DXVECTOR3( 0.0f , 90.0f , 0.0f ) );


	//	���̕�
	SetWall( D3DXVECTOR3( -870.0f , 0.0f , 0.0f ) , D3DXVECTOR3( 0.0f , -90.0f , 0.0f ) );

	//	���̕�
	SetWall( D3DXVECTOR3( 0.0f , 0.0f , 870.0f ) , D3DXVECTOR3( 0.0f , 0.0f , 0.0f ) );


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitMeshWall( void )
 ����:		
 �߂�l:	
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitMeshWall( void )
{

	if( g_pVtxBufferMeshWall != NULL )	//	���_�o�b�t�@�C���^�t�F�[�X�J��
	{
		g_pVtxBufferMeshWall -> Release();
		g_pVtxBufferMeshWall = NULL;

	}	//	end of if

	if( g_pIdxBufferMeshWall != NULL )	//	�C���f�b�N�X�o�b�t�@�C���^�t�F�[�X�J��
	{
		g_pIdxBufferMeshWall -> Release();
		g_pIdxBufferMeshWall = NULL;

	}	//	end of if

	if( g_pTextureMeshWall != NULL )	//	�e�N�X�`���|���S���J��
	{
		g_pTextureMeshWall -> Release();
		g_pTextureMeshWall = NULL;

	}	//	end of if

}	//	end of func
 
/*-----------------------------------------------------------------------------
 �֐���:	void UpdateMeshWall( void )
 ����:		
 �߂�l:	
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateMeshWall( void )
{

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawMeshWall( void )
 ����:		
 �߂�l:	
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawMeshWall( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�p�C�v���C���̃X�g���[��
	pDevice -> SetStreamSource( 0 , g_pVtxBufferMeshWall , 0 , sizeof( VERTEX_3D ));


	//	�C���f�b�N�X�̃Z�b�g
	pDevice -> SetIndices( g_pIdxBufferMeshWall );


	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_3D );


	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureMeshWall );



	for( int Cnt = 0 ; Cnt < MAX_WALL ; Cnt++ )
	{

		if( g_MeshWall[ Cnt ].Use == true )
		{

			//	�t�s��Ȃ��̃��[���h���W�ϊ�
			SetWorld( g_MeshWall[ Cnt ].World.Pos , g_MeshWall[ Cnt ].World.Rot , g_MeshWall[ Cnt ].World.Scl );

			//	�|���S���̕`��
			pDevice -> DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP , 0 , 0 , VERTEX , 0 , VERTEX - 2 );

		}	//	end of if

	}	//	end of for

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void MakeVertexMeshWall( LPDIRECT3DDEVICE9 pDevice , UINT NumBlock_X , UINT NumBlock_Y , float SizeBlock_X , float SizeBlock_Y )
 ����:		LPDIRECT3DDEVICE9 pDevice	�f�o�C�X
			UINT NumBlock_X				���̃u���b�N��
			UINT NumBlock_Y				�c�̃u���b�N��
			float SizeBlock_X			X���̑傫��
			float SizeBlock_Y			Y���̑傫��
 �߂�l:	�ǂ��ꍇ	return S_OK;
			�_���ȏꍇ	return E_FAIL;
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
HRESULT MakeVertexMeshWall( LPDIRECT3DDEVICE9 pDevice , UINT NumBlock_X , UINT NumBlock_Y , float SizeBlock_X , float SizeBlock_Y )
{

	VERTEX_3D* pVtx;	//	���z�A�h���X���擾����|�C���^�ϐ�

	WORD* pIdx;	//	�|�C���^�ϐ�

	HRESULT hr;

	//	���_���̌v�Z
	int VerTex = ( NumBlock_X + 1 ) * ( NumBlock_Y + 1 );

	//	�C���f�b�N�X�o�b�t�@�̌v�Z
	int IdxVerTexMeshWall = ( 2 + 2 * NumBlock_X ) * NumBlock_Y + ( NumBlock_Y - 1 ) * 2;


	//	���_�o�b�t�@�̐���
	if( FAILED( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * NUM_VERTEX * VerTex , D3DUSAGE_WRITEONLY , FVF_VERTEX_3D , D3DPOOL_MANAGED , &g_pVtxBufferMeshWall , NULL ) ) )
	{

		return E_FAIL;

	}	//	end of if

	//	�C���f�b�N�X�o�b�t�@�̐���
	hr = pDevice -> CreateIndexBuffer(
		sizeof( WORD ) * IdxVerTexMeshWall ,	//	�o�b�t�@��
		D3DUSAGE_WRITEONLY ,	//	�g�p���@�t���O
		D3DFMT_INDEX16 , //	�C���f�b�N�X�t�H�[�}�b�g
		D3DPOOL_MANAGED , //	�������̊Ǘ����@
		&g_pIdxBufferMeshWall ,	//	�C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^�̃A�h���X
		NULL);

	if( FAILED( hr ) )
	{

		return E_FAIL;

	}	//	end of if


	//	�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferMeshWall -> Lock( 0 , 0 , (void**)&pVtx , 0 );

	//	�c
	for( UINT Cnt1 = 0 ; Cnt1 < NumBlock_Y + 1 ; Cnt1++ )
	{
		//	��
		for( UINT Cnt2 = 0 ; Cnt2 < NumBlock_X + 1 ; Cnt2++ )
		{

			//	���_���W�̐ݒ�
			//	���̕�
			pVtx[ 0 ].pos = D3DXVECTOR3( ( SizeBlock_X * NumBlock_X / 2 ) - NumBlock_X * SizeBlock_X + ( SizeBlock_X * Cnt2 ) , ( SizeBlock_Y * NumBlock_Y ) - ( SizeBlock_Y * Cnt1 ) , 0.0f );


			//	�@���̐ݒ�
			pVtx[ 0 ].normal = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );


			//	���_�F�̐ݒ�
			pVtx[ 0 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );


			//	�e�N�X�`�����W�̐ݒ�
			pVtx[ 0 ].tex = D3DXVECTOR2( ( float )Cnt2 , ( float )Cnt1 );

			pVtx ++;	//	�|�C���^�����炷

		}	//	end of for

	}	//	end of for

	//	�o�b�t�@�̃A�����b�N
	g_pVtxBufferMeshWall -> Unlock();



	//	�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBufferMeshWall -> Lock( 0 , 0 , (void**)&pIdx , 0 );

	//	�c
	for( UINT Cnt1 = 0 ; Cnt1 < NumBlock_Y ; Cnt1++ )
	{
		//	�͂��߂���Ȃ�������
		//	�k�ރ|���S��
		if( Cnt1 != 0 )
		{
			//	1�_�ł�

			pIdx[ 0 ] = ( Cnt1 + 1 ) * ( NumBlock_X + 1 );

			pIdx++;	//	�|�C���^�����炷

		}	//	end of if

		//	2�_�ł�

		pIdx[ 0 ] = ( Cnt1 + 1 ) * ( NumBlock_X + 1 );
		pIdx[ 1 ] = ( Cnt1 + 1 ) * ( NumBlock_X + 1 ) - ( NumBlock_X + 1 );

		pIdx += 2;	//	�|�C���^�����炷

		//	��
		for( UINT Cnt2 = 0 ; Cnt2 < NumBlock_X ; Cnt2++ )
		{
			//	2�_�ł�

			pIdx[ 0 ] = ( ( Cnt1 + 1 ) * ( NumBlock_X + 1 ) + 1 ) + Cnt2;
			pIdx[ 1 ] = ( ( Cnt1 + 1 ) * ( NumBlock_X + 1 ) + 1 ) - ( NumBlock_X + 1 ) + Cnt2;

			pIdx += 2;	//	�|�C���^�����炷

		}	//	end of for

		//	�Ōザ��Ȃ�������
		//	�k�ރ|���S��
		if( Cnt1 != NumBlock_Y - 1 )
		{
			//	1�_�ł�

			pIdx[ 0 ] = ( Cnt1 + 1 ) * ( NumBlock_X + 1 ) - 1;

			pIdx++;	//	�|�C���^�����炷

		}	//	end of if

	}	//	end of for


	//	�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBufferMeshWall -> Unlock();

	return S_OK;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void SetWall( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot )
 ����:		D3DXVECTOR3 Pos		���W
			D3DXVECTOR3 Rot		��]��
 �߂�l:	
 ����:		�ǂ̃Z�b�g
-----------------------------------------------------------------------------*/
void SetWall( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot )
{

	for( int Cnt = 0 ; Cnt < MAX_WALL ; Cnt++ )
	{

		if( g_MeshWall[ Cnt ].Use == false )
		{

			//	���W
			g_MeshWall[ Cnt ].World.Pos = Pos;

			//	��]��
			g_MeshWall[ Cnt ].World.Rot = Rot;

			//	�g�p�t���O
			g_MeshWall[ Cnt ].Use = true;

			break;

		}	//	end of if

	}	//	end of for

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	MESHWALL *GetMeshWall( )
 ����:		
 �߂�l:	�Ȃ�
 ����:		���b�V���E�H�[�����擾
-----------------------------------------------------------------------------*/
MESHWALL *GetMeshWall( void )
{

	return &g_MeshWall[ 0 ];

}	//	end of func