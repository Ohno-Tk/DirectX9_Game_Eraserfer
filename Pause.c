/*=============================================================================

		�|�[�Y[ Pause.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/01/16
-------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "main.h"
#include "input.h"
#include "fade.h"
#include "Pause.h"
#include "sound.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/pauseBg.jpg"	//	�|�[�Y�w�i
#define POLYGON01_TEXTURENAME "data/TEXTURE/GAME/continue.png"	//	�R���e�B�j���[
#define POLYGON02_TEXTURENAME "data/TEXTURE/GAME/quit.png"	//	�I��
#define POLYGON03_TEXTURENAME "data/TEXTURE/GAME/pauseBg1.jpg"	//	�|�[�Y�w�i1
#define POLYGON04_TEXTURENAME "data/TEXTURE/GAME/pausescroll.png"	//	�|�[�Y�X�N���[��

#define MAX_TEXTURE ( 5 )	//	�ő�e�N�X�`����

#define MIN_ALPHA ( 0.5f )	//	���l�̍ŏ��l

/*-----------------------------------------------------------------------------
	��
-----------------------------------------------------------------------------*/
typedef enum
{
	TYPE_NONE = 0,
	TYPE_CONTINUE,	//	�R���e�B�j���[
	TYPE_QUIT,		//	�I��
	TYPE_MAX

}TYPE_PAUSE;

/*-----------------------------------------------------------------------------
	�\����
-----------------------------------------------------------------------------*/
typedef struct
{
	D3DXVECTOR2 Pos;	//	���W
	D3DXVECTOR2 Size;	//	�傫��
	D3DXCOLOR Color;	//	�F

}PAUSE;

/*-----------------------------------------------------------------------------
	�v���g�^�C�v�錾
-----------------------------------------------------------------------------*/

//	���_�̍쐬
HRESULT MakeVertexPause( LPDIRECT3DDEVICE9 pDevice );

//	���_�̕ύX
void VerTexPause( VERTEX_2D* pVtx , int Cnt );

//	UV�l�̕ύX
void VerTexUVPause( VERTEX_2D* pVtx , int Cnt );

//	�L�[�{�[�h�ł̈ړ�
void PauseCursorKeyBoard( void );

//	�J��
void PauseTransition( void );

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferPause = NULL;	//	���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePause[ MAX_TEXTURE ] = { NULL };//	�e�N�X�`���C���^�[�t�F�[�X

PAUSE g_Pause[ MAX_TEXTURE ];	//	�|�[�Y�\����

TYPE_PAUSE g_TypePause;	//	�|�[�Y��

D3DXVECTOR2 g_UV_Scroll;	//	UV���W

bool g_PauseFlag;	//	�|�[�Y�t���O

