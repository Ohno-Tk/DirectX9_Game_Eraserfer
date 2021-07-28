/*=============================================================================

		����[ Born.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2016/01/05
-------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <time.h>
#include <math.h>
#include "main.h"
#include "Born.h"
#include "Shadow.h"
#include "fade.h"
#include "MeshWall.h"
#include "Utility.h"
#include "Help.h"
#include "HelpNumber.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/����.jpg"

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
HRESULT MakeVertexBorn( LPDIRECT3DDEVICE9 pDevice );

//	�^�[�Q�b�g�̃Z�b�g
void SetBorn( D3DXVECTOR3 Pos );

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBorn = NULL;	//	���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9 g_pTextureBorn = NULL;//	�e�N�X�`���C���^�[�t�F�[�X

BORN g_Born[ MAX_BORN ];	//	�G�\����

/*-----------------------------------------------------------------------------
 �֐���:	void InitTarget( void )
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void InitBorn( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	���̃��[�h�̎擾
	MODE *Mode = GetNextMode();

	//	���݂̎������擾
	srand((unsigned)time(NULL));


	//	�G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureBorn  ) ) )
	{
		MessageBox( NULL , "�r���{�[�h�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	�\���̏�����
	for( int Cnt = 0 ; Cnt < MAX_BORN ; Cnt++ )
	{

		//	���W
		g_Born[ Cnt ].World.Pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	�g�嗦
		g_Born[ Cnt ].World.Scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//	��]��
		g_Born[ Cnt ].World.Rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	���a
		g_Born[ Cnt ].Radius = 25.0f;

		//	�g�p�t���O
		g_Born[ Cnt ].Use = false;

	}	//	end of for


	if( *Mode == MODE_GAME )
	{

		SetBorn( D3DXVECTOR3( 600.0f , 0.0f , 700.0f ) );

		SetBorn( D3DXVECTOR3( 500.0f , 0.0f , -200.0f ) );

		SetBorn( D3DXVECTOR3( -500.0f , 0.0f , 800.0f ) );

		SetBorn( D3DXVECTOR3( -400.0f , 0.0f , 60.0f ) );

		SetBorn( D3DXVECTOR3( 0.0f , 0.0f , 500.0f ) );

		SetBorn( D3DXVECTOR3( -500.0f , 0.0f , -800.0f ) );

		SetBorn( D3DXVECTOR3( 500.0f , 0.0f , -800.0f ) );

		SetBorn( D3DXVECTOR3( 300.0f , 0.0f , -60.0f ) );

		SetBorn( D3DXVECTOR3( -400.0f , 0.0f , -400.0f ) );

		SetBorn( D3DXVECTOR3( -50.0f , 0.0f , -80.0f ) );

		SetBorn( D3DXVECTOR3( 115.0f , 0.0f , -405.0f ) );
	
	}	//	end of if

	//	���_�̍쐬
	MakeVertexBorn( pDevice );

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitTarget( void )
 ����:		
 �߂�l:	
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitBorn( void )
{

	if( g_pVtxBufferBorn != NULL )	//	���_�o�b�t�@�C���^�t�F�[�X�J��
	{
		g_pVtxBufferBorn -> Release();
		g_pVtxBufferBorn = NULL;

	}	//	end of if

	if( g_pTextureBorn != NULL )	//	�e�N�X�`���|���S���J��
	{
		g_pTextureBorn -> Release();
		g_pTextureBorn = NULL;

	}	//	end of if


}	//	end of func
 
/*-----------------------------------------------------------------------------
 �֐���:	void UpdataTarget( void )
 ����:		
 �߂�l:	
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateBorn( void )
{

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawTarget( void )
 ����:		
 �߂�l:	
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawBorn( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�p�C�v���C���̃X�g���[��
	pDevice -> SetStreamSource( 0 , g_pVtxBufferBorn , 0 , sizeof( VERTEX_3D ));


	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_3D );


	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureBorn );


	//	���e�X�g
	pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );	//	���e�X�g��ON�ɂ���
	pDevice -> SetRenderState( D3DRS_ALPHAREF , 0 );			//	�Q�ƒl�̐ݒ�
	pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );	//	���Z�q�����߂�


	//	�S�̂̃��C�g��L���ɂ���
	pDevice -> SetRenderState( D3DRS_LIGHTING , FALSE );


	for( int Cnt = 0 ; Cnt < MAX_BORN ; Cnt++ )
	{

		if( g_Born[ Cnt ].Use == true )
		{

			//	�t�s�񂠂�̃��[���h���W�ϊ�
			SetWorldInv( g_Born[ Cnt ].World.Pos , g_Born[ Cnt ].World.Scl );


			//	�|���S���̕`��
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , Cnt * NUM_VERTEX , NUM_POLYGON );

		}	//	end of if

	}


	//	�S�̂̃��C�g��L���ɂ���
	pDevice -> SetRenderState( D3DRS_LIGHTING , TRUE );


	//	���ɖ߂�
	pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , FALSE );	//	���e�X�g��OFF�ɂ���


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void MakeVertexBorn( LPDIRECT3DDEVICE9 pDevice )
 ����:		LPDIRECT3DDEVICE9 pDevice
 �߂�l:	�Ȃ�
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
HRESULT MakeVertexBorn( LPDIRECT3DDEVICE9 pDevice )
{
	VERTEX_3D* pVtx;	//	���z�A�h���X���擾����|�C���^�ϐ�


	//	���_�o�b�t�@�̐���
	if( FAILED( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * NUM_VERTEX * MAX_BORN , D3DUSAGE_WRITEONLY , FVF_VERTEX_3D , D3DPOOL_MANAGED , &g_pVtxBufferBorn , NULL ) ) )
	{
		return E_FAIL;

	}	//	end of if

	//	�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferBorn -> Lock( 0 , 0 , (void**)&pVtx , 0 );

	for( int Cnt = 0 ; Cnt < MAX_BORN ; Cnt++ )
	{

		//	���_���W�̐ݒ�
		pVtx[ 0 ].pos = D3DXVECTOR3( -30.0f, 10.0f , 0.0f );
		pVtx[ 1 ].pos = D3DXVECTOR3( 30.0f , 10.0f , 0.0f );
		pVtx[ 2 ].pos = D3DXVECTOR3( -30.0f, 0.0f , 0.0f );
		pVtx[ 3 ].pos = D3DXVECTOR3( 30.0f , 0.0f , 0.0f );


		//	�@���̐ݒ�
		pVtx[ 0 ].normal = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[ 1 ].normal = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[ 2 ].normal = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[ 3 ].normal = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );


		//	���_�F�̐ݒ�
		pVtx[ 0 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[ 1 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[ 2 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[ 3 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );


		//	�e�N�X�`�����W�̐ݒ�
		pVtx[ 0 ].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[ 1 ].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[ 2 ].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[ 3 ].tex = D3DXVECTOR2( 1 , 1 );

		pVtx += 4;

	}


	//	�o�b�t�@�̃A�����b�N
	g_pVtxBufferBorn -> Unlock();


	return S_OK;

}	//	end of func


/*-----------------------------------------------------------------------------
 �֐���:	void SetTarget( D3DXVECTOR3 Pos , D3DXVECTOR3 Move )
 ����:		D3DXVECTOR3 Pos		���W
			D3DXVECTOR3 Move	�ړ���
 �߂�l:	
 ����:		�^�[�Q�b�g�̃Z�b�g
-----------------------------------------------------------------------------*/
void SetBorn( D3DXVECTOR3 Pos )
{

	for( int Cnt = 0 ; Cnt < MAX_BORN ; Cnt++ )
	{

		if( g_Born[ Cnt ].Use == false )
		{

			//	���W
			g_Born[ Cnt ].World.Pos = Pos;

			//	�g�p�t���O
			g_Born[ Cnt ].Use = true;

			SetHelp( D3DXVECTOR3( g_Born[ Cnt ].World.Pos.x , g_Born[ Cnt ].World.Pos.y + 40.0f , g_Born[ Cnt ].World.Pos.z ) );

			break;

		}	//	end of if
		
	}	//	end of for

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	Born *GetBornNor( void )
 ����:		
 �߂�l:	
 ����:		�^�[�Q�b�g���̎擾
-----------------------------------------------------------------------------*/
BORN *GetBorn( void )
{

	return &g_Born[ 0 ];

}	//	end of func