#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{

}

void GameScene::Initialize()
{
	//シングルトン代入
	mesh = Mesh::GetInstance();
	input = Input::GetInstance();

	//カメラ初期化
	camera = std::make_unique<Camera>();
	camera->Initialize(UpdateProjMatrixFunc_Perspective);

	//ライト初期化
	light.reset(Light::Create());
	light->SetLightColor(lightColor);
	//モデルにライトをセット
	Model::SetLight(light.get());

	//天球読み込み
	skydome.reset(ModelCreate::CreateModel("Resources/skydome"));

	//画層読み込み
	sprite2D.reset(SpriteCreat::CreateSprite(L"Resources/mario.jpg", false));
	sprite3D.reset(SpriteCreat::CreateSprite(L"Resources/peach.jpg", true));
	spriteBillboard.reset(SpriteCreat::CreateSprite(L"Resources/totten.jpg", true));

	//プリミティブモデル生成
	cube.reset(ModelCreate::CreateModel(ModelShape::Cube, L"Resources/mario.jpg"));
	sphere.reset(ModelCreate::CreateModel(ModelShape::Sphere, L"Resources/sekai.jpg"));
	cylinder.reset(ModelCreate::CreateModel(ModelShape::Cylinder, L"Resources/peach.jpg"));
	cone.reset(ModelCreate::CreateModel(ModelShape::Cone, L"Resources/totten.jpg"));

	//objモデル読み込み
	objModel1.reset(ModelCreate::CreateModel("Resources/sphere", true));
	objModel2.reset(ModelCreate::CreateModel("Resources/sphere", false));

}

void GameScene::Update()
{
	//ライトの光線方向設定
	MyMath::Vector3 rightDir = { 10.0f,3.0f,5.0f };
	light->SetLightDir(rightDir);
	light->Update();

	if (input->TriggerPush(DIK_RETURN))
	{
		if (sceneFlag < 4)
		{
			sceneFlag++;
		}
		else
		{
			sceneFlag = 0;
		}
		//視点座標
		MyMath::Vector3 pos = { 0.0f,0.0f,-100.0f };
		//注視点座標
		MyMath::Vector3 target = { 0.0f,0.0f,0.0f };
		//上方向ベクトル
		MyMath::Vector3 up = { 0.0f,1.0f,0.0f };
		camera->SetPosition(pos);
		camera->SetTarget(target);
		camera->SetUp(up);

	}

	switch (sceneFlag)
	{
	case 0://必須課題
		sin += 0.002f;
		cos += 0.005f;
		triangleColor = { 255 * std::sin(sin),255 * std::cos(cos),255 * std::cos(cos),255 * std::sin(sin) };
		break;

	case 1://図形描画
		MeshMove();

	break;

	case 2://スプライト描画
	{
		MyMath::Vector3 move = CameraMove();

		camera->MovePosition(move);
		sprite2D->Update(sprite2DPos, sprite2DRot, sprite2DSca);
		sprite3D->Update(sprite3DPos, sprite3DRot, sprite3DSca);
		spriteBillboard->Update(spriteBillboardPos, spriteBillboardRot, spriteBillboardSca);
	}
	break;

	case 3://プリミティブモデル描画

		ModelMove();

		if (input->TriggerPush(DIK_1))
		{
			modelType = ModelShape::Cube;
		}
		else if (input->TriggerPush(DIK_2))
		{
			modelType = ModelShape::Sphere;
		}
		else if (input->TriggerPush(DIK_3))
		{
			modelType = ModelShape::Cylinder;
		}
		else if (input->TriggerPush(DIK_4))
		{
			modelType = ModelShape::Cone;
		}

		switch (modelType)
		{
		case ModelShape::Cube:

			cube->Update(modelPos, modelRot, modelSca);
			break;

		case ModelShape::Sphere:

			sphere->Update(modelPos, modelRot, modelSca);
			break;

		case ModelShape::Cylinder:

			cylinder->Update(modelPos, modelRot, modelSca);
			break;

		case ModelShape::Cone:

			cone->Update(modelPos, modelRot, modelSca);
			break;
		}
		break;

	case 4://objモデル描画

		ObjMove();

		//デフォルト
		if (input->TriggerPush(DIK_1))
		{
			objModel1->SetShading(Default);
			objModel2->SetShading(Default);
		}
		//フォンシェーディング
		else if (input->TriggerPush(DIK_2))
		{
			objModel1->SetShading(Phong);
			objModel2->SetShading(Phong);
		}
		//ランバートシェーディング
		else if (input->TriggerPush(DIK_3))
		{
			objModel1->SetShading(Lambert);
			objModel2->SetShading(Lambert);
		}

		objModel1->Update(objModelPos + objModelPosShift, objModelRot, objModelSca);
		objModel2->Update(objModelPos - objModelPosShift, objModelRot, objModelSca);
		break;
	}
}