/*-----------------------------------------------------------------------------
 �֐���:	void InitPause( void )
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void InitPause( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�e�N�X�`���̃G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTexturePause[ 0 ] ) ) )
	{

		MessageBox( NULL , "[ Pause.cpp ]\n POLYGON00_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON01_TEXTURENAME , &g_pTexturePause[ 1 ] ) ) )
	{

		MessageBox( NULL , "[ Pause.cpp ]\n POLYGON01_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if


	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON02_TEXTURENAME , &g_pTexturePause[ 2 ] ) ) )
	{

		MessageBox( NULL , "[ Pause.cpp ]\n POLYGON02_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if

	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON03_TEXTURENAME , &g_pTexturePause[ 3 ] ) ) )
	{

		MessageBox( NULL , "[ Pause.cpp ]\n POLYGON03_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if

	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON04_TEXTURENAME , &g_pTexturePause[ 4 ] ) ) )
	{

		MessageBox( NULL , "[ Pause.cpp ]\n POLYGON04_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	���_�̍쐬
	MakeVertexPause( pDevice );


	//	�\���̏�����

	for( int CntPause = 0 ; CntPause < MAX_TEXTURE ; CntPause++ )
	{

		//	�F
		g_Pause[ CntPause ].Color = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f );

	}	//	end of for


	//	�|�[�Y�w�i
	//	���W
	g_Pause[ 0 ].Pos = D3DXVECTOR2( 0.0f , 0.0f );

	//	�傫��
	g_Pause[ 0 ].Size = D3DXVECTOR2( SCREEN_WIDTH , SCREEN_HEIGHT );

	//	�F
	g_Pause[ 0 ].Color = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 0.5f );


	//	�R���e�B�j���[
	//	���W
	g_Pause[ TYPE_CONTINUE ].Pos = D3DXVECTOR2( 330.0f , 80.0f );

	//	�傫��
	g_Pause[ TYPE_CONTINUE ].Size = D3DXVECTOR2( 200.0f , 100.0f );


	//	�I��
	//	���W
	g_Pause[ TYPE_QUIT ].Pos = D3DXVECTOR2( g_Pause[ TYPE_CONTINUE ].Pos.x , g_Pause[ TYPE_CONTINUE ].Pos.y + 325.0f );

	//	�傫��
	g_Pause[ TYPE_QUIT ].Size = g_Pause[ TYPE_CONTINUE ].Size;

	//	�F
	g_Pause[ TYPE_QUIT ].Color = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 0.5f );


	//	�|�[�Y�w�i1
	//	���W
	g_Pause[ 3 ].Pos = D3DXVECTOR2( SCREEN_WIDTH * 0.3f , SCREEN_HEIGHT * 0.05f );

	//	�傫��
	g_Pause[ 3 ].Size = D3DXVECTOR2( 350.0f , 500.0f );


	//	�|�[�Y�X�N���[��
	//	���W
	g_Pause[ 4 ].Pos = D3DXVECTOR2( SCREEN_WIDTH * 0.31f , SCREEN_HEIGHT * 0.08f );

	//	�傫��
	g_Pause[ 4 ].Size = D3DXVECTOR2( 330.0f , 475.0f );


	//	�񋓏�����
	g_TypePause = TYPE_CONTINUE;


	//	�ϐ�������

	//	UV���W
	g_UV_Scroll = D3DXVECTOR2( 0.0f , 0.0f );

	//	�|�[�Y�t���O
	g_PauseFlag = false;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitPause( void )
 ����:		
 �߂�l:	
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitPause( void )
{

	if(g_pVtxBufferPause != NULL)	//���_�o�b�t�@�̃C���^�[�t�F�[�X�|�C���^�̉��
	{
		g_pVtxBufferPause -> Release();
		g_pVtxBufferPause  = NULL;

	}	//	end of if


	for( int Cnt = 0 ; Cnt < MAX_TEXTURE ; Cnt++ )
	{

		if( g_pTexturePause[ Cnt ] != NULL )	//	�e�N�X�`���|���S���J��
		{
			g_pTexturePause[ Cnt ] -> Release();
			g_pTexturePause[ Cnt ] = NULL;

		}	//	end of if

	}	//	end of for

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UpdatePause( void )
 ����:		
 �߂�l:	
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdatePause( void )
{

	//	���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_2D* pVtx;


	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	g_pVtxBufferPause -> Lock ( 0 , 0 , ( void** )&pVtx , 0 );


	for( int Cnt = 0 ; Cnt < MAX_TEXTURE ; Cnt++ )
	{

		//	�|�[�Y����������
		if( g_PauseFlag == true )
		{

			//	���_�̕ύX
			VerTexPause( pVtx , Cnt );

			//	UV�l�̕ύX
			VerTexUVPause( pVtx , MAX_TEXTURE - 1 );

		}	//	end of if

	}	//	end of for


	g_pVtxBufferPause -> Unlock(); //����ȍ~�G��Ă͂����Ȃ�


	if( GetKeyboardTrigger( DIK_P ) )
	{

		//	�|�[�Y�t���O��ON�ɂ���
		g_PauseFlag = true;

		//	���y�Đ�
		PlaySound( SOUND_LABEL_SE_MENU );

	}	//	end of if


	//	�|�[�Y����������
	if( g_PauseFlag == true )
	{

		//	�L�[�{�[�h�ł̈ړ�
		PauseCursorKeyBoard();


		//	�J��
		PauseTransition();


		//	�e�N�X�`���A�j���[�V����
		g_UV_Scroll.x += 0.004f;
		g_UV_Scroll.y += 0.004f;

	}	//	end of if

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawPause( void )
 ����:		
 �߂�l:	
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawPause( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D );

	//	�X�g���[����ݒ肷��
	pDevice -> SetStreamSource( 0 , g_pVtxBufferPause , 0 , sizeof( VERTEX_2D ) );


	//	�|�[�Y����������
	if( g_PauseFlag == true )
	{

		//	�e�N�X�`���̃Z�b�g
		pDevice -> SetTexture( 0 , g_pTexturePause[ 0 ] );

		//	�|���S���̕`��
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , NUM_POLYGON);

		//	�e�N�X�`���̃Z�b�g
		pDevice -> SetTexture( 0 , g_pTexturePause[ 3 ] );

		//	�|���S���̕`��
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 12 , NUM_POLYGON);

		//	�e�N�X�`���̃Z�b�g
		pDevice -> SetTexture( 0 , g_pTexturePause[ 4 ] );

		//	�|���S���̕`��
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 16 , NUM_POLYGON);

		//	�e�N�X�`���̃Z�b�g
		pDevice -> SetTexture( 0 , g_pTexturePause[ 1 ] );

		//	�|���S���̕`��
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 4 , NUM_POLYGON);

		//	�e�N�X�`���̃Z�b�g
		pDevice -> SetTexture( 0 , g_pTexturePause[ 2 ] );

		//	�|���S���̕`��
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 8 , NUM_POLYGON);

	}	//	end of if

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void PauseCursorKeyBoard( void )
 ����:		
 �߂�l:	
 ����:		�L�[�{�[�h�ł̈ړ�
-----------------------------------------------------------------------------*/
void PauseCursorKeyBoard( void )
{

	if( GetKeyboardTrigger( DIK_W ) )
	{

		if( g_TypePause == TYPE_QUIT )
		{

			//	�^�C�v�̐؂�ւ�
			g_TypePause = TYPE_CONTINUE;


			//	���l�̕ύX
			g_Pause[ TYPE_CONTINUE ].Color.a = 1.0f;
			g_Pause[ TYPE_QUIT ].Color.a = MIN_ALPHA;

		}	//	end of if

	}	//	end of if

	else if( GetKeyboardTrigger( DIK_S ) )
	{

		if( g_TypePause == TYPE_CONTINUE )
		{

			//	�^�C�v�̐؂�ւ�
			g_TypePause = TYPE_QUIT;


			//	���l�̕ύX
			g_Pause[ TYPE_CONTINUE ].Color.a = MIN_ALPHA;
			g_Pause[ TYPE_QUIT ].Color.a = 1.0f;

		}	//	end of if

	}	//	end of else if

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void PauseTransition( void )
 ����:		
 �߂�l:	
 ����:		�J��
-----------------------------------------------------------------------------*/
void PauseTransition( void )
{

	if( GetKeyboardTrigger( DIK_SPACE ) )
	{

		if( g_TypePause == TYPE_CONTINUE )
		{

			g_PauseFlag = false;

		}	//	end of if

		else if( g_TypePause == TYPE_QUIT )
		{

			//	�t�F�[�h��Ԑݒ�
			SetFade( FADE_OUT , MODE_TITLE );

		}	//	end of else if

	}	//	end of if

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT MakeVertexPause( LPDIRECT3DDEVICE9 pDevice )
 ����:		LPDIRECT3DDEVICE9 pDevice	�f�o�C�X
 �߂�l:	�ǂ��ꍇ	return S_OK;
			�_���ȏꍇ	return E_FAIL;
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
HRESULT MakeVertexPause( LPDIRECT3DDEVICE9 pDevice )
{

	//	���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_2D* pVtx;


	// FAILED�}�N���ŃG���[�`�F�b�N
	if ( FAILED ( pDevice -> CreateVertexBuffer ( sizeof ( VERTEX_2D ) * NUM_VERTEX * MAX_TEXTURE , D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &g_pVtxBufferPause , NULL ) ) )
	{

		return E_FAIL;

	}	//	end of if


	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	g_pVtxBufferPause -> Lock ( 0 , 0 , ( void** )&pVtx , 0 );


	for( int Cnt = 0 ; Cnt < MAX_TEXTURE ; Cnt++ )
	{

		//	���_���W�̐ݒ�
		pVtx[ 0 ].pos = D3DXVECTOR3( g_Pause[ Cnt ].Pos.x                         , g_Pause[ Cnt ].Pos.y , 0.0f );
		pVtx[ 1 ].pos = D3DXVECTOR3( g_Pause[ Cnt ].Pos.x + g_Pause[ Cnt ].Size.x , g_Pause[ Cnt ].Pos.y , 0.0f );
		pVtx[ 2 ].pos = D3DXVECTOR3( g_Pause[ Cnt ].Pos.x                         , g_Pause[ Cnt ].Pos.y + g_Pause[ Cnt ].Size.y , 0.0f );
		pVtx[ 3 ].pos = D3DXVECTOR3( g_Pause[ Cnt ].Pos.x + g_Pause[ Cnt ].Size.x , g_Pause[ Cnt ].Pos.y + g_Pause[ Cnt ].Size.y , 0.0f );

		//	���W�ϊ��ςݒ��_�t���O�̐ݒ�
		pVtx[ 0 ].rhw = 1.0f;
		pVtx[ 1 ].rhw = 1.0f;
		pVtx[ 2 ].rhw = 1.0f;
		pVtx[ 3 ].rhw = 1.0f;

		//	���_�F�̐ݒ�
		pVtx[ 0 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 100 );
		pVtx[ 1 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 100 );
		pVtx[ 2 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 100 );
		pVtx[ 3 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 100 );

		//	�e�N�X�`�����W�̐ݒ�
		pVtx[ 0 ].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[ 1 ].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[ 2 ].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[ 3 ].tex = D3DXVECTOR2( 1 , 1 );

		pVtx += 4;

	}	//	end of for


	g_pVtxBufferPause -> Unlock(); //����ȍ~�G��Ă͂����Ȃ�

	return S_OK;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void VerTexPause( VERTEX_2D* pVtx , int Cnt )
 ����:		VERTEX_2D* pVtx		���z�A�h���X���擾����|�C���^�ϐ�
			int Cnt				�|�[�Y�\���̂̃J�E���^
 �߂�l:	
 ����:		���_�̕ύX
-----------------------------------------------------------------------------*/
void VerTexPause( VERTEX_2D* pVtx , int Cnt )
{

	pVtx += Cnt * NUM_VERTEX;

	//	���_���W�̐ݒ�
	pVtx[ 0 ].pos = D3DXVECTOR3( g_Pause[ Cnt ].Pos.x                         , g_Pause[ Cnt ].Pos.y , 0.0f );
	pVtx[ 1 ].pos = D3DXVECTOR3( g_Pause[ Cnt ].Pos.x + g_Pause[ Cnt ].Size.x , g_Pause[ Cnt ].Pos.y , 0.0f );
	pVtx[ 2 ].pos = D3DXVECTOR3( g_Pause[ Cnt ].Pos.x                         , g_Pause[ Cnt ].Pos.y + g_Pause[ Cnt ].Size.y , 0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3( g_Pause[ Cnt ].Pos.x + g_Pause[ Cnt ].Size.x , g_Pause[ Cnt ].Pos.y + g_Pause[ Cnt ].Size.y , 0.0f );


	//	���_�F�̐ݒ�
	pVtx[ 0 ].color = D3DXCOLOR( g_Pause[ Cnt ].Color.r , g_Pause[ Cnt ].Color.g , g_Pause[ Cnt ].Color.b , g_Pause[ Cnt ].Color.a );
	pVtx[ 1 ].color = D3DXCOLOR( g_Pause[ Cnt ].Color.r , g_Pause[ Cnt ].Color.g , g_Pause[ Cnt ].Color.b , g_Pause[ Cnt ].Color.a );
	pVtx[ 2 ].color = D3DXCOLOR( g_Pause[ Cnt ].Color.r , g_Pause[ Cnt ].Color.g , g_Pause[ Cnt ].Color.b , g_Pause[ Cnt ].Color.a );
	pVtx[ 3 ].color = D3DXCOLOR( g_Pause[ Cnt ].Color.r , g_Pause[ Cnt ].Color.g , g_Pause[ Cnt ].Color.b , g_Pause[ Cnt ].Color.a );

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void VerTexUVPause( VERTEX_2D* pVtx , int Cnt )
 ����:		VERTEX_2D* pVtx		���z�A�h���X���擾����|�C���^�ϐ�
			int CntPause		�|�[�Y�\���̂̃J�E���^
 �߂�l:	
 ����:		UV�l�̕ύX
-----------------------------------------------------------------------------*/
void VerTexUVPause( VERTEX_2D* pVtx , int Cnt )
{

	pVtx += Cnt * NUM_VERTEX;

	//	�e�N�X�`�����W�̐ݒ�
	pVtx[ 0 ].tex = D3DXVECTOR2( 0 + g_UV_Scroll.x , 0 + g_UV_Scroll.y );
	pVtx[ 1 ].tex = D3DXVECTOR2( 1 + g_UV_Scroll.x , 0 + g_UV_Scroll.y );
	pVtx[ 2 ].tex = D3DXVECTOR2( 0 + g_UV_Scroll.x , 1 + g_UV_Scroll.y );
	pVtx[ 3 ].tex = D3DXVECTOR2( 1 + g_UV_Scroll.x , 1 + g_UV_Scroll.y );
														 
}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	bool *GetPauseFlag( void )
 ����:		
 �߂�l:	return &g_PauseFlag;
			�|�[�Y��	true
			�|�[�Y�I��	false
 ����:		�|�[�Y�t���O���̎擾
-----------------------------------------------------------------------------*/
bool *GetPauseFlag( void )
{

	return &g_PauseFlag;

}	//	end of func