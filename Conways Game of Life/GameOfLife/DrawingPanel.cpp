#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"
#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
EVT_PAINT(DrawingPanel::OnPaint)
EVT_LEFT_UP(DrawingPanel::OnMouseUp)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxWindow* parentWindow, std::vector<std::vector<bool>>& parentGameBoard, Settings* parentSettings, std::vector<std::vector<int>>& parentNeighbors)
	: wxPanel(parentWindow), _gameBoard(parentGameBoard), _settings(parentSettings), _gameBoardNeighbors(parentNeighbors) {
	SetBackgroundStyle(wxBG_STYLE_PAINT);
	dummyWindow = parentWindow;
}

DrawingPanel::~DrawingPanel() {}

void DrawingPanel::SetSize(const wxSize& size) {
	wxPanel::SetSize(size);
	Refresh();
}

void DrawingPanel::SetGridSize(int size) {
	_settings->gridSize = size;
	Refresh();
}

void DrawingPanel::OnPaint(wxPaintEvent& event) {
	wxAutoBufferedPaintDC dc(this);
	dc.Clear();

	if (!_settings) {
		return;
	}

	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);
	if (!gc) {
		return;
	}

	const wxColour& livingColor = _settings->getLivingColor();
	const wxColour& deadColor = _settings->getDeadColor();

	gc->SetPen(wxPen(wxColor(0, 0, 0)));

	float clientHeight = static_cast<float>(GetClientSize().GetHeight());
	float clientWidth = static_cast<float>(GetClientSize().GetWidth());
	float cellHeight = clientHeight / _settings->gridSize;
	float cellWidth = clientWidth / _settings->gridSize;

	for (int i = 0; i < _settings->gridSize; ++i) {
		for (int j = 0; j < _settings->gridSize; ++j) {
			if (_gameBoard[i][j]) {
				gc->SetBrush(livingColor);
			}
			else {
				gc->SetBrush(deadColor);
			}

			float drawX = j * cellWidth;
			float drawY = i * cellHeight;
			gc->DrawRectangle(drawX, drawY, cellWidth, cellHeight);

			if (_settings->showNeighborCount && _gameBoardNeighbors[i][j] > 0) {
				gc->SetFont(wxFontInfo(cellHeight/2.5), *wxRED);
				wxString count = wxString::Format("%d", _gameBoardNeighbors[i][j]);
				gc->DrawText(count, drawX + cellWidth / 2.2, drawY + cellHeight / 2.75);
			}
		}
	}

	delete gc;
}

void DrawingPanel::OnMouseUp(wxMouseEvent& event) {
	int gridSize = _settings->gridSize;
	float clientHeight = static_cast<float>(GetClientSize().GetHeight());
	float clientWidth = static_cast<float>(GetClientSize().GetWidth());
	float cellHeight = clientHeight / gridSize;
	float cellWidth = clientWidth / gridSize;


	int x = event.GetX() / cellWidth;
	int y = event.GetY() / cellHeight;

	if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
		_gameBoard[y][x] = !_gameBoard[y][x];
	}

	MainWindow* neighborWindow = dynamic_cast<MainWindow*>(dummyWindow);
	if (neighborWindow != nullptr)
	{
		neighborWindow->UpdateNeighborCount();
	}
		Refresh();
}
