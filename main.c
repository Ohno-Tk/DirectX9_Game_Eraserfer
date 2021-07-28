/*=============================================================================

		[ main.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2016/12/07
-------------------------------------------------------------------------------
	���@Update
=============================================================================*/

/*-----------------------------------------------------------------------------
						scanf ��warning�h�~ 
-----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "camera.h"
#include "light.h"

#include "title.h"
#include "Tutorial.h"
#include "game.h"
#include "result.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define CLASS_NAME     "3D�Q�[��"			//	�E�C���h�E�N���X�̖��O
#define WINDOW_NAME    "Eraserfer"	//	�E�C���h�E�̖��O

/*-----------------------------------------------------------------------------
	��
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�\����
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	�v���g�^�C�v�錾
-----------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam );

HRESULT Init( HINSTANCE hInstance , HWND hWnd , BOOL bWindow );	//	�������֐�
void Uninit( void );	//	�I������
void Update( void );	//	�X�V����
void Draw( void );	//	�`�揈��

#ifdef _DEBUG

void DrawFPS( void );

#endif	//	_DEBUG

//	���C���[�t���[��
void Wireframe( void );

/*-----------------------------------------------------------------------------
	�O���[�o���ϐ�
-----------------------------------------------------------------------------*/
//	Direct3D�C���^�[�t�F�[�X�擾
LPDIRECT3D9 g_pD3D = NULL;

LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//	Direct3D�f�o�C�X�C���^�[�t�F�[�X�i�|�C���^�j

MODE g_mode = MODE_TITLE;	//	���̃��[�h

#ifdef _DEBUG

	LPD3DXFONT g_pFont = NULL;

#endif	//	_DEBUG

int g_nCountFPS = 0;	//	FPS�J�E���^

bool g_WireframeFlag = false;	//	���C���[�t���[���t���O

ModeFunc pInitFunc[]={
	InitTitle,
	InitTutorial,
	InitGame,
	InitResult,
	};

ModeFunc pUninitFunc[]={
	UninitTitle,
	UninitTutorial,
	UninitGame,
	UninitResult,
	};

ModeFunc pUpdateFunc[]={
	UpdateTitle,
	UpdateTutorial,
	UpdateGame,
	UpdateResult,
	};

ModeFunc pDrawFunc[]={
	DrawTitle,
	DrawTutorial,
	DrawGame,
	DrawResult,
	};

