#include "MainWindow.h"
#include "DrawingPanel.h"
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"
#include "wx/numdlg.h"
#include "wx/filedlg.h"

#define Play_ID 1001
#define Pause_ID 1002
#define Next_ID 1003 
#define Trash_ID 1004
#define Timer_ID 1005
#define MenuOption_Settings_ID 1006
#define MenuOption_Randomize_ID 1007
#define MenuOption_RandomizeSeed_ID 1008
#define MenuOption_File_New_ID 1009
#define MenuOption_File_Open_ID 1010
#define MenuOption_File_Save_ID 1011
#define MenuOption_File_SaveAs_ID 1012
#define MenuOption_File_Exit_ID 1013
#define MenuOption_View_Finite_ID 1014
#define MenuOption_View_Torodial_ID 1015
#define MenuOption_Settings_Reset_ID 1016

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_SIZE(MainWindow::OnResize)
EVT_MENU(Play_ID, MainWindow::OnPlay)
EVT_MENU(Pause_ID, MainWindow::OnPause)
EVT_MENU(Next_ID, MainWindow::OnNext)
EVT_MENU(Trash_ID, MainWindow::OnTrash)
EVT_TIMER(Timer_ID, MainWindow::OnTimer)
EVT_MENU(MenuOption_Settings_ID, MainWindow::OnMenuClick)
EVT_MENU(MenuOption_Randomize_ID, MainWindow::OnRandomize)
EVT_MENU(MenuOption_RandomizeSeed_ID, OnRandomizeSeed)
EVT_MENU(MenuOption_File_New_ID, MainWindow::OnNew)
EVT_MENU(MenuOption_File_Open_ID, MainWindow::OnOpen)
EVT_MENU(MenuOption_File_Save_ID, MainWindow::OnSave)
EVT_MENU(MenuOption_File_SaveAs_ID, MainWindow::OnSaveAs)
EVT_MENU(MenuOption_File_Exit_ID, MainWindow::OnExit)
EVT_MENU(MenuOption_View_Finite_ID, MainWindow::OnFinite)
EVT_MENU(MenuOption_View_Torodial_ID, MainWindow::OnToroidal)
EVT_MENU(MenuOption_Settings_Reset_ID, MainWindow::OnReset)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Game of Life", wxPoint(500, 250), wxSize(800, 550))
{
	_settings = new Settings();
	_settings->LoadData();

	_menuBar = new wxMenuBar();

	_menuOptions_Settings = new wxMenu();

	_menuOptions_Settings->Append(MenuOption_Settings_ID, "Settings");
	_menuOptions_Settings->Append(MenuOption_Settings_Reset_ID, "Reset");

	wxMenu* menuOption_Random = new wxMenu();

	menuOption_Random->Append(MenuOption_Randomize_ID, "Randomize");
	menuOption_Random->Append(MenuOption_RandomizeSeed_ID, "Randomize With Seed");

	wxMenu* menuOption_File = new wxMenu();

	menuOption_File->Append(MenuOption_File_New_ID, "New");
	menuOption_File->Append(MenuOption_File_Open_ID, "Open");
	menuOption_File->Append(MenuOption_File_Save_ID, "Save");
	menuOption_File->Append(MenuOption_File_SaveAs_ID, "Save As");
	menuOption_File->Append(MenuOption_File_Exit_ID, "Exit");

	menuOption_View = new wxMenu();

	_finite = new wxMenuItem(menuOption_File, MenuOption_View_Finite_ID, "Finite", "", wxITEM_CHECK);
	_torodial = new wxMenuItem(menuOption_File, MenuOption_View_Torodial_ID, "Doughnut", "", wxITEM_CHECK);

	_finite->SetCheckable(true);
	_torodial->SetCheckable(true);

	menuOption_View->Append(_finite);
	menuOption_View->Append(_torodial);

	_finite->Check(!_settings->isDoughnutMode);
	_torodial->Check(_settings->isDoughnutMode);

	_menuBar->Append(menuOption_File, "&File");
	_menuBar->Append(_menuOptions_Settings, "&Options");
	_menuBar->Append(menuOption_Random, "&Randomize");
	_menuBar->Append(menuOption_View, "&View");

	SetMenuBar(_menuBar);
	_drawingPanel = new DrawingPanel(this, _gameBoard, _settings, _gameBoardNeighbors);
	_boxSizer->Add(_drawingPanel, 1, wxEXPAND | wxALL);

	int widths[] = { -1, 80, 80 };
	_statusBar->SetStatusWidths(3, widths);
	_statusBar->SetStatusText("", 0);
	_statusBar->SetStatusText("Alive cells: 0", 1);
	_statusBar->SetStatusText("Generation: 0", 2);

	_toolBar->AddTool(Play_ID, "Play", wxBitmap(play_xpm));
	_toolBar->AddTool(Pause_ID, "Pause", wxBitmap(pause_xpm));
	_toolBar->AddTool(Next_ID, "Next", wxBitmap(next_xpm));
	_toolBar->AddTool(Trash_ID, "Clear", wxBitmap(trash_xpm));
	_toolBar->Realize();

	SetToolBar(_toolBar);

	GridInitialization();

	_timer = new wxTimer(this, Timer_ID);
}

