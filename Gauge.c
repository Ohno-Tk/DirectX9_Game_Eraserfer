/*=============================================================================

		�Q�[�W[ Gauge.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/02/01
-------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "Gauge.h"
#include "Player.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/Gauge.png"
#define POLYGON01_TEXTURENAME "data/TEXTURE/GAME/Gauge_bar.jpg"

#define MAX_TEXTURE ( 2 )	//	�e�N�X�`���̍ő吔

#define MAX_GAUGE ( 2 )	//	�ő�Q�[�W�{��

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
	int NowLife;		//	���݂̃��C�t
	int MaxLife;		//	�ő僉�C�t
	float Maxlength;	//	�ő�̑傫��
	bool Use;	//	�g�p�t���O
}GAUGE;

/*-----------------------------------------------------------------------------
	�v���g�^�C�v�錾
-----------------------------------------------------------------------------*/

//	���_�̍쐬
HRESULT MakeVertexGauge( LPDIRECT3DDEVICE9 pDevice );

//	���_�̕ύX
void VerTexGauge( VERTEX_2D* pVtx , int Cnt );

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferGauge = NULL;	//	���_�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureGauge[ MAX_TEXTURE ] = { NULL };	//	�e�N�X�`���C���^�[�t�F�[�X

GAUGE g_Gauge[ MAX_GAUGE ];	//	�\����

