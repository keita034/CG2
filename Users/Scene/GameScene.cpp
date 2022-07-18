#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{

}

void GameScene::Initialize()
{
	input = Input::GetInstance();

	camera = std::make_unique<Camera>();
	camera->Initialize(UpdateProjMatrixFunc_Perspective);
	camera->SetPosition(0,0,-5.0f);
	skyDome.reset(ModelCreate::CreateModel("Resources/skydome"));
	ground.reset(ModelCreate::CreateModel("Resources/ground"));

	sprite.reset(SpriteCreat::CreateSprite(L"Resources/mario.jpg", true));
	particle.reset(ParticleCreat::CreateParticle(L"Resources/Particle/effect3.png"));
}

void GameScene::Update()
{
	MyMath::Vector3 move = { 0.0f,0.0f,0.0f };

	if (input->KeepPush(DIK_W))
	{
		move += {0.0f, 0.0f, 0.1f};
	}
	if (input->KeepPush(DIK_S))
	{
		move -= {0.0f, 0.0f, 0.1f};
	}
	if (input->KeepPush(DIK_A))
	{
		move += {0.1f, 0.0f, 0.0f};
	}
	if (input->KeepPush(DIK_D))
	{
		move -= {0.1f, 0.0f, 0.0f};
	}
	if (input->KeepPush(DIK_UP))
	{
		move += {0.0f,0.1f,  0.0f};
	}
	if (input->KeepPush(DIK_DOWN))
	{
		move -= {0.0f,0.1f,  0.0f};
	}

	camera->MovePosition(move);

	skyDome->Update();
	ground->Update();
	sprite->Update({0,0,0},{0,0,0},{1,2,1,});

	for (size_t i = 0; i < 100; i++)
	{
		//X,Y,Z全て{-5.0f,+0.5f}でランダムに分布
		const float rnd_pos = 10.0f;
		MyMath::Vector3 pos{};
		pos.x = static_cast<float>(rand()) / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = static_cast<float>(rand()) / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = static_cast<float>(rand()) / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		//X,Y,Z全て{-0.05f,+0.05f}でランダムに分布
		const float rnd_vel = 0.1f;
		MyMath::Vector3 vel{};
		vel.x = static_cast<float>(rand()) / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = static_cast<float>(rand()) / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = static_cast<float>(rand()) / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		//重力に見立てYのみ{-0.001f,0}でランダムに分布
		const float rnd_acc = 0.001f;
		MyMath::Vector3 acc{};
		acc.y = static_cast<float>(rand()) / RAND_MAX * rnd_acc;
		//スケール
		MyMath::Vector2 sca = { 1.0f,0.0f };
		//回転角
		MyMath::Vector2 rot = { MyMath::AX_PIF/3.0f,0.0f };
		//生存時間
		UINT life = static_cast<UINT>(60 * rand() / RAND_MAX);
		//開始時カラー
		MyMath::Vector4 sCol = { 1.0f,1.0f,0.0f,1.0f };
		//終了カラー
		MyMath::Vector4 eCol = { 1.0f,1.0f,1.0f,1.0f };
		particle->Add(life, pos, vel, acc, sca, rot,sCol,eCol);
	}

	particle->Update();
}

void GameScene::Draw()
{
	skyDome->Draw(camera.get());
	//ground->Draw(camera.get());
	//sprite->BillboardYDraw(camera.get());

	particle->Draw(camera.get());
}
