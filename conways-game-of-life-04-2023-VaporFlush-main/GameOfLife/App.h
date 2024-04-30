#pragma once

#include "wx/wx.h"

class App : public wxApp
{
private:

public:
	App();
	~App();
	virtual bool OnInit();
};

