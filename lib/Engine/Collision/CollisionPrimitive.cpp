#include"CollisionPrimitive.h"

void Triangle::ComputeNormal()
{
	MyMath::Vector4 p0_p1 = p1 - p0;
	MyMath::Vector4 p0_p2 = p2 - p0;

	//�O�ςɂ��A2�ӂɐ����ȃx�N�g�����Z�o����
	normal = p0_p1.cross(p0_p2);
	normal.normalization();

}