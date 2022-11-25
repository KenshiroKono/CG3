#include "GameScene.h"
#include <cassert>
#include<random>

using namespace DirectX;

GameScene::GameScene() {
}

GameScene::~GameScene() {
	delete spriteBG;
	delete particleMan;
	/*for (size_t i = 0; i < 50; i++) {
		delete kusa[i];
	}*/

}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/background.png");

	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成
	particleMan = ParticleManager::Create();
	particleMan->Update();


	for (int i = 0; i < 100; i++) {

		//座標
		//xyz全て[+-5.0f]幅にランダムに分布
		const float rnd_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		//速度
		//xyz全て[+-0.05f]幅にランダムに分布
		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//重力に見立ててYのみ[-0.001f,0]でランダム分布
		XMFLOAT3 acc{};
		const float rnd_acc = 0.001f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		//追加
		particleMan->Add(60*2, pos, vel,acc,1.0f,0.0f);

	}

	//確認 ex

	// //乱数シード設定
	//std::random_device speed_gen;
	////メルセンヌ・ツイスター
	//std::mt19937_64 engine(speed_gen());
	////乱数範囲(座標用)
	//std::uniform_real_distribution<float> posDist(-20.0f, 20.0f);
	////乱数エンジンを渡し、指定範囲からランダムで数値を得る
	//float posValue = posDist(engine);
	//XMFLOAT3 ranPos;
	/*
	for (int  i = 0; i < 50; i++) {
		kusa[i] = nullptr;
		kusa[i] = Object3d::Create();
		ranPos.x =  posDist(engine) ;
		ranPos.y =  0.0 ;
		ranPos.z =  posDist(engine) ;
		kusa[i]->SetPosition(ranPos);
		kusa[i]-> Update();
	}*/


}

void GameScene::Update() {
	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT)) {

		// 移動後の座標を計算
		/*if (input->PushKey(DIK_UP)) { position.y += 0.1f; }
		else if (input->PushKey(DIK_DOWN)) { position.y -= 0.1f; }
		if (input->PushKey(DIK_RIGHT)) { position.x += 0.1f; }
		else if (input->PushKey(DIK_LEFT)) { position.x -= 0.1f; }*/


	}

	// カメラ移動
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A)) {
		if (input->PushKey(DIK_W)) { ParticleManager::CameraMoveEyeVector({ 0.0f,+0.1f,0.0f }); }
		else if (input->PushKey(DIK_S)) { ParticleManager::CameraMoveEyeVector({ 0.0f,-0.1f,0.0f }); }
		if (input->PushKey(DIK_D)) { ParticleManager::CameraMoveEyeVector({ +0.1f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { ParticleManager::CameraMoveEyeVector({ -0.1f,0.0f,0.0f }); }
	}


	if (input->PushKey(DIK_1)) {
		particleMan->isBillboard = 0;
		//particleMan->isYBillboard = 0;
	}

	else {
		particleMan->isBillboard = 1;
		//particleMan->isYBillboard = 0;
	}

	for (int i = 0; i < 10; i++) {

		//座標
		//xyz全て[+-5.0f]幅にランダムに分布
		const float rnd_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		//速度
		//xyz全て[+-0.05f]幅にランダムに分布
		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//重力に見立ててYのみ[-0.001f,0]でランダム分布
		XMFLOAT3 acc{};
		const float rnd_acc = 0.001f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		//追加
		particleMan->Add(60 * 2, pos, vel, acc, 1.0f, 0.0f);

	}

	particleMan->Update();

}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	ParticleManager::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	particleMan->Draw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	ParticleManager::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
