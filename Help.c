/*=============================================================================

		�r���{�[�h[ Help.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2016/11/16
-------------------------------------------------------------------------------
	���@Update
		2016/11/16
=============================================================================*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "Help.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define BIILLBOARD_TEXTURENAME "data/TEXTURE/GAME/���.png"

/*-----------------------------------------------------------------------------
	�v���g�^�C�v�錾
-----------------------------------------------------------------------------*/
HRESULT MakeVertexHelp( LPDIRECT3DDEVICE9 pDevice );	//	���_�̍쐬

/*-----------------------------------------------------------------------------
	�\����
-----------------------------------------------------------------------------*/
typedef struct
{
	WORLD World;	//	���[���h�ϊ��p�ϐ�
	D3DXVECTOR2 Pos;	
	bool Use;	//	�g�p�t���O

}HELP;

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/

LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferHelp = NULL;	//	���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^

LPDIRECT3DTEXTURE9 g_pTextureHelp = NULL;//	�e�N�X�`���C���^�[�t�F�[�X

HELP g_Help[ MAX_HELP ];

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT InitHelp( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		������
-----------------------------------------------------------------------------*/
void InitHelp( void )
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , BIILLBOARD_TEXTURENAME , &g_pTextureHelp  ) ) )
	{
		MessageBox( NULL , "�r���{�[�h�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if

	//	�\���̏�����
	for( int Cnt = 0 ; Cnt < MAX_HELP ; Cnt++ )
	{

		//	���W
		g_Help[ Cnt ].World.Pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	��]��
		g_Help[ Cnt ].World.Rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	�g�嗦
		g_Help[ Cnt ].World.Scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//	�g�p�t���O
		g_Help[ Cnt ].Use = false;

	}


	//	���_�̍쐬
	MakeVertexHelp( pDevice );

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitHelp( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitHelp( void )
{
	if( g_pVtxBufferHelp != NULL )	//	���_�o�b�t�@�C���^�t�F�[�X�J��
	{
		g_pVtxBufferHelp -> Release();
		g_pVtxBufferHelp = NULL;

	}	//	end of if

	if( g_pTextureHelp != NULL )	//	�e�N�X�`���|���S���J��
	{
		g_pTextureHelp -> Release();
		g_pTextureHelp = NULL;

	}	//	end of if

}	//	end of func
 
/*-----------------------------------------------------------------------------
 �֐���:	void UpdataHelp( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateHelp( void )
{

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawHelp( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawHelp( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�p�C�v���C���̃X�g���[��
	pDevice -> SetStreamSource( 0 , g_pVtxBufferHelp , 0 , sizeof( VERTEX_3D ));


	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_3D );


	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureHelp );


	//	���e�X�g
	pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );	//	���e�X�g��ON�ɂ���
	pDevice -> SetRenderState( D3DRS_ALPHAREF , 0 );			//	�Q�ƒl�̐ݒ�
	pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );	//	���Z�q�����߂�


	//	�S�̂̃��C�g��L���ɂ���
	pDevice -> SetRenderState( D3DRS_LIGHTING , FALSE );


	for( int Cnt = 0 ; Cnt < MAX_HELP ; Cnt++ )
	{

		if( g_Help[ Cnt ].Use == true )
		{

			//	�t�s�񂠂�̃��[���h���W�ϊ�
			SetWorldInv( g_Help[ Cnt ].World.Pos , g_Help[ Cnt ].World.Scl );


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
 �֐���:	void MakeVertexHelp( LPDIRECT3DDEVICE9 pDevice )
 ����:		LPDIRECT3DDEVICE9 pDevice
 �߂�l:	�Ȃ�
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
HRESULT MakeVertexHelp( LPDIRECT3DDEVICE9 pDevice )
{
	VERTEX_3D* pVtx;	//	���z�A�h���X���擾����|�C���^�ϐ�


	//	���_�o�b�t�@�̐���
	if( FAILED( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * NUM_VERTEX * MAX_HELP , D3DUSAGE_WRITEONLY , FVF_VERTEX_3D , D3DPOOL_MANAGED , &g_pVtxBufferHelp , NULL ) ) )
	{
		return E_FAIL;

	}	//	end of if

	//	�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferHelp -> Lock( 0 , 0 , (void**)&pVtx , 0 );

	for( int Cnt = 0 ; Cnt < MAX_HELP ; Cnt++ )
	{

		//	���_���W�̐ݒ�
		pVtx[ 0 ].pos = D3DXVECTOR3( -30.0f, 15.0f , 0.0f );
		pVtx[ 1 ].pos = D3DXVECTOR3( 30.0f , 15.0f , 0.0f );
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
	g_pVtxBufferHelp -> Unlock();


	return S_OK;

}	//	end of func

void SetHelp( D3DXVECTOR3 Pos )
{

	for( int Cnt = 0 ; Cnt < MAX_HELP ; Cnt++ )
	{

		if( g_Help[ Cnt ].Use == false )
		{

			g_Help[ Cnt ].World.Pos = Pos;


			g_Help[ Cnt ].Use = true;

			break;

		}

	}

}

void SetOff( int Index )
{

	g_Help[ Index ].Use = false;

}