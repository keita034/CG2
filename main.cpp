//#DirectXのやつ
#include"ErrorException.h"


//自作.h
#include "WindowsApp.h"
#include "Input.h"
#include"Controller.h"
#include"DirectX12Core.h"
#include"Mesh.h"
#include"Camera.h"
#include"GameScene.h"
#include"FPS.h"
#include"ModelPipeLine.h"
//pragma comment


//using namespace


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{

	WindowsApp* windowsApp = WindowsApp::GetInstance();//WindowsAppクラス読み込み
	windowsApp->CreatWindow();//ウィンドウ生成

	//DirectX初期化処理ここから

	DirectX12Core* DirectX12Core = DirectX12Core::GetInstance();//DirectX12Coreクラス読み込み
	DirectX12Core->DirectXInitialize();//DirectX12初期化
	DirectX12Core->SetBackScreenColor(0.1f, 0.25f, 0.5f, 0.0f);	//背景の色変更(R,G,B,A)

	//DirectX初期化処理ここまで

	//描画初期化処理ここから
	Mesh* mesh = Mesh::GetInstance();

	ModelPipeLine* pipeline = ModelPipeLine::GetInstance();
	pipeline->Initialize();
	//描画初期化処理ここまで

	Input* input = Input::GetInstance();
	input->Initialize();

	GameScene* gameScene = new GameScene;
	gameScene->Initialize();

	FPS* fps = new FPS;

	//ゲームループ
	while (true)
	{
		fps->FpsControlBegin();

		if (!windowsApp->MessageWindow())//メッセージ処理
		{
			break;
		}

		//準備処理
		DirectX12Core->BeginDraw();//描画準備

		//DirectX毎フレーム処理　ここから

		//更新処理
		mesh->DrawReset();
		input->Update();

		gameScene->Update();

		//描画処理

		gameScene->Draw();

		//DirectX毎フレーム処理　ここまで

		DirectX12Core->EndDraw();//描画後処理

		if (input->TriggerPush(DIK_ESCAPE))
		{
			break;
		}

		fps->FpsControlEnd();
	}

	windowsApp->Break();
	DirectX12Core->Destroy();
	pipeline->Destroy();
	mesh->Destroy();
	delete gameScene;
	delete fps;

	return 0;
}