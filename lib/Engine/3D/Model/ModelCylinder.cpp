#include "ModelCylinder.h"

ModelCylinder::ModelCylinder()
{
}

ModelCylinder::~ModelCylinder()
{
}

void ModelCylinder::Create(bool smoothing)
{
	static_cast<void>(smoothing);

	maxIndex = cylinderMaxIndex;
	maxVert = cylinderMaxVert;

	//���_�o�b�t�@�E�C���f�b�N�X����
	CreatVertexIndexBuffer();

	//�萔�o�b�t�@����(3D���W�ϊ��s��)
	DirectX12Core::GetInstance()->CreateConstBuff(constMapTransform, constBuffTransform);

	//�萔�o�b�t�@����(�}�e���A��)
	DirectX12Core::GetInstance()->CreateConstBuff(constMapMaterial, constBuffMaterial);
	MyMath::Vector3 one = { 1.0f,1.0f,1.0f };
	constMapMaterial->ambient = one;
	constMapMaterial->diffuse = one;
	constMapMaterial->specular = one;
	constMapMaterial->alpha = material.alpha;

	// ���_�f�[�^
	constexpr UINT NumDiv = 32; // ������
	float RadianPerDivision = MyMath::AX_2PIF / float(NumDiv); // ����1�P�ʂ̊p�x

	//�����_���������1�������Ă�����1�����悤�ɂ���
	std::array<float, NumDiv + 1> pointsZ{};
	std::array<float, NumDiv + 1> pointsX{};
	std::array<float, NumDiv + 1> pointsU{};
	std::array<float, NumDiv + 1> pointsV{};

	//�㑤�̌v�Z
	//���_���W�̌v�Z
	for (size_t i = 0; i < NumDiv; ++i)
	{
		float baseZ = cos(RadianPerDivision * static_cast<float>(i)) * 1.0f;
		float baseX = sin(RadianPerDivision * static_cast<float>(i)) * 1.0f;
		pointsZ[i] = baseZ * -1.0f;
		pointsX[i] = baseX;
		//UV���W�̌v�Z
		float baseU = cos(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		float baseV = sin(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		pointsU[i] = baseU + 0.75f;
		pointsV[i] = baseV + 0.75f;
	}

	//�Ō�ƍŏ��͈ꏏ
	(*pointsZ.rbegin()) = (*pointsZ.begin());
	(*pointsX.rbegin()) = (*pointsX.begin());
	(*pointsU.rbegin()) = (*pointsU.begin());
	(*pointsV.rbegin()) = (*pointsV.begin());

	PosNormalUv tmp;

	//�v�Z�����l����
	for (size_t i = 0; i < NumDiv; i++)
	{
		tmp = {{ pointsX[i],1.0f,pointsZ[i] },{},{ pointsV[i],pointsU[i] } };
		vertices.push_back(tmp);
	}

	tmp = { { 0.0f,1.0f,0.0f },{},{ 0.75f,0.75f } };
	vertices.push_back(tmp);

	//�����̌v�Z
	//UV���W�̌v�Z
	for (size_t i = 0; i < NumDiv; ++i)
	{
		float baseU = cos(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		float baseV = sin(RadianPerDivision * static_cast<float>(i)) * 0.25f;
		pointsU[i] = baseU + 0.25f;
		pointsV[i] = baseV + 0.75f;
	}

	(*pointsU.rbegin()) = (*pointsU.begin());
	(*pointsV.rbegin()) = (*pointsV.begin());

	//�v�Z�����l����
	for (size_t i = 0; i < static_cast<size_t>(NumDiv); i++)
	{
		tmp = { { pointsX[i],-1.0f,pointsZ[i] },{},{ pointsU[i],pointsV[i] }, };
		vertices.push_back(tmp);
	}

	tmp = { { 0.0f,-1.0f,0.0f },{},{ 0.25f,0.75f } };
	vertices.push_back(tmp);

	//UV���W�̌v�Z
	for (size_t i = 0; i < static_cast<size_t>(NumDiv + 1); ++i)
	{
		pointsU[i] = static_cast<float>(i) * (1.0f / 31.0f);
		pointsV[i] = 0.5f;
	}
	(*pointsU.rbegin()) = 1.0f;

	//�v�Z�����l����
	for (size_t i = 0; i < static_cast<size_t>(NumDiv + 1); i++)
	{
		tmp = { { pointsX[i],-1.0f,pointsZ[i] },{},{ pointsU[i],pointsV[i] } };
		vertices.push_back(tmp);
	}

	//UV���W�̌v�Z
	for (size_t i = 0; i < static_cast<size_t>(NumDiv + 1); ++i)
	{
		pointsU[i] = static_cast<float>(i) * (1.0f / 31.0f);
		pointsV[i] = 0.0f;
	}

	(*pointsU.rbegin()) = 1.0f;

	//�v�Z�����l����
	for (size_t i = 0; i < static_cast<size_t>(NumDiv + 1); i++)
	{
		tmp = { { pointsX[i],1.0f,pointsZ[i] },{},{ pointsU[i],pointsV[i] } };
		vertices.push_back(tmp);
	}

	// �C���f�b�N�X�f�[�^
	uint8_t count = 0;
	uint16_t indexData = 0;

	//�C���f�b�N�X�f�[�^�̌v�Z�㑤
	for (uint16_t i = 0; i < 93; i++)
	{
		if (count == 3)
		{
			count = 0;
		}

		if (i == 92)
		{
			indices.push_back(0);
			count++;
		}

		switch (count)
		{
		case 0:
			indices.push_back(indexData);
			break;
		case 1:
			indices.push_back(32);
			break;
		case 2:
			indexData++;
			indices.push_back(indexData);

			break;
		}

		count++;
	}

	count = 0;
	indexData = 34;
	//�C���f�b�N�X�f�[�^�̌v��
	for (size_t i = 0; i < 95; i++)
	{
		if (count == 3)
		{
			count = 0;
		}

		if (i == 93)
		{
			indices.push_back(33);
			count++;
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

	count = 0;
	indexData = 66;
	//�C���f�b�N�X�f�[�^�̌v��
	for (size_t i = 0; i < 96; i++)
	{
		if (count == 3)
		{
			count = 0;
		}

		if (i == 95)
		{
			indices.push_back(98);
			count++;
		}

		switch (count)
		{
		case 0:
			indices.push_back(indexData);
			break;
		case 1:
			indices.push_back(indexData + static_cast<unsigned>(33));
			break;
		case 2:
			indices.push_back(indexData + static_cast<unsigned>(1));
			indexData += 1;
			break;
		}
		count++;

	}

	count = 0;
	indexData = 98;
	//�C���f�b�N�X�f�[�^�̌v��
	for (size_t i = 0; i < 99; i++)
	{
		if (count == 3)
		{
			count = 0;
		}

		if (i == 97)
		{
			indices.push_back(98);
			count++;
		}

		switch (count)
		{
		case 0:
			indices.push_back(indexData + static_cast<unsigned>(1));
			break;
		case 1:
			indices.push_back(indexData - static_cast<unsigned>(32));
			break;
		case 2:
			indices.push_back(indexData);
			indexData += 1;
			break;
		}
		count++;
	}

	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		//�O�p�`1���ƂɌv�Z���Ă���
		//�O�p�`�̃C���f�b�N�X�����o���āA�ꎞ�I�ȕϐ��ɓ����
		unsigned short Index0 = indices[static_cast<std::vector<uint16_t, std::allocator<uint16_t>>::size_type>(i) * 3 + 0];
		unsigned short Index1 = indices[static_cast<std::vector<uint16_t, std::allocator<uint16_t>>::size_type>(i) * 3 + 1];
		unsigned short Index2 = indices[static_cast<std::vector<uint16_t, std::allocator<uint16_t>>::size_type>(i) * 3 + 2];
		//�O�p�`���\�����钸�_���W���x�N�g���ɑ��
		MyMath::Vector3 p0 = vertices[Index0].pos;
		MyMath::Vector3 p1 = vertices[Index1].pos;
		MyMath::Vector3 p2 = vertices[Index2].pos;
		//p0->p1�x�N�g���Ap0->p2�x�N�g�����v�Z(�x�N�g���̌��Z)
		MyMath::Vector3 v1 = p1 - p0;
		MyMath::Vector3 v2 = p2 - p0;
		//�O�ς͗������琂���ȃx�N�g��
		MyMath::Vector3 normal = v1.cross(v2);
		//���K������
		normal.normalization();
		vertices[Index0].normal = normal;
		vertices[Index1].normal = normal;
		vertices[Index2].normal = normal;

	}

	//���_�o�b�t�@�ւ̃f�[�^�]��
	for (size_t i = 0; i < vertices.size(); i++)
	{
		vertMap[i] = vertices[i]; // ���W���R�s�[
	}

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	for (size_t i = 0; i < indices.size(); i++)
	{
		indexMap[i] = indices[i];   // �C���f�b�N�X���R�s�[
	}

	matWorld = MyMath::MakeIdentity();
}

void ModelCylinder::SetTexture(const wchar_t* filePath)
{
	// WIC�e�N�X�`���̃��[�h
	result = LoadFromWICFile(
		filePath,
		DirectX::WIC_FLAGS_NONE,
		&metadata, scratchImg);
	assert(SUCCEEDED(result));

	//�~�b�v�}�b�v����
	result = GenerateMipMaps(
		scratchImg.GetImages(), scratchImg.GetImageCount(), scratchImg.GetMetadata(),
		DirectX::TEX_FILTER_DEFAULT, 0, mipChain);

	if (SUCCEEDED(result))
	{
		scratchImg = std::move(mipChain);
		metadata = scratchImg.GetMetadata();
	}

	//�ǂݍ��񂾃f�B�t���[�Y�e�N�X�`����SRGB�Ƃ��Ĉ���
	metadata.format = DirectX::MakeSRGB(metadata.format);

	//�e�N�X�`���o�b�t�@����
	CreatTextureBuffer();

	//�V�F�[�_�|���\�[�X�r���[����
	CreateShaderResourceView();
}

void ModelCylinder::Update(const MyMath::Vector3& pos, const MyMath::Vector3& rot, const MyMath::Vector3& scale)
{

	MyMath::Matrix4 mTrans, mRot, mScale;
	//���s�ړ��s��
	mTrans.MakeTranslation(pos);
	//��]�s��
	mRot.MakeRotation(rot);
	//�X�P�[���s��
	mScale.MakeScaling(scale);
	//���[���h�s��
	matWorld = mScale * mRot * mTrans;

}

void ModelCylinder::Draw(Camera* camera)
{
	assert(camera);

	constMapTransform->matWorld = matWorld * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();
	constMapTransform->world = matWorld;
	constMapTransform->cameraPos = camera->GetPosition();

	// �p�C�v���C���X�e�[�g�ƃ��[�g�V�O�l�`���̐ݒ�R�}���h
	cmdList->SetPipelineState(pipelineState.Get());
	cmdList->SetGraphicsRootSignature(rootSignature.Get());

	// �v���~�e�B�u�`��̐ݒ�R�}���h
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g

	// ���_�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetVertexBuffers(0, 1, &vbView);

	//�C���f�b�N�X�o�b�t�@�r���[�̐ݒ�R�}���h
	cmdList->IASetIndexBuffer(&ibView);

	// �萔�o�b�t�@�r���[(CBV)�̐ݒ�R�}���h
	cmdList->SetGraphicsRootConstantBufferView(0, constBuffTransform->GetGPUVirtualAddress());
	cmdList->SetGraphicsRootConstantBufferView(1, constBuffMaterial->GetGPUVirtualAddress());
	light->SetConstBufferView(cmdList.Get(), 3);

	// SRV�q�[�v�̐ݒ�R�}���h
	cmdList->SetDescriptorHeaps(1, srvHeap.GetAddressOf());

	// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
	cmdList->SetGraphicsRootDescriptorTable(2, gpuHandle);

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(maxIndex, 1, 0, 0, 0);

}

MyMath::Matrix4& ModelCylinder::GetMatWorld()
{
	return matWorld;
}


const std::vector<uint16_t> ModelCylinder::GetIndices()
{
	return indices;
}

void ModelCylinder::SetShading(ShaderType type)
{
	ModelPipeLine* pipeline = ModelPipeLine::GetInstance();
	switch (type)
	{
	case Default:
		pipelineState = pipeline->GetDefaultPipeline()->pipelineState;
		rootSignature = pipeline->GetDefaultPipeline()->rootSignature;
		break;
	case Flat:
		break;
	case Gouraud:
		break;
	case Lambert:
		pipelineState = pipeline->GetLambertPipeline()->pipelineState;
		rootSignature = pipeline->GetLambertPipeline()->rootSignature;
		break;
	case Phong:
		pipelineState = pipeline->GetPhongPipeline()->pipelineState;
		rootSignature = pipeline->GetPhongPipeline()->rootSignature;
		break;
	default:
		break;
	}
}

void ModelCylinder::CreateShaderResourceView()
{
	//SRV�q�[�v�̐擪�n���h�����擾
	cpuHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();
	gpuHandle = srvHeap->GetGPUDescriptorHandleForHeapStart();

	UINT incrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//�n���h���̃|�C���^���炵
	cpuHandle.ptr += static_cast<unsigned long long>(nextIndex) * incrementSize;
	gpuHandle.ptr += static_cast<unsigned long long>(nextIndex) * incrementSize;

	// �V�F�[�_���\�[�X�r���[�ݒ�
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	srvDesc.Format = metadata.format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = static_cast<UINT>(metadata.mipLevels);

	// �n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	device->CreateShaderResourceView(texBuff.Get(), &srvDesc, cpuHandle);
}

void ModelCylinder::CreatVertexIndexBuffer()
{
	// �q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};

	// ���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(PosNormalUv) * maxVert);

	// ���_�o�b�t�@�̐ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
	// ���\�[�X�ݒ�
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB; // ���_�f�[�^�S�̂̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// ���_�o�b�t�@�̐���
	result = device->CreateCommittedResource(
		&heapProp, // �q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc, // ���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(vertBuff.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));

	// GPU��̃o�b�t�@�ɑΉ��������z������(���C����������)���擾
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	assert(SUCCEEDED(result));

	// ���_�o�b�t�@�r���[�̍쐬
	// GPU���z�A�h���X
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	// ���_�o�b�t�@�̃T�C�Y
	vbView.SizeInBytes = sizeVB;
	// ���_�P���̃f�[�^�T�C�Y
	vbView.StrideInBytes = sizeof(PosNormalUv);

	// �C���f�b�N�X�f�[�^�̃T�C�Y
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * maxIndex);
	// ���_�o�b�t�@�̐ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD; // GPU�ւ̓]���p
	//���\�[�X�ݒ�
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeIB;//�C���f�b�N�X��񂪓��镪�̃T�C�Y
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//�C���f�b�N�X�o�b�t�@�̐���
	result = device->CreateCommittedResource(
		&heapProp,//�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&resDesc,//���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(indexBuff.ReleaseAndGetAddressOf()));

	//�C���f�b�N�X�o�b�t�@���}�b�s���O
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	//�}�b�s���O����
	indexBuff->Unmap(0, nullptr);

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;
	assert(SUCCEEDED(result));
}

void ModelCylinder::CreatTextureBuffer()
{

	// �q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	textureHeapProp.Type = D3D12_HEAP_TYPE_CUSTOM;
	textureHeapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK;
	textureHeapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_L0;
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC textureResourceDesc{};
	textureResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	textureResourceDesc.Format = metadata.format;
	textureResourceDesc.Width = metadata.width;//��
	textureResourceDesc.Height = (UINT)metadata.height;//����
	textureResourceDesc.DepthOrArraySize = (UINT16)metadata.arraySize;
	textureResourceDesc.MipLevels = (UINT16)metadata.mipLevels;
	textureResourceDesc.SampleDesc.Count = 1;

	// �e�N�X�`���o�b�t�@�̐���
	result = device->CreateCommittedResource(
		&textureHeapProp,
		D3D12_HEAP_FLAG_NONE,
		&textureResourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(texBuff.ReleaseAndGetAddressOf()));

	//�e�N�X�`���o�b�t�@�Ƀf�[�^�]��
	for (size_t i = 0; i < metadata.mipLevels; i++)
	{
		// �~�b�v�}�b�v���x�����w�肵�ăC���[�W���擾
		const DirectX::Image* img = scratchImg.GetImage(i, 0, 0);
		// �e�N�X�`���o�b�t�@�Ƀf�[�^�]��
		result = texBuff->WriteToSubresource(
			(UINT)i,
			nullptr,              // �S�̈�փR�s�[
			img->pixels,          // ���f�[�^�A�h���X
			(UINT)img->rowPitch,  // 1���C���T�C�Y
			(UINT)img->slicePitch // 1���T�C�Y
		);
		assert(SUCCEEDED(result));
	}
}

void ModelCylinder::Create(const char* filePath,bool smoothing)
{
	static_cast<void>(filePath);
	static_cast<void>(smoothing);
};

void ModelCylinder::Initialize(ModelShareVaria& modelShareVaria)
{
	device = DirectX12Core::GetInstance()->GetDevice();
	cmdList = DirectX12Core::GetInstance()->GetCommandList();

	maxIndex = cylinderMaxIndex;
	maxVert = cylinderMaxVert;

	descriptorRange = modelShareVaria.descriptorRange;
	nextIndex = modelShareVaria.nextIndex;
	pipelineState = modelShareVaria.pipelineState;
	rootSignature = modelShareVaria.rootSignature;
	srvHeap = modelShareVaria.srvHeap;

}

const std::vector<PosNormalUv> ModelCylinder::GetVertices()
{
	return vertices;
}