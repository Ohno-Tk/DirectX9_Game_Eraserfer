/*=============================================================================

		�p�[�e�B�N��[ Particle.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2016/11/16
-------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
						scanf ��warning�h�~ 
-----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "main.h"
#include "particle.h"
#include "input.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/effect000.jpg"

#define MAX_PARTICLE ( 500 )	//	�p�[�e�B�N���ő吔

/*-----------------------------------------------------------------------------
	�\����
-----------------------------------------------------------------------------*/
typedef struct
{
	WORLD World;	//	���[���h�ϊ��p�ϐ�
	D3DXVECTOR3 Move;	//	�ړ���
	D3DXCOLOR Color;	//	�J���[
	int Life;	//	����
	float length;	//	����
	float Radius;	//���a
	float RadiusValue;	//���a�̕ω���
	bool Use;	//	�g�p�t���O
}PARTICLE;

/*-----------------------------------------------------------------------------
	�v���g�^�C�v�錾
-----------------------------------------------------------------------------*/

//	���_�̍쐬
HRESULT MakeVertexParticle( LPDIRECT3DDEVICE9 pDevice );

//	���W�ύX
void VerTexParticle( VERTEX_3D* pVtx , int Cnt );

//	�f�o�b�O�p
void DegubParticle( void );

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferParticle = NULL;	//	���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;//	�e�N�X�`���C���^�[�t�F�[�X

#ifdef _DEBUG

	LPD3DXFONT g_pFontParticle = NULL;

#endif	//	_DEBUG

PARTICLE g_Particle[ MAX_PARTICLE ];

D3DXVECTOR3 g_Rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
float g_ScatteringWidth  = 1.0f;	//	��U��
float g_Legth  = 100.0f;	//	����

/*-----------------------------------------------------------------------------
 �֐���:	void InitParticle( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		������
-----------------------------------------------------------------------------*/
void InitParticle( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	���݂̎������擾
	srand((unsigned)time(NULL));


	//	�G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureParticle  ) ) )
	{

		MessageBox( NULL , "[ Particle.cpp ]\n POLYGON00_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	���_�̍쐬
	MakeVertexParticle( pDevice );


	//	�\���̏�����
	for( int Cnt = 0 ; Cnt < MAX_PARTICLE ; Cnt++ )
	{
		//	���W
		g_Particle[ Cnt ].World.Pos.x = 0.0f;
		g_Particle[ Cnt ].World.Pos.y = 0.0f;
		g_Particle[ Cnt ].World.Pos.z = 0.0f;

		//	��]��
		g_Particle[ Cnt ].World.Rot.x = 0.0f;
		g_Particle[ Cnt ].World.Rot.y = 0.0f;
		g_Particle[ Cnt ].World.Rot.z = 0.0f;

		//	�g�嗦
		g_Particle[ Cnt ].World.Scl.x = 1.0f;
		g_Particle[ Cnt ].World.Scl.y = 1.0f;
		g_Particle[ Cnt ].World.Scl.z = 1.0f;

		//	�ړ���
		g_Particle[ Cnt ].Move.x = 0.0f;
		g_Particle[ Cnt ].Move.y = 0.0f;
		g_Particle[ Cnt ].Move.z = 0.0f;

		//	�J���[
		g_Particle[ Cnt ].Color.r = 10;
		g_Particle[ Cnt ].Color.g = 10;
		g_Particle[ Cnt ].Color.b = 10;
		g_Particle[ Cnt ].Color.a = 255;

		//	����
		g_Particle[ Cnt ].Life = 50;

		//	����
		g_Particle[ Cnt ].length = 0.5f;

		//���a
		g_Particle[ Cnt ].Radius = 3.0f;

		//���a�̕ω���
		g_Particle[ Cnt ].RadiusValue = 0.0f;

		//	�g�p�t���O
		g_Particle[ Cnt ].Use = false;

	}	//	end of for

#ifdef _DEBUG
	//	�t�H���g�̐ݒ�
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
				&g_pFontParticle );
#endif


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitParticle( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitParticle( void )
{

	if( g_pVtxBufferParticle != NULL )	//	���_�o�b�t�@�C���^�t�F�[�X�J��
	{
		g_pVtxBufferParticle -> Release();
		g_pVtxBufferParticle = NULL;

	}	//	end of if

	if( g_pTextureParticle != NULL )	//	�e�N�X�`���|���S���J��
	{
		g_pTextureParticle -> Release();
		g_pTextureParticle = NULL;

	}	//	end of if

#ifdef _DEBUG

	if( g_pFontParticle != NULL )
	{

		g_pFontParticle -> Release();
		g_pFontParticle = NULL;

	}	//	end of if

#endif	//	_DEBUG

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UpdateParticle( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateParticle( void )
{

	// �\���̂̃|�C���^�錾
	VERTEX_3D* pVtx;


	//	�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferParticle -> Lock( 0 , 0 , (void**)&pVtx , 0 );


	for( int Cnt = 0 ; Cnt < MAX_PARTICLE ; Cnt++ )
	{
		if( g_Particle[ Cnt ].Use == true )
		{
			//	���W�ړ�
			g_Particle[ Cnt ].World.Pos += g_Particle[ Cnt ].Move;

			//	���a�����炷
			g_Particle[ Cnt ].Radius -= g_Particle[ Cnt ].RadiusValue;

			//	���������炷
			g_Particle[ Cnt ].Life--;

			if( g_Particle[ Cnt ].Life <= 0 )
			{
				g_Particle[ Cnt ].Use = false;

			}	//	end of if

			//	���_�ύX
			VerTexParticle( pVtx , Cnt );

		}	//	end of if

	}	//	end of for

	//	�o�b�t�@�̃A�����b�N
	g_pVtxBufferParticle -> Unlock();

#ifdef _DEBUG


//	SetParticle( D3DXVECTOR3( 0.0f ,15.0f , -800.0f ) , g_Rot , D3DXCOLOR( 0.0f , 0.0f , 1.0f , 1.0f ) , g_ScatteringWidth , 100 , g_Legth , 2.0f );


	if( GetKeyboardPress( DIK_1 ) )
	{
		g_Rot.x += 0.1f;
	}
	if( GetKeyboardPress( DIK_2 ) )
	{
		g_Rot.x -= 0.1f;
	}
	if( GetKeyboardPress( DIK_3 ) )
	{
		g_Legth += 0.1f;
	}
	if( GetKeyboardPress( DIK_4 ) )
	{
		g_Legth -= 0.1f;
	}
	if( GetKeyboardPress( DIK_5 ) )
	{
		g_ScatteringWidth += 0.01f;
	}
	if( GetKeyboardPress( DIK_6 ) )
	{
		g_ScatteringWidth -= 0.01f;
	}

#endif	//	_DEBUG

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawParticle( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�p�[�e�B�N���̕`��
-----------------------------------------------------------------------------*/
void DrawParticle( void )
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�p�C�v���C���̃X�g���[��
	pDevice -> SetStreamSource( 0 , g_pVtxBufferParticle , 0 , sizeof( VERTEX_3D ));

	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_3D );

	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureParticle );

	//	a�u�����h�i���Z�����j
	pDevice -> SetRenderState( D3DRS_BLENDOP , D3DBLENDOP_ADD );	//	Init�ɏ����Ă���̂ŏȗ���
	pDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );	//	Init�ɏ����Ă���̂ŏȗ���
	pDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_ONE );

	//	Z�o�b�t�@
	pDevice -> SetRenderState( D3DRS_ZENABLE , D3DZB_TRUE );
	pDevice -> SetRenderState( D3DRS_ZWRITEENABLE , FALSE );


	for( int Cnt = 0 ; Cnt < MAX_PARTICLE ; Cnt++ )
	{

		//	�t�s�񂠂�̃��[���h���W�ϊ�
		SetWorldInv( g_Particle[ Cnt ].World.Pos , g_Particle[ Cnt ].World.Scl );


		if( g_Particle[ Cnt ].Use == true )
		{
			//	�|���S���̕`��
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , Cnt * NUM_VERTEX , NUM_POLYGON );

		}	//	end of if

	}	//	end of for


	//	���ɖ߂�
	pDevice -> SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE );
	pDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
	pDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );

	pDevice -> SetRenderState( D3DRS_ZENABLE , D3DZB_TRUE );
	pDevice -> SetRenderState( D3DRS_ZWRITEENABLE , TRUE );


#ifdef _DEBUG

	DegubParticle();

#endif	//	_DEBUG

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT MakeVertexParticle( LPDIRECT3DDEVICE9 pDevice )
 ����:		LPDIRECT3DDEVICE9 pDevice
 �߂�l:	�Ȃ�
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
HRESULT MakeVertexParticle( LPDIRECT3DDEVICE9 pDevice )
{
	VERTEX_3D* pVtx;	//	���z�A�h���X���擾����|�C���^�ϐ�

	//	���_�o�b�t�@�̐���
	if( FAILED( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * NUM_VERTEX * MAX_PARTICLE , D3DUSAGE_WRITEONLY , FVF_VERTEX_3D , D3DPOOL_MANAGED , &g_pVtxBufferParticle , NULL ) ) )
	{
		return E_FAIL;

	}	//	end of if

	//	�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferParticle -> Lock( 0 , 0 , (void**)&pVtx , 0 );

	for( int CntParticle = 0 ; CntParticle < MAX_PARTICLE ; CntParticle++ )
	{

		//	���_���W�̐ݒ�
		pVtx[ 0 ].pos = D3DXVECTOR3( -g_Particle[ CntParticle ].Radius , g_Particle[ CntParticle ].Radius  , 0.0f );
		pVtx[ 1 ].pos = D3DXVECTOR3( g_Particle[ CntParticle ].Radius  , g_Particle[ CntParticle ].Radius  , 0.0f );
		pVtx[ 2 ].pos = D3DXVECTOR3( -g_Particle[ CntParticle ].Radius , 0.0f                              , 0.0f );
		pVtx[ 3 ].pos = D3DXVECTOR3( g_Particle[ CntParticle ].Radius  , 0.0f                              , 0.0f );

		//	�@���̐ݒ�
		pVtx[ 0 ].normal = D3DXVECTOR3( 0.0f , 1.0f , -1.0f );
		pVtx[ 1 ].normal = D3DXVECTOR3( 0.0f , 1.0f , -1.0f );
		pVtx[ 2 ].normal = D3DXVECTOR3( 0.0f , 1.0f , -1.0f );
		pVtx[ 3 ].normal = D3DXVECTOR3( 0.0f , 1.0f , -1.0f );

		//	���_�F�̐ݒ�
		pVtx[ 0 ].color = D3DXCOLOR( g_Particle[ CntParticle ].Color.r , g_Particle[ CntParticle ].Color.g , g_Particle[ CntParticle ].Color.b , g_Particle[ CntParticle ].Color.a );
		pVtx[ 1 ].color = D3DXCOLOR( g_Particle[ CntParticle ].Color.r , g_Particle[ CntParticle ].Color.g , g_Particle[ CntParticle ].Color.b , g_Particle[ CntParticle ].Color.a );
		pVtx[ 2 ].color = D3DXCOLOR( g_Particle[ CntParticle ].Color.r , g_Particle[ CntParticle ].Color.g , g_Particle[ CntParticle ].Color.b , g_Particle[ CntParticle ].Color.a );
		pVtx[ 3 ].color = D3DXCOLOR( g_Particle[ CntParticle ].Color.r , g_Particle[ CntParticle ].Color.g , g_Particle[ CntParticle ].Color.b , g_Particle[ CntParticle ].Color.a );

		//	�e�N�X�`�����W�̐ݒ�
		pVtx[ 0 ].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[ 1 ].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[ 2 ].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[ 3 ].tex = D3DXVECTOR2( 1 , 1 );

		pVtx += 4;	//	pVtx�����炷

	}	//	end of for

	//	�o�b�t�@�̃A�����b�N
	g_pVtxBufferParticle -> Unlock();

	return S_OK;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void VerTexParticle( VERTEX_3D* pVtx , int Cnt )
 ����:		VERTEX_3D* pVtx
			int CntParticle
 �߂�l:	�Ȃ�
 ����:		���_�ύX
-----------------------------------------------------------------------------*/
void VerTexParticle( VERTEX_3D* pVtx , int Cnt )
{

	pVtx += Cnt * NUM_VERTEX;

	//	���_���W�̐ݒ�
	pVtx[ 0 ].pos = D3DXVECTOR3( -g_Particle[ Cnt ].Radius , g_Particle[ Cnt ].Radius  , 0.0f );
	pVtx[ 1 ].pos = D3DXVECTOR3(  g_Particle[ Cnt ].Radius , g_Particle[ Cnt ].Radius  , 0.0f );
	pVtx[ 2 ].pos = D3DXVECTOR3( -g_Particle[ Cnt ].Radius , 0.0f                      , 0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3(  g_Particle[ Cnt ].Radius , 0.0f                      , 0.0f );


	//	���_�F�̐ݒ�
	pVtx[ 0 ].color = D3DXCOLOR( g_Particle[ Cnt ].Color.r , g_Particle[ Cnt ].Color.g , g_Particle[ Cnt ].Color.b , g_Particle[ Cnt ].Color.a );
	pVtx[ 1 ].color = D3DXCOLOR( g_Particle[ Cnt ].Color.r , g_Particle[ Cnt ].Color.g , g_Particle[ Cnt ].Color.b , g_Particle[ Cnt ].Color.a );
	pVtx[ 2 ].color = D3DXCOLOR( g_Particle[ Cnt ].Color.r , g_Particle[ Cnt ].Color.g , g_Particle[ Cnt ].Color.b , g_Particle[ Cnt ].Color.a );
	pVtx[ 3 ].color = D3DXCOLOR( g_Particle[ Cnt ].Color.r , g_Particle[ Cnt ].Color.g , g_Particle[ Cnt ].Color.b , g_Particle[ Cnt ].Color.a );

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void SetParticle( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot , D3DXCOLOR Color , float ScatteringWidth , int Life , float Length , float Radius )
 ����:		D3DXVECTOR3 Pos			���W
			D3DXVECTOR3 Rot			�p�x
			D3DXCOLOR Color			�J���[
			float ScatteringWidth	��U��( 1.0f ~ 6.28 )
			int Life				����
			float Length			����
			float Radius			���a
 �߂�l:	�Ȃ�
 ����:		�p�[�e�B�N���̃Z�b�g
-----------------------------------------------------------------------------*/
void SetParticle( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot , D3DXCOLOR Color , float ScatteringWidth , int Life , float Length , float Radius )
{

	int ScatWidth = ( int )( ScatteringWidth * 100 );	//	��U���̐��l�𐮐��ɂ���

	//	�p�x�������_���ŋ��߂�
	float Dam = ( rand()%ScatWidth - 314 ) * 0.01f;


	for( int Cnt = 0 ; Cnt < MAX_PARTICLE ; Cnt++ )
	{
		if( g_Particle[ Cnt ].Use == false )
		{

			//	���W
			g_Particle[ Cnt ].World.Pos = Pos;

			//	�ړ���
			g_Particle[ Cnt ].Move.x = cosf( Dam + Rot.x ) * g_Particle[Cnt].length;
			g_Particle[ Cnt ].Move.y = sinf( Dam + Rot.x ) * g_Particle[Cnt].length;

			//	�J���[
			g_Particle[ Cnt ].Color = Color;

			//	����
			g_Particle[ Cnt ].Life = Life;

			//���a
			g_Particle[ Cnt ].Radius = Radius;

			//���a�̕ω���
			g_Particle[ Cnt ].RadiusValue = g_Particle[ Cnt ].Radius / g_Particle[ Cnt ].Life;

			//	�g�p�t���O
			g_Particle[ Cnt ].Use = true;

			break;

		}	//	end of if

	}	//	end of for

}	//	end of func

#ifdef _DEBUG

/*-----------------------------------------------------------------------------
 �֐���:	void DegubParticle( void )
 ����:		
 �߂�l:	�Ȃ�
 ����:		�f�o�b�O�p
-----------------------------------------------------------------------------*/
void DegubParticle( void )
{

	int Height = 200;
	D3DXCOLOR Color = D3DXCOLOR( 255 , 255 , 255 , 255 );

	RECT rect00 = { 0 , Height , SCREEN_WIDTH , SCREEN_HEIGHT };
	RECT rect01 = { 0 , Height + 15 , SCREEN_WIDTH , SCREEN_HEIGHT };
	RECT rect02 = { 0 , Height + 30 , SCREEN_WIDTH , SCREEN_HEIGHT };

	char aStr00[ 256 ] , aStr01[ 256 ] , aStr02[ 256 ];

	sprintf( &aStr00[ 0 ] , "[ �p�x ] ( %f : %f : %f )" , g_Rot.x , g_Rot.y , g_Rot.z );
	sprintf( &aStr01[ 0 ] , "[ ��U�� ] ( %.3f )" , g_ScatteringWidth );
	sprintf( &aStr02[ 0 ] , "[ ���� ] ( %.3f )" , g_Legth );

	g_pFontParticle -> DrawText( NULL ,
						&aStr00[ 0 ] ,
						-1 ,
						&rect00 ,
						DT_LEFT ,
						Color );

	g_pFontParticle -> DrawText( NULL ,
						&aStr01[ 0 ] ,
						-1 ,
						&rect01 ,
						DT_LEFT ,
						Color );

	g_pFontParticle -> DrawText( NULL ,
						&aStr02[ 0 ] ,
						-1 ,
						&rect02 ,
						DT_LEFT ,
						Color );


}	//	end of func

#endif