MainWindow::~MainWindow()
{
	if (_settings != nullptr) {
		_settings->SaveData();
		delete _settings;
	}

	if (_timer != nullptr)
		delete _timer;

	_gameBoard.clear();
	_gameBoardNeighbors.clear();
}

void MainWindow::GridInitialization()
{
	_gameBoard.resize(_settings->gridSize);

	for (int i = 0; i < _settings->gridSize; i++)
		_gameBoard[i].resize(_settings->gridSize);

	_gameBoardNeighbors.resize(_gameBoard.size());
	for (int i = 0; i < _gameBoard.size(); i++)
		_gameBoardNeighbors[i].resize(_gameBoard.size());


	_drawingPanel->SetGridSize(_settings->gridSize);
}

void MainWindow::UpdateStatusBar()
{
	wxString statusText = "Alive cells: " + wxString::Format("%d", _aliveCells);
	GetStatusBar()->SetStatusText(statusText, 1);
	statusText = "Generation: " + wxString::Format("%d", _generationCount);
	GetStatusBar()->SetStatusText(statusText, 2);
}

void MainWindow::OnResize(wxSizeEvent& event)
{
	wxSize size = GetClientSize();
	if (_drawingPanel != nullptr)
		_drawingPanel->SetSize(size);
}

void MainWindow::OnPlay(wxCommandEvent& event)
{
	_timer->Start(_settings->interval);
}

void MainWindow::OnPause(wxCommandEvent& event)
{
	_timer->Stop();
}

void MainWindow::OnNext(wxCommandEvent& event)
{
	NextGeneration();
}

void MainWindow::OnTrash(wxCommandEvent& event)
{
	_timer->Stop();
	for (int i = 0; i < _gameBoard.size(); i++)
	{
		for (int j = 0; j < _gameBoard[i].size(); j++)
		{
			_gameBoard[i][j] = false();
		}
	}
	_aliveCells = 0;
	_generationCount = 0;
	UpdateNeighborCount();
	UpdateStatusBar();
	_drawingPanel->Refresh();
}

void MainWindow::OnTimer(wxTimerEvent& event)
{
	NextGeneration();
}

bool MainWindow::WithinBound(int x, int y)
{
	if (_settings->isDoughnutMode)
	{
		if (x < 0)
			x = _settings->gridSize - 1;
		if (x >= _settings->gridSize)
			x = 0;
		if (y < 0)
			y = _settings->gridSize - 1;
		if (y >= _settings->gridSize)
			y = 0;
		return true;
	}
	else
	{
		return x >= 0 && x < _settings->gridSize && y >= 0 && y < _settings->gridSize;
	}
}

void MainWindow::OnRandomize(wxCommandEvent& event)
{
	std::srand(std::time(nullptr));
	RandomGrid(std::rand());
}

int MainWindow::NeighborCount(int mainX, int mainY)
{
	int result = 0;
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++)
		{
			if (x == 0 && y == 0)
				continue;
			if (_settings->isDoughnutMode)
			{
				if (WithinBound(mainX + x, mainY + y))
					result += _gameBoard[(mainY + y + _settings->gridSize) % _settings->gridSize][(mainX + x + _settings->gridSize) % _settings->gridSize];
			}
			else
			{
				if (WithinBound(mainX + x, mainY + y))
					result += _gameBoard[mainY + y][mainX + x];
			}
		}
	}
	return result;
}

void MainWindow::OnRandomizeSeed(wxCommandEvent& event)
{
	RandomGrid(wxGetNumberFromUser("0 up to 2147483647.", "Input Seed:", "Randomize", 0, 0, LONG_MAX));
	
}

void MainWindow::NextGeneration()
{
	std::vector<std::vector<bool>> sandBox = _gameBoard;
	_aliveCells = 0;

	for (int i = 0; i < sandBox.size(); i++)
		for (int j = 0; j < sandBox[i].size(); j++) {
			int neighborCount = NeighborCount(i, j);

			if (neighborCount < 2 || neighborCount > 3)
				sandBox[j][i] = false;

			else if (neighborCount == 3)
				sandBox[j][i] = true;

			if (_gameBoard[j][i])
				_aliveCells++;
		}

	_gameBoard = sandBox;
	_generationCount++;
	UpdateNeighborCount();
	UpdateStatusBar();
	_drawingPanel->Refresh();
}

