/*=============================================================================

		���U���g[ ResultBg.cpp ]

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
#include "ResultBg.h"
#include "fade.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/TITLE/ButtomRogo .png"
#define POLYGON01_TEXTURENAME "data/TEXTURE/RESULT/playing.png"
#define POLYGON02_TEXTURENAME "data/TEXTURE/TUTORIAL/Bg.jpg"

#define MAX_TEXTURE ( 3 )	//	�ő�e�N�X�`����

#define FADE_RATE ( 1.0f / 60 )	//	�ǂ̂��炢�Ńt�F�[�h������̂�

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

}RESULT;

/*-----------------------------------------------------------------------------
	�v���g�^�C�v�錾
-----------------------------------------------------------------------------*/

//	���_�̍쐬
HRESULT MakeVertexResult( LPDIRECT3DDEVICE9 pDevice );

//	���_�̕ύX
void VerTexResult( VERTEX_2D* pVtx , int Cnt );


/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferResult = NULL;	//	���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureResult[ MAX_TEXTURE ] = { NULL };//	�e�N�X�`���C���^�[�t�F�[�X

RESULT g_Result[ MAX_TEXTURE ];	//	�^�C�g���\���̏��

FADE g_ResultFade;	//	�t�F�[�h�̗�

/*-----------------------------------------------------------------------------
 �֐���:	void InitResultBg( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		������
-----------------------------------------------------------------------------*/
void InitResultBg( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�e�N�X�`���̃G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureResult[ 0 ] ) ) )
	{

		MessageBox( NULL , "[ RESULTBg.cpp ]\n POLYGON00_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if

	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON01_TEXTURENAME , &g_pTextureResult[ 1 ] ) ) )
	{

		MessageBox( NULL , "[ RESULTBg.cpp ]\n POLYGON01_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if

	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON02_TEXTURENAME , &g_pTextureResult[ 2 ] ) ) )
	{

		MessageBox( NULL , "[ RESULTBg.cpp ]\n POLYGON02_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if



	//	���_�̍쐬
	MakeVertexResult( pDevice );



	//	�\���̏�����

	//	���W
	g_Result[ 0 ].Pos = D3DXVECTOR2( SCREEN_WIDTH - 520.0f , SCREEN_HEIGHT * 0.8f );

	//	�傫��
	g_Result[ 0 ].Size = D3DXVECTOR2( 260.0f , 80.0f );

	//	�F
	g_Result[ 0 ].Color = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f );


	//	���W
	g_Result[ 1 ].Pos = D3DXVECTOR2( 200.0f , -10.0f );

	//	�傫��
	g_Result[ 1 ].Size = D3DXVECTOR2( 450.0f , 250.0f );

	//	�F
	g_Result[ 1 ].Color = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f );


	//	���W
	g_Result[ 2 ].Pos = D3DXVECTOR2( 0.0f , 0.0f );

	//	�傫��
	g_Result[ 2 ].Size = D3DXVECTOR2( SCREEN_WIDTH , SCREEN_HEIGHT );

	//	�F
	g_Result[ 2 ].Color = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 0.5f );


	//	�ϐ�������
	g_ResultFade = FADE_IN;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitResultBg( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitResultBg( void )
{

	if(g_pVtxBufferResult != NULL)	//���_�o�b�t�@�̃C���^�[�t�F�[�X�|�C���^�̉��
	{

		g_pVtxBufferResult -> Release();
		g_pVtxBufferResult  = NULL;

	}	//	end of if


	for( int Cnt = 0 ; Cnt < MAX_TEXTURE ; Cnt++ )
	{

		if( g_pTextureResult[ Cnt ] != NULL )	//	�e�N�X�`���|���S���J��
		{

			g_pTextureResult[ Cnt ] -> Release();
			g_pTextureResult[ Cnt ] = NULL;

		}	//	end of if

	}	//	end of for

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UpdateResultBg( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateResultBg( void )
{

	//	���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_2D* pVtx;


	//�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferResult -> Lock( 0 , 0 ,	( void** )&pVtx , 0 );


	for( int Cnt = 0 ; Cnt < MAX_TEXTURE ; Cnt++ )
	{

		//	���_�̕ύX
		VerTexResult( pVtx , Cnt );

	}	//	end of for


	g_pVtxBufferResult -> Unlock(); //����ȍ~�G��Ă͂����Ȃ�


	if( g_ResultFade == FADE_IN )	//	�t�F�[�h�C�����̏���
	{

		g_Result[ 0 ].Color.a -= FADE_RATE;	//	a�l�����Z���Č��̉�ʂ𕂂��яオ�点��

		//	�t�F�[�h�C���̏I��
		if( g_Result[ 0 ].Color.a < 0.0f )
		{

			g_Result[ 0 ].Color.a = 0.0f;
			g_ResultFade = FADE_OUT;

		}	//	end od if

	}	//	end of if

	else if( g_ResultFade == FADE_OUT )	//	�t�F�[�h�A�E�g���̏���
	{

		g_Result[ 0 ].Color.a += FADE_RATE;	//	a�l�����Z���Č��̉�ʂ������Ă���

		//	�t�F�[�h�A�E�g�̏I��
		if( g_Result[ 0 ].Color.a > 1.0f )
		{

			g_Result[ 0 ].Color.a = 1.0f;
			g_ResultFade = FADE_IN;	//	�t�F�[�h�C���ɏ����̐؂�ւ�

		}	//	end of if

	}	//	end of else if


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawResultBg( void )
 ����:		�Ȃ�
 �߂�l:	�Ȃ�
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawResultBg( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D );

	//	�X�g���[����ݒ肷��
	pDevice -> SetStreamSource( 0 , g_pVtxBufferResult , 0 , sizeof( VERTEX_2D ) );


	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureResult[ 2 ] );

	//	�|���S���̕`��
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 8 , NUM_POLYGON);

	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureResult[ 0 ] );

	//	�|���S���̕`��
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , NUM_POLYGON);


	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureResult[ 1 ] );

	//	�|���S���̕`��
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 4 , NUM_POLYGON);


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT MakeVertexResult( LPDIRECT3DDEVICE9 pDevice )
 ����:		LPDIRECT3DDEVICE9 pDevice	�f�o�C�X
 �߂�l:	�ǂ��ꍇ	return S_OK;
			�_���ȏꍇ	return E_FAIL;
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
HRESULT MakeVertexResult( LPDIRECT3DDEVICE9 pDevice )
{

	//	���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_2D* pVtx;


	// FAILED�}�N���ŃG���[�`�F�b�N
	if ( FAILED ( pDevice -> CreateVertexBuffer ( sizeof ( VERTEX_2D ) * NUM_VERTEX * MAX_TEXTURE , D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &g_pVtxBufferResult , NULL ) ) )
	{

		return E_FAIL;

	}	//	end of if


	//�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferResult -> Lock( 0 , 0 ,	( void** )&pVtx , 0 );


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


		pVtx += 4;	//	�|�C���^�����炷


	}	//	end of for


	g_pVtxBufferResult -> Unlock(); //����ȍ~�G��Ă͂����Ȃ�


	return S_OK;


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void VerTexResult( VERTEX_2D* pVtx , int Cnt )
 ����:		VERTEX_2D* pVtx		���z�A�h���X���擾����|�C���^�ϐ�
			int Cnt				�J�E���^
 �߂�l:	
 ����:		���_�̕ύX
