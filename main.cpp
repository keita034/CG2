//#DirectX�̂��
#include"ErrorException.h"


//����.h
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
	Mesh* mesh = new Mesh();

	Camera* camera = new Camera();
	camera->Initialize(UpdateProjMatrixFunc_Perspective);
	Model* model = new Model();
	model->Create(Cube);
	model->SetTexture(L"Resources/mario.jpg");

	//�`�揉�������������܂�
	Input* input = new Input();
	input->Initialize();
	float angle = 0.0f;
	camera->SetPosition(-10.0f * sinf(angle), 0.0f, -10.0f * cosf(angle));
	//�Q�[�����[�v
	while (true)
	{

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
		//�`�揈��
		
		//DirectX���t���[�������@�����܂�

		DirectX12Core->EndDraw();//�`��㏈��

	}

	windowsApp->Break();



	return 0;
}