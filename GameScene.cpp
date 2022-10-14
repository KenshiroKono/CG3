#include "GameScene.h"
#include <cassert>
#include<random>

using namespace DirectX;

GameScene::GameScene() {
}

GameScene::~GameScene() {
	delete spriteBG;
	delete object3d;
	for (size_t i = 0; i < 50; i++) {
		delete kusa[i];
	}

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
	object3d = Object3d::Create();
	object3d->Update();

	//確認 ex
	
	 //乱数シード設定
	std::random_device speed_gen;
	//メルセンヌ・ツイスター
	std::mt19937_64 engine(speed_gen());
	//乱数範囲(座標用)
	std::uniform_real_distribution<float> posDist(-20.0f, 20.0f);
	//乱数エンジンを渡し、指定範囲からランダムで数値を得る
	float posValue = posDist(engine);
	XMFLOAT3 ranPos;
	
	for (int  i = 0; i < 50; i++) {
		kusa[i] = nullptr;
		kusa[i] = Object3d::Create();
		ranPos.x =  posDist(engine) ;
		ranPos.y =  0.0 ;
		ranPos.z =  posDist(engine) ;
		kusa[i]->SetPosition(ranPos);
		kusa[i]-> Update();
	}
}

void GameScene::Update() {
	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT)) {
		// 現在の座標を取得
		XMFLOAT3 position = object3d->GetPosition();
		

		// 移動後の座標を計算
		if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
		else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
		if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
		else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }

		// 座標の変更を反映
		object3d->SetPosition(position);
	}

	// カメラ移動
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A)) {
		if (input->PushKey(DIK_W)) { Object3d::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_S)) { Object3d::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_D)) { Object3d::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { Object3d::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
	}

	if (input->PushKey(DIK_1)) {
		object3d->isBillboard = 1;
		object3d->isYBillboard = 0;
	}
	else if (input->PushKey(DIK_2)) {
		object3d->isYBillboard = 1;
		object3d->isBillboard = 0;
	}
	else {
		object3d->isBillboard = 0;
		object3d->isYBillboard = 0;
	}

	object3d->Update();
	for (size_t i = 0; i < 50; i++) {
		if (input->PushKey(DIK_1)) {
			kusa[i]->isBillboard = 1;
			kusa[i]->isYBillboard = 0;
		}
		else if (input->PushKey(DIK_2)) {
			kusa[i]->isYBillboard = 1;
			kusa[i]->isBillboard = 0;
		}
		else {
			kusa[i]->isBillboard = 0;
			kusa[i]->isYBillboard = 0;
		}
		kusa[i]->Update();
	}
}

void GameScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//spriteBG->Draw();

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
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	//object3d->Draw();

	for (size_t i = 0; i < 50; i++) {
		kusa[i]->Draw();
	}
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
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
