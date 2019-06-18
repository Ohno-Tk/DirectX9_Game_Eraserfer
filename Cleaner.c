/*=============================================================================

		黒板消しクリーナー[ Cleaner.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/02/23
-------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "Cleaner.h"

/*-----------------------------------------------------------------------------
	定数定義
-----------------------------------------------------------------------------*/
#define MODEL_NAME "data/MODEL/黒板消しクリーナー.x"

#define MAX_MAT ( 3 )	//	モデルの最大マテリアル数

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
LPD3DXMESH g_pMeshCleaner;	//	メッシュインターフェースポインタ

LPD3DXBUFFER g_pBufferMatCleaner;	//	マテリアル情報

DWORD g_nNumMatCleaner;	//	マテリアル数

LPDIRECT3DTEXTURE9 g_pTextureCleaner[ MAX_MAT ] = { NULL };//	テクスチャインターフェース

D3DXMATERIAL* pMatCleaner;	//	マテリアルポインタ

CLEANER g_Cleaner;	//	構造体

/*-----------------------------------------------------------------------------
 関数名:	void InitCleaner( void )
 引数:		
 戻り値:	
 説明:		初期化
-----------------------------------------------------------------------------*/
void InitCleaner( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	HRESULT hr;

	hr = D3DXLoadMeshFromX( MODEL_NAME ,			//	ファイル名
							D3DXMESH_MANAGED,
							pDevice,				//	デバイス
							NULL,					//	隣接バッファ
							&g_pBufferMatCleaner,		//	マテリアル情報を格納
							NULL,
							&g_nNumMatCleaner,		//	マテリアル数
							&g_pMeshCleaner );		//	メッシュ

	//	モデルのエラーチェック
	if( FAILED( hr ) )
	{

		MessageBox( NULL , "[ Cleaner.cpp ]\n MODEL_NAME\nの読み込みができませんでした" , "警告" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	マテリアル情報のポインタとしてバッファのアドレスを取得
	pMatCleaner = ( D3DXMATERIAL* )g_pBufferMatCleaner -> GetBufferPointer();

	for( int i = 0 ; i < ( int )g_nNumMatCleaner ; i++ )
	{
		if( pMatCleaner[ i ].pTextureFilename != NULL )
		{

			//	テクスチャのエラーチェック
			if( FAILED( D3DXCreateTextureFromFile( pDevice , pMatCleaner[ i ].pTextureFilename , &g_pTextureCleaner[ i ]  ) ) )
			{
				MessageBox( NULL , "モデルの画像の読み込みができませんでした" , "警告" , MB_OK | MB_ICONHAND );

			}	//	end of if

		}	//	end of if

	}	//	end of for


	//	構造体初期化
	g_Cleaner.World.Pos = D3DXVECTOR3( 780.0f , 50.0f , -860.0f );
	g_Cleaner.World.Rot = D3DXVECTOR3( 270.0f , 0.0f , 180.0f );
	g_Cleaner.World.Scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
	g_Cleaner.Radius = 120.0f;

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UninitCleaner( void )
 引数:		
 戻り値:	
 説明:		終了
-----------------------------------------------------------------------------*/
void UninitCleaner( void )
{

	if( g_pMeshCleaner != NULL )	//	メッシュインターフェースポインタ
	{

		g_pMeshCleaner -> Release();
		g_pMeshCleaner = NULL;

	}	//	end of if

	if( g_pBufferMatCleaner != NULL )	//	マテリアル情報開放
	{

		g_pBufferMatCleaner -> Release();
		g_pBufferMatCleaner = NULL;

	}	//	end of if

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UpdataCleaner( void )
 引数:		
 戻り値:	
 説明:		更新
-----------------------------------------------------------------------------*/
void UpdateCleaner( void )
{
}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void DrawCleaner( void )
 引数:		
 戻り値:	
 説明:		描画
-----------------------------------------------------------------------------*/
void DrawCleaner( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	現在デバイスに設定されているマテリアル情報の取得
	D3DMATERIAL9 matDef;
	pDevice -> GetMaterial( &matDef );



	//	逆行列なしのワールド座標変換
	SetWorld( g_Cleaner.World.Pos , g_Cleaner.World.Rot , g_Cleaner.World.Scl );


	for( int i = 0 ; i < ( int )g_nNumMatCleaner ; i++ )
	{
		//	デバイスにマテリアルを設定
		pDevice -> SetMaterial( &pMatCleaner[ i ].MatD3D );

		//	テクスチャ設定
		pDevice -> SetTexture( 0 , g_pTextureCleaner[ i ] );


		//	描画
		g_pMeshCleaner -> DrawSubset( i );

	}	//	end of for


	pDevice -> SetMaterial( &matDef );

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	CLEANER *GetCleaner( void )
 引数:		
 戻り値:	return &g_Cleaner;
 説明:		黒板消しクリーナー情報の取得
-----------------------------------------------------------------------------*/
CLEANER *GetCleaner( void )
{

	return &g_Cleaner;

}	//	end of func