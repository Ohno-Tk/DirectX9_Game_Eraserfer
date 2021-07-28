/*=============================================================================

		�e[ Shadow.cpp ]

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
#include "main.h"
#include "Shadow.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/shadow000.jpg"

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
HRESULT MakeVertexShadow( LPDIRECT3DDEVICE9 pDevice );

//	���_�̕ύX
void VerTexPos( VERTEX_3D* pVtx , int Cnt );

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferShadow = NULL;	//	���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;//	�e�N�X�`���C���^�[�t�F�[�X

SHADOW g_Shadow[ MAX_SHADOW ];	//	�e�\����

/*-----------------------------------------------------------------------------
 �֐���:	void InitShadow( void )
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void InitShadow( void )
{
	
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�e�N�X�`���̃G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureShadow  ) ) )
	{

		MessageBox( NULL , "[ Shadow.cpp ]\n POLYGON00_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	���_�̍쐬
	MakeVertexShadow( pDevice );


	//	�\���̏�����
	for( int Cnt = 0 ; Cnt < MAX_SHADOW ; Cnt++ )
	{
		//	���W
		g_Shadow[ Cnt ].World.Pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	�g�嗦
		g_Shadow[ Cnt ].World.Scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//	��]��
		g_Shadow[ Cnt ].World.Rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	�J���[
		g_Shadow[ Cnt ].Color = D3DXCOLOR( 255 , 255 , 255 , 255 );

		//	�g�p�t���O
		g_Shadow[ Cnt ].Use = false;

	}	//	end of for

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitShadow( void )
 ����:		
 �߂�l:	
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitShadow( void )
{

	if(g_pVtxBufferShadow != NULL)	//���_�o�b�t�@�̃C���^�[�t�F�[�X�|�C���^�̉��
	{

		g_pVtxBufferShadow -> Release();
		g_pVtxBufferShadow = NULL;

	}	//	end of if

	if( g_pTextureShadow != NULL )	//	�e�N�X�`���|���S���J��
	{

		g_pTextureShadow -> Release();
		g_pTextureShadow = NULL;

	}	//	end of if

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UpdataShadow( void )
 ����:		
 �߂�l:	
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateShadow( void )
{

	//	���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_3D* pVtx;


	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	g_pVtxBufferShadow -> Lock ( 0 , 0 ,( void** )&pVtx , 0 );


	for( int Cnt = 0 ; Cnt < MAX_SHADOW ; Cnt++ )
	{

		//	���_�̕ύX
		VerTexPos( pVtx , Cnt );


	}	//	end of for


	//	�o�b�t�@�̃A�����b�N
	g_pVtxBufferShadow -> Unlock();

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawShadow( void )
 ����:		
 �߂�l:	
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawShadow( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_3D );

	//	�X�g���[����ݒ肷��
	pDevice -> SetStreamSource( 0 , g_pVtxBufferShadow , 0 , sizeof( VERTEX_3D ) );

	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureShadow );


	//	���Z����
	pDevice -> SetRenderState( D3DRS_BLENDOP , D3DBLENDOP_REVSUBTRACT );
	pDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
	pDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_ONE );
	

	for( int Cnt = 0 ; Cnt < MAX_SHADOW ; Cnt++ )
	{

		if( g_Shadow[ Cnt ].Use == true )
		{

			//	�t�s��Ȃ��̃��[���h���W�ϊ�
			SetWorld( g_Shadow[ Cnt ].World.Pos , g_Shadow[ Cnt ].World.Rot , g_Shadow[ Cnt ].World.Scl );


			//	�|���S���̕`��
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , Cnt * NUM_VERTEX, NUM_POLYGON);

		}	//	end of if

	}	//	end of for


	//	���ɖ߂�
	pDevice -> SetRenderState( D3DRS_BLENDOP , D3DBLENDOP_ADD );
	pDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
	pDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT MakeVertexShadow( LPDIRECT3DDEVICE9 pDevice )
 ����:		LPDIRECT3DDEVICE9 pDevice	�f�o�C�X
 �߂�l:	�ǂ��ꍇ	return S_OK;
			�_���ȏꍇ	return E_FAIL;
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
HRESULT MakeVertexShadow( LPDIRECT3DDEVICE9 pDevice )
{

	//	���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_3D* pVtx;

	//	���_�o�b�t�@�̐���
	if( FAILED( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * NUM_VERTEX * MAX_SHADOW , D3DUSAGE_WRITEONLY , FVF_VERTEX_3D , D3DPOOL_MANAGED , &g_pVtxBufferShadow , NULL ) ) )
	{

		return E_FAIL;

	}	//	end of if


	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	g_pVtxBufferShadow -> Lock( 0 , 0 ,( void** )&pVtx , 0 );


	for( int Cnt = 0 ; Cnt < MAX_SHADOW ; Cnt++ )
	{
		//	���_���W�̐ݒ�
		pVtx[ 0 ].pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		pVtx[ 1 ].pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		pVtx[ 2 ].pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		pVtx[ 3 ].pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	�@���̐ݒ�
		pVtx[ 0 ].normal = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		pVtx[ 1 ].normal = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		pVtx[ 2 ].normal = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		pVtx[ 3 ].normal = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );

		//	���_�F�̐ݒ�
		pVtx[ 0 ].color = D3DXCOLOR( 255 , 255 , 255 , 255 );
		pVtx[ 1 ].color = D3DXCOLOR( 255 , 255 , 255 , 255 );
		pVtx[ 2 ].color = D3DXCOLOR( 255 , 255 , 255 , 255 );
		pVtx[ 3 ].color = D3DXCOLOR( 255 , 255 , 255 , 255 );

		//	�e�N�X�`�����W�̐ݒ�
		pVtx[ 0 ].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[ 1 ].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[ 2 ].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[ 3 ].tex = D3DXVECTOR2( 1 , 1 );

		pVtx += 4;	//	pVtx�����炷


	}	//	end of for


	//	�o�b�t�@�̃A�����b�N
	g_pVtxBufferShadow -> Unlock();

	return S_OK;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void VerTexPos( VERTEX_3D* pVtx , int Cnt )
 ����:		VERTEX_3D* pVtx		���z�A�h���X���擾����|�C���^�ϐ�
			int Cnt				�e�\���̂̃J�E���^
 �߂�l:	
 ����:		���_�̕ύX
-----------------------------------------------------------------------------*/
void VerTexPos( VERTEX_3D* pVtx , int Cnt )
{

	//	pVtx��Cnt�����炷
	pVtx += Cnt * NUM_VERTEX;


	//	���_���W�̐ݒ�
	pVtx[ 0 ].pos = D3DXVECTOR3(  g_Shadow[ Cnt ].Radius , 0.0f , -g_Shadow[ Cnt ].Radius );
	pVtx[ 1 ].pos = D3DXVECTOR3( -g_Shadow[ Cnt ].Radius , 0.0f , -g_Shadow[ Cnt ].Radius );
	pVtx[ 2 ].pos = D3DXVECTOR3(  g_Shadow[ Cnt ].Radius , 0.0f ,  g_Shadow[ Cnt ].Radius );
	pVtx[ 3 ].pos = D3DXVECTOR3( -g_Shadow[ Cnt ].Radius , 0.0f ,  g_Shadow[ Cnt ].Radius );


	//	���_�F�̐ݒ�
	pVtx[ 0 ].color = D3DXCOLOR( g_Shadow[ Cnt ].Color.r , g_Shadow[ Cnt ].Color.g , g_Shadow[ Cnt ].Color.b , g_Shadow[ Cnt ].Color.a );
	pVtx[ 1 ].color = D3DXCOLOR( g_Shadow[ Cnt ].Color.r , g_Shadow[ Cnt ].Color.g , g_Shadow[ Cnt ].Color.b , g_Shadow[ Cnt ].Color.a );
	pVtx[ 2 ].color = D3DXCOLOR( g_Shadow[ Cnt ].Color.r , g_Shadow[ Cnt ].Color.g , g_Shadow[ Cnt ].Color.b , g_Shadow[ Cnt ].Color.a );
	pVtx[ 3 ].color = D3DXCOLOR( g_Shadow[ Cnt ].Color.r , g_Shadow[ Cnt ].Color.g , g_Shadow[ Cnt ].Color.b , g_Shadow[ Cnt ].Color.a );

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void SetShadow( D3DXVECTOR3 Pos , float Radius , D3DXCOLOR Color )
 ����:		D3DXVECTOR3 Pos		���W
			float Radius		���a
			D3DXCOLOR Color		�F
 �߂�l:	
 ����:		�e�̃Z�b�g
-----------------------------------------------------------------------------*/
void SetShadow( D3DXVECTOR3 Pos , float Radius , D3DXCOLOR Color )
{

	for( int Cnt = 0 ; Cnt < MAX_SHADOW ; Cnt++ )
	{

		if( g_Shadow[ Cnt ].Use == false )
		{
			
			//	���W
			g_Shadow[ Cnt ].World.Pos.x = Pos.x;
			g_Shadow[ Cnt ].World.Pos.z = Pos.z;

			//	�F
			g_Shadow[ Cnt ].Color.r = Color.r;
			g_Shadow[ Cnt ].Color.g = Color.g;
			g_Shadow[ Cnt ].Color.b = Color.b;
			g_Shadow[ Cnt ].Color.a = Color.a;

			//	���a
			g_Shadow[ Cnt ].Radius = Radius;

			//	�g�p�t���O
			g_Shadow[ Cnt ].Use = true;

			break;

		}	//	end of if

	}	//	end of for

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void IndexShadow( int Index )
 ����:		int Index
 �߂�l:	
 ����:		����̉e�̎g�p�t���O��OFF�ɂ���
-----------------------------------------------------------------------------*/
void IndexShadow( int Index )
{

	g_Shadow[ Index ].Use = false;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	SHADOW *GetShadow( int Index )
 ����:		int Index
 �߂�l:	
 ����:		�e�̏��擾
-----------------------------------------------------------------------------*/
SHADOW *GetShadow( int Index )
{

	return &g_Shadow[ Index ];

}	//	end of func
