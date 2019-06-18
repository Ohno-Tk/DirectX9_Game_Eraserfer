/*=============================================================================

		汚れ[ Born.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2016/01/05
-------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include <time.h>
#include <math.h>
#include "main.h"
#include "Born.h"
#include "Shadow.h"
#include "fade.h"
#include "MeshWall.h"
#include "Utility.h"
#include "Help.h"
#include "HelpNumber.h"

/*-----------------------------------------------------------------------------
	定数定義
-----------------------------------------------------------------------------*/
#define POLYGON00_TEXTURENAME "data/TEXTURE/GAME/汚れ.jpg"

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
HRESULT MakeVertexBorn( LPDIRECT3DDEVICE9 pDevice );

//	ターゲットのセット
void SetBorn( D3DXVECTOR3 Pos );

/*-----------------------------------------------------------------------------
	グローバル変数
-----------------------------------------------------------------------------*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBorn = NULL;	//	頂点バッファインタフェースへのポインタ

LPDIRECT3DTEXTURE9 g_pTextureBorn = NULL;//	テクスチャインターフェース

BORN g_Born[ MAX_BORN ];	//	敵構造体

/*-----------------------------------------------------------------------------
 関数名:	void InitTarget( void )
 引数:		
 戻り値:	
 説明:		初期化
-----------------------------------------------------------------------------*/
void InitBorn( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//	次のモードの取得
	MODE *Mode = GetNextMode();

	//	現在の時刻を取得
	srand((unsigned)time(NULL));


	//	エラーチェック
	if( FAILED( D3DXCreateTextureFromFile(  pDevice , POLYGON00_TEXTURENAME , &g_pTextureBorn  ) ) )
	{
		MessageBox( NULL , "ビルボードの読み込みができませんでした" , "警告" , MB_OK | MB_ICONHAND );

	}	//	end of if


	//	構造体初期化
	for( int Cnt = 0 ; Cnt < MAX_BORN ; Cnt++ )
	{

		//	座標
		g_Born[ Cnt ].World.Pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	拡大率
		g_Born[ Cnt ].World.Scl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//	回転量
		g_Born[ Cnt ].World.Rot = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );

		//	半径
		g_Born[ Cnt ].Radius = 25.0f;

		//	使用フラグ
		g_Born[ Cnt ].Use = false;

	}	//	end of for


	if( *Mode == MODE_GAME )
	{

		SetBorn( D3DXVECTOR3( 600.0f , 0.0f , 700.0f ) );

		SetBorn( D3DXVECTOR3( 500.0f , 0.0f , -200.0f ) );

		SetBorn( D3DXVECTOR3( -500.0f , 0.0f , 800.0f ) );

		SetBorn( D3DXVECTOR3( -400.0f , 0.0f , 60.0f ) );

		SetBorn( D3DXVECTOR3( 0.0f , 0.0f , 500.0f ) );

		SetBorn( D3DXVECTOR3( -500.0f , 0.0f , -800.0f ) );

		SetBorn( D3DXVECTOR3( 500.0f , 0.0f , -800.0f ) );

		SetBorn( D3DXVECTOR3( 300.0f , 0.0f , -60.0f ) );

		SetBorn( D3DXVECTOR3( -400.0f , 0.0f , -400.0f ) );

		SetBorn( D3DXVECTOR3( -50.0f , 0.0f , -80.0f ) );

		SetBorn( D3DXVECTOR3( 115.0f , 0.0f , -405.0f ) );
	
	}	//	end of if

	//	頂点の作成
	MakeVertexBorn( pDevice );

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void UninitTarget( void )
 引数:		
 戻り値:	
 説明:		終了
-----------------------------------------------------------------------------*/
void UninitBorn( void )
{

	if( g_pVtxBufferBorn != NULL )	//	頂点バッファインタフェース開放
	{
		g_pVtxBufferBorn -> Release();
		g_pVtxBufferBorn = NULL;

	}	//	end of if

	if( g_pTextureBorn != NULL )	//	テクスチャポリゴン開放
	{
		g_pTextureBorn -> Release();
		g_pTextureBorn = NULL;

	}	//	end of if


}	//	end of func
 
