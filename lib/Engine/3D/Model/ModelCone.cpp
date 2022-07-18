#include "ModelCone.h"


ModelCone::ModelCone()
{
}

ModelCone::~ModelCone()
{
}

void ModelCone::Create()
{
	//頂点バッファ・インデックス生成
	CreatVertexIndexBuffer();

	//定数バッファ生成(3D座標変換行列)
	DirectX12Core::GetInstance()->CreateConstBuff(constMapTransform, constBuffTransform);

	// 頂点データ
	constexpr UINT NumDiv = 32; // 分割数
	float RadianPerDivision = MyMath::AX_2PIF / float(NumDiv); // 分割1単位の角度

	//分割点分割数より1つ多くしておいて1周回るようにする
	std::array<float, NumDiv + 1> pointsZ{};
	std::array<float, NumDiv + 1> pointsX{};
	std::array<float, NumDiv + 1> pointsU{};
	std::array<float, NumDiv + 1> pointsV{};

	//上側の計算
	//頂点座標の計算
	for (size_t i = 0; i < NumDiv; ++i)
	{
		float baseZ = cos(RadianPerDivision * static_cast<float>(i)) * 1.0f;
		float baseX = sin(RadianPerDivision * static_cast<float>(i)) * 1.0f;
		pointsZ[i] = baseZ * -1.0f;
		pointsX[i] = baseX;
	}

	//UV座標の計算
	for (size_t i = 0; i < NumDiv; ++i)
	{
		float baseU = cos(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		float baseV = sin(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		pointsU[i] = baseU + 0.25f;
		pointsV[i] = baseV + 0.5f;
	}

	//最後と最初は一緒
	(*pointsZ.rbegin()) = (*pointsZ.begin());
	(*pointsX.rbegin()) = (*pointsX.begin());
	(*pointsU.rbegin()) = (*pointsU.begin());
	(*pointsV.rbegin()) = (*pointsV.begin());

	PosUvColor tmp{};
	//計算した値を代入
	for (size_t i = 0; i < static_cast<size_t>(NumDiv + 1.0f); i++)
	{
		tmp = {{ pointsX[i],-1.0f,pointsZ[i] },{},{ pointsU[i],pointsV[i]},{1.0f,1.0f,1.0f,1.0f}};
		vertices.push_back(tmp);
	}

	tmp = {{ 0.0f,1.0f,0.0f },{},{ 0.25f,0.5f },{1.0f,1.0f,1.0f,1.0f} };
	vertices.push_back(tmp);

	//下側の計算
	//UV座標の計算
	for (size_t i = 0; i < NumDiv; ++i)
	{
		float baseU = cos(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		float baseV = sin(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		pointsU[i] = baseU + 0.75f;
		pointsV[i] = baseV + 0.5f;
	}

	(*pointsU.rbegin()) = (*pointsU.begin());
	(*pointsV.rbegin()) = (*pointsV.begin());

	//計算した値を代入
	for (size_t i = 1; i < static_cast<size_t>(NumDiv + 1.0f); i++)
	{
		tmp = { { pointsX[i],-1.0f,pointsZ[i] },{},{ pointsU[i],pointsV[i]},{1.0f,1.0f,1.0f,1.0f} };
		vertices.push_back(tmp);
	}

	tmp = { { 0.0f,-1.0f,0.0f },{},{ 0.75f,0.5 },{1.0f,1.0f,1.0f,1.0f} };
	vertices.push_back(tmp);

	// インデックスデータ
	uint8_t count = 0;
	uint16_t indexData = 0;

	//インデックスデータの計算上側
	for (uint16_t i = 0; i < 96; i++)
	{
		if (count == 3)
		{
			count = 0;
		}

		switch (count)
		{
		case 0:
			indices.push_back(indexData);
			break;
		case 1:
			indices.push_back(33);
			break;
		case 2:
			indexData++;
			indices.push_back(indexData);
			break;
		}

		count++;
	}

	count = 0;
	indexData = 35;
	//インデックスデータの計側
	for (size_t i = 96; i < maxIndex; i++)
	{
		if (count == 3)
		{
			count = 0;
		}

		switch (count)
		{
		case 0:
			indices.push_back(indexData);
			break;
		case 1:
			indices.push_back(65);
			break;
		case 2:
			indices.push_back(indexData - static_cast<unsigned>(1));
			indexData++;
			break;
		}

		count++;
	}

	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		//三角形1つごとに計算していく
		//三角形のインデックスを取り出して、一時的な変数に入れる
		unsigned short Index0 = indices[static_cast<std::vector<uint16_t, std::allocator<uint16_t>>::size_type>(i * 3 + 0)];
		unsigned short Index1 = indices[static_cast<std::vector<uint16_t, std::allocator<uint16_t>>::size_type>(i * 3 + 1)];
		unsigned short Index2 = indices[static_cast<std::vector<uint16_t, std::allocator<uint16_t>>::size_type>(i * 3 + 2)];
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

	//ワールド座標
	matWorld = MyMath::MakeIdentity();
}

void ModelCone::SetTexture(const wchar_t* filePath)
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

void ModelCone::Update(const MyMath::Vector3& pos, const MyMath::Vector3& rot, const MyMath::Vector3& scale, const MyMath::Vector4& color)
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

void ModelCone::Draw(Camera* camera)
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

MyMath::Matrix4& ModelCone::GetMatWorld()
{
	return matWorld;
}

const std::vector<uint16_t> ModelCone::GetIndices()
{
	return indices;
}


void ModelCone::CreateShaderResourceView()
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

void ModelCone::CreatVertexIndexBuffer()
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

void ModelCone::CreatTextureBuffer()
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

void ModelCone::Create(const char* filePath)
{
	MyMath::getFileNames(filePath);
}

void ModelCone::Initialize(ModelShareVaria& modelShareVaria, ID3D12PipelineState* pipelineState_, ID3D12RootSignature* rootSignature_)
{
	device = DirectX12Core::GetInstance()->GetDevice();
	cmdList = DirectX12Core::GetInstance()->GetCommandList();

	descriptorRange = modelShareVaria.descriptorRange;
	nextIndex = modelShareVaria.nextIndex;
	pipelineState = pipelineState_;
	rootSignature = rootSignature_;
	srvHeap = modelShareVaria.srvHeap;
};

void ModelCone::Initialize(ModelShareVaria& modelShareVaria)
{
	device = DirectX12Core::GetInstance()->GetDevice();
	cmdList = DirectX12Core::GetInstance()->GetCommandList();

	maxIndex = coneMaxIndex;
	maxVert = coneMaxVert;

	descriptorRange = modelShareVaria.descriptorRange;
	nextIndex = modelShareVaria.nextIndex;
	pipelineState = modelShareVaria.pipelineState;
	rootSignature = modelShareVaria.rootSignature;
	srvHeap = modelShareVaria.srvHeap;

}

const std::vector<PosUvColor> ModelCone::GetVertices()
{
	return vertices;
}
