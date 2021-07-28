/*=============================================================================

		���ꐔ[ HelpNumber.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2016/01/05
-------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "main.h"
#include "HelpNumber.h"
#include "Born.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/number000.png"
#define POLYGON01_TEXTURENAME "data/TEXTURE/GAME/yogore.png"

#define MAX_TEXTURE ( 2 )	//	�ő�e�N�X�`����

#define SCORE_DIGIT ( 2 )	//	�����̐����̕\��

#define SCORE_MAX ( 9999 )	//	�X�R�A�̍ő�l

#define ADD_SCORE ( 10 )	//	���Z����X�R�A�̒l


#define POLYGON00_X ( SCREEN_WIDTH - 80.0f )		//	�X�R�A��X
#define POLYGON00_Y ( 50.0f )		//	�X�R�A��Y
#define POLYGON00_WIDTH  ( 70.0f )	//	�X�R�A��Width
#define POLYGON00_HEIGHT ( 70.0f )	//	�X�R�A��Height

#define POLYGON01_X ( SCREEN_WIDTH - 220.0f )		//	�X�R�A������X
#define POLYGON01_Y ( -10.0f )		//	�X�R�A������Y
#define POLYGON01_WIDTH  ( 150.0f )	//	�X�R�A������Width
#define POLYGON01_HEIGHT ( 75.0f )	//	�X�R�A������Height

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
HRESULT MakeVertexHelpNumber( LPDIRECT3DDEVICE9 pDevice );

//	���_�̕ύX
void VerTexHelpNumber( VERTEX_2D* pVtx , int Cnt , int num );

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferScore = NULL;	//	���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureScore[ MAX_TEXTURE ] = { NULL };//	�e�N�X�`���C���^�[�t�F�[�X

D3DXCOLOR g_ScoreColor;	//	�F

int g_Number;	//	�l��

/*-----------------------------------------------------------------------------
 �֐���:	void InitHelpNumber( void )
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void InitHelpNumber( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	�e�N�X�`���̃G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureScore[ 0 ] ) ) )
	{

		MessageBox( NULL , "[ HelpNumber.cpp ]\n POLYGON00_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if


	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON01_TEXTURENAME , &g_pTextureScore[ 1 ] ) ) )
	{

		MessageBox( NULL , "[ HelpNumber.cpp ]\n POLYGON01_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	���_�̍쐬
	MakeVertexHelpNumber( pDevice );


	//	�ϐ�������

	//	�F
	g_ScoreColor = D3DXCOLOR( 255 , 255 , 255 , 255 );

	//	�X�R�A
	g_Number = 11;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitHelpNumber( void )
 ����:		
 �߂�l:	
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitHelpNumber( void )
{

	if(g_pVtxBufferScore != NULL)	//���_�o�b�t�@�̃C���^�[�t�F�[�X�|�C���^�̉��
	{
		g_pVtxBufferScore -> Release();
		g_pVtxBufferScore  = NULL;

	}	//	end of if


	for( int Cnt = 0 ; Cnt < MAX_TEXTURE ; Cnt++ )
	{

		if( g_pTextureScore[ Cnt ] != NULL )	//	�e�N�X�`���|���S���J��
		{
			g_pTextureScore[ Cnt ] -> Release();
			g_pTextureScore[ Cnt ] = NULL;

		}	//	end of if

	}	//	end of for

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UpdateHelpNumber( void )
 ����:		
 �߂�l:	
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateHelpNumber( void )
{

	int num;	//	������\������ϐ�
	int value = g_Number;


	//	���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_2D* pVtx;


	//�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferScore -> Lock( 0 , 0 ,	( void** )&pVtx , 0 );

	for( int Cnt = 0 ; Cnt < SCORE_DIGIT ; Cnt++ )
	{

		num = value % 10;
		value /= 10;

		//	���_�̕ύX
		VerTexHelpNumber( pVtx , Cnt , num );

	}	//	end of for


	g_pVtxBufferScore -> Unlock(); //����ȍ~�G��Ă͂����Ȃ�


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawHelpNumber( void )
 ����:		
 �߂�l:	
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawHelpNumber( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D );

	//	�X�g���[����ݒ肷��
	pDevice -> SetStreamSource( 0 , g_pVtxBufferScore , 0 , sizeof( VERTEX_2D ) );

	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureScore[ 0 ] );


	for( int Cnt = 0 ; Cnt < SCORE_DIGIT ; Cnt++ )
	{

		//	�|���S���̕`��
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , Cnt * NUM_VERTEX , NUM_POLYGON);

	}	//	end of for


	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureScore[ 1 ] );

	//	�|���S���̕`��
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , SCORE_DIGIT * NUM_VERTEX , NUM_POLYGON);


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT MakeVertexScore( LPDIRECT3DDEVICE9 pDevice )
 ����:		LPDIRECT3DDEVICE9 pDevice	�f�o�C�X
 �߂�l:	�ǂ��ꍇ	return S_OK;
			�_���ȏꍇ	return E_FAIL;
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
HRESULT MakeVertexHelpNumber( LPDIRECT3DDEVICE9 pDevice )
{

	int num;	//	������\������ϐ�
	int value = g_Number;


	//	���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_2D* pVtx;


	// FAILED�}�N���ŃG���[�`�F�b�N
	if ( FAILED ( pDevice -> CreateVertexBuffer ( sizeof ( VERTEX_2D ) * NUM_VERTEX * SCORE_DIGIT * MAX_TEXTURE , D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &g_pVtxBufferScore , NULL ) ) )
	{

		return E_FAIL;

	}	//	end of if


	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	g_pVtxBufferScore -> Lock ( 0 , 0 , ( void** )&pVtx , 0 );

	for( int Cnt = 0 ; Cnt < SCORE_DIGIT ; Cnt++ )
	{

		num = value % 10;
		value /= 10;

		//	���_���W�̐ݒ�
		pVtx[ 0 ].pos = D3DXVECTOR3( POLYGON00_X                   - Cnt * POLYGON00_WIDTH , POLYGON00_Y                    , 0.0f );
		pVtx[ 1 ].pos = D3DXVECTOR3( POLYGON00_X + POLYGON00_WIDTH - Cnt * POLYGON00_WIDTH , POLYGON00_Y                    , 0.0f );
		pVtx[ 2 ].pos = D3DXVECTOR3( POLYGON00_X                   - Cnt * POLYGON00_WIDTH , POLYGON00_Y + POLYGON00_HEIGHT , 0.0f );
		pVtx[ 3 ].pos = D3DXVECTOR3( POLYGON00_X + POLYGON00_WIDTH - Cnt * POLYGON00_WIDTH , POLYGON00_Y + POLYGON00_HEIGHT , 0.0f );

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
		pVtx[ 0 ].tex = D3DXVECTOR2( 0.1f * num        , 0 );
		pVtx[ 1 ].tex = D3DXVECTOR2( 0.1f * num + 0.1f , 0 );
		pVtx[ 2 ].tex = D3DXVECTOR2( 0.1f * num        , 1 );
		pVtx[ 3 ].tex = D3DXVECTOR2( 0.1f * num + 0.1f , 1 );

		pVtx += 4;	//	�|�C���^�����炷

	}	//	end of for


	//	���_���W�̐ݒ�
	pVtx[ 0 ].pos = D3DXVECTOR3( POLYGON01_X                   , POLYGON01_Y                    , 0.0f );
	pVtx[ 1 ].pos = D3DXVECTOR3( POLYGON01_X + POLYGON01_WIDTH , POLYGON01_Y                    , 0.0f );
	pVtx[ 2 ].pos = D3DXVECTOR3( POLYGON01_X                   , POLYGON01_Y + POLYGON01_HEIGHT , 0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3( POLYGON01_X + POLYGON01_WIDTH , POLYGON01_Y + POLYGON01_HEIGHT , 0.0f );

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


	g_pVtxBufferScore -> Unlock(); //����ȍ~�G��Ă͂����Ȃ�

	return S_OK;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void VerTexScore( VERTEX_2D* pVtx , int Cnt , int num )
 ����:		VERTEX_2D* pVtx		���z�A�h���X���擾����|�C���^�ϐ�
			int Cnt				�X�R�A�̃J�E���^
			int num				�e�N�X�`�������炷�ϐ�
 �߂�l:	
 ����:		���_�̕ύX
-----------------------------------------------------------------------------*/
void VerTexHelpNumber( VERTEX_2D* pVtx , int Cnt , int num )
{

	//	pVtx��Cnt�����炷
	pVtx += Cnt * NUM_VERTEX;


	//	���_�F�̐ݒ�
	pVtx[ 0 ].color = D3DXCOLOR( g_ScoreColor.r , g_ScoreColor.g , g_ScoreColor.b , g_ScoreColor.a );
	pVtx[ 1 ].color = D3DXCOLOR( g_ScoreColor.r , g_ScoreColor.g , g_ScoreColor.b , g_ScoreColor.a );
	pVtx[ 2 ].color = D3DXCOLOR( g_ScoreColor.r , g_ScoreColor.g , g_ScoreColor.b , g_ScoreColor.a );
	pVtx[ 3 ].color = D3DXCOLOR( g_ScoreColor.r , g_ScoreColor.g , g_ScoreColor.b , g_ScoreColor.a );

	//	�e�N�X�`�����W�̐ݒ�
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.1f * num        , 0 );
	pVtx[ 1 ].tex = D3DXVECTOR2( 0.1f * num + 0.1f , 0 );
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.1f * num        , 1 );
	pVtx[ 3 ].tex = D3DXVECTOR2( 0.1f * num + 0.1f , 1 );


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	int *GetHelpNumber( void )
 ����:		
 �߂�l:	return &g_Number;
 ����:		�X�R�A���̎擾
-----------------------------------------------------------------------------*/
int *GetHelpNumber( void )
{

	return &g_Number;

}	//	end of func