/*-----------------------------------------------------------------------------
 関数名:	void UpdataTarget( void )
 引数:		
 戻り値:	
 説明:		更新
-----------------------------------------------------------------------------*/
void UpdateBorn( void )
{

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	void DrawTarget( void )
 引数:		
 戻り値:	
 説明:		描画
-----------------------------------------------------------------------------*/
void DrawBorn( void )
{

	//	デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	//	パイプラインのストリーム
	pDevice -> SetStreamSource( 0 , g_pVtxBufferBorn , 0 , sizeof( VERTEX_3D ));


	//	頂点フォーマットの設定
	pDevice -> SetFVF( FVF_VERTEX_3D );


	//	テクスチャのセット
	pDevice -> SetTexture( 0 , g_pTextureBorn );


	//	αテスト
	pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );	//	αテストをONにする
	pDevice -> SetRenderState( D3DRS_ALPHAREF , 0 );			//	参照値の設定
	pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );	//	演算子を決める


	//	全体のライトを有効にする
	pDevice -> SetRenderState( D3DRS_LIGHTING , FALSE );


	for( int Cnt = 0 ; Cnt < MAX_BORN ; Cnt++ )
	{

		if( g_Born[ Cnt ].Use == true )
		{

			//	逆行列ありのワールド座標変換
			SetWorldInv( g_Born[ Cnt ].World.Pos , g_Born[ Cnt ].World.Scl );


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
 関数名:	void MakeVertexBorn( LPDIRECT3DDEVICE9 pDevice )
 引数:		LPDIRECT3DDEVICE9 pDevice
 戻り値:	なし
 説明:		頂点の作成
-----------------------------------------------------------------------------*/
HRESULT MakeVertexBorn( LPDIRECT3DDEVICE9 pDevice )
{
	VERTEX_3D* pVtx;	//	仮想アドレスを取得するポインタ変数


	//	頂点バッファの生成
	if( FAILED( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * NUM_VERTEX * MAX_BORN , D3DUSAGE_WRITEONLY , FVF_VERTEX_3D , D3DPOOL_MANAGED , &g_pVtxBufferBorn , NULL ) ) )
	{
		return E_FAIL;

	}	//	end of if

	//	バッファをロックし仮想アドレスを取得する
	g_pVtxBufferBorn -> Lock( 0 , 0 , (void**)&pVtx , 0 );

	for( int Cnt = 0 ; Cnt < MAX_BORN ; Cnt++ )
	{

		//	頂点座標の設定
		pVtx[ 0 ].pos = D3DXVECTOR3( -30.0f, 10.0f , 0.0f );
		pVtx[ 1 ].pos = D3DXVECTOR3( 30.0f , 10.0f , 0.0f );
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
	g_pVtxBufferBorn -> Unlock();


	return S_OK;

}	//	end of func


/*-----------------------------------------------------------------------------
 関数名:	void SetTarget( D3DXVECTOR3 Pos , D3DXVECTOR3 Move )
 引数:		D3DXVECTOR3 Pos		座標
			D3DXVECTOR3 Move	移動量
 戻り値:	
 説明:		ターゲットのセット
-----------------------------------------------------------------------------*/
void SetBorn( D3DXVECTOR3 Pos )
{

	for( int Cnt = 0 ; Cnt < MAX_BORN ; Cnt++ )
	{

		if( g_Born[ Cnt ].Use == false )
		{

			//	座標
			g_Born[ Cnt ].World.Pos = Pos;

			//	使用フラグ
			g_Born[ Cnt ].Use = true;

			SetHelp( D3DXVECTOR3( g_Born[ Cnt ].World.Pos.x , g_Born[ Cnt ].World.Pos.y + 40.0f , g_Born[ Cnt ].World.Pos.z ) );

			break;

		}	//	end of if
		
	}	//	end of for

}	//	end of func

/*-----------------------------------------------------------------------------
 関数名:	Born *GetBornNor( void )
 引数:		
 戻り値:	
 説明:		ターゲット情報の取得
-----------------------------------------------------------------------------*/
BORN *GetBorn( void )
{

	return &g_Born[ 0 ];

}	//	end of func