#include "Model.h"

Light* Model::light = nullptr;

void Model::SetLight(Light* light_)
{
	light = light_;
}
