/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"Player.h"
#include	"Stage.h"


//カメラ
CCamera			gCamera;
//ライト
CDirectionalLight	gLight;
//プレイヤー
CPlayer			gPlayer;
//ステージ
CStage			gStage;
//デバックの表示フラグ
bool			gbDebug = false;
/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");

	//カメラ初期化
	gCamera.SetViewPort();
	gCamera.LookAt(Vector3(0, 6.0f, -17.0f), Vector3(0, 0, -10), Vector3(0, 1, 0));
	gCamera.PerspectiveFov(MOF_ToRadian(60.0f), 1024.0f / 768.0f,0.01f, 1000.0f);
	CGraphicsUtilities::SetCamera(&gCamera);

	//ライト初期化
	gLight.SetDirection(Vector3(-1, -2, 1.5f));
	gLight.SetDiffuse(MOF_COLOR_WHITE);
	gLight.SetAmbient(MOF_COLOR_WHITE);
	gLight.SetSpeculer(MOF_COLOR_WHITE);
	CGraphicsUtilities::SetDirectionalLight(&gLight);

	//プレイヤーの素材読み込み
	gPlayer.Load();
	//ステージ素材読み込み
	gStage.Load();
	//プレイヤーの状態初期化
	gPlayer.Initialize();
	//ステージの状態初期化
	gStage.Initialize();
	
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//キーの更新
	g_pInput->RefreshKey();
	//プレイヤーの更新
	gPlayer.Update();
	//ステージの更新
	gStage.Update();
	//デバック表示の切り替え
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		gbDebug = ((gbDebug) ? false : true);
	}
	//プレイヤーに合わせてカメラを動かす
	float posX = gPlayer.GetPosition().x * 0.4f;
	CVector3 cPos = gCamera.GetViewPosition();
	CVector3 tPos = gCamera.GetTargetPosition();
	CVector3 vup = CVector3(0, 1, 0);
	cPos.x = posX;
	tPos.x = posX;
	vup.RotationZ(gPlayer.GetPosition().x / FIELD_HALF_X * MOF_ToRadian(10.0f));
	gCamera.LookAt(cPos, tPos, vup);
	gCamera.Update();
	return TRUE;
}

/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//描画処理
	g_pGraphics->RenderStart();
	// 画面のクリア
	g_pGraphics->ClearTarget(0.65f,0.65f,0.67f,0.0f,1.0f,0);

	//深度バッファ有効化
	g_pGraphics->SetDepthEnable(TRUE);

	//プレイヤー描画
	gPlayer.Render();
	//ステージ描画
	gStage.Render();
	//3Dデバック描画
	if (gbDebug)
	{
		//移動可能範囲の表示
		CMatrix44 matWorld;
		matWorld.Scaling(FIELD_HALF_X * 2, 1, FIELD_HALF_Z * 2);
		CGraphicsUtilities::RenderPlane(matWorld, Vector4(1, 1, 1, 0.4f));
	}

	//深度バッファ無効化
	g_pGraphics->SetDepthEnable(FALSE);

	//２Dデバック描画
	if (gbDebug)
	{
		//プレイヤーのデバック文字描画
		gPlayer.RenderDebugText();
		//ステージのデバック文字描画
		gStage.RenderDebugText();
	}

	// 描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void){
	gPlayer.Release();
	gStage.Release();
	return TRUE;
}