void MainWindow::UpdateNeighborCount()
{
	for (int i = 0; i < _gameBoardNeighbors.size(); i++)
		for (int j = 0; j < _gameBoardNeighbors[i].size(); j++) {
			_gameBoardNeighbors[i][j] = NeighborCount(j, i);
		}
}

void MainWindow::OnMenuClick(wxCommandEvent& event)
{
	_timer->Stop();
	SettingsDialog* test = new SettingsDialog(this, "Settings", _settings);
	if (test->ShowModal() == wxID_OK) {
		GridInitialization();
		_drawingPanel->Refresh();
	}
	delete test;
}

void MainWindow::RandomGrid(int seed)
{
	std::srand(seed);
	for (int i = 0; i < _gameBoard.size(); i++) {
		for (int j = 0; j < _gameBoard[i].size(); j++)
		{
			if ((std::rand() % 100) < _settings->randomAmount)
			{
				_gameBoard[i][j] = true;
			}
			else
			{
				_gameBoard[i][j] = false;
			}
		}
	}
	_drawingPanel->Refresh();
}

void MainWindow::OnNew(wxCommandEvent& event)
{
	_gameBoard.clear();
	_gameBoardNeighbors.clear();
	_fileName.clear();
	_generationCount = 0;
	_aliveCells = 0;
	GridInitialization();
	UpdateStatusBar();
}

void MainWindow::OnOpen(wxCommandEvent& event)
{
	wxFileDialog openFileDialog(this, _("Open .cells file"), "", "",
		"Cells files (*.cells)|*.cells", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	_fileName = openFileDialog.GetPath().ToStdString();

	// Read file and update game board
	std::ifstream file(_fileName);
	std::string line;
	_gameBoard.clear();

	while (std::getline(file, line)) {
		if (line[0] == '!') // Ignore comments
			continue;

		std::vector<bool> row;

		for (const auto& c : line) {
			if (c == '*') {
				row.push_back(true);
				_aliveCells++;
			}
			else {
				row.push_back(false);
			}
		}

		_gameBoard.push_back(row);
	}

	// Update board dimensions
	int width = _gameBoard[0].size();
	int height = _gameBoard.size();
	_drawingPanel->SetGridSize(width);
	_gameBoardNeighbors.resize(height, std::vector<int>(width, 0));

	// Refresh screen and status bar
	_generationCount = 0;
	GridInitialization();
	UpdateNeighborCount();
	UpdateStatusBar();
	_drawingPanel->Refresh();
}

void MainWindow::OnSave(wxCommandEvent& event)
{
	if (_fileName.empty()) {
		OnSaveAs(event);
	}
	else {
		std::ofstream file(_fileName);

		for (const auto& row : _gameBoard) {
			for (const auto& cell : row) {
				file << (cell ? "*" : ".");
			}

			file << std::endl;
		}
	}
}

void MainWindow::OnSaveAs(wxCommandEvent& event)
{
	wxFileDialog saveFileDialog(this, _("Save .cells file"), "", "",
		"Cells files (*.cells)|*.cells", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;

	_fileName = saveFileDialog.GetPath().ToStdString();
	OnSave(event);
}

void MainWindow::OnExit(wxCommandEvent& event)
{
	Close();
}

void MainWindow::OnFinite(wxCommandEvent& event)
{
	_finite->Check();
	_torodial->Check(false);
	_settings->isDoughnutMode = false;
	_drawingPanel->Refresh();
}

void MainWindow::OnToroidal(wxCommandEvent& event)
{
	_finite->Check(false);
	_torodial->Check();
	_settings->isDoughnutMode = true;
	_drawingPanel->Refresh();
}

void MainWindow::OnReset(wxCommandEvent& event)
{
	_settings->livingRed = 128;
	_settings->livingGreen = 128;
	_settings->livingBlue = 128;
	_settings->livingAlpha = 255;
	_settings->deadRed = 255;
	_settings->deadGreen = 255;
	_settings->deadBlue = 255;
	_settings->deadAlpha = 255;

	_settings->gridSize = 15;
	GridInitialization();
	_settings->interval = 50;
	_settings->randomAmount = 55;

	_settings->showNeighborCount = false;
	_settings->isDoughnutMode = false;
	_drawingPanel->Refresh();
	Refresh();
	OnTrash(event);
}