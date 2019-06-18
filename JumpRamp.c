/*=============================================================================

		ジャンプ台[ JumpRamp.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/02/15
-------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "main.h"
#include "JumpRamp.h"

/*-----------------------------------------------------------------------------
	定数定義
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/坂.jpg"

/*-----------------------------------------------------------------------------
	列挙
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	構造体
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	プロトタイプ宣言
-----------------------------------------------------------------------------*/

//	頂点の作成
HRESULT MakeVertexJumpRamp( LPDIRECT3DDEVICE9 pDevice );

//	ジャンプ台のセット
void SetJumpRamp( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot );

/*-----------------------------------------------------------------------------
	グローバル変数
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferJumpRamp = NULL;	//	頂点バッファインタフェースへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureJumpRamp = NULL;//	テクスチャインターフェース

JUMPRAMP g_JumpRamp[ MAX_JUMPRAMP ];	//	構造体

/*-----------------------------------------------------------------------------
 関数名:	void InitJumpRamp( void )
 引数:		
 戻り値:	
 説明:		初期化
-----------------------------------------------------------------------------*/
void InitJumpRamp( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	テクスチャのエラーチェック
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureJumpRamp ) ) )
	{

		MessageBox( NULL , "[ JumpRamp.cpp ]\n POLYGON00_TEXTURENAME\nの読み込みができませんでした" , "警告" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	頂点の作成
	MakeVertexJumpRamp( pDevice );


	//	構造体初期化
	for( int Cnt = 0 ; Cnt < MAX_JUMPRAMP ; Cnt++ )
	{

		g_JumpRamp[ Cnt ].World.Pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_JumpRamp[ Cnt ].World.Rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_JumpRamp[ Cnt ].World.Scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		g_JumpRamp[ Cnt ].Use = false;

	}	//	end of for


	SetJumpRamp( D3DXVECTOR3( 0.0f , 0.0f , 0.0f ) , D3DXVECTOR3( 60.0f , 0.0f , 0.0f ) );

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UninitJumpRamp( void )
 引数:		
 戻り値:	
 説明:		終了
-----------------------------------------------------------------------------*/
void UninitJumpRamp( void )
{

	if(g_pVtxBufferJumpRamp != NULL)	//頂点バッファのインターフェースポインタの解放
	{

		g_pVtxBufferJumpRamp -> Release();
		g_pVtxBufferJumpRamp  = NULL;

	}	//	end of if



	if( g_pTextureJumpRamp != NULL )	//	テクスチャポリゴン開放
	{

		g_pTextureJumpRamp -> Release();
		g_pTextureJumpRamp = NULL;

	}	//	end of if

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UpdateJumpRamp( void )
 引数:		
 戻り値:	
 説明:		更新
-----------------------------------------------------------------------------*/
void UpdateJumpRamp( void )
{
}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void DrawJumpRamp( void )
 引数:		
 戻り値:	
 説明:		描画
-----------------------------------------------------------------------------*/
void DrawJumpRamp( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	パイプラインのストリーム
	pDevice -> SetStreamSource( 0 , g_pVtxBufferJumpRamp , 0 , sizeof( VERTEX_3D ));


	//	頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_3D );


	//	テクスチャのセット
	pDevice -> SetTexture( 0 , g_pTextureJumpRamp );


	for( int Cnt = 0 ; Cnt < MAX_JUMPRAMP ; Cnt++ )
	{

		if( g_JumpRamp[ Cnt ].Use == true )
		{

			//	逆行列なしのワールド座標変換
			SetWorld( g_JumpRamp[ Cnt ].World.Pos , g_JumpRamp[ Cnt ].World.Rot , g_JumpRamp[ Cnt ].World.Scl );


			//	ポリゴンの描画
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , Cnt * NUM_VERTEX , NUM_POLYGON );

		}	//	end of if

	}


}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	HRESULT MakeVertexJumpRamp( LPDIRECT3DDEVICE9 pDevice )
 引数:		LPDIRECT3DDEVICE9 pDevice	デバイス
 戻り値:	良い場合	return S_OK;
			ダメな場合	return E_FAIL;
 説明:		頂点の作成
-----------------------------------------------------------------------------*/
HRESULT MakeVertexJumpRamp( LPDIRECT3DDEVICE9 pDevice )
{

		VERTEX_3D* pVtx;	//	仮想アドレスを取得するポインタ変数


	//	頂点バッファの生成
	if( FAILED( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * NUM_VERTEX * MAX_JUMPRAMP , D3DUSAGE_WRITEONLY , FVF_VERTEX_3D , D3DPOOL_MANAGED , &g_pVtxBufferJumpRamp , NULL ) ) )
	{
		return E_FAIL;

	}	//	end of if

	//	バッファをロックし仮想アドレスを取得する
	g_pVtxBufferJumpRamp -> Lock( 0 , 0 , (void**)&pVtx , 0 );


	for( int Cnt = 0 ; Cnt < MAX_JUMPRAMP ; Cnt++ )
	{

		//	頂点座標の設定
		pVtx[ 0 ].pos = D3DXVECTOR3( -20.0f, 30.0f , 0.0f );
		pVtx[ 1 ].pos = D3DXVECTOR3(  20.0f, 30.0f , 0.0f );
		pVtx[ 2 ].pos = D3DXVECTOR3( -20.0f, 0.0f , 0.0f );
		pVtx[ 3 ].pos = D3DXVECTOR3(  20.0f, 0.0f , 0.0f );


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

	}	//	end of for


	//	バッファのアンロック
	g_pVtxBufferJumpRamp -> Unlock();


	return S_OK;

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void SetJumpRamp( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot )
 引数:		
 戻り値:	
 説明:		ジャンプ台のセット
-----------------------------------------------------------------------------*/
void SetJumpRamp( D3DXVECTOR3 Pos , D3DXVECTOR3 Rot )
{

	for( int Cnt = 0 ; Cnt < MAX_JUMPRAMP ; Cnt++ )
	{

		if( g_JumpRamp[ Cnt ].Use == false )
		{

			g_JumpRamp[ Cnt ].World.Pos = Pos;
			g_JumpRamp[ Cnt ].World.Rot = Rot;

			g_JumpRamp[ Cnt ].Use = true;

			break;

		}	//	end of if

	}	//	end of for

}	//	end of func