/*-----------------------------------------------------------------------------
	���C���֐�
-----------------------------------------------------------------------------*/
int APIENTRY WinMain( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR IpCmdLine , int nCmdShow )
{
	//  waring�̌x����������
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( IpCmdLine );

	//	�E�C���h�E�̃p�[�c�o�^
	WNDCLASSEX wcex =
	{
		sizeof( WNDCLASSEX ) ,					//	WNDCLASSEX�̃������T�C�Y���w��
		CS_CLASSDC ,							//	�\������E�C���h�E�̃X�^�C����ݒ�
		WndProc ,								//	�E�B���h�E�v���V�[�W���̃A�h���X( �֐��� )���w��@�v���g�^�C�v�錾�����֐��������i�d�v�I�I�j
		0 ,										//	�ʏ�͎g�p���Ȃ��̂�" 0 "���w��
		0 ,										//	�ʏ�͎g�p���Ȃ��̂�" 0 "���w��
		hInstance ,								//	WinMain�̃p�����[�^�̃C���X�^���X�n���h����ݒ�
		NULL ,									//	�g�p����A�C�R�����w��( Windows�������Ă���A�C�R�����g���Ȃ� )
		LoadCursor( NULL , IDC_ARROW ),			//	�}�E�X�J�[�\�����w��	�i���Ƃł͂��Ȃ��j
		( HBRUSH )( COLOR_WINDOW + 1 ) ,		//	�E�C���h�E�̃N���C�A���g�̈�̔w�i�F��ݒ�	�i���Ƃł͂��Ȃ��j
		NULL ,									//	Windows�ɂ��郁�j���[��ݒ�
		CLASS_NAME ,							//	�E�C���h�E�N���X�̖��O	�i�d�v�I�I�j
		NULL									//	�������A�C�R�����ݒ肳�ꂽ�ꍇ�̏����L�q	�i���Ƃł͂��Ȃ��j
	};

	//	�E�C���h�E�N���X�̓o�^
	RegisterClassEx( &wcex );	//	�I���W�i���̃E�C���h�E�p�[�c�̖��O������( �J�X�^���E�C���h�E�p�̐ݒ� )

	HWND hWnd;	//	�E�C���h�E�n���h���i�@���C���n���h���@�j
	MSG msg;

	const int Windowstyle = WS_OVERLAPPEDWINDOW ^  WS_MINIMIZEBOX ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME;

	//	�`��̈�̃T�C�Y����E�C���h�E�̋�`���擾
	RECT cr = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };
	AdjustWindowRect( &cr , Windowstyle , FALSE );

	RECT dr;
	GetWindowRect( GetDesktopWindow() , &dr );

	int dw = dr.right - dr.left;
	int dh = dr.bottom - dr.top;

	int ww = cr.right - cr.left;
	int wh = cr.bottom - cr.top;

	int wx = ww > dw ? 0 : ( dw - ww ) / 2 ;
	int wy = wh > dh ? 0 : ( dh - wh ) / 2 ;

	//	�E�C���h�E�̍쐬
	hWnd/*���E�C���h�n���h��*/ = CreateWindowEx( 0 ,		//	�g���E�C���h�E�X�^�C���i�@������Ɛݒ肷��@�j
		CLASS_NAME ,										//	�E�C���h�E�N���X�̖��O
		WINDOW_NAME ,										//	�E�C���h�E�̖��O
		Windowstyle ,								//	�E�C���h�E�X�^�C��
		wx ,										//	�E�C���h�E�̍���w���W
		wy ,										//	�E�C���h�E�̍���x���W
		ww ,										//	�E�C���h�E�̕��i�@�t���[�������킹�����@�j
		wh ,										//	�E�C���h�E�̍����i�@�t���[�������킹�������@�j
		NULL ,												//	�e�E�C���h�E�̃n���h���i�@�|�C���^�@�j
		NULL ,												//	���j���[�n���h���܂��͎q�E�C���h�EID
		hInstance ,											//	�C���X�^���X�n���h��
		NULL );												//	�E�C���h�E�쐬�f�[�^

	//	�E�C���h�E�̕\��
	ShowWindow( hWnd , nCmdShow );		//	�w�肳�ꂽ�E�C���h�E�̕\��
	UpdateWindow( hWnd );				//	�E�C���h�E�̏�Ԃ𒼂��ɔ��f

	Init( hInstance , hWnd , TRUE );	//	�������֐�

	GetDevice();

	//	����\�̐ݒ�i�^�C�}�[�̐��x��ǂ�����j
	timeBeginPeriod( 1 );

	//	�e�J�E���^�[�̏�����
	DWORD dwFrameCount = 0;
	DWORD dwCurrentTime = 0;	//	���݂̎���
	DWORD dwExecLastTime = timeGetTime();	//	���݂̎������~���P�ʂŎ擾
	DWORD dwFPSLastTime = dwExecLastTime;

	//	���b�Z�[�W���[�v
	//	��P�����F���b�Z�[�W���
	//	��Q�����F�E�C���h�E�̃n���h��
	//	��R�����F�ŏ��̃��b�Z�[�W
	//	��S�����F�Ō�̃��b�Z�[�W
	for( ;; )
	{
		if( PeekMessage( &msg , NULL , 0 , 0 , PM_REMOVE ) != 0 )
		{
			//	Windows�̏���
			if( msg.message == WM_QUIT )
			{
				break;
			}
			else
			{
				//	�Ăяo�����X���b�h�̃��b�Z�[�W�L���[����
				//	���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	//	���݂̎������~���P�ʂŎ擾
			if( (dwCurrentTime - dwFPSLastTime) >= 500 )
			{
				g_nCountFPS = ( dwFrameCount * 1000 ) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}
			if( (dwCurrentTime - dwExecLastTime) >= (1000/60) )	//	���݂̃t���[������ǂ�ʂ������̂�( �����v�Z )	�f�o�b�O�Ōv���������Ƃ���if���R�����g�A�E�g
			{
				dwExecLastTime = dwCurrentTime;	//	�����������Ԃ�ۑ�

				//	DirectX�̏����i�Q�[�������j
				Update();	//	�X�V����

				Draw();	//	�`�揈��

				dwFrameCount++;

			}
		}
	}

	//	�E�C���h�E�N���X�̓o�^������
	//	�������F���N���X��
	//	�������F�A�v���P�[�V�����C���X�^���X
	UnregisterClass( CLASS_NAME , wcex.hInstance );

	Uninit();	//	�I������

	return ( int )msg.wParam;
}	//	end of func

