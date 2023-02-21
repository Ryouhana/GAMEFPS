#include "../gm_manager.h"
#include "gm_scene_result.h"
#include "gm_scene_title.h"


void SceneResult::initialzie() {
	
	HelpImage = LoadGraph("graphics/help.jpg");
	ModelHandle = MV1LoadModel("zombietaro/zombie.pmx");
	//3Dモデルの読み込み
	
	testModel = MV1LoadModel("MEUPistol/MEUPistol.pmd");
	
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




	if (tnl::Input::IsKeyDown(eKeys::KB_W)) {
		testpos_.y -= 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_S)) {
		testpos_.y += 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_A)) {
		testpos_.x -= 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_D)) {
		testpos_.x += 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_Q)) {
		testpos_.z -= 0.1f;
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_E)) {
		testpos_.z += 0.1f;
	}

	if (tnl::Input::IsKeyDown(eKeys::KB_Z)) {
		testrot_ *= tnl::Quaternion::RotationAxis({ 1,0,0 }, tnl::ToRadian(5));
	}
	else if (tnl::Input::IsKeyDown(eKeys::KB_X)) {
		testrot_ *= tnl::Quaternion::RotationAxis({ 0,1,0 },tnl::ToRadian(5));
	}

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
	
	MATRIX view, proj;
	memcpy(view.m, result_Camera->view_.m, sizeof(float) * 16);
	memcpy(proj.m, result_Camera->proj_.m, sizeof(float) * 16);
	SetCameraViewMatrix(view);
	SetupCamera_ProjectionMatrix(proj);
	DxLib::VECTOR vp;
	vp = VGet(testpos_.x, testpos_.y, testpos_.z);
	//rot_(tnl::Quaternion型)をMATRIX型に変換
	MATRIX rot;
	memcpy(rot.m, testrot_.getMatrix().m, sizeof(float) * 16);
	MV1SetRotationMatrix(testModel, rot);
	MV1SetScale(testModel, { 1.0f,1.0f,1.0f });
	MV1SetPosition(testModel, vp);
	DxLib::VECTOR vpzombi;
	vpzombi = VGet(pos_zombi.x, pos_zombi.y, pos_zombi.z);
	//rot_(tnl::Quaternion型)をMATRIX型に変換
	MATRIX rotzombi;
	memcpy(rotzombi.m, rot_zombi.getMatrix().m, sizeof(float) * 16);
	MV1SetRotationMatrix(ModelHandle, rotzombi);
	MV1SetScale(ModelHandle, { 4.0f,4.0f,4.0f });
	MV1SetPosition(ModelHandle, vpzombi);
	MV1DrawModel(testModel);
	
	MV1DrawModel(ModelHandle);
	MV1GetDifColorScale(testModel);
	MV1GetSpcColorScale(testModel);
	MV1GetEmiColorScale(testModel);
	MV1GetAmbColorScale(testModel);
	DrawStringEx(100, 100, -1, "%f %f %f %f", MV1GetDifColorScale(testModel).r, MV1GetDifColorScale(testModel).g, MV1GetDifColorScale(testModel).b, MV1GetDifColorScale(testModel).a);
	DrawStringEx(100, 200, -1, "%f %f %f %f", MV1GetSpcColorScale(testModel).r, MV1GetSpcColorScale(testModel).g, MV1GetSpcColorScale(testModel).b, MV1GetSpcColorScale(testModel).a);
	DrawStringEx(100, 300, -1, "%f %f %f %f", MV1GetEmiColorScale(testModel).r, MV1GetEmiColorScale(testModel).g, MV1GetEmiColorScale(testModel).b, MV1GetEmiColorScale(testModel).a);
	DrawStringEx(100, 400, -1, "%f %f %f %f", MV1GetAmbColorScale(testModel).r, MV1GetAmbColorScale(testModel).g, MV1GetAmbColorScale(testModel).b, MV1GetAmbColorScale(testModel).a);

	/*ModelHandle->render(result_Camera);*/
	

	

	
	/*DrawRotaGraph(520, 410, 0.9, 0, HelpImage,true);
	DrawStringEx(440, 50, -1, "操作方法");*/
}
