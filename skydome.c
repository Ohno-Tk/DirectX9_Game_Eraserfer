/*=============================================================================

		�X�J�C�h�[��[ skydome.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2016/11/14
-------------------------------------------------------------------------------
	���@Update
		2016/11/14
=============================================================================*/
/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "skydome.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/Skydome.jpg"

#define FIELD_WIDTH ( 20 )	//	���̖���
#define FIELD_HEIGHT ( 30 )	//	�c�̖���

#define RADIUS ( 2000.0f )	//	���a

#define VERTEX ( ( ( 2 + 2 * FIELD_WIDTH ) * FIELD_HEIGHT + ( FIELD_HEIGHT - 1 ) * 2 ) ) //	���_��

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

}SKYDOME;

/*-----------------------------------------------------------------------------
	�v���g�^�C�v�錾
-----------------------------------------------------------------------------*/

//	���_�̍쐬
HRESULT MakeVertexSkyDome( LPDIRECT3DDEVICE9 pDevice , int NumBlock_X , int NumBlock_Y , float Radius );

//	���b�V���t�B�[���h�̃Z�b�g
void SetSkyDome( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot );

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferSkyDome = NULL;	//	���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBufferSkyDome = NULL;	//	�C���f�b�N�X�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^�̃A�h���X

LPDIRECT3DTEXTURE9 g_pTextureSkyDome = NULL;	//	�e�N�X�`���C���^�[�t�F�[�X

