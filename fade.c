/*=============================================================================

		�t�F�[�h����[ fade.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2016/12/16
-------------------------------------------------------------------------------
	���@Update
=============================================================================*/
/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "main.h"
#include "fade.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define FADE_TEXTURENAME "data/TEXTURE/GAME/fade.png"

#define FADE_RATE ( 1.0f / 60 )	//	�ǂ̂��炢�Ńt�F�[�h������̂�

#define FADE_POS_X ( 0.0f )	//	�t�F�[�h�̕\���ʒu�w
#define FADE_POS_Y ( 0.0f )	//	�t�F�[�h�̕\���ʒu�x

/*-----------------------------------------------------------------------------
	��
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�\����
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�v���g�^�C�v�錾
-----------------------------------------------------------------------------*/
HRESULT MakeVertexFade( LPDIRECT3DDEVICE9 pDevice );	//	���_�̍쐬
void SetColorFade( D3DXCOLOR colorFade , VERTEX_2D* pVtx );	//	���_�J���[�̐ݒ�

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferFade = NULL;	//	���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;//	�e�N�X�`���C���^�[�t�F�[�X

D3DXCOLOR g_colorFade;	//	�t�F�[�h�F
FADE g_fade;	//	�t�F�[�h���

MODE g_modenext = MODE_TITLE;	//	���̃��[�h

