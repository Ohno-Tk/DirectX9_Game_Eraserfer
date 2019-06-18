/*=============================================================================

		汚れ増やす敵[ Enemy1.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/02/22
-------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include <time.h>
#include "main.h"
#include "Enemy1.h"
#include "Born.h"
#include "HelpNumber.h"

/*-----------------------------------------------------------------------------
	定数定義
-----------------------------------------------------------------------------*/
#define MODEL_NAME "data/MODEL/Player/Player.x"

#define MAX_MAT ( 8 )	//	モデルの最大マテリアル数

#define SET_FRAME ( 325 )

/*-----------------------------------------------------------------------------
	列挙
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	構造体
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	プロトタイプ宣言
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	グローバル変数
-----------------------------------------------------------------------------*/
LPD3DXMESH g_pMeshEnemy1;	//	メッシュインターフェースポインタ

LPD3DXBUFFER g_pBufferMatEnemy1;	//	マテリアル情報

DWORD g_nNumMatEnemy1;	//	マテリアル数

LPDIRECT3DTEXTURE9 g_pTextureEnemy1[ MAX_MAT ] = { NULL };//	テクスチャインターフェース

D3DXMATERIAL* pMatEnemy1;	//	マテリアルポインタ

ENEMY g_Enemy1;	//	構造体

int g_Frame;

/*-----------------------------------------------------------------------------
 関数名:	void InitEnemy1( void )
 引数:		
 戻り値:	
 説明:		初期化
-----------------------------------------------------------------------------*/
void InitEnemy1( void )
{

	//	現在の時刻を取得
	srand((unsigned)time(NULL));


	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	HRESULT hr;

	hr = D3DXLoadMeshFromX( MODEL_NAME ,			//	ファイル名
							D3DXMESH_MANAGED,
							pDevice,				//	デバイス
							NULL,					//	隣接バッファ
							&g_pBufferMatEnemy1,		//	マテリアル情報を格納
							NULL,
							&g_nNumMatEnemy1,		//	マテリアル数
							&g_pMeshEnemy1 );		//	メッシュ

	//	モデルのエラーチェック
	if( FAILED( hr ) )
	{

		MessageBox( NULL , "[ Enemy1.cpp ]\n MODEL_NAME\nの読み込みができませんでした" , "警告" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	マテリアル情報のポインタとしてバッファのアドレスを取得
	pMatEnemy1 = ( D3DXMATERIAL* )g_pBufferMatEnemy1 -> GetBufferPointer();

	for( int i = 0 ; i < ( int )g_nNumMatEnemy1 ; i++ )
	{
		if( pMatEnemy1[ i ].pTextureFilename != NULL )
		{

			//	テクスチャのエラーチェック
			if( FAILED( D3DXCreateTextureFromFile( pDevice , pMatEnemy1[ i ].pTextureFilename , &g_pTextureEnemy1[ i ]  ) ) )
			{
				MessageBox( NULL , "モデルの画像の読み込みができませんでした" , "警告" , MB_OK | MB_ICONHAND );

			}	//	end of if

		}	//	end of if

	}	//	end of for


	//	構造体初期化
	g_Enemy1.World.Pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Enemy1.World.Rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Enemy1.World.Scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	g_Enemy1.Use = true;

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UninitEnemy1( void )
 引数:		
 戻り値:	
 説明:		終了
-----------------------------------------------------------------------------*/
void UninitEnemy1( void )
{

	if( g_pMeshEnemy1 != NULL )	//	メッシュインターフェースポインタ
	{

		g_pMeshEnemy1 -> Release();
		g_pMeshEnemy1 = NULL;

	}	//	end of if

	if( g_pBufferMatEnemy1 != NULL )	//	マテリアル情報開放
	{

		g_pBufferMatEnemy1 -> Release();
		g_pBufferMatEnemy1 = NULL;

	}	//	end of if

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UpdataEnemy1( void )
 引数:		
 戻り値:	
 説明:		更新
-----------------------------------------------------------------------------*/
void UpdateEnemy1( void )
{

	if( g_Enemy1.Use == true )
	{

		int *Number = GetHelpNumber();

		if( g_Frame == SET_FRAME && *Number != MAX_BORN )
		{
		
			SetBorn( D3DXVECTOR3( rand()%500 - 400 , 0.0f , rand()%500 - 400 ) );

			*Number += 1;

			g_Frame = 0;
		
		}


		g_Frame++;

	}

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void DrawEnemy1( void )
 引数:		
 戻り値:	
 説明:		描画
-----------------------------------------------------------------------------*/
void DrawEnemy1( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	現在デバイスに設定されているマテリアル情報の取得
	D3DMATERIAL9 matDef;
	pDevice -> GetMaterial( &matDef );


	if( g_Enemy1.Use == true)
	{

		//	逆行列なしのワールド座標変換
		SetWorld( g_Enemy1.World.Pos , g_Enemy1.World.Rot , g_Enemy1.World.Scl );


		for( int i = 0 ; i < ( int )g_nNumMatEnemy1 ; i++ )
		{
			//	デバイスにマテリアルを設定
			pDevice -> SetMaterial( &pMatEnemy1[ i ].MatD3D );

			//	テクスチャ設定
			pDevice -> SetTexture( 0 , g_pTextureEnemy1[ i ] );


			//	描画
			g_pMeshEnemy1 -> DrawSubset( i );

		}	//	end of for

	}	//	end of if

	pDevice -> SetMaterial( &matDef );

}	//	end of func

ENEMY *GetEnemy1( void )
{

	return &g_Enemy1;

}