void GameScene::Draw()
{
	//天球の描画
	skydome->Draw(camera.get());

	switch (sceneFlag)
	{
	case 0://必須課題

		//三角形の描画
		mesh->DrawTriangle(100.0f, 100.0f, 100.0f, 600.0f, 1200.0f, 600.0f, mesh->GetColor(triangleColor), wireFrameFlag);
		break;

	case 1://図形描画

		//ブレンドモードを設定
		mesh->SetBlendMode(BlendMode::AX_BLENDMODE_ALPHA);
		//顔を描画
		mesh->DrawEllipse(faceCenter.x, faceCenter.y, faceRadius.x, faceRadius.y, 0.0f, mesh->GetColor(0, 0, 255, alphaNum), wireFrameFlag);
		//鼻の描画
		mesh->DrawTriangle(nose[0].x, nose[0].y, nose[1].x, nose[1].y, nose[2].x, nose[2].y, mesh->GetColor(0, 0, 0, alphaNum), wireFrameFlag);
		//左目の描画
		mesh->DrawTriangle(eye[0].x - eyeShift, eye[0].y, eye[1].x - eyeShift, eye[1].y, eye[2].x - eyeShift, eye[2].y, mesh->GetColor(0, 0, 0, alphaNum), wireFrameFlag);
		//右目の描画
		mesh->DrawTriangle(eye[0].x + eyeShift, eye[0].y, eye[1].x + eyeShift, eye[1].y, eye[2].x + eyeShift, eye[2].y, mesh->GetColor(0, 0, 0, alphaNum), wireFrameFlag);
		//口の描画
		mesh->DrawTriangle(mouth[0].x, mouth[0].y, mouth[1].x, mouth[1].y, mouth[2].x, mouth[2].y, mesh->GetColor(0, 0, 0, alphaNum), wireFrameFlag);
		//ブレンドモードの解除
		mesh->SetBlendMode(BlendMode::AX_BLENDMODE_NOBLEND);
		break;

	case 2://スプライト描画

		sprite2D->Draw(camera.get());
		sprite3D->Draw(camera.get());
		spriteBillboard->BillboardDraw(camera.get());
		break;

	case 3://プリミティブモデル描画

		switch (modelType)
		{

		case ModelShape::Cube:

			cube->Draw(camera.get());
			break;

		case ModelShape::Sphere:

			sphere->Draw(camera.get());
			break;

		case ModelShape::Cylinder:

			cylinder->Draw(camera.get());
			break;

		case ModelShape::Cone:

			cone->Draw(camera.get());
			break;
		}

		break;

	case 4://objモデル描画

		objModel1->Draw(camera.get());
		objModel2->Draw(camera.get());

		break;
	}
}

void GameScene::MeshMove()
{
	MyMath::Vector2 move = { 0.0f,0.0f };

	MyMath::Vector2 radiusMove = { 0.0f,0.0f };

	if (input->KeepPush(DIK_W))
	{
		move += {0.0f, -5.0f};
	}
	else if (input->KeepPush(DIK_S))
	{
		move += {0.0f, 5.0f};
	}

	if (input->KeepPush(DIK_A))
	{
		move += {-5.0f, 0.0f};
	}
	else if (input->KeepPush(DIK_D))
	{
		move += {5.0f, 0.0f};
	}

	if (input->TriggerPush(DIK_SPACE))
	{
		if (wireFrameFlag)
		{
			wireFrameFlag = false;
		}
		else
		{
			wireFrameFlag = true;
		}
	}

	if (input->KeepPush(DIK_UP))
	{
		alphaNum++;
	}
	else if (input->KeepPush(DIK_DOWN))
	{
		alphaNum--;
	}

	if (input->KeepPush(DIK_J))
	{
		radiusMove += {2.0f, 0.0f};
	}
	else if (input->KeepPush(DIK_L))
	{
		radiusMove += {-2.0f, 0.0f};
	}

	if (input->KeepPush(DIK_I))
	{
		radiusMove += {0.0f, 2.0f};
	}
	else if (input->KeepPush(DIK_K))
	{
		radiusMove += {0.0f, -2.0f};
	}

	for (size_t i = 0; i < _countof(nose); i++)
	{
		nose[i] += move;
		eye[i] += move;
		mouth[i] += move;
	}

	faceCenter += move;
	faceRadius += radiusMove;
}

