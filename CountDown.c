/*=============================================================================

		�J�E���g�_�E��[ CountDown.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2016/01/05
-------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "CountDown.h"
#include "sound.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/CountDown_Start.png"
#define POLYGON01_TEXTURENAME "data/TEXTURE/GAME/CountDown_1.png"
#define POLYGON02_TEXTURENAME "data/TEXTURE/GAME/CountDown_2.png"
#define POLYGON03_TEXTURENAME "data/TEXTURE/GAME/CountDown_3.png"

#define MAX_TEXTURE ( 4 )	//	�e�N�X�`���̍ő吔


#define COUNTDOWN_X ( SCREEN_WIDTH * 0.35f )		//	�X�R�A��X
#define COUNTDOWN_Y ( SCREEN_HEIGHT * 0.4f )		//	�X�R�A��Y
#define COUNTDOWN_WIDTH  ( 250.0f )	//	�X�R�A��Width
#define COUNTDOWN_HEIGHT ( 150.0f )	//	�X�R�A��Height

/*-----------------------------------------------------------------------------
	��
-----------------------------------------------------------------------------*/
typedef enum
{
	COUNTDOWN_GO = 0,
	COUNTDOWN_1,
	COUNTDOWN_2,
	COUNTDOWN_3,
	COUNTDOWN_MAX,

}COUNTDOWN;

/*-----------------------------------------------------------------------------
	�\����
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�v���g�^�C�v�錾
-----------------------------------------------------------------------------*/

//	���_�̍쐬
HRESULT MakeVertexCountDown( LPDIRECT3DDEVICE9 pDevice );

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferCountDown = NULL;	//	���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureCountDown[ MAX_TEXTURE ] = { NULL };//	�e�N�X�`���C���^�[�t�F�[�X


COUNTDOWN g_CountDown = COUNTDOWN_3;	// �J�E���g�_�E���̗�

int g_CountDown_TexNo;	// �e�N�X�`��NO
int g_CountDown_Time;	// �^�C�}�[�J�E���^
int g_CountDown_Frame;	// �t���[���J�E���^

bool g_Start;			// �X�^�[�g�������ǂ���


/*-----------------------------------------------------------------------------
 �֐���:	void InitCountDown( void )
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void InitCountDown( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�e�N�X�`���̃G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureCountDown[ 0 ] ) ) )
	{
		MessageBox( NULL , "[ CountDown.cpp ]\n POLYGON00_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if

	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON01_TEXTURENAME , &g_pTextureCountDown[ 1 ] ) ) )
	{
		MessageBox( NULL , "[ CountDown.cpp ]\n POLYGON01_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if

	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON02_TEXTURENAME , &g_pTextureCountDown[ 2 ] ) ) )
	{
		MessageBox( NULL , "[ CountDown.cpp ]\n POLYGON02_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if

	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON03_TEXTURENAME , &g_pTextureCountDown[ 3 ] ) ) )
	{
		MessageBox( NULL , "[ CountDown.cpp ]\n POLYGON03_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	���_�̍쐬
	MakeVertexCountDown( pDevice );


	// �ϐ�������
	g_CountDown_TexNo = (int)g_CountDown;

	g_CountDown_Time = (int)g_CountDown;

	g_CountDown_Frame = 0;

	g_Start = false;


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitCountDown( void )
 ����:		
 �߂�l:	
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitCountDown( void )
{

	if(g_pVtxBufferCountDown != NULL)	//���_�o�b�t�@�̃C���^�[�t�F�[�X�|�C���^�̉��
	{
		g_pVtxBufferCountDown -> Release();
		g_pVtxBufferCountDown  = NULL;

	}	//	end of if


	for( int CntCountDown = 0 ; CntCountDown < MAX_TEXTURE ; CntCountDown++ )
	{

		if( g_pTextureCountDown[ CntCountDown ] != NULL )	//	�e�N�X�`���|���S���J��
		{
			g_pTextureCountDown[ CntCountDown ] -> Release();
			g_pTextureCountDown[ CntCountDown ] = NULL;

		}	//	end of if

	}	//	end of for


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UpdateCountDown( void )
 ����:		
 �߂�l:	
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateCountDown( void )
{

	int num = 0;


	if( g_CountDown_Time != 0 )
	{

		g_CountDown_Frame++;

		if( g_CountDown_Frame == 60 )
		{

			g_CountDown_Frame = 0;
			g_CountDown_TexNo--;
			g_CountDown_Time--;

			if( g_CountDown_TexNo == COUNTDOWN_GO )
			{

				PlaySound( SOUND_LABEL_SE_COUNTDOWN02 );	//	���y�Đ�

			}
			else
			{

				PlaySound( SOUND_LABEL_SE_COUNTDOWN01 );	//	���y�Đ�

			}

		}	//	end of if

	}	//	end of if

	//�Q�[���X�^�[�g
	else
	{

		// 60�t���[�������\��
		if( g_CountDown_Frame != 60 )
		{

			g_CountDown_Frame++;

		}	//	end of if

		else
		{

			g_Start = true;

		}	//	end of else

	}	//	end of else


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawCountDown( void )
 ����:		
 �߂�l:	
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawCountDown( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D );

	//	�X�g���[����ݒ肷��
	pDevice -> SetStreamSource( 0 , g_pVtxBufferCountDown , 0 , sizeof( VERTEX_2D ) );

	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureCountDown[ g_CountDown_TexNo ] );


	if( g_Start == false )
	{

		//	�|���S���̕`��
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , NUM_POLYGON);

	}	//	end of if


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT MakeVertexCountDown( LPDIRECT3DDEVICE9 pDevice )
 ����:		LPDIRECT3DDEVICE9 pDevice	�f�o�C�X
 �߂�l:	�ǂ��ꍇ	return S_OK;
			�_���ȏꍇ	return E_FAIL;
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
HRESULT MakeVertexCountDown( LPDIRECT3DDEVICE9 pDevice )
{

	// �\���̂̃|�C���^�錾
	VERTEX_2D* pVtx;


	// FAILED�}�N���ŃG���[�`�F�b�N
	if ( FAILED ( pDevice -> CreateVertexBuffer ( sizeof ( VERTEX_2D ) * NUM_VERTEX , D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &g_pVtxBufferCountDown , NULL ) ) )
	{

		return E_FAIL;

	}	//	end of if


	//�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferCountDown -> Lock( 0 , 0 ,	( void** )&pVtx , 0 );


	//	���_���W�̐ݒ�
	pVtx[ 0 ].pos = D3DXVECTOR3( COUNTDOWN_X                   , COUNTDOWN_Y                    , 0.0f );
	pVtx[ 1 ].pos = D3DXVECTOR3( COUNTDOWN_X + COUNTDOWN_WIDTH , COUNTDOWN_Y                    , 0.0f );
	pVtx[ 2 ].pos = D3DXVECTOR3( COUNTDOWN_X                   , COUNTDOWN_Y + COUNTDOWN_HEIGHT , 0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3( COUNTDOWN_X + COUNTDOWN_WIDTH , COUNTDOWN_Y + COUNTDOWN_HEIGHT , 0.0f );

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


	g_pVtxBufferCountDown -> Unlock(); //����ȍ~�G��Ă͂����Ȃ�

	return S_OK;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	bool *GetStart( void )
 ����:		
 �߂�l:	return &g_Start;
 ����:		�X�^�[�g�������̏��擾
-----------------------------------------------------------------------------*/
bool *GetStart( void )
{

	return &g_Start;

}	//	end of func