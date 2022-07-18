#include "MyMath.h"

namespace MyMath
{
	void SinCos(float& sin_, float& cos_, float angle)
	{
		sin_ = sin(angle);
		cos_ = cos(angle);
	}

	float ChangeRadians(const float& angle)
	{
		float radian = angle * AX_PIF / 180;
		return radian;
	}

	float ChangeDira(const float& angle)
	{
		float radian = angle * 180 / AX_PIF;
		return radian;
	}

	std::vector<std::string> getFileNames(std::string folderPath)
	{
		{
			std::filesystem::directory_iterator iter(folderPath), end;
			std::error_code err;
			std::vector<std::string> file_names;

			for (; iter != end && !err; iter.increment(err))
			{
				const std::filesystem::directory_entry entry = *iter;

				file_names.push_back(entry.path().string());
				printf("%s\n", file_names.back().c_str());
			}

			return file_names;
		}
	}

	Vector3 Vector3Trns(Vector3& vec, Matrix4& mat)
	{
		Vector3 retVec = {};

		retVec.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0];

		retVec.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1];

		retVec.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2];

		return retVec;
	}

	Vector4 Vector4Trns(Vector4& vec, Matrix4& mat)
	{
		Vector4 retVec = {};

		retVec.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + vec.w * mat.m[3][0];

		retVec.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + vec.w * mat.m[3][1];

		retVec.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + vec.w * mat.m[3][2];

		return retVec;
	}

}