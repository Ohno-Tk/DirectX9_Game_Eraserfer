/*=============================================================================

		���b�V���t�B�[���h[ MeshField.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2016/11/09
-------------------------------------------------------------------------------
	���@Update
		2016/11/02
=============================================================================*/
/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "MeshField.h"
#include "fade.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/Field.jpg"

#define MAX_FIELD ( 1 )	//	�ő�t�B�[���h��

#define FIELD00_WIDTH ( 35 )	//	���̖���
#define FIELD00_HEIGHT ( 35 )	//	�c�̖���

#define ONE_SIZE ( 50 )	//	1�ӂ̑傫��

#define VERTEX ( ( ( 2 + 2 * FIELD00_WIDTH ) * FIELD00_HEIGHT + ( FIELD00_HEIGHT - 1 ) * 2 ) ) //	���_��

/*-----------------------------------------------------------------------------
	��
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�\����
-----------------------------------------------------------------------------*/
typedef struct
{
	WORLD World;	//	���[���h�ϊ��p�ϐ�
	bool Use;	//	�g�p�t���O

}MESHFIELD;

/*-----------------------------------------------------------------------------
	�v���g�^�C�v�錾
-----------------------------------------------------------------------------*/

//	���_�̍쐬
HRESULT MakeVertexMeshField( LPDIRECT3DDEVICE9 pDevice , UINT NumBlock_X , UINT NumBlock_Y , float SizeBlock_X , float SizeBlock_Z );

//	���_�̕ύX
void VerTexField( void );

//	���b�V���t�B�[���h�̃Z�b�g
void SetField( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot );

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferField = NULL;	//	���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBufferField = NULL;	//	�C���f�b�N�X�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^�̃A�h���X
LPDIRECT3DTEXTURE9 g_pTextureField = NULL;//	�e�N�X�`���C���^�[�t�F�[�X

MESHFIELD g_MeshField[ MAX_FIELD ];	//	���b�V���t�B�[���h�\����

float g_VSet;	//	V���W

