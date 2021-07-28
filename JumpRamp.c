/*=============================================================================

		�W�����v��[ JumpRamp.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/02/15
-------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "main.h"
#include "JumpRamp.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/��.jpg"

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
HRESULT MakeVertexJumpRamp( LPDIRECT3DDEVICE9 pDevice );

//	�W�����v��̃Z�b�g
void SetJumpRamp( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot );

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferJumpRamp = NULL;	//	���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureJumpRamp = NULL;//	�e�N�X�`���C���^�[�t�F�[�X

JUMPRAMP g_JumpRamp[ MAX_JUMPRAMP ];	//	�\����

/*-----------------------------------------------------------------------------
 �֐���:	void InitJumpRamp( void )
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void InitJumpRamp( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�e�N�X�`���̃G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureJumpRamp ) ) )
	{

		MessageBox( NULL , "[ JumpRamp.cpp ]\n POLYGON00_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	���_�̍쐬
	MakeVertexJumpRamp( pDevice );


	//	�\���̏�����
	for( int Cnt = 0 ; Cnt < MAX_JUMPRAMP ; Cnt++ )
	{

		g_JumpRamp[ Cnt ].World.Pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_JumpRamp[ Cnt ].World.Rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_JumpRamp[ Cnt ].World.Scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		g_JumpRamp[ Cnt ].Use = false;

	}	//	end of for


	SetJumpRamp( D3DXVECTOR3( 0.0f , 0.0f , 0.0f ) , D3DXVECTOR3( 60.0f , 0.0f , 0.0f ) );

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitJumpRamp( void )
 ����:		
 �߂�l:	
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitJumpRamp( void )
{

	if(g_pVtxBufferJumpRamp != NULL)	//���_�o�b�t�@�̃C���^�[�t�F�[�X�|�C���^�̉��
	{

		g_pVtxBufferJumpRamp -> Release();
		g_pVtxBufferJumpRamp  = NULL;

	}	//	end of if



	if( g_pTextureJumpRamp != NULL )	//	�e�N�X�`���|���S���J��
	{

		g_pTextureJumpRamp -> Release();
		g_pTextureJumpRamp = NULL;

	}	//	end of if

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UpdateJumpRamp( void )
 ����:		
 �߂�l:	
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateJumpRamp( void )
{
}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawJumpRamp( void )
 ����:		
 �߂�l:	
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawJumpRamp( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�p�C�v���C���̃X�g���[��
	pDevice -> SetStreamSource( 0 , g_pVtxBufferJumpRamp , 0 , sizeof( VERTEX_3D ));


	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_3D );


	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureJumpRamp );


	for( int Cnt = 0 ; Cnt < MAX_JUMPRAMP ; Cnt++ )
	{

		if( g_JumpRamp[ Cnt ].Use == true )
		{

			//	�t�s��Ȃ��̃��[���h���W�ϊ�
			SetWorld( g_JumpRamp[ Cnt ].World.Pos , g_JumpRamp[ Cnt ].World.Rot , g_JumpRamp[ Cnt ].World.Scl );


			//	�|���S���̕`��
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , Cnt * NUM_VERTEX , NUM_POLYGON );

		}	//	end of if

	}


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT MakeVertexJumpRamp( LPDIRECT3DDEVICE9 pDevice )
 ����:		LPDIRECT3DDEVICE9 pDevice	�f�o�C�X
 �߂�l:	�ǂ��ꍇ	return S_OK;
			�_���ȏꍇ	return E_FAIL;
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
HRESULT MakeVertexJumpRamp( LPDIRECT3DDEVICE9 pDevice )
{

		VERTEX_3D* pVtx;	//	���z�A�h���X���擾����|�C���^�ϐ�


	//	���_�o�b�t�@�̐���
	if( FAILED( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * NUM_VERTEX * MAX_JUMPRAMP , D3DUSAGE_WRITEONLY , FVF_VERTEX_3D , D3DPOOL_MANAGED , &g_pVtxBufferJumpRamp , NULL ) ) )
	{
		return E_FAIL;

	}	//	end of if

	//	�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferJumpRamp -> Lock( 0 , 0 , (void**)&pVtx , 0 );


	for( int Cnt = 0 ; Cnt < MAX_JUMPRAMP ; Cnt++ )
	{

		//	���_���W�̐ݒ�
		pVtx[ 0 ].pos = D3DXVECTOR3( -20.0f, 30.0f , 0.0f );
		pVtx[ 1 ].pos = D3DXVECTOR3(  20.0f, 30.0f , 0.0f );
		pVtx[ 2 ].pos = D3DXVECTOR3( -20.0f, 0.0f , 0.0f );
		pVtx[ 3 ].pos = D3DXVECTOR3(  20.0f, 0.0f , 0.0f );


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

	}	//	end of for


	//	�o�b�t�@�̃A�����b�N
	g_pVtxBufferJumpRamp -> Unlock();


	return S_OK;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void SetJumpRamp( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot )
 ����:		
 �߂�l:	
 ����:		�W�����v��̃Z�b�g
-----------------------------------------------------------------------------*/
void SetJumpRamp( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot )
{

	for( int Cnt = 0 ; Cnt < MAX_JUMPRAMP ; Cnt++ )
	{

		if( g_JumpRamp[ Cnt ].Use == false )
		{

			g_JumpRamp[ Cnt ].World.Pos = Pos;
			g_JumpRamp[ Cnt ].World.Rot = Rot;

			g_JumpRamp[ Cnt ].Use = true;

			break;

		}	//	end of if

	}	//	end of for

}	//	end of func