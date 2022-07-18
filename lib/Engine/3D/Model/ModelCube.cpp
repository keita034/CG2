#include "ModelCube.h"
#include"DirectX12Core.h"

ModelCube::ModelCube()
{
}

ModelCube::~ModelCube()
{
}

void ModelCube::Create()
{
	//頂点バッファ・インデックス生成
	CreatVertexIndexBuffer();

	//定数バッファ生成(3D座標変換行列)
	DirectX12Core::GetInstance()->CreateConstBuff(constMapTransform, constBuffTransform);

	// 頂点データ
	//正面
	PosUvColor tmp = { { -1.0f, -1.0f, -1.0f }, {}, { 0.0f, 1.0f }, { 1.0f,1.0f,1.0f,1.0f } };//左上インデックス0
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f,-1.0f},{},{ 0.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//左下インデックス1
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f,-1.0f},{},{ 1.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//右上インデックス2
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f,-1.0f},{},{ 1.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//右下インデックス3
	vertices.push_back(tmp);

	//右
	tmp = { { 1.0f,-1.0f,-1.0f},{},{ 0.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//左上インデックス4
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f,-1.0f},{},{ 0.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//左下インデックス5
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f, 1.0f},{},{ 1.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//右上インデックス6
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f, 1.0f},{},{ 1.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//右下インデックス7
	vertices.push_back(tmp);

	//左
	tmp = { {-1.0f,-1.0f, 1.0f},{},{ 0.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//左上インデックス8
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f, 1.0f},{},{ 0.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//左下インデックス9
	vertices.push_back(tmp);
	tmp = { {-1.0f,-1.0f,-1.0f},{},{ 1.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//右上インデックス10
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f,-1.0f},{},{ 1.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//右下インデックス11
	vertices.push_back(tmp);
	
	//裏
	tmp = { { 1.0f,-1.0f, 1.0f},{},{ 0.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//左上インデックス12
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f, 1.0f},{},{ 0.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//左下インデックス13
	vertices.push_back(tmp);
	tmp = { {-1.0f,-1.0f, 1.0f},{},{ 1.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//右上インデックス14
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f, 1.0f},{},{ 1.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//右下インデックス15
	vertices.push_back(tmp);

	//上
	tmp = { {-1.0f, 1.0f,-1.0f},{},{ 0.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//左上インデックス16
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f, 1.0f},{},{ 0.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//左下インデックス17
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f,-1.0f},{},{ 1.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//右上インデックス18
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f, 1.0f},{},{ 1.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//右下インデックス19
	vertices.push_back(tmp);

	//底
	tmp = { {-1.0f,-1.0f, 1.0f},{},{ 0.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//左上インデックス20
	vertices.push_back(tmp);
	tmp = { {-1.0f,-1.0f,-1.0f},{},{ 0.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//左下インデックス21
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f, 1.0f},{},{ 1.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//右上インデックス22
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f,-1.0f},{},{ 1.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//右下インデックス23
	vertices.push_back(tmp);

// インデックスデータ

	//正面
	indices.push_back(0), indices.push_back(1), indices.push_back(3);//0
	indices.push_back(3), indices.push_back(2), indices.push_back(0);//1

	//右
	indices.push_back(4), indices.push_back(5), indices.push_back(7);//2
	indices.push_back(7), indices.push_back(6), indices.push_back(4);//3

	//左
	indices.push_back(8), indices.push_back(9), indices.push_back(11);//4
	indices.push_back(11), indices.push_back(10), indices.push_back(8);//5

	//裏
	indices.push_back(12), indices.push_back(13), indices.push_back(15);//6
	indices.push_back(15), indices.push_back(14), indices.push_back(12);//7

	//上
	indices.push_back(16), indices.push_back(17), indices.push_back(19);//8
	indices.push_back(19), indices.push_back(18), indices.push_back(16);//9

	//底
	indices.push_back(20), indices.push_back(21), indices.push_back(23);//10
	indices.push_back(23), indices.push_back(22), indices.push_back(20);//11

	for (size_t i = 0; i < cubeMaxIndex / 3; i++)
	{
		//三角形1つごとに計算していく
		//三角形のインデックスを取り出して、一時的な変数に入れる
		unsigned short Index0 = indices[i * 3 + 0];
		unsigned short Index1 = indices[i * 3 + 1];
		unsigned short Index2 = indices[i * 3 + 2];
		//三角形を構成する頂点座標をベクトルに代入
		MyMath::Vector3 p0 = vertices[Index0].pos;
		MyMath::Vector3 p1 = vertices[Index1].pos;
		MyMath::Vector3 p2 = vertices[Index2].pos;
		//p0->p1ベクトル、p0->p2ベクトルを計算(ベクトルの減算)
		MyMath::Vector3 v1 = p1 - p0;
		MyMath::Vector3 v2 = p2 - p0;
		//外積は両方から垂直なベクトル
		MyMath::Vector3 normal = v1.cross(v2);
		//正規化する
		normal.normalization();
		vertices[Index0].normal = normal;
		vertices[Index1].normal = normal;
		vertices[Index2].normal = normal;

	}
	//頂点バッファへのデータ転送
	for (size_t i = 0; i < vertices.size(); i++)
	{
		vertMap[i] = vertices[i]; // 座標をコピー
	}

	//インデックスバッファへのデータ転送
	for (size_t i = 0; i < indices.size(); i++)
	{
		indexMap[i] = indices[i];   // インデックスをコピー
	}

	matWorld = MyMath::MakeIdentity();
}

void ModelCube::SetTexture(const wchar_t* filePath)
{
	// WICテクスチャのロード
	result = LoadFromWICFile(
		filePath,
		DirectX::WIC_FLAGS_NONE,
		&metadata, scratchImg);
	assert(SUCCEEDED(result));

	//ミップマップ生成
	result = GenerateMipMaps(
		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
		DirectX::TEX_FILTER_DEFAULT, 0, mipChain);

	if (SUCCEEDED(result))
	{
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	//読み込んだディフューズテクスチャをSRGBとして扱う
	metadata.format = DirectX::MakeSRGB(metadata.format);

	//テクスチャバッファ生成
	CreatTextureBuffer();

	//シェーダ－リソースビュー生成
	CreateShaderResourceView();
}

void ModelCube::Update(const MyMath::Vector3& pos, const MyMath::Vector3& rot, const MyMath::Vector3& scale, const MyMath::Vector4& color)
{
	//カラー
	for (int i = 0; i < 4; i++)
	{
		vertMap[i].color = color;
	}

	MyMath::Matrix4 mTrans, mRot, mScale;
	//平行移動行列
	mTrans.MakeTranslation(pos);
	//回転行列
	mRot.MakeRotation(rot);
	//スケール行列
	mScale.MakeScaling(scale);
	//ワールド行列
	matWorld = mScale * mRot * mTrans;

}

MyMath::Matrix4& ModelCube::GetMatWorld()
{
	return matWorld;
}


void ModelCube::Draw(Camera* camera)
{
	assert(camera);
	constMapTransform->mat = matWorld * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();

	// パイプラインステートとルートシグネチャの設定コマンド
	cmdList->SetPipelineState(pipelineState.Get());
	cmdList->SetGraphicsRootSignature(rootSignature.Get());

	// プリミティブ形状の設定コマンド
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // 三角形リスト

	// 頂点バッファビューの設定コマンド
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//インデックスバッファビューの設定コマンド
	cmdList->IASetIndexBuffer(&ibView);

	// 定数バッファビュー(CBV)の設定コマンド
	cmdList->SetGraphicsRootConstantBufferView(0, constBuffTransform->GetGPUVirtualAddress());

	// SRVヒープの設定コマンド
	cmdList->SetDescriptorHeaps(1, srvHeap.GetAddressOf());

	// SRVヒープの先頭にあるSRVをルートパラメータ1番に設定
	cmdList->SetGraphicsRootDescriptorTable(1, gpuHandle);

	// 描画コマンド
	cmdList->DrawIndexedInstanced(maxIndex, 1, 0, 0, 0);

}

const std::vector<uint16_t> ModelCube::GetIndices()
{
	return indices;
}

void ModelCube::CreateShaderResourceView()
{
	//SRVヒープの先頭ハンドルを取得
	cpuHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();
	gpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();

	UINT incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//ハンドルのポインタずらし
	cpuHandle.ptr += static_cast<unsigned long long>(nextIndex) * incrementSize;
	gpuHandle.ptr += static_cast<unsigned long long>(nextIndex) * incrementSize;

	// シェーダリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = static_cast<UINT>(metadata.mipLevels);

	// ハンドルの指す位置にシェーダーリソースビュー作成
	device->CreateShaderResourceView(texBuff.Get(), &srvDesc, cpuHandle);
}

void ModelCube::CreatVertexIndexBuffer()
{
	// ヒープ設定
	D3D12_HEAP_PROPERTIES heapProp{};
	// リソース設定
	D3D12_RESOURCE_DESC resDesc{};

	// 頂点データ全体のサイズ = 頂点データ一つ分のサイズ * 頂点データの要素数
	UINT sizeVB = static_cast<UINT>(sizeof(PosUvColor) * maxVert);

	// 頂点バッファの設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPUへの転送用
	// リソース設定
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB; // 頂点データ全体のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 頂点バッファの生成
	result = device->CreateCommittedResource(
		&heapProp, // ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc, // リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(vertBuff.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	// GPU上のバッファに対応した仮想メモリ(メインメモリ上)を取得
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));

	// 頂点バッファビューの作成
	// GPU仮想アドレス
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	// 頂点バッファのサイズ
	vbView.SizeInBytes = sizeVB;
	// 頂点１つ分のデータサイズ
	vbView.StrideInBytes = sizeof(PosUvColor);

	// インデックスデータのサイズ
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * maxIndex);
	// 頂点バッファの設定
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPUへの転送用
	//リソース設定
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB;//インデックス情報が入る分のサイズ
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//インデックスバッファの生成
	result = device->CreateCommittedResource(
		&heapProp,//ヒープ設定
		D3D12_HEAP_FLAG_NONE,
		&resDesc,//リソース設定
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(indexBuff.ReleaseAndGetAddressOf()));

	//インデックスバッファをマッピング
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	//マッピング解除
	indexBuff->Unmap(0, nullptr);

	//インデックスバッファビューの作成
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;
	assert(SUCCEEDED(result));
}

void ModelCube::CreatTextureBuffer()
{

	// ヒープ設定
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	textureHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	// リソース設定
	D3D12_RESOURCE_DESC textureResourceDesc{};
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = metadata.format;
	textureResourceDesc.Width = metadata.width;//幅
	textureResourceDesc.Height = (UINT)metadata.height;//高さ
	textureResourceDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
	textureResourceDesc.MipLevels = (UINT16)metadata.mipLevels;
	textureResourceDesc.SampleDesc.Count = 1;

	// テクスチャバッファの生成
	result = device->CreateCommittedResource(
		&textureHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(texBuff.ReleaseAndGetAddressOf()));

	//テクスチャバッファにデータ転送
	for (size_t i = 0; i < metadata.mipLevels; i++)
	{
		// ミップマップレベルを指定してイメージを取得
		const DirectX::Image* img = scratchImg.GetImage(i, 0, 0);
		// テクスチャバッファにデータ転送
		result = texBuff->WriteToSubresource(
			(UINT)i,
			nullptr,              // 全領域へコピー
			img->pixels,          // 元データアドレス
			(UINT)img->rowPitch,  // 1ラインサイズ
			(UINT)img->slicePitch // 1枚サイズ
		);
		assert(SUCCEEDED(result));
	}
}

void ModelCube::Create(const char* filePath)
{
	MyMath::getFileNames(filePath);
}

void ModelCube::Initialize(ModelShareVaria& modelShareVaria, ID3D12PipelineState* pipelineState_, ID3D12RootSignature* rootSignature_)
{
	device = DirectX12Core::GetInstance()->GetDevice();
	cmdList = DirectX12Core::GetInstance()->GetCommandList();

	descriptorRange = modelShareVaria.descriptorRange;
	nextIndex = modelShareVaria.nextIndex;
	pipelineState = pipelineState_;
	rootSignature = rootSignature_;
	srvHeap = modelShareVaria.srvHeap;
};

void ModelCube::Initialize(ModelShareVaria& modelShareVaria)
{
	device = DirectX12Core::GetInstance()->GetDevice();
	cmdList = DirectX12Core::GetInstance()->GetCommandList();

	maxIndex = cubeMaxIndex;
	maxVert = cubeMaxVert;

	descriptorRange = modelShareVaria.descriptorRange;
	nextIndex = modelShareVaria.nextIndex;
	pipelineState = modelShareVaria.pipelineState;
	rootSignature = modelShareVaria.rootSignature;
	srvHeap = modelShareVaria.srvHeap;

}

const std::vector<PosUvColor> ModelCube::GetVertices()
{
	return vertices;
}