/*-----------------------------------------------------------------------------
 �֐���:	void InitMeshField( void )
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void InitMeshField( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�e�N�X�`���̃G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureField  ) ) )
	{
		MessageBox( NULL , "[ MeshField.cpp ]\n POLYGON00_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	���_�̍쐬
	MakeVertexMeshField( pDevice , FIELD00_WIDTH , FIELD00_HEIGHT , ONE_SIZE , ONE_SIZE );


	//	�\���̏�����
	for( int Cnt = 0 ; Cnt < MAX_FIELD ; Cnt++ )
	{
		//	���W
		g_MeshField[ Cnt ].World.Pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	�g�嗦
		g_MeshField[ Cnt ].World.Scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//	��]��
		g_MeshField[ Cnt ].World.Rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	�g�p�t���O
		g_MeshField[ Cnt ].Use = false;

	}	//	end of for


	//	�ϐ�������

	//	V���W
	g_VSet = 0.0f;


	//	���b�V���t�B�[���h�̃Z�b�g
	SetField( D3DXVECTOR3( 0.0f , 0.0f , 0.0f ) , D3DXVECTOR3( 0.0f , 0.0f , 0.0f ) );

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitMeshField( void )
 ����:		
 �߂�l:	
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitMeshField( void )
{

	if( g_pVtxBufferField != NULL )	//	���_�o�b�t�@�C���^�t�F�[�X�J��
	{

		g_pVtxBufferField -> Release();
		g_pVtxBufferField = NULL;

	}	//	end of if

	if( g_pIdxBufferField != NULL )	//	�C���f�b�N�X�o�b�t�@�C���^�t�F�[�X�J��
	{

		g_pIdxBufferField -> Release();
		g_pIdxBufferField = NULL;

	}	//	end of if

	if( g_pTextureField != NULL )	//	�e�N�X�`���|���S���J��
	{

		g_pTextureField -> Release();
		g_pTextureField = NULL;

	}	//	end of if

}	//	end of func
 
/*-----------------------------------------------------------------------------
 �֐���:	void UpdateMeshField( void )
 ����:		
 �߂�l:	
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateMeshField( void )
{

	//	���̃��[�h�̎擾
	MODE *ModeNext = GetNextMode();

	//	���[�h�̎擾
	MODE *Mode = GetMode();


	//if( *ModeNext == MODE_TITLE )
	//{

	//	//	���_�̕ύX
	//	VerTexField();


	//	//	V���W�����炷
	//	g_VSet -= 0.07f;

	//}	//	end of if

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawMeshField( void )
 ����:		
 �߂�l:	
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawMeshField( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�p�C�v���C���̃X�g���[��
	pDevice -> SetStreamSource( 0 , g_pVtxBufferField , 0 , sizeof( VERTEX_3D ));

	pDevice -> SetIndices( g_pIdxBufferField );

	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_3D );

	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureField );


	for( int Cnt = 0 ; Cnt < MAX_FIELD ; Cnt++ )
	{

		if( g_MeshField[ Cnt ].Use == true )
		{

			//	�t�s��Ȃ��̃��[���h���W�ϊ�
			SetWorld( g_MeshField[ Cnt ].World.Pos , g_MeshField[ Cnt ].World.Rot , g_MeshField[ Cnt ].World.Scl );

			//	�|���S���̕`��
			pDevice -> DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP , 0 , 0 , VERTEX , 0 , VERTEX - 2 );

		}	//	end of if

	}	//	end of for

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT MakeVertexMeshField( LPDIRECT3DDEVICE9 pDevice , UINT NumBlock_X , UINT NumBlock_Y , float SizeBlock_X , float SizeBlock_Z )
 ����:		LPDIRECT3DDEVICE9 pDevice		�f�o�C�X
			UINT NumBlock_X					���̃u���b�N��
			UINT NumBlock_Y					�c�̃u���b�N��
			float SizeBlock_X				X���̑傫��
			float SizeBlock_Z				Z���̑傫��
 �߂�l:	�ǂ��ꍇ	return S_OK;
			�_���ȏꍇ	return E_FAIL;
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
HRESULT MakeVertexMeshField( LPDIRECT3DDEVICE9 pDevice , UINT NumBlock_X , UINT NumBlock_Y , float SizeBlock_X , float SizeBlock_Z )
{

	VERTEX_3D* pVtx;	//	���z�A�h���X���擾����|�C���^�ϐ�

	WORD* pIdx;	//	�|�C���^�ϐ�

	HRESULT hr;

	D3DXVECTOR3 Pos;

	float x = 1.0f / FIELD00_WIDTH;
	float y = 1.0f / FIELD00_HEIGHT;


	//	���_���̌v�Z
	int VerTex = ( NumBlock_X + 1 ) * ( NumBlock_Y + 1 );


	//	�C���f�b�N�X�o�b�t�@�̌v�Z
	int IdxVerTex = ( 2 + 2 * NumBlock_X ) * NumBlock_Y + ( NumBlock_Y - 1 ) * 2;


	//	���_�o�b�t�@�̐���
	if( FAILED( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * NUM_VERTEX * VerTex , D3DUSAGE_WRITEONLY , FVF_VERTEX_3D , D3DPOOL_MANAGED , &g_pVtxBufferField , NULL ) ) )
	{

		return E_FAIL;

	}	//	end of if


	//	�C���f�b�N�X�o�b�t�@�̐���
	hr = pDevice -> CreateIndexBuffer(
		sizeof( WORD ) * IdxVerTex ,	//	�o�b�t�@��
		D3DUSAGE_WRITEONLY ,	//	�g�p���@�t���O
		D3DFMT_INDEX16 , //	�C���f�b�N�X�t�H�[�}�b�g
		D3DPOOL_MANAGED , //	�������̊Ǘ����@
		&g_pIdxBufferField ,	//	�C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^�̃A�h���X
		NULL);


	//	�C���f�b�N�X�o�b�t�@�̃G���[�`�F�b�N
	if( FAILED( hr ) )
	{

		return E_FAIL;

	}	//	end of if


	//	�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferField -> Lock( 0 , 0 , (void**)&pVtx , 0 );


	//	�c
	for( UINT Cnt1 = 0 ; Cnt1 < NumBlock_Y + 1 ; Cnt1++ )
	{

		//	��
		for( UINT Cnt2 = 0 ; Cnt2 < NumBlock_X + 1 ; Cnt2++ )
		{

			//	���W�̐ݒ�
			Pos.x = ( SizeBlock_X * NumBlock_X / 2 ) - NumBlock_X * SizeBlock_X + ( SizeBlock_X * Cnt2 );
			Pos.y = 0.0f;
			Pos.z = ( SizeBlock_Z * NumBlock_Y / 2 ) - ( SizeBlock_Z * Cnt1 );


			//	���_���W�̐ݒ�
			pVtx[ 0 ].pos = D3DXVECTOR3( Pos.x , Pos.y , Pos.z );


			//	�@���̐ݒ�
			pVtx[ 0 ].normal = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );


			//	���_�F�̐ݒ�
			pVtx[ 0 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );


			//	�e�N�X�`�����W�̐ݒ�
//			pVtx[ 0 ].tex = D3DXVECTOR2( ( float )Cnt2 , ( float )Cnt1 );
			pVtx[ 0 ].tex = D3DXVECTOR2( x * Cnt2 , y * Cnt1 );


			pVtx ++;	//	�|�C���^�����炷

		}	//	end of for

	}	//	end of for


	//	�o�b�t�@�̃A�����b�N
	g_pVtxBufferField -> Unlock();



	//	�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBufferField -> Lock( 0 , 0 , (void**)&pIdx , 0 );


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
	g_pIdxBufferField -> Unlock();

	return S_OK;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void VerTexField( void )
 ����:		
 �߂�l:	
 ����:		���_�̕ύX
-----------------------------------------------------------------------------*/
void VerTexField( void )
{

	float x = 1.0f / FIELD00_WIDTH;
	float y = 1.0f / FIELD00_HEIGHT;

	VERTEX_3D* pVtx;	//	���z�A�h���X���擾����|�C���^�ϐ�


	//	�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferField -> Lock( 0 , 0 , (void**)&pVtx , 0 );


	//	�c
	for( UINT Cnt1 = 0 ; Cnt1 < FIELD00_HEIGHT + 1 ; Cnt1++ )
	{

		//	��
		for( UINT Cnt2 = 0 ; Cnt2 < FIELD00_WIDTH + 1 ; Cnt2++ )
		{

			//	�e�N�X�`�����W�̐ݒ�
//			pVtx[ 0 ].tex = D3DXVECTOR2( ( float )Cnt2 , ( float )Cnt1 + g_VSet );
			pVtx[ 0 ].tex = D3DXVECTOR2( x * Cnt2 , y * ( Cnt1 + g_VSet ) );


			pVtx ++;	//	�|�C���^�����炷

		}	//	end of for

	}	//	end of for


	//	�o�b�t�@�̃A�����b�N
	g_pVtxBufferField -> Unlock();

}

/*-----------------------------------------------------------------------------
 �֐���:	void SetField( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot )
 ����:		D3DXVECTOR3 Pos		���W
			D3DXVECTOR3 Rot		��]��
 �߂�l:	
 ����:		���b�V���t�B�[���h�̃Z�b�g
-----------------------------------------------------------------------------*/
void SetField( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot )
{
	for( int CntField = 0 ; CntField < MAX_FIELD ; CntField++ )
	{

		if( g_MeshField[ CntField ].Use == false )
		{

			//	���W
			g_MeshField[ CntField ].World.Pos = Pos;

			//	��]��
			g_MeshField[ CntField ].World.Rot = Rot;

			//	�g�p�t���O
			g_MeshField[ CntField ].Use = true;

			break;

		}	//	end of if

	}	//	end of for

}	//	end of func