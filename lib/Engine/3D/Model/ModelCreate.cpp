#include "ModelCreate.h"

#include"ModelCube.h"
#include"ModelCone.h"
#include"ModelCylinder.h"
#include"ModelSphere.h"
#include"objModel.h"

ModelShareVaria ModelCreate::modelShareVaria{};


Model* ModelCreate::CreateModel(ModelShape shape, const wchar_t* filePath, bool smoothing)
{
	if (modelShareVaria.pipelineState == nullptr)
	{
		//デスクプリタヒープ生成
		CreateDescriptorHeap();

		//デスクプリタレンジ設定
		CreateDescriptorRange();

		//パイプライン生成
		CreatPipeline();
	}

	switch (shape)
	{
	case ModelShape::Cube:
	{
		Model* cube = new ModelCube;
		cube->Initialize(modelShareVaria);
		cube->SetTexture(filePath);
		cube->Create(smoothing);
		modelShareVaria.nextIndex++;
		return cube;
	}
	case ModelShape::Sphere:
	{
		Model* sphere = new ModelSphere;
		sphere->Initialize(modelShareVaria);
		sphere->SetTexture(filePath);
		sphere->Create(smoothing);
		modelShareVaria.nextIndex++;
		return sphere;
	}
	case ModelShape::Capsule:

	case ModelShape::Cylinder:
	{
		Model* cylinder = new ModelCylinder;
		cylinder->Initialize(modelShareVaria);
		cylinder->SetTexture(filePath);
		cylinder->Create(smoothing);
		modelShareVaria.nextIndex++;
		return cylinder;
	}
	case ModelShape::Cone:
	{
		Model* cone = new ModelCone;
		cone->Initialize(modelShareVaria);
		cone->SetTexture(filePath);
		cone->Create(smoothing);
		modelShareVaria.nextIndex++;
		return cone;
	}
	default:
		return nullptr;
		break;
	}
}

Model* ModelCreate::CreateModel(const char* filePath, bool smoothing)
{
	if (modelShareVaria.pipelineState == nullptr)
	{
		//デスクプリタヒープ生成
		CreateDescriptorHeap();

		//デスクプリタレンジ設定
		CreateDescriptorRange();

		//パイプライン生成
		CreatPipeline();
	}
	
	Model* model = new objModel;
	model->Initialize(modelShareVaria);
	model->Create(filePath, smoothing);
	modelShareVaria.nextIndex++;
	return model;

}