SKYDOME g_SkyDome;		//	�X�J�C�h�[���\����

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT InitSkyDome( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		������
-----------------------------------------------------------------------------*/
void InitSkydome( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureSkyDome  ) ) )
	{
		MessageBox( NULL , "[ skydome.cpp ]\n POLYGON00_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	���_�̍쐬
	MakeVertexSkyDome( pDevice , FIELD_WIDTH , FIELD_HEIGHT , RADIUS );


	//	�\���̏�����

	//	���W
	g_SkyDome.World.Pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

	//	��]��
	g_SkyDome.World.Rot =  D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

	//	�g�嗦
	g_SkyDome.World.Scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	//	�g�p�t���O
	g_SkyDome.Use = false;



	//	���b�V���t�B�[���h�̃Z�b�g
	SetSkyDome( D3DXVECTOR3( 0.0f , -100.0f , 0.0f ) , D3DXVECTOR3( 0.0f , 0.0f , 0.0f ) );

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitSkyDome( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitSkydome( void )
{

	if( g_pVtxBufferSkyDome != NULL )	//	���_�o�b�t�@�C���^�t�F�[�X�J��
	{
		g_pVtxBufferSkyDome -> Release();
		g_pVtxBufferSkyDome = NULL;

	}	//	end of if

	if( g_pIdxBufferSkyDome != NULL )	//	�C���f�b�N�X�o�b�t�@�C���^�t�F�[�X�J��
	{
		g_pIdxBufferSkyDome -> Release();
		g_pIdxBufferSkyDome = NULL;

	}	//	end of if

	if( g_pTextureSkyDome != NULL )	//	�e�N�X�`���|���S���J��
	{
		g_pTextureSkyDome -> Release();
		g_pTextureSkyDome = NULL;

	}	//	end of if

}	//	end of func
 
/*-----------------------------------------------------------------------------
 �֐���:	void UpdateSkyDome( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateSkydome( void )
{

	g_SkyDome.World.Rot.y += 0.01f;

	if( g_SkyDome.World.Rot.y >= 360 )
	{
		g_SkyDome.World.Rot.y = 0;

	}	//	end of if

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawSkyDome( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawSkydome( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�p�C�v���C���̃X�g���[��
	pDevice -> SetStreamSource( 0 , g_pVtxBufferSkyDome , 0 , sizeof( VERTEX_3D ));

	pDevice -> SetIndices( g_pIdxBufferSkyDome );

	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_3D );

	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureSkyDome );

	if( g_SkyDome.Use == true )
	{

		//	�t�s��Ȃ��̃��[���h���W�ϊ�
		SetWorld( g_SkyDome.World.Pos , g_SkyDome.World.Rot , g_SkyDome.World.Scl );

		//	�|���S���̕`��
		pDevice -> DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP , 0 , 0 , VERTEX , 0 , VERTEX - 2 );

	}	//	end of if


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT MakeVertex( LPDIRECT3DDEVICE9 pDevice , UINT NumBlock_X , UINT NumBlock_Y , float Radius )
 ����:		LPDIRECT3DDEVICE9 pDevice	�f�o�C�X
			UINT NumBlock_X				���̖���
			UINT NumBlock_Y				�c�̖���
			float Radius				���a
 �߂�l:	�ǂ��ꍇ	return S_OK;
			�_���ȏꍇ	return E_FAIL;
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
HRESULT MakeVertexSkyDome( LPDIRECT3DDEVICE9 pDevice , int NumBlock_X , int NumBlock_Y , float Radius )
{

	//	���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_3D* pVtx;

	//	�|�C���^�ϐ�
	WORD* pIdx;

	HRESULT hr;

	//	���W�̊i�[�ϐ�
	D3DXVECTOR3 Pos;

	//	���_���̌v�Z
	int VerTex = ( NumBlock_X + 1 ) * ( NumBlock_Y + 1 );

	//	�C���f�b�N�X�o�b�t�@�̌v�Z
	int IdxVerTex = ((2 + 2 * NumBlock_X) * NumBlock_Y+ ( NumBlock_Y - 1 ) * 2);

	//	360�x�̈���̊p�x���߂�
	float Rot_XZ = ( float )360 / NumBlock_X;

	//	180�x�̈���̊p�x���߂�( ���~�̏ꍇ��90�ɂ��� , �~�̏ꍇ��180�ɂ��� )
	float Rot_Y = ( float )90 / NumBlock_Y;

	//	���UV���W�����߂�
	float Uset = 1.0f / NumBlock_X;
	float Vset = 1.0f / NumBlock_Y;



	//	���_�o�b�t�@�̐���
	if( FAILED( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * NUM_VERTEX * VerTex , D3DUSAGE_WRITEONLY , FVF_VERTEX_3D , D3DPOOL_MANAGED , &g_pVtxBufferSkyDome , NULL ) ) )
	{
		return E_FAIL;

	}	//	end of if


	//	�C���f�b�N�X�o�b�t�@�̐���
	hr = pDevice -> CreateIndexBuffer(
		sizeof( WORD ) * IdxVerTex ,	//	�o�b�t�@��
		D3DUSAGE_WRITEONLY ,	//	�g�p���@�t���O
		D3DFMT_INDEX16 , //	�C���f�b�N�X�t�H�[�}�b�g
		D3DPOOL_MANAGED , //	�������̊Ǘ����@
		&g_pIdxBufferSkyDome ,	//	�C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^�̃A�h���X
		NULL);

	if( FAILED( hr ) )
	{

		return E_FAIL;

	}	//	end of if

	//	�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferSkyDome -> Lock( 0 , 0 , (void**)&pVtx , 0 );

	//	�c
	for( int Cnt1 = 0 ; Cnt1 < NumBlock_Y + 1 ; Cnt1++ )
	{
		//	�p�x�̐ݒ�
		float ��y = 90 - ( Cnt1 * Rot_Y );

		//	�ŏ���90�x���狁�߂�
		//	90�x��������Ă���
		Pos.y = Radius * sinf( D3DXToRadian( ��y ) );

		//	��
		for( int Cnt2 = 0 ; Cnt2 < NumBlock_X + 1 ; Cnt2++ )
		{
			//	�p�x�̐ݒ�
			float ��xz = ( -1 * Cnt2 ) * Rot_XZ;

			//	XZ����360�x���߂�
			Pos.x = Radius * cosf( D3DXToRadian( ��y ) ) * cosf( D3DXToRadian( ��xz ) );
			Pos.z = Radius * cosf( D3DXToRadian( ��y ) ) * sinf( D3DXToRadian( ��xz ) );


			//	���_���W�̐ݒ�
			pVtx[ 0 ].pos = D3DXVECTOR3( Pos.x , Pos.y , Pos.z );


			//	�@���̐ݒ�
			pVtx[ 0 ].normal = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );


			//	���_�F�̐ݒ�
			pVtx[ 0 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );


			//	�e�N�X�`�����W�̐ݒ�
			pVtx[ 0 ].tex = D3DXVECTOR2( Cnt2 * Uset , Cnt1 * Vset );

			pVtx ++;	//	�|�C���^�����炷

		}	//	end of for

	}	//	end of for

	//	�o�b�t�@�̃A�����b�N
	g_pVtxBufferSkyDome -> Unlock();


	//	�C���f�b�N�X�o�b�t�@�����b�N
	g_pIdxBufferSkyDome -> Lock( 0 , 0 , (void**)&pIdx , 0 );

#if 1
	//	���v���𗠖�
	//	�c
	for( int Cnt1 = 0 ; Cnt1 < NumBlock_Y ; Cnt1++ )
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
		for( int Cnt2 = 0 ; Cnt2 < NumBlock_X ; Cnt2++ )
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
#endif

	//for(int h = 0; h < NumBlock_Y; h ++)
	//{
	//	if( h != 0 )
	//	{

	//		pIdx[ 0 ] = (h - 1) * ( NumBlock_X + 1 ) + NumBlock_X;

	//		pIdx ++;

	//		pIdx[ 0 ] = h * ( NumBlock_X + 1 ) + ( NumBlock_X + 1 );

	//		pIdx ++;
	//	}

	//	pIdx[ 0 ] = h * ( NumBlock_X + 1 ) + ( NumBlock_X + 1 );

	//	pIdx ++;


	//	pIdx[ 0 ] = h * ( NumBlock_X + 1 );

	//	pIdx ++;

	//	for(int w = 0; w < NumBlock_X; w ++)
	//	{
	//		pIdx[ 0 ] = h * ( NumBlock_X + 1 ) + (w + 1) + ( NumBlock_X + 1 );

	//		pIdx ++;

	//		pIdx[ 0 ] = h * ( NumBlock_X + 1 ) + (w + 1) ;

	//		pIdx ++;

	//	}

	//
	//}

	//	�t���v���𗠖ʂƂ���
	//	�c
	//for( int Cnt1 = 0 ; Cnt1 < NumBlock_Y ; Cnt1++ )
	//{
	//	//	�͂��߂���Ȃ�������
	//	//	�k�ރ|���S��
	//	if( Cnt1 != 0 )
	//	{
	//		//	1�_�ł�

	//		pIdx[ 0 ] = ( Cnt1 + 1 ) * ( NumBlock_X + 1 ) - 1;

	//		pIdx++;	//	�|�C���^�����炷

	//	}	//	end of if

	//	//	2�_�ł�
	//	pIdx[ 1 ] = ( Cnt1 + 1 ) * ( NumBlock_X + 1 );
	//	pIdx[ 0 ] = ( Cnt1 + 1 ) * ( NumBlock_X + 1 ) - ( NumBlock_X + 1 );

	//	pIdx += 2;	//	�|�C���^�����炷

	//	//	��
	//	for( int Cnt2 = 0 ; Cnt2 < NumBlock_X ; Cnt2++ )
	//	{
	//		//	2�_�ł�
	//		pIdx[ 1 ] = ( ( Cnt1 + 1 ) * ( NumBlock_X + 1 ) + 1 ) + Cnt2;
	//		pIdx[ 0 ] = ( ( Cnt1 + 1 ) * ( NumBlock_X + 1 ) + 1 ) - ( NumBlock_X + 1 ) + Cnt2;

	//		pIdx += 2;	//	�|�C���^�����炷

	//	}	//	end of for

	//	//	�Ōザ��Ȃ�������
	//	//	�k�ރ|���S��
	//	if( Cnt1 != NumBlock_Y - 1 )
	//	{
	//		//	1�_�ł�
	//		pIdx[ 0 ] = ( Cnt1 + 1 ) * ( NumBlock_X + 1 );

	//		pIdx++;	//	�|�C���^�����炷

	//	}	//	end of if

	//}	//	end of for



	//	�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBufferSkyDome -> Unlock();

	return S_OK;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void SetField( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot )
 ����:		D3DXVECTOR3 Pos		���W
			D3DXVECTOR3 Rot		��]��
 �߂�l:	�Ȃ�
 ����:		���b�V���t�B�[���h�̃Z�b�g
-----------------------------------------------------------------------------*/
void SetSkyDome( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot )
{

	if( g_SkyDome.Use == false )
	{
		//	���W
		g_SkyDome.World.Pos = Pos;

		//	��]��
		g_SkyDome.World.Rot = Rot;

		//	�g�p�t���O
		g_SkyDome.Use = true;


	}	//	end of if

}	//	end of func