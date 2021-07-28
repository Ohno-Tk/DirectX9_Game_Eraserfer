/*=============================================================================

		�^�C�g��[ Titlebg.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/01/06
-------------------------------------------------------------------------------
	���@Update
=============================================================================*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "main.h"
#include "Titlebg.h"
#include "fade.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/TITLE/ButtomRogo .png"
#define POLYGON01_TEXTURENAME "data/TEXTURE/TITLE/Title.png"

#define MAX_TEXTURE ( 2 )	//	�ő�e�N�X�`����

#define FADE_RATE ( 1.0f / 80 )	//	�ǂ̂��炢�Ńt�F�[�h������̂�

#define MIN_ALPHA ( 0.5f )	//	���l�̍ŏ��l

/*-----------------------------------------------------------------------------
	��
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�\����
-----------------------------------------------------------------------------*/
typedef struct
{
	D3DXVECTOR2 Pos;	//	���W
	D3DXVECTOR2 Size;	//	�傫��
	D3DXCOLOR Color;	//	�F

}TITLE;

/*-----------------------------------------------------------------------------
	�v���g�^�C�v�錾
-----------------------------------------------------------------------------*/

//	���_�̍쐬
HRESULT MakeVertexTitle( LPDIRECT3DDEVICE9 pDevice );

//	���_�̕ύX
void VerTexTitle( VERTEX_2D* pVtx , int Cnt );


/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferTitle = NULL;	//	���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureTitle[ MAX_TEXTURE ] = { NULL };	//	�e�N�X�`���C���^�[�t�F�[�X

TITLE g_Title[ MAX_TEXTURE ];	//	�^�C�g���\���̏��

FADE g_TitleFade;	//	�^�C�g����

/*-----------------------------------------------------------------------------
 �֐���:	void InitTitleBg( void )
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void InitTitleBg( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�e�N�X�`���̃G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureTitle[ 0 ] ) ) )
	{

		MessageBox( NULL , "[ Titlebg.cpp ]\n POLYGON00_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if

	//	�e�N�X�`���̃G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON01_TEXTURENAME , &g_pTextureTitle[ 1 ] ) ) )
	{

		MessageBox( NULL , "[ Titlebg.cpp ]\n POLYGON01_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if



	//	���_�̍쐬
	MakeVertexTitle( pDevice );


	//	�\���̏�����

	//	���W
	g_Title[ 0 ].Pos = D3DXVECTOR2( SCREEN_WIDTH - 520.0f , SCREEN_HEIGHT * 0.8f );

	//	�傫��
	g_Title[ 0 ].Size = D3DXVECTOR2( 260.0f , 80.0f );

	//	�F
	g_Title[ 0 ].Color = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f );


	//	�^�C�g�����S
	//	���W
	g_Title[ 1 ].Pos = D3DXVECTOR2( SCREEN_WIDTH * 0.2f , 50.0f );

	//	�傫��
	g_Title[ 1 ].Size = D3DXVECTOR2( 500.0f , 260.0f );

	//	�F
	g_Title[ 1 ].Color = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f );


	//	�ϐ�������
	g_TitleFade = FADE_IN;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitTitleBg( void )
 ����:		
 �߂�l:	
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitTitleBg( void )
{

	if(g_pVtxBufferTitle != NULL)	//���_�o�b�t�@�̃C���^�[�t�F�[�X�|�C���^�̉��
	{

		g_pVtxBufferTitle -> Release();
		g_pVtxBufferTitle  = NULL;

	}	//	end of if


	for( int Cnt = 0 ; Cnt < MAX_TEXTURE ; Cnt++ )
	{

		if( g_pTextureTitle[ Cnt ] != NULL )	//	�e�N�X�`���|���S���J��
		{

			g_pTextureTitle[ Cnt ] -> Release();
			g_pTextureTitle[ Cnt ] = NULL;

		}	//	end of if

	}	//	end of for

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UpdateTitleBg( void )
 ����:		
 �߂�l:	
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateTitleBg( void )
{

	// ���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_2D* pVtx;


	//�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferTitle -> Lock( 0 , 0 ,	( void** )&pVtx , 0 );


	for( int Cnt = 0 ; Cnt < MAX_TEXTURE ; Cnt++ )
	{

		//	���_�̕ύX
		VerTexTitle( pVtx , Cnt );

	}	//	end of for


	g_pVtxBufferTitle -> Unlock(); //����ȍ~�G��Ă͂����Ȃ�


	if( g_TitleFade == FADE_IN )	//	�t�F�[�h�C�����̏���
	{

		g_Title[ 0 ].Color.a -= FADE_RATE;	//	a�l�����Z���Č��̉�ʂ𕂂��яオ�点��

		//	�t�F�[�h�C���̏I��
		if( g_Title[ 0 ].Color.a < MIN_ALPHA )
		{

			g_Title[ 0 ].Color.a = MIN_ALPHA;
			g_TitleFade = FADE_OUT;

		}	//	end od if

	}	//	end of if

	else if( g_TitleFade == FADE_OUT )	//	�t�F�[�h�A�E�g���̏���
	{

		g_Title[ 0 ].Color.a += FADE_RATE;	//	a�l�����Z���Č��̉�ʂ������Ă���

		//	�t�F�[�h�A�E�g�̏I��
		if( g_Title[ 0 ].Color.a > 1.0f )
		{

			g_Title[ 0 ].Color.a = 1.0f;
			g_TitleFade = FADE_IN;	//	�t�F�[�h�C���ɏ����̐؂�ւ�

		}	//	end of if

	}	//	end of else if


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawTitleBg( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawTitleBg( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D );

	//	�X�g���[����ݒ肷��
	pDevice -> SetStreamSource( 0 , g_pVtxBufferTitle , 0 , sizeof( VERTEX_2D ) );

	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureTitle[ 0 ] );

	//	�|���S���̕`��
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , NUM_POLYGON);

	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureTitle[ 1 ] );

	//	�|���S���̕`��
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 4 , NUM_POLYGON);


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT MakeVertexTitle( LPDIRECT3DDEVICE9 pDevice )
 ����:		LPDIRECT3DDEVICE9 pDevice	�f�o�C�X
 �߂�l:	�ǂ��ꍇ	return S_OK;
			�_���ȏꍇ	return E_FAIL;
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
HRESULT MakeVertexTitle( LPDIRECT3DDEVICE9 pDevice )
{

	// ���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_2D* pVtx;


	// FAILED�}�N���ŃG���[�`�F�b�N
	if ( FAILED ( pDevice -> CreateVertexBuffer ( sizeof ( VERTEX_2D ) * NUM_VERTEX * MAX_TEXTURE , D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &g_pVtxBufferTitle , NULL ) ) )
	{

		return E_FAIL;

	}	//	end of if


	//�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferTitle -> Lock( 0 , 0 ,	( void** )&pVtx , 0 );


	for( int Cnt = 0 ; Cnt < MAX_TEXTURE ; Cnt++ )
	{

		//	���_���W�̐ݒ�
		pVtx[ 0 ].pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		pVtx[ 1 ].pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		pVtx[ 2 ].pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		pVtx[ 3 ].pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );


		//	���W�ϊ��ςݒ��_�t���O�̐ݒ�
		pVtx[ 0 ].rhw = 1.0f;
		pVtx[ 1 ].rhw = 1.0f;
		pVtx[ 2 ].rhw = 1.0f;
		pVtx[ 3 ].rhw = 1.0f;


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


	g_pVtxBufferTitle -> Unlock(); //����ȍ~�G��Ă͂����Ȃ�


	return S_OK;


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void VerTexTitle( VERTEX_2D* pVtx , int Cnt )
 ����:		VERTEX_2D* pVtx		���z�A�h���X���擾����|�C���^�ϐ�
			int Cnt				�J�E���^
 �߂�l:	
 ����:		���_�̕ύX
-----------------------------------------------------------------------------*/
void VerTexTitle( VERTEX_2D* pVtx , int Cnt )
{

	//	pVtx��Cnt�����炷
	pVtx += Cnt * NUM_VERTEX;


	//	���_���W�̐ݒ�
	pVtx[ 0 ].pos = D3DXVECTOR3( g_Title[ Cnt ].Pos.x                         , g_Title[ Cnt ].Pos.y                         , 0.0f );
	pVtx[ 1 ].pos = D3DXVECTOR3( g_Title[ Cnt ].Pos.x + g_Title[ Cnt ].Size.x , g_Title[ Cnt ].Pos.y                         , 0.0f );
	pVtx[ 2 ].pos = D3DXVECTOR3( g_Title[ Cnt ].Pos.x                         , g_Title[ Cnt ].Pos.y + g_Title[ Cnt ].Size.y , 0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3( g_Title[ Cnt ].Pos.x + g_Title[ Cnt ].Size.x , g_Title[ Cnt ].Pos.y + g_Title[ Cnt ].Size.y , 0.0f );

	//	���_�F�̐ݒ�
	pVtx[ 0 ].color = D3DXCOLOR( g_Title[ Cnt ].Color.r , g_Title[ Cnt ].Color.g , g_Title[ Cnt ].Color.b , g_Title[ Cnt ].Color.a );
	pVtx[ 1 ].color = D3DXCOLOR( g_Title[ Cnt ].Color.r , g_Title[ Cnt ].Color.g , g_Title[ Cnt ].Color.b , g_Title[ Cnt ].Color.a );
	pVtx[ 2 ].color = D3DXCOLOR( g_Title[ Cnt ].Color.r , g_Title[ Cnt ].Color.g , g_Title[ Cnt ].Color.b , g_Title[ Cnt ].Color.a );
	pVtx[ 3 ].color = D3DXCOLOR( g_Title[ Cnt ].Color.r , g_Title[ Cnt ].Color.g , g_Title[ Cnt ].Color.b , g_Title[ Cnt ].Color.a );

}	//	end of func