/*-----------------------------------------------------------------------------
				�E�C���h�E�v���V�[�W��
		( CALLBACK:Win32API�֐����Ăяo���Ƃ��̋K�� )
		hWnd :   �E�C���h�E�̃n���h��
		uMsg :   ���b�Z�[�W�̎��ʎq
		wParam : ���b�Z�[�W�̍ŏ��̃p�����[�^
		lParam : ���b�Z�[�W�̂Q�Ԗڂ̃p�����[�^
-------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam )
{
	UINT nSelect;	//	Esc�L�[�̓��͔���

	switch( uMsg )
	{

	case WM_DESTROY:										//	�E�C���h�E�j���̃��b�Z�[�W
		//MessageBox( NULL , "WM_DESTROY�����s���ꂽ" , "" , MB_OK );
		PostQuitMessage( 0 );								//	"WM_QUIT"���b�Z�[�W��Ԃ�
		break;

	case WM_KEYDOWN:	//	�L�[����
		switch( wParam )
		{
			case VK_ESCAPE:	//	ESCAPE�L�[
			nSelect = MessageBox( NULL , "�I�����܂����H" , "�I�����b�Z�[�W" , MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2 );
			if( nSelect == IDYES )
			{
				DestroyWindow( hWnd );
			}
			break;
		}
	case WM_CLOSE:
		//MessageBox( NULL , "WM_CLOSE�����s���ꂽ" , "" , MB_OK );
		break;

	default:
		break;
	}

	return DefWindowProc( hWnd , uMsg , wParam , lParam );	//	����̏������
}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	HRESULT Init( HINSTANCE hInstance , HWND hWnd , BOOL bWindow )
 ����:		HINSTANCE hInstance
			HWND hWnd
			BOOL bWindow
 �߂�l:	S_OK
 ����:		�������֐�
-----------------------------------------------------------------------------*/
HRESULT Init( HINSTANCE hInstance , HWND hWnd , BOOL bWindow )
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	//	D3D9�C���^�[�t�F�[�X�̎擾
	g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	if( g_pD3D == NULL )
	{
		return E_FAIL;
	}	//	end of if
	//	���݂̃f�B�X�v���C���[�h�̎擾
	if( FAILED( g_pD3D -> GetAdapterDisplayMode( D3DADAPTER_DEFAULT , &d3ddm ) ) )
	{
		return E_FAIL;
	}	//	end of if

	//	�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�(�f�o�C�X�̐ݒ�̂��߂̐ݒ�)
	ZeroMemory( &d3dpp , sizeof( d3dpp ) );
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//	Direct3D�f�o�C�X�̍쐬
	//	�ǂ�����n�[�h�E�F�A����
	if( FAILED( g_pD3D -> CreateDevice( D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL , hWnd , D3DCREATE_HARDWARE_VERTEXPROCESSING , &d3dpp , &g_pD3DDevice ) ) )
	{
		//	�`�揈���̓n�[�h�E�F�A�����@���_�����̓\�t�g�E�F�A����
		if( FAILED( g_pD3D -> CreateDevice( D3DADAPTER_DEFAULT , D3DDEVTYPE_HAL , hWnd , D3DCREATE_SOFTWARE_VERTEXPROCESSING , &d3dpp , &g_pD3DDevice ) ) )
		{
			//	�ǂ�����\�t�g�E�F�A����
			if( FAILED( g_pD3D -> CreateDevice( D3DADAPTER_DEFAULT , D3DDEVTYPE_REF , hWnd , D3DCREATE_SOFTWARE_VERTEXPROCESSING , &d3dpp , &g_pD3DDevice ) ) )
			{
				MessageBox( NULL , "�f�o�C�X�����܂���ł���" , "�x��" , MB_OK | MB_ICONHAND );
				return E_FAIL;
			}	//	end of if
		}	//	end of if
	}	//	end of if

