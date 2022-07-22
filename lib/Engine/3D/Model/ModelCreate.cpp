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
		//�f�X�N�v���^�q�[�v����
		CreateDescriptorHeap();

		//�f�X�N�v���^�����W�ݒ�
		CreateDescriptorRange();

		//�p�C�v���C������
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
		//�f�X�N�v���^�q�[�v����
		CreateDescriptorHeap();

		//�f�X�N�v���^�����W�ݒ�
		CreateDescriptorRange();

		//�p�C�v���C������
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

	Microsoft::WRL::ComPtr<ID3DBlob> vsBlob = nullptr; // ���_�V�F�[�_�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob> psBlob = nullptr; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr; // �G���[�I�u�W�F�N�g

	// ���_�V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"Resources/Shaders/3D/Model/ModelBasicVS.hlsl", // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		"main", "vs_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		vsBlob.ReleaseAndGetAddressOf(), errorBlob.ReleaseAndGetAddressOf());

	// �G���[�Ȃ�
	if (FAILED(result))
	{
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string error;
		error.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	}

	// �s�N�Z���V�F�[�_�̓ǂݍ��݂ƃR���p�C��
	result = D3DCompileFromFile(
		L"Resources/Shaders/3D/Model/ModelBasicPS.hlsl", // �V�F�[�_�t�@�C����
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // �C���N���[�h�\�ɂ���
		"main", "ps_5_0", // �G���g���[�|�C���g���A�V�F�[�_�[���f���w��
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // �f�o�b�O�p�ݒ�
		0,
		psBlob.ReleaseAndGetAddressOf(), errorBlob.ReleaseAndGetAddressOf());

	// �G���[�Ȃ�
	if (FAILED(result))
	{
		// errorBlob����G���[���e��string�^�ɃR�s�[
		std::string error;
		error.resize(errorBlob->GetBufferSize());
		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			error.begin());
		error += "\n";
		// �G���[���e���o�̓E�B���h�E�ɕ\��
		OutputDebugStringA(error.c_str());
		assert(0);
	};

	// ���_���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[] =
	{
		// xyz���W
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		//�@���x�N�g��
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
		// uv���W
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,D3D12_APPEND_ALIGNED_ELEMENT,D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

	//���[�g�p�����[�^�̐ݒ�
	D3D12_ROOT_PARAMETER rootParams[4] = {};
	//�萔�o�b�t�@0��
	rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;//���
	rootParams[0].Descriptor.ShaderRegister = 0;//�萔�o�b�t�@�o�b�t�@�ԍ�
	rootParams[0].Descriptor.RegisterSpace = 0;//�f�t�H���g�l
	rootParams[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//�S�ẴV�F�[�_�[���猩����
	//�萔�o�b�t�@1��
	rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;//���
	rootParams[1].Descriptor.ShaderRegister = 1;//�萔�o�b�t�@�o�b�t�@�ԍ�
	rootParams[1].Descriptor.RegisterSpace = 0;//�f�t�H���g�l
	rootParams[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//�S�ẴV�F�[�_�[���猩����

	//�e�N�X�`�����W�X�^0��
	rootParams[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;//���
	rootParams[2].DescriptorTable.pDescriptorRanges = &modelShareVaria.descriptorRange;//�f�X�N�v���^�����W
	rootParams[2].DescriptorTable.NumDescriptorRanges = 1;//�f�X�N�v���^�����W��
	rootParams[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//�S�ẴV�F�[�_�[���猩����
	
																 //�萔�o�b�t�@2��
	rootParams[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;//���
	rootParams[3].Descriptor.ShaderRegister = 2;//�萔�o�b�t�@�o�b�t�@�ԍ�
	rootParams[3].Descriptor.RegisterSpace = 0;//�f�t�H���g�l
	rootParams[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;//�S�ẴV�F�[�_�[���猩����
	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};

	// �V�F�[�_�[�̐ݒ�
	pipelineDesc.VS.pShaderBytecode = vsBlob->GetBufferPointer();
	pipelineDesc.VS.BytecodeLength = vsBlob->GetBufferSize();
	pipelineDesc.PS.pShaderBytecode = psBlob->GetBufferPointer();
	pipelineDesc.PS.BytecodeLength = psBlob->GetBufferSize();

	// �T���v���}�X�N�̐ݒ�
	pipelineDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // �W���ݒ�

	// ���X�^���C�U�̐ݒ�
	pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK; // �J�����O���Ȃ�
	pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID; // �|���S�����h��Ԃ�
	pipelineDesc.RasterizerState.DepthClipEnable = true; // �[�x�N���b�s���O��L����

	// �u�����h�X�e�[�g
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = pipelineDesc.BlendState.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	//���ʐݒ�(�A���t�@�l)
	blenddesc.BlendEnable = true;// �u�����h��L��
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;//���Z
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;//�\�[�X�̒l��100%�g��
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;//�e�X�g�̒l��0%�g��

	// ����������
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;// ���Z
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;// �\�[�X�̃A���t�@�l
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;;// 1.0f-�\�[�X�̃A���t�@�l

	// ���_���C�A�E�g�̐ݒ�
	pipelineDesc.InputLayout.NumElements = _countof(inputLayout);
	pipelineDesc.InputLayout.pInputElementDescs = inputLayout;

	// �}�`�̌`��ݒ�
	pipelineDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	//D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE
	// //D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE
	//�f�v�X�X�e���V���X�e�[�g�̐ݒ�
	pipelineDesc.DepthStencilState.DepthEnable = true;//�[�x�e�X�g���s��
	pipelineDesc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;//�������݋���
	pipelineDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;//��������΍��i
	pipelineDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;//�[�x�t�H�[�}�b�g
	// ���̑��̐ݒ�
	pipelineDesc.NumRenderTargets = 1; // �`��Ώۂ�1��
	pipelineDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 0�`255�w���RGBA
	pipelineDesc.SampleDesc.Count = 1; // 1�s�N�Z���ɂ�1��T���v�����O

	//�e�N�X�`���T���v���[�̐ݒ�
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};
	samplerDesc.AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;//���J��Ԃ��i�^�C�����O�j
	samplerDesc.AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;//�c�J��Ԃ��i�^�C�����O�j
	samplerDesc.AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;//���s�J��Ԃ��i�^�C�����O�j
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;//�{�[�_�[�̎��͍�
	samplerDesc.Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;//�S�ă��j�A���
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;//�~�b�v�}�b�v�ő�l
	samplerDesc.MinLOD = 0.0f;//�~�b�v�}�b�v�ŏ��l
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;//�s�N�Z���V�F�[�_����̂ݎg�p�\

	// ���[�g�V�O�l�`��
	// ���[�g�V�O�l�`���̐ݒ�
	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams; //���[�g�p�����[�^�̐擪�A�h���X
	rootSignatureDesc.NumParameters = _countof(rootParams);        //���[�g�p�����[�^��
	rootSignatureDesc.pStaticSamplers = &samplerDesc;
	rootSignatureDesc.NumStaticSamplers = 1;

	// ���[�g�V�O�l�`���̃V���A���C�Y
	Microsoft::WRL::ComPtr<ID3DBlob> rootSigBlob = nullptr;
	result = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, rootSigBlob.ReleaseAndGetAddressOf(), errorBlob.ReleaseAndGetAddressOf());
	assert(SUCCEEDED(result));
	result = device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(modelShareVaria.rootSignature.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));
	// �p�C�v���C���Ƀ��[�g�V�O�l�`�����Z�b�g
	pipelineDesc.pRootSignature = modelShareVaria.rootSignature.Get();

	// �p�C�v�����X�e�[�g�̐���
	result = device->CreateGraphicsPipelineState(&pipelineDesc, IID_PPV_ARGS(modelShareVaria.pipelineState.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));
}

void ModelCreate::CreateDescriptorHeap()
{
	HRESULT result;
	Microsoft::WRL::ComPtr<ID3D12Device> device = DirectX12Core::GetInstance()->GetDevice();
	//SRV�̍ő��
	const size_t kMaxSRVCount = 2042;

	// �f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_���猩����悤��
	srvHeapDesc.NumDescriptors = kMaxSRVCount;

	// �ݒ������SRV�p�f�X�N���v�^�q�[�v�𐶐�
	result = device->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(modelShareVaria.srvHeap.ReleaseAndGetAddressOf()));
	assert(SUCCEEDED(result));
}

void ModelCreate::CreateDescriptorRange()
{
	modelShareVaria.descriptorRange.NumDescriptors = 1;//1�x�̕`��Ɏg���e�N�X�`�����ꖇ�Ȃ̂�
	modelShareVaria.descriptorRange.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	modelShareVaria.descriptorRange.BaseShaderRegister = 0;//�e�N�X�`�����W�X�^0��
	modelShareVaria.descriptorRange.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
}