void ModelCreate::CreatPipeline()
{
	HRESULT result;
	Microsoft::WRL::ComPtr<ID3D12Device> device = DirectX12Core::GetInstance()->GetDevice();

	Microsoft::WRL::ComPtr<ID3DBlob> vsBlob = nullptr; // 頂点シェーダオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> psBlob = nullptr; // ピクセルシェーダオブジェクト
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr; // エラーオブジェクト

	// 頂点シェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/Shaders/3D/Model/ModelBasicVS.hlsl", // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "vs_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		vsBlob.ReleaseAndGetAddressOf(), errorBlob.ReleaseAndGetAddressOf());

	// エラーなら
	if (FAILED(result))
	{
		// errorBlobからエラー内容をstring型にコピー
		std::string error;
		error.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(error.c_str());
		assert(0);
	}

	// ピクセルシェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/Shaders/3D/Model/ModelBasicPS.hlsl", // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		psBlob.ReleaseAndGetAddressOf(), errorBlob.ReleaseAndGetAddressOf());

	// エラーなら
	if (FAILED(result))
	{
		// errorBlobからエラー内容をstring型にコピー
		std::string error;
		error.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(error.c_str());
		assert(0);
	};

	// 頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] =
	{
		// xyz座標
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//法線ベクトル
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		// uv座標
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	//ルートパラメータの設定
	D3D12_ROOT_PARAMETER rootParams[4] = {};
	//定数バッファ0番
	rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;//種類
	rootParams[0].Descriptor.ShaderRegister = 0;//定数バッファバッファ番号
	rootParams[0].Descriptor.RegisterSpace = 0;//デフォルト値
	rootParams[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//全てのシェーダーから見える
	//定数バッファ1番
	rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;//種類
	rootParams[1].Descriptor.ShaderRegister = 1;//定数バッファバッファ番号
	rootParams[1].Descriptor.RegisterSpace = 0;//デフォルト値
	rootParams[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//全てのシェーダーから見える

	//テクスチャレジスタ0番
	rootParams[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;//種類
	rootParams[2].DescriptorTable.pDescriptorRanges = &modelShareVaria.descriptorRange;//デスクプリタレンジ
	rootParams[2].DescriptorTable.NumDescriptorRanges = 1;//デスクプリタレンジ数
	rootParams[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//全てのシェーダーから見える
	
																 //定数バッファ2番
	rootParams[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;//種類
	rootParams[3].Descriptor.ShaderRegister = 2;//定数バッファバッファ番号
	rootParams[3].Descriptor.RegisterSpace = 0;//デフォルト値
	rootParams[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//全てのシェーダーから見える
	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	// シェーダーの設定
	pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();

	// サンプルマスクの設定
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定

	// ラスタライザの設定
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // カリングしない
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // ポリゴン内塗りつぶし
	pipelineDesc.RasterizerState.DepthClipEnable = true; // 深度クリッピングを有効に

	// ブレンドステート
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	//共通設定(アルファ値)
	blenddesc.BlendEnable = true;// ブレンドを有効
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;//加算
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;//ソースの値を100%使う
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;//テストの値を0%使う

	// 半透明合成
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;// 加算
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;// ソースのアルファ値
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;;// 1.0f-ソースのアルファ値

	// 頂点レイアウトの設定
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;

	// 図形の形状設定
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	//D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE
	// //D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE
	//デプスステンシルステートの設定
	pipelineDesc.DepthStencilState.DepthEnable = true;//深度テストを行う
	pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;//書き込み許可
	pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;//小さければ合格
	pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;//深度フォーマット
	// その他の設定
	pipelineDesc.NumRenderTargets = 1; // 描画対象は1つ
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0〜255指定のRGBA
	pipelineDesc.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	//テクスチャサンプラーの設定
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;//横繰り返し（タイリング）
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;//縦繰り返し（タイリング）
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;//奥行繰り返し（タイリング）
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;//ボーダーの時は黒
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;//全てリニア補間
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;//ミップマップ最大値
	samplerDesc.MinLOD = 0.0f;//ミップマップ最小値
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;//ピクセルシェーダからのみ使用可能

	// ルートシグネチャ
	// ルートシグネチャの設定
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams; //ルートパラメータの先頭アドレス
	rootSignatureDesc.NumParameters = _countof(rootParams);        //ルートパラメータ数
	rootSignatureDesc.pStaticSamplers = &samplerDesc;
	rootSignatureDesc.NumStaticSamplers = 1;

	// ルートシグネチャのシリアライズ
	Microsoft::WRL::ComPtr<ID3DBlob> rootSigBlob = nullptr;
	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, rootSigBlob.ReleaseAndGetAddressOf(), errorBlob.ReleaseAndGetAddressOf());
	assert(SUCCEEDED(result));
	result = device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(modelShareVaria.rootSignature.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));
	// パイプラインにルートシグネチャをセット
	pipelineDesc.pRootSignature = modelShareVaria.rootSignature.Get();

	// パイプランステートの生成
	result = device->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(modelShareVaria.pipelineState.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));
}

void ModelCreate::CreateDescriptorHeap()
{
	HRESULT result;
	Microsoft::WRL::ComPtr<ID3D12Device> device = DirectX12Core::GetInstance()->GetDevice();
	//SRVの最大個数
	const size_t kMaxSRVCount = 2042;

	// デスクリプタヒープの設定
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
	srvHeapDesc.NumDescriptors = kMaxSRVCount;

	// 設定を元にSRV用デスクリプタヒープを生成
	result = device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(modelShareVaria.srvHeap.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));
}

void ModelCreate::CreateDescriptorRange()
{
	modelShareVaria.descriptorRange.NumDescriptors = 1;//1度の描画に使うテクスチャが一枚なので
	modelShareVaria.descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	modelShareVaria.descriptorRange.BaseShaderRegister = 0;//テクスチャレジスタ0番
	modelShareVaria.descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
}