/*-----------------------------------------------------------------------------
 �֐���:	void InitGauge( void )
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void InitGauge( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	�v���C���[���̎擾
	PLAYER *Player = GetPlayer();


	//	�e�N�X�`���̃G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureGauge[ 0 ] ) ) )
	{
		MessageBox( NULL , "[ Gauge.cpp ]\n POLYGON00_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if

	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON01_TEXTURENAME , &g_pTextureGauge[ 1 ] ) ) )
	{
		MessageBox( NULL , "[ Gauge.cpp ]\n POLYGON01_TEXTURENAME\n�̓ǂݍ��݂��ł��܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );

	}	//	end of if

	//	�\���̏�����

	//	�v���C���[
	g_Gauge[ 0 ].Pos = D3DXVECTOR2( 0.0f , 50.0f );
	g_Gauge[ 0 ].Size = D3DXVECTOR2( 350.0f , 25.0f );
	g_Gauge[ 0 ].Color = D3DXCOLOR( 255 , 255 , 255 , 255 );


	g_Gauge[ 1 ].Pos = D3DXVECTOR2( g_Gauge[ 0 ].Pos.x + 11.0f , g_Gauge[ 0 ].Pos.y + 3.0f );
	g_Gauge[ 1 ].Size = D3DXVECTOR2( g_Gauge[ 0 ].Size.x - 18.0f , g_Gauge[ 0 ].Size.y - 5.0f );
	g_Gauge[ 1 ].Color = D3DXCOLOR( 0 , 0 , 255 , 255 );
	g_Gauge[ 1 ].MaxLife = 10;
	g_Gauge[ 1 ].NowLife = Player -> Life;
	g_Gauge[ 1 ].Maxlength = g_Gauge[ 1 ].Size.x;


	//	���_�̍쐬
	MakeVertexGauge( pDevice );

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UninitGauge( void )
 ����:		
 �߂�l:	
 ����:		�I��
-----------------------------------------------------------------------------*/
void UninitGauge( void )
{

	if(g_pVtxBufferGauge != NULL)	//���_�o�b�t�@�̃C���^�[�t�F�[�X�|�C���^�̉��
	{
		g_pVtxBufferGauge -> Release();
		g_pVtxBufferGauge  = NULL;

	}	//	end of if


	for( int Cnt = 0 ; Cnt < MAX_TEXTURE ; Cnt++ )
	{

		if( g_pTextureGauge[ Cnt ] != NULL )	//	�e�N�X�`���|���S���J��
		{
			g_pTextureGauge[ Cnt ] -> Release();
			g_pTextureGauge[ Cnt ] = NULL;

		}	//	end of if

	}	//	end of for

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void UpdateGauge( void )
 ����:		
 �߂�l:	
 ����:		�X�V
-----------------------------------------------------------------------------*/
void UpdateGauge( void )
{

	float Life;

	//	���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_2D* pVtx;

	//	�v���C���[���̎擾
	PLAYER *Player = GetPlayer();


	//�o�b�t�@�����b�N�����z�A�h���X���擾����
	g_pVtxBufferGauge -> Lock( 0 , 0 ,	( void** )&pVtx , 0 );


	for( int Cnt = 0 ; Cnt < MAX_GAUGE ; Cnt++ )
	{

		
		//	���_�̕ύX
		VerTexGauge( pVtx , Cnt );

	}	//	end of for


	g_pVtxBufferGauge -> Unlock(); //����ȍ~�G��Ă͂����Ȃ�


	//	�Q�[�W�������������������߂�
	Life = ( float )Player -> Life / g_Gauge[ 1 ].MaxLife;

	//	�Q�[�W�̒�����ύX
	g_Gauge[ 1 ].Size.x = Life * g_Gauge[ 1 ].Maxlength;


	if( Player -> Life >= 10 )
	{

		g_Gauge[ 1 ].Color = D3DXCOLOR( 255 , 0 , 0 , 255 );

	}	//	end of if
	else
	{

		g_Gauge[ 1 ].Color = D3DXCOLOR( 0 , 0 , 255 , 255 );

	}
	
}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawGauge( void )
 ����:		
 �߂�l:	
 ����:		�`��
-----------------------------------------------------------------------------*/
void DrawGauge( void )
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D );

	//	�X�g���[����ݒ肷��
	pDevice -> SetStreamSource( 0 , g_pVtxBufferGauge , 0 , sizeof( VERTEX_2D ) );


	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureGauge[ 0 ] );

	//	�|���S���̕`��
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , NUM_POLYGON);


	//	�e�N�X�`���̃Z�b�g
	pDevice -> SetTexture( 0 , g_pTextureGauge[ 1 ] );

	//	�|���S���̕`��
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 4 , NUM_POLYGON);



}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT MakeVertexGauge( LPDIRECT3DDEVICE9 pDevice )
 ����:		LPDIRECT3DDEVICE9 pDevice	�f�o�C�X
 �߂�l:	�ǂ��ꍇ	return S_OK;
			�_���ȏꍇ	return E_FAIL;
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
HRESULT MakeVertexGauge( LPDIRECT3DDEVICE9 pDevice )
{

	//	���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_2D* pVtx;


	// FAILED�}�N���ŃG���[�`�F�b�N
	if ( FAILED ( pDevice -> CreateVertexBuffer ( sizeof ( VERTEX_2D ) * NUM_VERTEX * MAX_GAUGE , D3DUSAGE_WRITEONLY , FVF_VERTEX_2D , D3DPOOL_MANAGED , &g_pVtxBufferGauge , NULL ) ) )
	{

		return E_FAIL;

	}	//	end of if


	float Life;

	//	�v���C���[���̎擾
	PLAYER *Player = GetPlayer();

	//	�Q�[�W�������������������߂�
	Life = ( float )Player -> Life / g_Gauge[ 1 ].MaxLife;

	//	�Q�[�W�̒�����ύX
	g_Gauge[ 1 ].Size.x = Life * g_Gauge[ 1 ].Maxlength;


	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	g_pVtxBufferGauge -> Lock ( 0 , 0 , ( void** )&pVtx , 0 );


	for( int Cnt = 0 ; Cnt < MAX_GAUGE ; Cnt++ )
	{

		//	���_���W�̐ݒ�
		pVtx[ 0 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x                         , g_Gauge[ Cnt ].Pos.y , 0.0f );
		pVtx[ 1 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x + g_Gauge[ Cnt ].Size.x , g_Gauge[ Cnt ].Pos.y , 0.0f );
		pVtx[ 2 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x                         , g_Gauge[ Cnt ].Pos.y + g_Gauge[ Cnt ].Size.y , 0.0f );
		pVtx[ 3 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x + g_Gauge[ Cnt ].Size.x , g_Gauge[ Cnt ].Pos.y + g_Gauge[ Cnt ].Size.y , 0.0f );

		//	���W�ϊ��ςݒ��_�t���O�̐ݒ�
		pVtx[ 0 ].rhw = 1.0f;
		pVtx[ 1 ].rhw = 1.0f;
		pVtx[ 2 ].rhw = 1.0f;
		pVtx[ 3 ].rhw = 1.0f;

		//	���_�F�̐ݒ�
		pVtx[ 0 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );
		pVtx[ 1 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );
		pVtx[ 2 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );
		pVtx[ 3 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );

		//	�e�N�X�`�����W�̐ݒ�
		pVtx[ 0 ].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[ 1 ].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[ 2 ].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[ 3 ].tex = D3DXVECTOR2( 1 , 1 );

		pVtx += 4;	//	�|�C���^�����炷

	}	//	end of for



	g_pVtxBufferGauge -> Unlock(); //����ȍ~�G��Ă͂����Ȃ�

	return S_OK;


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void VerTexGauge( VERTEX_2D* pVtx , int Cnt )
 ����:		VERTEX_2D* pVtx , int Cnt
 �߂�l:	
 ����:		���_�̕ύX
-----------------------------------------------------------------------------*/
void VerTexGauge( VERTEX_2D* pVtx , int Cnt )
{

	pVtx += Cnt * NUM_VERTEX;


	//	���_���W�̐ݒ�
	pVtx[ 0 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x                         , g_Gauge[ Cnt ].Pos.y , 0.0f );
	pVtx[ 1 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x + g_Gauge[ Cnt ].Size.x , g_Gauge[ Cnt ].Pos.y , 0.0f );
	pVtx[ 2 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x                         , g_Gauge[ Cnt ].Pos.y + g_Gauge[ Cnt ].Size.y , 0.0f );
	pVtx[ 3 ].pos = D3DXVECTOR3( g_Gauge[ Cnt ].Pos.x + g_Gauge[ Cnt ].Size.x , g_Gauge[ Cnt ].Pos.y + g_Gauge[ Cnt ].Size.y , 0.0f );


	//	���_�F�̐ݒ�
	pVtx[ 0 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );
	pVtx[ 1 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );
	pVtx[ 2 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );
	pVtx[ 3 ].color = D3DXCOLOR( g_Gauge[ Cnt ].Color.r , g_Gauge[ Cnt ].Color.g , g_Gauge[ Cnt ].Color.b , g_Gauge[ Cnt ].Color.a );

}	//	end of func