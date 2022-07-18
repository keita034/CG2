#include "Sprite2D.h"

void Sprite2D::BillboardDraw(Camera* camera)
{
	assert(0);
	static_cast<void>(camera);
}

void Sprite2D::BillboardXDraw(Camera* camera)
{
	assert(0);
	static_cast<void>(camera);
}

void Sprite2D::BillboardYDraw(Camera* camera)
{
	assert(0);
	static_cast<void>(camera);
}

void Sprite2D::BillboardZDraw(Camera* camera)
{
	assert(0);
	static_cast<void>(camera);
}

//�萔�o�b�t�@�̐���
void Sprite2D::CreateShaderResourceView()
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

//�萔�o�b�t�@����
void Sprite2D::CreatConstBuff()
{
	//�萔�o�b�t�@����
	DirectX12Core::GetInstance()->CreateConstBuff(constMapTransform, constBuffTransform);

	float width = static_cast<float>(WindowsApp::GetInstance()->GetWindowWidth());
	float height = static_cast<float>(WindowsApp::GetInstance()->GetWindowHeight());

	MyMath::MakeOrthogonalL(0.0f, width, height, 0.0f, 0.0f, 1.0f, matProjection);
}

//���_�o�b�t�@�E�C���f�b�N�X����
void Sprite2D::CreatVertexIndexBuffer()
{
	// �q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};

	// ���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(PosUvColor) * 4);

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
	vbView.StrideInBytes = sizeof(PosUvColor);

	// �C���f�b�N�X�f�[�^�̃T�C�Y
	UINT sizeIB = static_cast<UINT>(sizeof(uint16_t) * 6);
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

//�e�N�X�`���o�b�t�@����
void Sprite2D::CreatTextureBuffer()
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

void Sprite2D::Initialize(ModelShareVaria& modelShareVaria)
{
	device = DirectX12Core::GetInstance()->GetDevice();
	cmdList = DirectX12Core::GetInstance()->GetCommandList();

	descriptorRange = modelShareVaria.descriptorRange;
	nextIndex = modelShareVaria.nextIndex;
	pipelineState = modelShareVaria.pipelineState;
	rootSignature = modelShareVaria.rootSignature;
	srvHeap = modelShareVaria.srvHeap;
}

//�R���X�g���N�^
void Sprite2D::Load(const wchar_t* filePath)
{
	device = DirectX12Core::GetInstance()->GetDevice();
	cmdList = DirectX12Core::GetInstance()->GetCommandList();

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

	//���_�o�b�t�@�E�C���f�b�N�X����
	CreatVertexIndexBuffer();

	//�萔�o�b�t�@����(2D���W�ϊ��s��)
	CreatConstBuff();


	//�摜�̔����̃T�C�Y
	float halfW = static_cast<float>(metadata.width) * 0.5f;
	float halfH = static_cast<float>(metadata.height) * 0.5f;

	// ���_�f�[�^
	PosUvColor vertices[] =
	{//		x		y		z		u	v
		{{-halfW, -halfH, 0.0f},{},{0.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//����C���f�b�N�X0
		{{-halfW, halfH, 0.0f},{},{0.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//�����C���f�b�N�X1
		{{halfW, -halfH, 0.0f},{},{1.0f,0.0f},{1.0f,1.0f,1.0f,1.0f}},//�E��C���f�b�N�X2
		{{halfW, halfH, 0.0f},{},{1.0f,1.0f},{1.0f,1.0f,1.0f,1.0f}},//�E���C���f�b�N�X3
	};

	// �C���f�b�N�X�f�[�^
	uint16_t indices[] =
	{
		1, 0, 3, // �O�p�`1��
		0, 3, 2, // �O�p�`2��
	};

	//���_�o�b�t�@�ւ̃f�[�^�]��
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i]; // ���W���R�s�[
	}

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];   // �C���f�b�N�X���R�s�[
	}


	matWorld = MyMath::MakeIdentity();
}

void Sprite2D::Update(const MyMath::Vector3& pos, const MyMath::Vector3& rot, const MyMath::Vector3& scale, const MyMath::Vector4& color)
{
	//�J���[
	for (int i = 0; i < 4; i++)
	{
		vertMap[i].color = color;
	}

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

//�`��
void Sprite2D::Draw(Camera* camera)
{
	static_cast<void>(camera);
	constMapTransform->mat = matWorld * matProjection;

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

	// SRV�q�[�v�̐ݒ�R�}���h
	cmdList->SetDescriptorHeaps(1, srvHeap.GetAddressOf());

	//// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
	cmdList->SetGraphicsRootDescriptorTable(1, gpuHandle);

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(6, 1, 0, 0, 0);
}