bool g_FadeFlag = false;	//	�t�F�[�h�t���O

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT InitFade( void )
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void InitFade( void )
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	�G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , FADE_TEXTURENAME , &g_pTextureFade  ) ) )
	{
		MessageBox( NULL , "�e�N�X�`���̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if

	//	���_�̍쐬
	MakeVertexFade( pDevice );


	//������

	//	�t�F�[�h�F
	g_colorFade = D3DXCOLOR( 0.0f , 0.0f , 0.0f , 1.0f );


	//	�t�F�[�h���
	g_fade = FADE_IN;


	//	�t�F�[�h�t���O
	g_FadeFlag = false;

	//	���[�h�̎擾
	MODE *ModeNext = GetMode();

	g_modenext = *ModeNext;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitFade( void )
 ����:		
 �߂�l:	
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitFade( void )
{

	if( g_pTextureFade != NULL )	//	�e�N�X�`���|���S���J��
	{

		g_pTextureFade -> Release();
		g_pTextureFade = NULL;

	}	//	end of if

	if(g_pVtxBufferFade != NULL)	//	���_�o�b�t�@�̊J��
	{

		g_pVtxBufferFade -> Release();
		g_pVtxBufferFade = NULL;

	}	//	end of if

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UpdataFade( void )
 ����:		
 �߂�l:	
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateFade( void )
{

	// ���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_2D* pVtx;



	if( g_fade == FADE_NONE )	//	�t�F�[�h���Ȃ����̏���
	{

		return;

	}	//	end of if

	if( g_fade == FADE_IN )	//	�t�F�[�h�C�����̏���
	{

		g_colorFade.a -= FADE_RATE;	//	a�l�����Z���Č��̉�ʂ𕂂��яオ�点��

		//	�t�F�[�h�C���̏I��
		if( g_colorFade.a < 0.0f )
		{
			g_colorFade.a = 0.0f;
			g_fade = FADE_NONE;

			//	�t�F�[�h���̃t���O��OFF
			g_FadeFlag = false;

		}	//	end of if

	}	//	end of if


	else if( g_fade == FADE_OUT )	//	�t�F�[�h�A�E�g���̏���
	{

		g_colorFade.a += FADE_RATE;	//	a�l�����Z���Č��̉�ʂ������Ă���

		//	�t�F�[�h�A�E�g�̏I��
		if( g_colorFade.a > 1.0f )
		{

			g_colorFade.a = 1.0f;
			g_fade = FADE_IN;	//	�t�F�[�h�C���ɏ����̐؂�ւ�

			//	�t�F�[�h�̐ݒ�
			SetMode( g_modenext );

		}	//	end of if

	}	//	end of else if



	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	g_pVtxBufferFade -> Lock ( 0 , 0 , ( void** )&pVtx , 0 );


	//	���_�J���[�̐ݒ�
	SetColorFade( g_colorFade , pVtx );


	//	�o�b�t�@���A�����b�N
	g_pVtxBufferFade -> Unlock();

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawFade( void )
 ����:		
 �߂�l:	
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawFade( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D );


	//	�X�g���[����ݒ肷��
	pDevice -> SetStreamSource( 0 , g_pVtxBufferFade , 0 , sizeof( VERTEX_2D ) );


	//	�e�N�X�`���ݒ�
	pDevice -> SetTexture( 0 , g_pTextureFade );


	//	�t�F�[�h�̕`��
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0, NUM_POLYGON);


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void MakeVertexFade( LPDIRECT3DDEVICE9 pDevice )
 ����:		LPDIRECT3DDEVICE9 pDevice
 �߂�l:	
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
HRESULT MakeVertexFade( LPDIRECT3DDEVICE9 pDevice )
{
	
	// FAILED�}�N���ŃG���[�`�F�b�N
	if ( FAILED ( pDevice -> CreateVertexBuffer ( sizeof ( VERTEX_2D ) * NUM_VERTEX , D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &g_pVtxBufferFade , NULL ) ) )
	{
		return E_FAIL;

	}	//	end of if


	// ���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_2D* pVtx;


	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	g_pVtxBufferFade -> Lock ( 0 , 0 , ( void** )&pVtx , 0 );


	//	���_���W�̐ݒ�
	pVtx[ 0 ].pos = D3DXVECTOR3( FADE_POS_X                , FADE_POS_Y                 , 0.0f );
	pVtx[ 1 ].pos = D3DXVECTOR3( FADE_POS_X + SCREEN_WIDTH , FADE_POS_Y                 , 0.0f );
	pVtx[ 2 ].pos = D3DXVECTOR3( FADE_POS_X                , FADE_POS_Y + SCREEN_HEIGHT , 0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3( FADE_POS_X + SCREEN_WIDTH , FADE_POS_Y + SCREEN_HEIGHT , 0.0f );


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


	//	�o�b�t�@���A�����b�N
	g_pVtxBufferFade -> Unlock();


	return S_OK;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void SetColorFade( D3DXCOLOR colorFade , VERTEX_2D* pVtx )
 ����:		D3DXCOLOR g_colorFade	�F
			VERTEX_2D* pVtx			���z�A�h���X���擾����|�C���^�ϐ�
 �߂�l:	
 ����:		���_�J���[�̐ݒ�
-----------------------------------------------------------------------------*/
void SetColorFade( D3DXCOLOR colorFade , VERTEX_2D* pVtx )
{

	//	���_�F�̐ݒ�
	pVtx[ 0 ].color = D3DXCOLOR( colorFade.r , colorFade.g , colorFade.b , colorFade.a );
	pVtx[ 1 ].color = D3DXCOLOR( colorFade.r , colorFade.g , colorFade.b , colorFade.a );
	pVtx[ 2 ].color = D3DXCOLOR( colorFade.r , colorFade.g , colorFade.b , colorFade.a );
	pVtx[ 3 ].color = D3DXCOLOR( colorFade.r , colorFade.g , colorFade.b , colorFade.a );


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void SetFade( FADE fade , MODE modenext )
 ����:		FADE fade		�t�F�[�h�̏��
			MODE modenext	���̃��[�h
 �߂�l:	
 ����:		�t�F�[�h�̐ݒ�
-----------------------------------------------------------------------------*/
void SetFade( FADE fade , MODE modenext )
{
	//	�t�F�[�h�̏��
	g_fade = fade;

	//	���̃��[�h�̐ݒ�
	g_modenext = modenext;

	//	�t�F�[�h���̃t���O��ON
	g_FadeFlag = true;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	MODE *GetNextMode( void )
 ����:		
 �߂�l:	return &g_modenext;
 ����:		���̃��[�h�̎擾
-----------------------------------------------------------------------------*/
MODE *GetNextMode( void )
{

	return &g_modenext;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	bool *GetFadeFlag( void )
 ����:		
 �߂�l:	return &g_FadeFlag;
			�t�F�[�h��		true
			�t�F�[�h�I��	false
 ����:		�t�F�[�h�����ǂ���
-----------------------------------------------------------------------------*/
bool *GetFadeFlag( void )
{
	return &g_FadeFlag;

}	//	end of func