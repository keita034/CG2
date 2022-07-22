//#DirectX�̂��
#include"ErrorException.h"


//����.h
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


// Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{

	WindowsApp* windowsApp = WindowsApp::GetInstance();//WindowsApp�N���X�ǂݍ���
	windowsApp->CreatWindow();//�E�B���h�E����

	//DirectX������������������

	DirectX12Core* DirectX12Core = DirectX12Core::GetInstance();//DirectX12Core�N���X�ǂݍ���
	DirectX12Core->DirectXInitialize();//DirectX12������
	DirectX12Core->SetBackScreenColor(0.1f, 0.25f, 0.5f, 0.0f);	//�w�i�̐F�ύX(R,G,B,A)

	//DirectX���������������܂�

	//�`�揉����������������
	Mesh* mesh = Mesh::GetInstance();

	ModelPipeLine* pipeline = ModelPipeLine::GetInstance();
	pipeline->Initialize();
	//�`�揉�������������܂�

	Input* input = Input::GetInstance();
	input->Initialize();

	GameScene* gameScene = new GameScene;
	gameScene->Initialize();

	FPS* fps = new FPS;

	//�Q�[�����[�v
	while (true)
	{
		fps->FpsControlBegin();

		if (!windowsApp->MessageWindow())//���b�Z�[�W����
		{
			break;
		}

		//��������
		DirectX12Core->BeginDraw();//�`�揀��

		//DirectX���t���[�������@��������

		//�X�V����
		mesh->DrawReset();
		input->Update();

		gameScene->Update();

		//�`�揈��

		gameScene->Draw();

		//DirectX���t���[�������@�����܂�

		DirectX12Core->EndDraw();//�`��㏈��

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