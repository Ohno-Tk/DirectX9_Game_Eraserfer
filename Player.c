/*=============================================================================

		プレイヤー[ Player.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2016/12/29
-------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
						scanf のwarning防止 
-----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "MeshWall.h"
#include "Player.h"
#include "Shadow.h"
#include "fade.h"
#include "Utility.h"
#include "Born.h"
#include "Help.h"
#include "HelpNumber.h"
#include "Particle.h"
#include "Cleaner.h"

/*-----------------------------------------------------------------------------
	定数定義
-----------------------------------------------------------------------------*/
#define MODEL_NAME "data/MODEL/Player/Player.x"

#define MAX_MAT ( 8 )	//	モデルの最大マテリアル数

#define ROT_SPEED ( 1.5f )	//	回転量

#define LEEP_ROT ( 0.1f )	//	リープの回転速度

/*-----------------------------------------------------------------------------
	列挙
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	構造体
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	プロトタイプ宣言
-----------------------------------------------------------------------------*/

//	キーボードでの操作
void KeyboardOperate( void );

//	物体との当たり判定
void CollisionObject( void );

/*-----------------------------------------------------------------------------
	グローバル変数
-----------------------------------------------------------------------------*/
LPD3DXMESH g_pMeshPlayer;	//	メッシュインターフェースポインタ

LPD3DXBUFFER g_pBufferMatPlayer;	//	マテリアル情報

DWORD g_nNumMatPlayer;	//	マテリアル数

LPDIRECT3DTEXTURE9 g_pTexturePlayer[ MAX_MAT ] = { NULL };//	テクスチャインターフェース

D3DXMATERIAL* pMatPlayer;	//	マテリアルポインタ

LPD3DXFONT g_pFontPlayer = NULL;	//	フォントポインタ

PLAYER g_Player;	//	プレイヤー構造体

#ifdef _DEBUG

	LPD3DXFONT g_pFontModel = NULL;

#endif	//	_DEBUG

