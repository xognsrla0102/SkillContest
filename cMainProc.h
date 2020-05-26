#pragma once
class cMainProc
{
public:
	cMainProc();
	~cMainProc();
	
	void Update();
	void Render();

	void ResetDevice();
	void LostDevice();
};

