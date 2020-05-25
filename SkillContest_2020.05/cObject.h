#pragma once
#include "cComponent.h"

enum OBJ_Tag
{
	PLAYER,
	ENEMY,
	MID_BOSS,
	LAST_BOSS,
	BULLET,
	ITEM,
	OBJTAG_NUM
};

class cObject
{
	friend class cObjectManager;
	friend class cComponent;
private:
	VEC2 m_pos = VEC2(0, 0);
	VEC2 m_scale = VEC2(1, 1);
	OBJ_Tag m_tag;
	string  m_name;
	INT     m_depth = 0;
	BOOL    m_destroy = FALSE;
	BOOL    m_enable = TRUE;
	FLOAT   m_rot = 0;

	list<cComponent*> m_components;

	void Init() {}
	void Update() {}
	void Render() {}
	void Release();
public:
	cObject() {}
	~cObject() {}

	template <typename T>
	T* GetComponent()
	{
 	  	for (auto iter : m_components)
 		{
 			if (typeid(*iter) == typeid(T))
			{
				return static_cast<T*>(iter);
			}
		}
		return nullptr;
	}

	template <typename T>
	T* AddComponent()
	{
		if (GetComponent<T>() != nullptr)
			return nullptr;

		T* component = new T(this);
		m_components.push_back(component);
		component->Init();
		return component;
	}

	void Translate(VEC2 pos)
	{
		m_pos += pos;
	}

	void Rot(FLOAT degree)
	{
		m_rot += degree;
	}

	void Scale(VEC2 scale)
	{
		m_scale += scale;
	}

	void Destroy()
	{
		m_destroy = TRUE;
	}

	BOOL GetDestroy()
	{
		return m_destroy;
	}

	VEC2 GetPos()
	{
		return m_pos;
	}

	FLOAT GetRot()
	{
		return m_rot;
	}

	VEC2 GetScale()
	{
		return m_scale;
	}

	OBJ_Tag GetTag()
	{
		return m_tag;
	}

	BOOL GetEnable()
	{
		return m_enable;
	}

	string GetName()
	{
		return m_name;
	}

	void SetPos(VEC2 pos)
	{
		m_pos = pos;
	}

	void SetRot(FLOAT rotate)
	{
		m_rot = rotate;
	}

	void SetScale(VEC2 scale)
	{
		m_scale = scale;
	}

	void SetTag(OBJ_Tag objTag)
	{
		m_tag = objTag;
	}

	void SetEnable(BOOL enable)
	{
		m_enable = enable;
	}

	void SetName(string name)
	{
		m_name = name;
	}
};