/*-----------------------------------------------------------------------------
 関数名:	void InitPlayer( void )
 引数:		
 戻り値:	
 説明:		初期化
-----------------------------------------------------------------------------*/
void InitPlayer( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	次のモードの取得
	MODE *Mode = GetNextMode();


	HRESULT hr;

	hr = D3DXLoadMeshFromX( MODEL_NAME ,			//	ファイル名
							D3DXMESH_MANAGED,
							pDevice,				//	デバイス
							NULL,					//	隣接バッファ
							&g_pBufferMatPlayer,		//	マテリアル情報を格納
							NULL,
							&g_nNumMatPlayer,		//	マテリアル数
							&g_pMeshPlayer );		//	メッシュ

	//	モデルのエラーチェック
	if( FAILED( hr ) )
	{

		MessageBox( NULL , "[ Player.cpp ]\n MODEL_NAME\nの読み込みができませんでした" , "警告" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	マテリアル情報のポインタとしてバッファのアドレスを取得
	pMatPlayer = ( D3DXMATERIAL* )g_pBufferMatPlayer -> GetBufferPointer();

	for( int i = 0 ; i < ( int )g_nNumMatPlayer ; i++ )
	{
		if( pMatPlayer[ i ].pTextureFilename != NULL )
		{

			//	テクスチャのエラーチェック
			if( FAILED( D3DXCreateTextureFromFile( pDevice , pMatPlayer[ i ].pTextureFilename , &g_pTexturePlayer[ i ]  ) ) )
			{
				MessageBox( NULL , "モデルの画像の読み込みができませんでした" , "警告" , MB_OK | MB_ICONHAND );

			}	//	end of if

		}	//	end of if

	}	//	end of for



	//	構造体初期化

	if( *Mode == MODE_TITLE )
	{

		//	座標
		g_Player.World.Pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	回転量
		g_Player.World.Rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

	}	//	end of if

	else if( *Mode == MODE_GAME )
	{

		//	座標
		g_Player.World.Pos = D3DXVECTOR3( 0.0f , 0.0f , -800.0f );

		//	回転量
		g_Player.World.Rot = D3DXVECTOR3( 0.0f , 180.0f , 0.0f );

	}	//	end of else if

	else if( *Mode == MODE_RESULT )
	{

		//	座標
		g_Player.World.Pos = D3DXVECTOR3( 0.0f , 1050.0f , -13.0f );

		//	回転量
		g_Player.World.Rot = D3DXVECTOR3( 90.0f , 180.0f , 180.0f );

	}	//	end of else if

	//	拡大率
	g_Player.World.Scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	//	前の座標
	g_Player.OldPos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

	//	回転
	g_Player.Rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

	//	移動量
	g_Player.Move = D3DXVECTOR3( 5.0f , 5.0f , 5.0f );

	//	回転量
	g_Player.RotSpeed = D3DXVECTOR3( 3.0f , 1.0f , 1.0f );

	//	半径
	g_Player.Radius = 10.0f;

	g_Player.Rot2 = 180.0f;

	//	体力
	g_Player.Life = 0;

	//	使用フラグ
	g_Player.Use = true;


	//	影のセット
	SetShadow( g_Player.World.Pos , 10.0f , D3DXCOLOR( 0.5f , 0.5f , 0.5f , 1.0f ) );


#ifdef _DEBUG
	//	フォントの設定
	D3DXCreateFont( pDevice ,
				18 ,	//	文字高さ
				0 ,	//	文字幅
				0 ,	//	文字の太さ
				0 ,	//	ミップマップ
				FALSE ,	//	イタリック
				SHIFTJIS_CHARSET ,
				OUT_DEFAULT_PRECIS ,
				DEFAULT_QUALITY ,
				DEFAULT_PITCH ,
				"Terminal" ,
				&g_pFontModel );
#endif


}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UninitPlayer( void )
 引数:		
 戻り値:	
 説明:		終了
-----------------------------------------------------------------------------*/
void UninitPlayer( void )
{

	if( g_pMeshPlayer != NULL )	//	メッシュインターフェースポインタ
	{

		g_pMeshPlayer -> Release();
		g_pMeshPlayer = NULL;

	}	//	end of if

	if( g_pBufferMatPlayer != NULL )	//	マテリアル情報開放
	{

		g_pBufferMatPlayer -> Release();
		g_pBufferMatPlayer = NULL;

	}	//	end of if


#ifdef _DEBUG

	if( g_pFontPlayer != NULL )
	{

		g_pFontPlayer -> Release();
		g_pFontPlayer = NULL;

	}	//	end of if

#endif	//	_DEBUG

}	//	end of func
 
/*-----------------------------------------------------------------------------
 関数名:	void UpdataPlayer( void )
 引数:		
 戻り値:	
 説明:		更新
-----------------------------------------------------------------------------*/
void UpdatePlayer( void )
{

	//	次のモードの取得
	MODE *Mode = GetNextMode();


	if( *Mode == MODE_GAME )
	{

		//	前回の座標を取得
		g_Player.OldPos = g_Player.World.Pos;


		//	キーボードでの操作
		KeyboardOperate();

		//	物体との当たり判定
		CollisionObject();


		//	カメラのセット
		SetCamera( g_Player.World.Pos , g_Player.World.Rot , g_Player.Rot2 );

	}	//	end of if


}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void DrawPlayer( void )
 引数:		
 戻り値:	
 説明:		描画
-----------------------------------------------------------------------------*/
void DrawPlayer( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	現在デバイスに設定されているマテリアル情報の取得
	D3DMATERIAL9 matDef;
	pDevice -> GetMaterial( &matDef );


	if( g_Player.Use == true)
	{

		//	逆行列なしのワールド座標変換
		SetWorld( g_Player.World.Pos , g_Player.World.Rot , g_Player.World.Scl );


		for( int i = 0 ; i < ( int )g_nNumMatPlayer ; i++ )
		{
			//	デバイスにマテリアルを設定
			pDevice -> SetMaterial( &pMatPlayer[ i ].MatD3D );

			//	テクスチャ設定
			pDevice -> SetTexture( 0 , g_pTexturePlayer[ i ] );


			//	描画
			g_pMeshPlayer -> DrawSubset( i );

		}	//	end of for

	}	//	end of if

	pDevice -> SetMaterial( &matDef );

#ifdef _DEBUG

	RECT rect = { 0 , 100 , SCREEN_WIDTH , SCREEN_HEIGHT };
	RECT rect01 = { 0 , 130 , SCREEN_WIDTH , SCREEN_HEIGHT };

	char aStr[ 256 ] , aStr01[ 256 ];

	sprintf( &aStr[ 0 ] , "プレイヤー座標 : %.3f , %.3f , %.3f" , g_Player.World.Pos.x , g_Player.World.Pos.y , g_Player.World.Pos.z );
	sprintf( &aStr01[ 0 ] , "プレイヤー角度 : %.3f , %.3f , %.3f" , g_Player.World.Rot.x , g_Player.World.Rot.y , g_Player.World.Rot.z );

	g_pFontModel -> DrawText( NULL ,
						&aStr[ 0 ] ,
						-1 ,
						&rect ,
						DT_LEFT ,
						D3DCOLOR_RGBA( 255 , 255 , 255 , 255));

	g_pFontModel -> DrawText( NULL ,
						&aStr01[ 0 ] ,
						-1 ,
						&rect01 ,
						DT_LEFT ,
						D3DCOLOR_RGBA( 255 , 255 , 255 , 255));

#endif



}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void KeyboardOperate( void )
 引数:		
 戻り値:	
 説明:		キーボードでの操作
-----------------------------------------------------------------------------*/
void KeyboardOperate( void )
{

	//	影の情報取得
	SHADOW *Shadow = GetShadow( 0 );

	//	メッシュウォール情報取得
	MESHWALL *MeshWall = GetMeshWall();



	if( GetKeyboardPress( DIK_W ) )
	{
		g_Player.World.Pos.x += sinf( D3DXToRadian( g_Player.Rot2 ) ) * g_Player.Move.z * -1;
		g_Player.World.Pos.z += cosf( D3DXToRadian( g_Player.Rot2 ) ) * g_Player.Move.z * -1;

		Shadow -> World.Pos = g_Player.World.Pos;

		g_Player.World.Rot.y = g_Player.Rot2;


		SetParticle( D3DXVECTOR3( g_Player.World.Pos.x - 5.0f ,g_Player.World.Pos.y + 2.0f , g_Player.World.Pos.z ) , D3DXVECTOR3( -0.9f , 0.0f , 0.0f ) , D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f ) , 1.0f , 50 , 10.0f , 3.0f );

		SetParticle( D3DXVECTOR3( g_Player.World.Pos.x + 5.0f ,g_Player.World.Pos.y + 2.0f , g_Player.World.Pos.z ) , D3DXVECTOR3( -110.0f , 0.0f , 0.0f ) , D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f ) , 1.0f , 50 , 10.0f , 3.0f );


	}	//	end of if

	if( GetKeyboardPress( DIK_S ) )
	{

		g_Player.World.Pos.x += sinf( D3DXToRadian( g_Player.Rot2 ) ) * g_Player.Move.z;
		g_Player.World.Pos.z += cosf( D3DXToRadian( g_Player.Rot2 ) ) * g_Player.Move.z;

		Shadow -> World.Pos = g_Player.World.Pos;

		g_Player.World.Rot.y = g_Player.Rot2 - 180;

		
		SetParticle( D3DXVECTOR3( g_Player.World.Pos.x - 5.0f ,g_Player.World.Pos.y + 2.0f , g_Player.World.Pos.z ) , D3DXVECTOR3( -0.9f , 0.0f , 0.0f ) , D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f ) , 1.0f , 50 , 10.0f , 3.0f );

		SetParticle( D3DXVECTOR3( g_Player.World.Pos.x + 5.0f ,g_Player.World.Pos.y + 2.0f , g_Player.World.Pos.z ) , D3DXVECTOR3( -110.0f , 0.0f , 0.0f ) , D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f ) , 1.0f , 50 , 10.0f , 3.0f );


	}	//	end of if


	if( GetKeyboardPress( DIK_A ) )
	{

		g_Player.World.Pos.x += sinf( D3DXToRadian( g_Player.Rot2 + 90 ) ) * g_Player.Move.z;
		g_Player.World.Pos.z += cosf( D3DXToRadian( g_Player.Rot2 + 90 ) ) * g_Player.Move.z;

		Shadow -> World.Pos = g_Player.World.Pos;

		g_Player.World.Rot.y = g_Player.Rot2 - 90;


		SetParticle( D3DXVECTOR3( g_Player.World.Pos.x ,g_Player.World.Pos.y + 2.0f , g_Player.World.Pos.z - 5.0f ) , D3DXVECTOR3( -0.9f , 0.0f , 0.0f ) , D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f ) , 1.0f , 50 , 10.0f , 3.0f );

		SetParticle( D3DXVECTOR3( g_Player.World.Pos.x ,g_Player.World.Pos.y + 2.0f , g_Player.World.Pos.z + 5.0f ) , D3DXVECTOR3( -0.9f , 0.0f , 0.0f ) , D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f ) , 1.0f , 50 , -10.0f , 3.0f );


	}	//	end of if


	if( GetKeyboardPress( DIK_D ) )
	{

		g_Player.World.Pos.x += sinf( D3DXToRadian( g_Player.Rot2 - 90 ) ) * g_Player.Move.z;
		g_Player.World.Pos.z += cosf( D3DXToRadian( g_Player.Rot2 - 90 ) ) * g_Player.Move.z;

		Shadow -> World.Pos = g_Player.World.Pos;

		g_Player.World.Rot.y = g_Player.Rot2 + 90.0f;


		SetParticle( D3DXVECTOR3( g_Player.World.Pos.x ,g_Player.World.Pos.y + 2.0f , g_Player.World.Pos.z - 5.0f ) , D3DXVECTOR3( -110.0f , 0.0f , 0.0f ) , D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f ) , 1.0f , 50 , 10.0f , 3.0f );

		SetParticle( D3DXVECTOR3( g_Player.World.Pos.x ,g_Player.World.Pos.y + 2.0f , g_Player.World.Pos.z + 5.0f ) , D3DXVECTOR3( -110.0f , 0.0f , 0.0f ) , D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f ) , 1.0f , 50 , -10.0f , 3.0f );


	}	//	end of if



	//	角度が１８０度を超えたら
	if( g_Player.World.Rot.y > 180 )
	{

		//	-１７９度にする
		g_Player.World.Rot.y -= 360;

	}	//	end of if

	//	角度が-１８０度を超えたら
	else if( g_Player.World.Rot.y < -180 )
	{

		//	１７９度にする
		g_Player.World.Rot.y += 360;

	}	//	end of else if
	

	if( GetKeyboardPress( DIK_LEFTARROW ) )
	{
		g_Player.Rot2 -= g_Player.RotSpeed.x;
	}

	if( GetKeyboardPress( DIK_RIGHTARROW ) )
	{
		g_Player.Rot2 += g_Player.RotSpeed.x;
	}


}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void CollisionObject( void )
 引数:		
 戻り値:	
 説明:		物体との当たり判定