-----------------------------------------------------------------------------*/
void VerTexResult( VERTEX_2D* pVtx , int Cnt )
{

	//	pVtx��Cnt�����炷
	pVtx += Cnt * NUM_VERTEX;


	//	���_���W�̐ݒ�
	pVtx[ 0 ].pos = D3DXVECTOR3( g_Result[ Cnt ].Pos.x                          , g_Result[ Cnt ].Pos.y                          , 0.0f );
	pVtx[ 1 ].pos = D3DXVECTOR3( g_Result[ Cnt ].Pos.x + g_Result[ Cnt ].Size.x , g_Result[ Cnt ].Pos.y                          , 0.0f );
	pVtx[ 2 ].pos = D3DXVECTOR3( g_Result[ Cnt ].Pos.x                          , g_Result[ Cnt ].Pos.y + g_Result[ Cnt ].Size.y , 0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3( g_Result[ Cnt ].Pos.x + g_Result[ Cnt ].Size.x , g_Result[ Cnt ].Pos.y + g_Result[ Cnt ].Size.y , 0.0f );

	//	���_�F�̐ݒ�
	pVtx[ 0 ].color = D3DXCOLOR( g_Result[ Cnt ].Color.r , g_Result[ Cnt ].Color.g , g_Result[ Cnt ].Color.b , g_Result[ Cnt ].Color.a );
	pVtx[ 1 ].color = D3DXCOLOR( g_Result[ Cnt ].Color.r , g_Result[ Cnt ].Color.g , g_Result[ Cnt ].Color.b , g_Result[ Cnt ].Color.a );
	pVtx[ 2 ].color = D3DXCOLOR( g_Result[ Cnt ].Color.r , g_Result[ Cnt ].Color.g , g_Result[ Cnt ].Color.b , g_Result[ Cnt ].Color.a );
	pVtx[ 3 ].color = D3DXCOLOR( g_Result[ Cnt ].Color.r , g_Result[ Cnt ].Color.g , g_Result[ Cnt ].Color.b , g_Result[ Cnt ].Color.a );

}	//	end of func