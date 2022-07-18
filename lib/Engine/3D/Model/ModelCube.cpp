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
	//���_�o�b�t�@�E�C���f�b�N�X����
	CreatVertexIndexBuffer();

	//�萔�o�b�t�@����(3D���W�ϊ��s��)
	DirectX12Core::GetInstance()->CreateConstBuff(constMapTransform, constBuffTransform);

	// ���_�f�[�^
	//����
	PosUvColor tmp = { { -1.0f, -1.0f, -1.0f }, {}, { 0.0f, 1.0f }, { 1.0f,1.0f,1.0f,1.0f } };//����C���f�b�N�X0
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f,-1.0f},{},{ 0.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//�����C���f�b�N�X1
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f,-1.0f},{},{ 1.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//�E��C���f�b�N�X2
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f,-1.0f},{},{ 1.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//�E���C���f�b�N�X3
	vertices.push_back(tmp);

	//�E
	tmp = { { 1.0f,-1.0f,-1.0f},{},{ 0.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//����C���f�b�N�X4
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f,-1.0f},{},{ 0.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//�����C���f�b�N�X5
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f, 1.0f},{},{ 1.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//�E��C���f�b�N�X6
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f, 1.0f},{},{ 1.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//�E���C���f�b�N�X7
	vertices.push_back(tmp);

	//��
	tmp = { {-1.0f,-1.0f, 1.0f},{},{ 0.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//����C���f�b�N�X8
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f, 1.0f},{},{ 0.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//�����C���f�b�N�X9
	vertices.push_back(tmp);
	tmp = { {-1.0f,-1.0f,-1.0f},{},{ 1.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//�E��C���f�b�N�X10
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f,-1.0f},{},{ 1.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//�E���C���f�b�N�X11
	vertices.push_back(tmp);
	
	//��
	tmp = { { 1.0f,-1.0f, 1.0f},{},{ 0.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//����C���f�b�N�X12
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f, 1.0f},{},{ 0.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//�����C���f�b�N�X13
	vertices.push_back(tmp);
	tmp = { {-1.0f,-1.0f, 1.0f},{},{ 1.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//�E��C���f�b�N�X14
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f, 1.0f},{},{ 1.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//�E���C���f�b�N�X15
	vertices.push_back(tmp);

	//��
	tmp = { {-1.0f, 1.0f,-1.0f},{},{ 0.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//����C���f�b�N�X16
	vertices.push_back(tmp);
	tmp = { {-1.0f, 1.0f, 1.0f},{},{ 0.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//�����C���f�b�N�X17
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f,-1.0f},{},{ 1.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//�E��C���f�b�N�X18
	vertices.push_back(tmp);
	tmp = { { 1.0f, 1.0f, 1.0f},{},{ 1.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//�E���C���f�b�N�X19
	vertices.push_back(tmp);

	//��
	tmp = { {-1.0f,-1.0f, 1.0f},{},{ 0.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//����C���f�b�N�X20
	vertices.push_back(tmp);
	tmp = { {-1.0f,-1.0f,-1.0f},{},{ 0.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//�����C���f�b�N�X21
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f, 1.0f},{},{ 1.0f, 1.0f},{1.0f,1.0f,1.0f,1.0f} };//�E��C���f�b�N�X22
	vertices.push_back(tmp);
	tmp = { { 1.0f,-1.0f,-1.0f},{},{ 1.0f, 0.0f},{1.0f,1.0f,1.0f,1.0f} };//�E���C���f�b�N�X23
	vertices.push_back(tmp);

// �C���f�b�N�X�f�[�^

	//����
	indices.push_back(0), indices.push_back(1), indices.push_back(3);//0
	indices.push_back(3), indices.push_back(2), indices.push_back(0);//1

	//�E
	indices.push_back(4), indices.push_back(5), indices.push_back(7);//2
	indices.push_back(7), indices.push_back(6), indices.push_back(4);//3

	//��
	indices.push_back(8), indices.push_back(9), indices.push_back(11);//4
	indices.push_back(11), indices.push_back(10), indices.push_back(8);//5

	//��
	indices.push_back(12), indices.push_back(13), indices.push_back(15);//6
	indices.push_back(15), indices.push_back(14), indices.push_back(12);//7

	//��
	indices.push_back(16), indices.push_back(17), indices.push_back(19);//8
	indices.push_back(19), indices.push_back(18), indices.push_back(16);//9

	//��
	indices.push_back(20), indices.push_back(21), indices.push_back(23);//10
	indices.push_back(23), indices.push_back(22), indices.push_back(20);//11

	for (size_t i = 0; i < cubeMaxIndex / 3; i++)
	{
		//�O�p�`1���ƂɌv�Z���Ă���
		//�O�p�`�̃C���f�b�N�X�����o���āA�ꎞ�I�ȕϐ��ɓ����
		unsigned short Index0 = indices[i * 3 + 0];
		unsigned short Index1 = indices[i * 3 + 1];
		unsigned short Index2 = indices[i * 3 + 2];
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

void ModelCube::SetTexture(const wchar_t* filePath)
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

void ModelCube::Update(const MyMath::Vector3& pos, const MyMath::Vector3& rot, const MyMath::Vector3& scale, const MyMath::Vector4& color)
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

MyMath::Matrix4& ModelCube::GetMatWorld()
{
	return matWorld;
}


void ModelCube::Draw(Camera* camera)
{
	assert(camera);
	constMapTransform->mat = matWorld * camera->GetViewMatrixInv() * camera->GetProjectionMatrix();

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

	// SRV�q�[�v�̐擪�ɂ���SRV�����[�g�p�����[�^1�Ԃɐݒ�
	cmdList->SetGraphicsRootDescriptorTable(1, gpuHandle);

	// �`��R�}���h
	cmdList->DrawIndexedInstanced(maxIndex, 1, 0, 0, 0);

}

const std::vector<uint16_t> ModelCube::GetIndices()
{
	return indices;
}

void ModelCube::CreateShaderResourceView()
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

void ModelCube::CreatVertexIndexBuffer()
{
	// �q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	// ���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};

	// ���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(PosUvColor) * maxVert);

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

void ModelCube::CreatTextureBuffer()
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