-----------------------------------------------------------------------------*/
void CollisionObject( void )
{

	//	影の情報取得
	SHADOW *Shadow = GetShadow( 0 );

	//	メッシュウォール情報取得
	MESHWALL *MeshWall = GetMeshWall();

	
	if( g_Player.World.Pos.z - 10.0f < MeshWall[ 0 ].World.Pos.z || g_Player.World.Pos.z + 10.0f > MeshWall[ 3 ].World.Pos.z )
	{

		g_Player.World.Pos = g_Player.OldPos;

		Shadow -> World.Pos = g_Player.OldPos;

	}	//	end of else if

	else if( g_Player.World.Pos.x + 10.0f > MeshWall[ 1 ].World.Pos.x || g_Player.World.Pos.x - 10.0f < MeshWall[ 2 ].World.Pos.x )
	{

		g_Player.World.Pos = g_Player.OldPos;

		Shadow -> World.Pos = g_Player.OldPos;

	}	//	end of else if


	
	BORN *Born = GetBorn();

	int *HelpNumber = GetHelpNumber();

	for( int Cnt = 0 ; Cnt < MAX_BORN ; Cnt++ , Born++ )
	{

		if( Born->Use == true )
		{

			if( SphereCollision( g_Player.World.Pos , D3DXVECTOR3( Born->World.Pos.x , Born->World.Pos.y + 10.0f , Born->World.Pos.z ) , g_Player.Radius , Born->Radius ) )
			{

				if( g_Player.Life < 10 )
				{

					Born->Use = false;

					*HelpNumber-=1;

					g_Player.Life++;

					SetOff( Cnt );

				}	//	end of if

				else
				{

					SetParticle( Born -> World.Pos , D3DXVECTOR3( -2.5f , 0.0f , 0.0f ) , D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f ) , 1.3f , 80 , 100.0f , 15.0f );

					
				}	//	end of else

			}	//	end of if

		}	//	end of if

	}	//	end of for


	//	黒板消しクリーナー情報の取得
	CLEANER *Cleaner = GetCleaner();


	if( SphereCollision( g_Player.World.Pos , D3DXVECTOR3( Cleaner->World.Pos.x , Cleaner->World.Pos.y , Cleaner->World.Pos.z + 30.0f ) , g_Player.Radius , Cleaner->Radius ) )
	{

		g_Player.Life = 0;

		g_Player.World.Pos = g_Player.OldPos;

	}	//	end of if


}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	PLAYER *GetPlayer( void )
 引数:		
 戻り値:	return &g_Player;
 説明:		プレイヤー情報の取得
-----------------------------------------------------------------------------*/
PLAYER *GetPlayer( void )
{

	return &g_Player;

}	//	end of func