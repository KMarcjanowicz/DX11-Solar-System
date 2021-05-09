////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "pointlightclass.h"

PointLightClass::PointLightClass()
{
}


PointLightClass::PointLightClass(const PointLightClass& other)
{
}


PointLightClass::~PointLightClass()
{
}


void PointLightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = XMFLOAT4(red, green, blue, alpha);
	return;
}


void PointLightClass::SetPosition(float x, float y, float z)
{
	m_position = XMFLOAT4(x, y, z, 1.0f);
	return;
}


XMFLOAT4 PointLightClass::GetDiffuseColor()
{
	return m_diffuseColor;
}


XMFLOAT4 PointLightClass::GetPosition()
{
	return m_position;
}