#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "Vector2.h"
#include "Texture.h"
#include "TextureManager.h"

class GameObject
{
private:
	enum WORLDSPACE
	{
		local = 0,
		world = 1
	};

	std::string m_sTag;

	Vector2 m_v2Pos;
	Vector2 m_v2Dimensions;
	float m_fRotation;
	float m_fDeltaTime;

	bool m_bActive;
	GameObject* m_oParent;
	Texture* m_tTexture;
	TextureManager* m_tTextureManager;
public:
	//Constructors / Destructor.
	GameObject();
	GameObject(Vector2 a_v2Pos, Vector2 a_v2Dimensions, float a_fRotation, bool a_bActiveState, GameObject* a_oParent, TextureManager* a_tTextureManager, std::string texturePath);
	GameObject(float a_fX, float a_fY, float a_fWidth, float a_fHeight, float a_fRotation, bool a_bActiveState, GameObject* a_oParent, TextureManager* a_tTextureManager, std::string texturePath);
	~GameObject();

	//Getters
	Vector2 GetPos();
	Vector2 GetDimensions();
	float GetRotation();
	bool GetActiveState();
	GameObject* GetParentPtr();
	Texture* GetTexturePtr();
	TextureManager* GetTextureManager();
	std::string GetTag();

	//Setters
	void SetPos(Vector2 a_v2Position);
	void SetDimensions(Vector2 a_v2Dimensions);
	void SetRotation(float a_fRotation);
	void SetActiveState(bool a_bActiveState);
	void SetParent(GameObject* a_oParent);
	void SetTexturePath(std::string texturePath);
	void SetTag(std::string a_sTag);

	//Increase or decrease member variables by arguments.
	void TranslatePos(float a_fMovementX, float a_fMovementY);
	void TranslatePos(Vector2 a_v2Movement);
	void TransformDimensions(Vector2 a_v2DimensionChange);
	void TransformDimensions(float a_fWidthChange, float a_fHeightChange);
	void TransformRotation(float a_fRotationChange);

	//Other Methods
	void Update(float a_fDeltaTime);
};

#endif // !_GAMEOBJECT_H_