MyMath::Vector3 GameScene::CameraMove()
{
	MyMath::Vector3 move = { 0.0f,0.0f,0.0f };

	if (input->KeepPush(DIK_W))
	{
		move += {0.0f, 0.0f, 0.5f};
	}
	else if (input->KeepPush(DIK_S))
	{
		move -= {0.0f, 0.0f, 0.5f};
	}

	if (input->KeepPush(DIK_A))
	{
		move += {0.5f, 0.0f, 0.0f};
	}
	else if (input->KeepPush(DIK_D))
	{
		move -= {0.5f, 0.0f, 0.0f};
	}

	if (input->KeepPush(DIK_UP))
	{
		move += {0.0f, 0.5f, 0.0f};
	}
	else if (input->KeepPush(DIK_DOWN))
	{
		move -= {0.0f, 0.5f, 0.0f};
	}

	return move;
}

void GameScene::ModelMove()
{
	MyMath::Vector3 move = { 0.0f,0.0f,0.0f };
	MyMath::Vector3 rot = { 0.0f,0.0f,0.0f };

	if (input->KeepPush(DIK_W))
	{
		move += {0.0f, 0.1f, 0.0f};
	}
	else if (input->KeepPush(DIK_S))
	{
		move -= {0.0f, 0.1f, 0.0f};
	}

	if (input->KeepPush(DIK_D))
	{
		move += {0.1f, 0.0f, 0.0f};
	}
	else if (input->KeepPush(DIK_A))
	{
		move -= {0.1f, 0.0f, 0.0f};
	}

	if (input->KeepPush(DIK_UP))
	{
		rot += {MyMath::ChangeRadians(5.0f), 0.0f, 0.0f};
	}
	else if (input->KeepPush(DIK_DOWN))
	{
		rot -= {MyMath::ChangeRadians(5.0f), 0.0f, 0.0f};
	}

	if (input->KeepPush(DIK_LEFT))
	{
		rot += {0.0f, MyMath::ChangeRadians(5.0f), 0.0f};
	}
	else if (input->KeepPush(DIK_RIGHT))
	{
		rot -= {0.0f, MyMath::ChangeRadians(5.0f), 0.0f};
	}

	modelPos += move;
	modelRot += rot;
}

void GameScene::ObjMove()
{
	MyMath::Vector3 move = { 0.0f,0.0f,0.0f };
	MyMath::Vector3 rot = { 0.0f,0.0f,0.0f };

	if (input->KeepPush(DIK_W))
	{
		move += {0.0f, 0.1f, 0.0f};
	}
	else if (input->KeepPush(DIK_S))
	{
		move -= {0.0f, 0.1f, 0.0f};
	}

	if (input->KeepPush(DIK_D))
	{
		move += {0.1f, 0.0f, 0.0f};
	}
	else if (input->KeepPush(DIK_A))
	{
		move -= {0.1f, 0.0f, 0.0f};
	}

	if (input->KeepPush(DIK_UP))
	{
		rot += {MyMath::ChangeRadians(5.0f), 0.0f, 0.0f};
	}
	else if (input->KeepPush(DIK_DOWN))
	{
		rot -= {MyMath::ChangeRadians(5.0f), 0.0f, 0.0f};
	}

	if (input->KeepPush(DIK_LEFT))
	{
		rot += {0.0f, MyMath::ChangeRadians(5.0f), 0.0f};
	}
	else if (input->KeepPush(DIK_RIGHT))
	{
		rot -= {0.0f, MyMath::ChangeRadians(5.0f), 0.0f};
	}

	objModelPos += move;
	objModelRot += rot;
}