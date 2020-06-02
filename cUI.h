#pragma once
class cUI abstract
{
public:
	cUI() {}
	virtual ~cUI() {}

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Release() PURE;
	virtual void Render() PURE;
};

