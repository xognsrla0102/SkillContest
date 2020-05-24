#pragma once
class cRenderer : public cComponent
{
private:
	friend class cObject;
	cTexture* m_image;
	INT m_alpha;
private:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
public:
	cRenderer(cObject* Object);
	~cRenderer();

	cTexture* GetImage()
	{
		return m_image;
	}
	void SetImage(cTexture* Texture)
	{
		m_image = Texture;
	}

	INT GetAlpha()
	{
		return m_alpha;
	}
	void SetAlpha(INT Alpha)
	{
		m_alpha = Alpha;
	}
};

