#include "Camera.h"



Camera::Camera(FbxCamera* camera)
{
	SetData(camera);
}


Camera::~Camera()
{
}

void Camera::SetData(FbxCamera * camera)
{
	m_position.x = (float)camera->Position.Get().mData[0];
	m_position.y = (float)camera->Position.Get().mData[1];
	m_position.z = (float)camera->Position.Get().mData[2];

	m_upVector.x = (float)camera->UpVector.Get().mData[0];
	m_upVector.y = (float)camera->UpVector.Get().mData[1];
	m_upVector.z = (float)camera->UpVector.Get().mData[2];

	m_lookAt.x = (float)camera->InterestPosition.Get().mData[0];
	m_lookAt.y = (float)camera->InterestPosition.Get().mData[1];
	m_lookAt.z = (float)camera->InterestPosition.Get().mData[2];

	m_aspectRatio.x = (float)camera->AspectWidth.Get();
	m_aspectRatio.y = (float)camera->AspectHeight.Get();

	m_FOV = (float)camera->FieldOfView.Get();

	m_nearPlane = (float)camera->NearPlane.Get();
	m_farPlane = (float)camera->FarPlane.Get();

}

glm::vec3 Camera::GetPosition()
{
	return m_position;
}

glm::vec3 Camera::GetUpVector()
{
	return m_upVector;
}

glm::vec3 Camera::GetLookAt()
{
	return m_lookAt;
}

glm::vec2 Camera::GetAspectRatio()
{
	return m_aspectRatio;
}

float Camera::GetFOV()
{
	return m_FOV;
}

float Camera::GetNearPlane()
{
	return m_nearPlane;
}

float Camera::GetFarPlane()
{
	return m_farPlane;
}
