//#DirectXのやつ
#include"ErrorException.h"


//自作.h
#include "WindowsApp.h"
#include "Input.h"
#include"DirectX12Core.h"
#include"Mesh.h"
#include"Sprite2D.h"
#include"Sprite3D.h"
#include"Camera.h"
#include"Model.h"

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
	Mesh* mesh = new Mesh();

	Camera* camera = new Camera();
	camera->Initialize(UpdateProjMatrixFunc_Perspective);
	Model* model = new Model();
	model->Create(Cube);
	model->SetTexture(L"Resources/mario.jpg");

	//描画初期化処理ここまで
	Input* input = new Input();
	input->Initialize();
	float angle = 0.0f;
	camera->SetPosition(-10.0f * sinf(angle), 0.0f, -10.0f * cosf(angle));
	//ゲームループ
	while (true)
	{

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

		if (input->KeepPush(DIK_D)||input->KeepPush(DIK_A))
		{
			if (input->KeepPush(DIK_D))
			{
				angle += MyMath::ChangeRadians(1.0f);
			}

			if (input->KeepPush(DIK_A))
			{
				angle -= MyMath::ChangeRadians(1.0f);
			}
			
			camera->SetPosition(-10.0f*sinf(angle),0.0f, -10.0f * cosf(angle));
		}


		model->Update(MyMath::Vector3(0, 0, 0), MyMath::Vector3(0, 0, 0), MyMath::Vector3(1.0f, 1.0f, 1));
		model->Draw(camera);
		//描画処理
		
		//DirectX毎フレーム処理　ここまで

		DirectX12Core->EndDraw();//描画後処理

	}

	windowsApp->Break();



	return 0;
}