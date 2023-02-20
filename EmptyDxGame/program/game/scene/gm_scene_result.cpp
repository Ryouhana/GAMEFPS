#include "../gm_manager.h"
#include "gm_scene_result.h"
#include "gm_scene_title.h"


void SceneResult::initialzie() {
	
	HelpImage = LoadGraph("graphics/help.jpg");

	//3Dモデルの読み込み
	
	
	
	// 再生時間の初期化
	PlayTime = 0.0f;
	// ３Ｄモデルの1番目のアニメーションをアタッチする
	//>>>>>AttachIndex = MV1AttachAnim(ModelHandle, 4, -1);
	result_Camera = new GmCamera();
	result_Camera->pos_ = { 0,50,-100 };
}

void SceneResult::update(float delta_time)
{
	GameManager* mgr = GameManager::GetInstance();
	

	// Update the camera
	
	

	//pos_(tnl::Vector3型)をDxLib_VECTOR型に変換
	
	/*DxLib::VECTOR cp;
	cp = VGet(result_Camera->pos_.x, result_Camera->pos_.y, result_Camera->pos_.z);
	cp = {pos_.x,pos_.y,pos_.z};*/
	////奥行0.1～1000までをカメラの描画範囲とする
	//SetCameraNearFar(0.1f, 1000.0f);

	////(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
	//SetCameraPositionAndTarget_UpVecY(VGet(0, 10, -20), VGet(0.0f, 10.0f, 0.0f));



	// アタッチしたアニメーションの総再生時間を取得する
	//>>>>>TotalTime = MV1GetAttachAnimTotalTime(ModelHandle, AttachIndex);




	//if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
	//	pos_.y -= 0.1f;
	//}
	//else if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
	//	pos_.y += 0.1f;
	//}
	//else if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
	//	pos_.x -= 0.1f;
	//}
	//else if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
	//	pos_.x += 0.1f;
	//}
	//else if (tnl::Input::IsKeyDown(eKeys::KB_Q)) {
	//	pos_.z -= 0.1f;
	//}
	//else if (tnl::Input::IsKeyDown(eKeys::KB_E)) {
	//	pos_.z += 0.1f;
	//}

	//if (tnl::Input::IsKeyDown(eKeys::KB_Z)) {
	//	rot_ *= tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(5));
	//}
	//else if (tnl::Input::IsKeyDown(eKeys::KB_X)) {
	//	rot_ *= tnl::Quaternion::RotationAxis({ 0,1,0 },tnl::ToRadian(5));
	//}

	// 再生時間を進める
	PlayTime += 1;

	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		PlayTime = 0.0f;
	}

	// 再生時間をセットする
	//>>>>>>MV1SetAttachAnimTime(ModelHandle, AttachIndex, PlayTime);
	//第二引数の回転角度をセット
	

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		mgr->chengeScene(new SceneTitle());
	}
}

void SceneResult::render()
{

	result_Camera->update();
	

	/*ModelHandle->render(result_Camera);*/
	

	

	
	/*DrawRotaGraph(520, 410, 0.9, 0, HelpImage,true);
	DrawStringEx(440, 50, -1, "操作方法");*/
}
