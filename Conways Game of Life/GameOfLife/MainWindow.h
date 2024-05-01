#pragma once
#include "wx/wx.h"
#include "Settings.h"
#include "SettingsDialog.h"
#include <vector>
#include <string>

class DrawingPanel;

class MainWindow : public wxFrame {
private:
	int _generationCount = 0;
	int _aliveCells = 0;
	std::string _fileName = "";
	std::vector<std::vector<bool>> _gameBoard;
	std::vector<std::vector<int>> _gameBoardNeighbors;

	wxMenuBar* _menuBar = nullptr;
	wxMenu* _menuOptions_Settings = nullptr;
	wxStatusBar* _statusBar = CreateStatusBar(3);
	wxToolBar* _toolBar = CreateToolBar();
	wxTimer* _timer = nullptr;
	wxBoxSizer* _boxSizer = new wxBoxSizer(wxVERTICAL);
	DrawingPanel* _drawingPanel = nullptr;
	wxMenuItem* _finite;
	wxMenuItem* _torodial;
	wxMenu* menuOption_View;

	Settings* _settings;

	void OnResize(wxSizeEvent& event);
	void OnPlay(wxCommandEvent& event);
	void OnPause(wxCommandEvent& event);
	void OnNext(wxCommandEvent& event);
	void OnTrash(wxCommandEvent& event);
	void OnTimer(wxTimerEvent& event);
	void OnMenuClick(wxCommandEvent& event);
	void OnRandomize(wxCommandEvent& event);
	void OnRandomizeSeed(wxCommandEvent& event);
	void OnNew(wxCommandEvent& event);
	void OnOpen(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);
	void OnSaveAs(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnFinite(wxCommandEvent& event);
	void OnToroidal(wxCommandEvent& event);
	void OnReset(wxCommandEvent& event);

	void GridInitialization();
	void UpdateStatusBar();
	void RandomGrid(int seed);
	void NextGeneration();
	bool WithinBound(int x, int y);
	int NeighborCount(int mainX, int mainY);

public:
	MainWindow();
	~MainWindow();

	void UpdateNeighborCount();

	wxDECLARE_EVENT_TABLE();
};