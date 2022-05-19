#include "Stage.h"

/**
 * コンストラクタ
 *
 */
CStage::CStage():
m_BG(),
m_Scroll(0.0f){
}

/**
 * デストラクタ
 *
 */
CStage::~CStage(){
}

/**
 * 読み込み
 *
 */
bool CStage::Load(){
	return true;
}

/**
 * 初期化
 *
 */
void CStage::Initialize(){
}

/**
 * 更新
 *
 */
void CStage::Update(){
}

/**
 * 描画
 *
 */
void CStage::Render(){
}

/**
 * デバッグ文字描画
 *
 */
void CStage::RenderDebugText(){
	//スクロール値の描画
	CGraphicsUtilities::RenderString(10,10,MOF_XRGB(0,0,0),
		"スクロール : %.0f",m_Scroll);
}

/**
 * 解放
 *
 */
void CStage::Release(){
}