#if 0
	//	�r���[�|�[�g�ϐ�
	D3DVIEWPORT9 vp;


	vp.X = 0.0f;
	vp.Y = SCREEN_HEIGHT / 2;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;
	vp.Width = SCREEN_WIDTH;
	vp.Height = SCREEN_HEIGHT / 2;

	//	�r���[�|�[�g��������
	g_pD3DDevice -> SetViewport( &vp );

#endif

	// �t���v���𗠖ʂƂ���
	g_pD3DDevice -> SetRenderState( D3DRS_CULLMODE , D3DCULL_CCW );
#if 0
	// ���v���𗠖ʂƂ���
	_pD3DDevice -> SetRenderState( D3DRS_CULLMODE , D3DCULL_CW );

	// ���ʂɂ���
	g_pD3DDevice -> SetRenderState( D3DRS_CULLMODE , D3DCULL_NONE );
#endif

	
	//	a�u�����h
	//	���Z����
	g_pD3DDevice -> SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE );
	g_pD3DDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
	g_pD3DDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );

	//	�A���t�@�u�����h�̐ݒ�
	g_pD3DDevice -> SetTextureStageState( 0 , D3DTSS_ALPHAOP , D3DTOP_MODULATE );
	g_pD3DDevice -> SetTextureStageState( 0 , D3DTSS_ALPHAARG1 , D3DTA_TEXTURE );
	g_pD3DDevice -> SetTextureStageState( 0 , D3DTSS_ALPHAARG2 , D3DTA_DIFFUSE );


	// ���݉�ʂɕ`����Ă����Ԃɑ΂��č�����`�悷����e

	// �T���v���[�X�e�[�g�̐ݒ�
	// �k����
	g_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_MINFILTER , D3DTEXF_LINEAR );

	// �g�厞
	g_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_MAGFILTER , D3DTEXF_LINEAR );

#if 0
	// ���E�~���[
	g_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_ADDRESSU , D3DTADDRESS_MIRROR );

	// �㉺�~���[
	g_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_ADDRESSV , D3DTADDRESS_MIRROR );

	// CLAMP
	g_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_ADDRESSU , D3DTADDRESS_CLAMP );
	g_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_ADDRESSV , D3DTADDRESS_CLAMP );
#endif

	// CLAMP
	g_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_ADDRESSU , D3DTADDRESS_WRAP );
	g_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_ADDRESSV , D3DTADDRESS_WRAP );

#ifdef _DEBUG
	D3DXCreateFont( g_pD3DDevice ,
					18 ,	//	��������
					0 ,	//	������
					0 ,	//	�����̑���
					0 ,	//	�~�b�v�}�b�v
					FALSE ,	//	�C�^���b�N
					SHIFTJIS_CHARSET ,
					OUT_DEFAULT_PRECIS ,
					DEFAULT_QUALITY ,
					DEFAULT_PITCH ,
					"Terminal" ,
					&g_pFont);
#endif	//	_DEBUG

	//	������
	g_WireframeFlag = false;	//	���C���[�t���[���t���O

	InitKeyboard( hInstance, hWnd);	//	�L�[�{�[�h������

	InitSound( hWnd );	//	���y�̏�����

	InitFade();	//	�t�F�[�h�̏�����

	pInitFunc[ g_mode ]();


//	InitCamera();	//	�J�����̏�����

	InitLight();		//	���C�g�̏�����

	return S_OK;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void Uninit( void )
 ����:		
 �߂�l:	
 ����:		�I���֐�
-----------------------------------------------------------------------------*/
void Uninit( void )
{

	if( g_pD3DDevice != NULL )
	{
		g_pD3DDevice -> Release();	//	Direct3DDevice�J��
		g_pD3DDevice = NULL;	
	}
	if( g_pD3D != NULL )
	{
		g_pD3D -> Release();	//	Direct3D�C���^�[�t�F�[�X�J��
		g_pD3D = NULL;
	}

#ifdef _DEBUG
	if( g_pFont != NULL )
	{
		g_pFont -> Release();	//	�t�H���g�̃C���^�[�t�F�[�X�J��
		g_pFont = NULL;
	}
#endif	//	_DEBUG

	UninitKeyboard();	//	�L�[�{�[�h�̏I��

	UninitSound();	//	���y�̏I��

	UninitFade();	//	�t�F�[�h�̏I��

	pUninitFunc[g_mode]();

	UninitCamera();	//	�J�����̏I��

	UninitLight();	//	���C�g�̏I��

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void Update( void )
 ����:		
 �߂�l:	
 ����:		�X�V�֐�
-----------------------------------------------------------------------------*/
void Update( void )
{
	
	//	���C���[�t���[����ON�EOFF
	if( GetKeyboardTrigger( DIK_F2 ) )
	{
		if( g_WireframeFlag == false )
		{
			g_WireframeFlag = true;

		}

		else if( g_WireframeFlag == true )
		{
			g_WireframeFlag = false;

		}

	}

	Wireframe();	//	���C���[�t���[��

	UpdateKeyboard();	//	�L�[�{�[�h�̍X�V

	UpdateFade();	//	�t�F�[�h�̍X�V

	pUpdateFunc[g_mode]();

	UpdateCamera();	//	�J�����̍X�V

	UpdateLight();	//	���C�g�̍X�V

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void Draw( void )
 ����:		
 �߂�l:	
 ����:		�`��֐�
-----------------------------------------------------------------------------*/
void Draw( void )
{

	//	�o�b�N�o�b�t�@�Ƃy�o�b�t�@�̃N���A
	g_pD3DDevice ->Clear( 0 , NULL , D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , D3DCOLOR_RGBA( 0 , 177 , 184 , 255 ) , 1.0f , 0 );

	//	�`��̊J�n
	if( SUCCEEDED( g_pD3DDevice -> BeginScene() ) )
	{

		DrawCamera();	//	�J�����̕`��

		DrawLight();	//	���C�g�̕`��

		pDrawFunc[g_mode]();

		DrawFade();	//	�t�F�[�h�̕`��
		
#ifdef _DEBUG
		DrawFPS();	//	FPS�\��

#endif

		//	�`��I��
		g_pD3DDevice -> EndScene();

	}	//	end of if

	g_pD3DDevice -> Present( NULL , NULL , NULL , NULL );

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void SetMode(MODE mode)
 ����:		MODE mode
 �߂�l:	
 ����:		���[�h�ݒu
-----------------------------------------------------------------------------*/
void SetMode( MODE mode )
{

	pUninitFunc[ g_mode ]();

	pInitFunc[ mode ]();

	g_mode = mode;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	LPDIRECT3DDEVICE9 GetDevice( void )
 ����:		
 �߂�l:	
 ����:		D3DDevice�̎擾
-----------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 GetDevice( void )
{

	return g_pD3DDevice;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	MODE *GetMode( void )
 ����:		
 �߂�l:	return &g_mode;
 ����:		���[�h�̎擾
-----------------------------------------------------------------------------*/
MODE *GetMode( void )
{

	return &g_mode;

}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void SetWorldInv( D3DXVECTOR3 Pos , D3DXVECTOR3 Scl )
 ����:		D3DXVECTOR3 Pos		���W
			D3DXVECTOR3 Scl		�g�嗦
 �߂�l:	
 ����:		�t�s�񂠂�̃��[���h���W�ϊ�
-----------------------------------------------------------------------------*/
void SetWorldInv( D3DXVECTOR3 Pos , D3DXVECTOR3 Scl )
{
	//	�r���[�s��̋t�s��̍쐬
	D3DXMATRIX mtxViewInverse;

	//	�r���[�s��̏��擾
	D3DXMATRIX mtxView = GetView();

	//	�]�u�s��
	D3DXMatrixTranspose( &mtxViewInverse , &mtxView );

	//	���s�ړ��������J�b�g
	mtxViewInverse._14 = 0.0f;
	mtxViewInverse._24 = 0.0f;
	mtxViewInverse._34 = 0.0f;

	D3DXMATRIX mtxWorld , mtxScl , mtxPos;

	D3DXMatrixIdentity( &mtxWorld );	//	�s���P�ʍs��ɂ���

		//	�g��s������
	D3DXMatrixScaling( &mtxScl ,	//�g��s�񂪍����
		Scl.x ,	//	X���g��
		Scl.y ,	//	Y���g��
		Scl.z );	//	Z���g��

	//	���s�ړ��s������
	D3DXMatrixTranslation( &mtxPos ,
		Pos.x ,	//	X���ړ�
		Pos.y ,	//	Y���ړ�
		Pos.z );	//	Z���ړ�


	//	�|���Ă�����
	D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxViewInverse );

	D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxScl );

	D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxPos );

	//	�f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	g_pD3DDevice -> SetTransform( D3DTS_WORLD , &mtxWorld );


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void SetWorld( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot , D3DXVECTOR3 Scl )
 ����:		D3DXVECTOR3 Pos		���W
			D3DXVECTOR3 Rot		��]
			D3DXVECTOR3 Scl		�g�嗦
 �߂�l:	
 ����:		�t�s��Ȃ��̃��[���h���W�ϊ�
-----------------------------------------------------------------------------*/
void SetWorld( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot , D3DXVECTOR3 Scl )
{

	D3DXMATRIX mtxWorld , mtxScl , mtxRot , mtxPos;

	D3DXMatrixIdentity( &mtxWorld );	//	�s���P�ʍs��ɂ���

		//	�g��s������
	D3DXMatrixScaling( &mtxScl ,	//�g��s�񂪍����
		Scl.x ,	//	X���g��
		Scl.y ,	//	Y���g��
		Scl.z );	//	Z���g��

	//	��]�s������
	D3DXMatrixRotationYawPitchRoll( &mtxRot ,	//	��]�s�񂪍����
		D3DXToRadian( Rot.y ) , //	Y����]
		D3DXToRadian( Rot.x ) , //	X����]
		D3DXToRadian( Rot.z ) ); //	Z����]

	//	���s�ړ��s������
	D3DXMatrixTranslation( &mtxPos ,
		Pos.x ,	//	X���ړ�
		Pos.y ,	//	Y���ړ�
		Pos.z );	//	Z���ړ�


	//	�|���Ă�����
	D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxScl );

	D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxRot );

	D3DXMatrixMultiply( &mtxWorld , &mtxWorld , &mtxPos );

	//	�f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	g_pD3DDevice -> SetTransform( D3DTS_WORLD , &mtxWorld );


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void Wireframe( void )
 ����:		
 �߂�l:	
 ����:		���C���[�t���[��
-----------------------------------------------------------------------------*/
void Wireframe( void )
{

	if( g_WireframeFlag == false )
	{

		// ���C���[�t���[���\���ɂ���
		g_pD3DDevice -> SetRenderState( D3DRS_FILLMODE , D3DFILL_FORCE_DWORD );

	}	//	end of if

	else if( g_WireframeFlag == true )
	{

		// ���C���[�t���[���\���ɂ���
		g_pD3DDevice -> SetRenderState( D3DRS_FILLMODE , D3DFILL_WIREFRAME );

	}	//	end of else if


}	//	end of func

/*-----------------------------------------------------------------------------
 �֐���:	void DrawFPS( void )
 ����:		
 �߂�l:	
 ����:		FPS�\��
-----------------------------------------------------------------------------*/
#ifdef _DEBUG
void DrawFPS( void )
{
	RECT rect = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };

	char aStr[ 256 ];

	sprintf( &aStr[ 0 ] , "FPS:%d" , g_nCountFPS );

	g_pFont -> DrawText( NULL ,
						&aStr[ 0 ] ,
						-1 ,
						&rect ,
						DT_LEFT ,
						D3DCOLOR_RGBA( 255 , 255 , 255 , 255));
}
#endif	//	_DEBUG
