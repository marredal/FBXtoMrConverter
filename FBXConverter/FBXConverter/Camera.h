#ifndef __CAMERA_H__
#define	__CAMERA_H__

#include <fbxsdk.h>
#include <glm.hpp>



class Camera
{
public:
	//::..Constructor, Destructor does nothing..:://
	Camera(FbxCamera* camera);
	virtual ~Camera();


	//::..Set Functions..:://
	void SetData(FbxCamera* camera);

	//::..Get Functions..:://
	glm::vec3 GetPosition();
	glm::vec3 GetUpVector();
	glm::vec3 GetLookAt();
	glm::vec2 GetAspectRatio();
	float GetFOV();
	float GetNearPlane();
	float GetFarPlane();

private:
	glm::vec3 m_position;
	glm::vec3 m_upVector;
	glm::vec3 m_lookAt;
	glm::vec2 m_aspectRatio;
	float	  m_FOV;
	float	  m_nearPlane;
	float	  m_farPlane;

};

#endif // !__CAMERA_H__