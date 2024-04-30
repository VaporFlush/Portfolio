#pragma once

#include <wx/wx.h>
#include <wx/graphics.h>
#include <vector>
#include "Settings.h"

class DrawingPanel : public wxPanel 
{
private:
	std::vector<std::vector<bool>>& _gameBoard;
	std::vector<std::vector<int>>& _gameBoardNeighbors;
	Settings* _settings;
	wxWindow* dummyWindow = nullptr;

	void OnPaint(wxPaintEvent& event);
	void OnMouseUp(wxMouseEvent& event);

	wxDECLARE_EVENT_TABLE();

public:
	DrawingPanel(wxWindow*, std::vector<std::vector<bool>>&, Settings*, std::vector<std::vector<int>>&);
	virtual ~DrawingPanel();

	void SetSize(const wxSize& size);
	void SetGridSize(int size);
};