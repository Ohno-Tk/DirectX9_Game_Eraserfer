/*=============================================================================

		ビルボード[ Help.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2016/11/16
-------------------------------------------------------------------------------
	■　Update
		2016/11/16
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "main.h"
#include "Help.h"

/*-----------------------------------------------------------------------------
	定数定義
-----------------------------------------------------------------------------*/
#define BIILLBOARD_TEXTURENAME "data/TEXTURE/GAME/矢印.png"

/*-----------------------------------------------------------------------------
	プロトタイプ宣言
-----------------------------------------------------------------------------*/
HRESULT MakeVertexHelp( LPDIRECT3DDEVICE9 pDevice );	//	頂点の作成

/*-----------------------------------------------------------------------------
	構造体
-----------------------------------------------------------------------------*/
typedef struct
{
	WORLD World;	//	ワールド変換用変数
	D3DXVECTOR2 Pos;	
	bool Use;	//	使用フラグ

}HELP;

/*-----------------------------------------------------------------------------
	グローバル変数
-----------------------------------------------------------------------------*/

LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferHelp = NULL;	//	頂点バッファインタフェースへのポインタ

LPDIRECT3DTEXTURE9 g_pTextureHelp = NULL;//	テクスチャインターフェース

HELP g_Help[ MAX_HELP ];

/*-----------------------------------------------------------------------------
 関数名:	HRESULT InitHelp( void )
 引数:		なし
 戻り値:	なし
 説明:		初期化
-----------------------------------------------------------------------------*/
void InitHelp( void )
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	エラーチェック
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , BIILLBOARD_TEXTURENAME , &g_pTextureHelp  ) ) )
	{
		MessageBox( NULL , "ビルボードの読み込みができませんでした" , "警告" , MB_OK | MB_ICONHAND );

	}	//	end of if

	//	構造体初期化
	for( int Cnt = 0 ; Cnt < MAX_HELP ; Cnt++ )
	{

		//	座標
		g_Help[ Cnt ].World.Pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	回転量
		g_Help[ Cnt ].World.Rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	拡大率
		g_Help[ Cnt ].World.Scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//	使用フラグ
		g_Help[ Cnt ].Use = false;

	}


	//	頂点の作成
	MakeVertexHelp( pDevice );

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UninitHelp( void )
 引数:		なし
 戻り値:	なし
 説明:		終了
-----------------------------------------------------------------------------*/
void UninitHelp( void )
{
	if( g_pVtxBufferHelp != NULL )	//	頂点バッファインタフェース開放
	{
		g_pVtxBufferHelp -> Release();
		g_pVtxBufferHelp = NULL;

	}	//	end of if

	if( g_pTextureHelp != NULL )	//	テクスチャポリゴン開放
	{
		g_pTextureHelp -> Release();
		g_pTextureHelp = NULL;

	}	//	end of if

}	//	end of func
 
/*-----------------------------------------------------------------------------
 関数名:	void UpdataHelp( void )
 引数:		なし
 戻り値:	なし
 説明:		更新
-----------------------------------------------------------------------------*/
void UpdateHelp( void )
{

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void DrawHelp( void )
 引数:		なし
 戻り値:	なし
 説明:		描画
-----------------------------------------------------------------------------*/
void DrawHelp( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	パイプラインのストリーム
	pDevice -> SetStreamSource( 0 , g_pVtxBufferHelp , 0 , sizeof( VERTEX_3D ));


	//	頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_3D );


	//	テクスチャのセット
	pDevice -> SetTexture( 0 , g_pTextureHelp );


	//	αテスト
	pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );	//	αテストをONにする
	pDevice -> SetRenderState( D3DRS_ALPHAREF , 0 );			//	参照値の設定
	pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );	//	演算子を決める


	//	全体のライトを有効にする
	pDevice -> SetRenderState( D3DRS_LIGHTING , FALSE );


	for( int Cnt = 0 ; Cnt < MAX_HELP ; Cnt++ )
	{

		if( g_Help[ Cnt ].Use == true )
		{

			//	逆行列ありのワールド座標変換
			SetWorldInv( g_Help[ Cnt ].World.Pos , g_Help[ Cnt ].World.Scl );


			//	ポリゴンの描画
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , Cnt * NUM_VERTEX , NUM_POLYGON );

		}	//	end of if

	}


	//	全体のライトを有効にする
	pDevice -> SetRenderState( D3DRS_LIGHTING , TRUE );


	//	元に戻す
	pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , FALSE );	//	αテストをOFFにする


}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void MakeVertexHelp( LPDIRECT3DDEVICE9 pDevice )
 引数:		LPDIRECT3DDEVICE9 pDevice
 戻り値:	なし
 説明:		頂点の作成
-----------------------------------------------------------------------------*/
HRESULT MakeVertexHelp( LPDIRECT3DDEVICE9 pDevice )
{
	VERTEX_3D* pVtx;	//	仮想アドレスを取得するポインタ変数


	//	頂点バッファの生成
	if( FAILED( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * NUM_VERTEX * MAX_HELP , D3DUSAGE_WRITEONLY , FVF_VERTEX_3D , D3DPOOL_MANAGED , &g_pVtxBufferHelp , NULL ) ) )
	{
		return E_FAIL;

	}	//	end of if

	//	バッファをロックし仮想アドレスを取得する
	g_pVtxBufferHelp -> Lock( 0 , 0 , (void**)&pVtx , 0 );

	for( int Cnt = 0 ; Cnt < MAX_HELP ; Cnt++ )
	{

		//	頂点座標の設定
		pVtx[ 0 ].pos = D3DXVECTOR3( -30.0f, 15.0f , 0.0f );
		pVtx[ 1 ].pos = D3DXVECTOR3( 30.0f , 15.0f , 0.0f );
		pVtx[ 2 ].pos = D3DXVECTOR3( -30.0f, 0.0f , 0.0f );
		pVtx[ 3 ].pos = D3DXVECTOR3( 30.0f , 0.0f , 0.0f );


		//	法線の設定
		pVtx[ 0 ].normal = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[ 1 ].normal = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[ 2 ].normal = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[ 3 ].normal = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );


		//	頂点色の設定
		pVtx[ 0 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[ 1 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[ 2 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[ 3 ].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );


		//	テクスチャ座標の設定
		pVtx[ 0 ].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[ 1 ].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[ 2 ].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[ 3 ].tex = D3DXVECTOR2( 1 , 1 );

		pVtx += 4;

	}


	//	バッファのアンロック
	g_pVtxBufferHelp -> Unlock();


	return S_OK;

}	//	end of func

void SetHelp( D3DXVECTOR3 Pos )
{

	for( int Cnt = 0 ; Cnt < MAX_HELP ; Cnt++ )
	{

		if( g_Help[ Cnt ].Use == false )
		{

			g_Help[ Cnt ].World.Pos = Pos;


			g_Help[ Cnt ].Use = true;

			break;

		}

	}

}

void SetOff( int Index )
{

	g_Help[ Index ].Use = false;

}