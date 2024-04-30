#include "SettingsDialog.h"

#define Setting_Interval_ID 2001
#define Setting_GridSize_ID 2002
#define Setting_LivingColour_ID 2003
#define Setting_DeadColour_ID 2004
#define Setting_NeighborCount_ID 2005
#define Setting_RandomChance_ID 2006
#define Setting_Reset_ID 2007

wxBEGIN_EVENT_TABLE(SettingsDialog, wxDialog)
EVT_SPINCTRL(Setting_Interval_ID, SettingsDialog::OnSpinCtrl1)
EVT_SPINCTRL(Setting_GridSize_ID, SettingsDialog::OnSpinCtrl2)
EVT_COLOURPICKER_CHANGED(Setting_LivingColour_ID, SettingsDialog::OnColorPicker1Changed)
EVT_COLOURPICKER_CHANGED(Setting_DeadColour_ID, SettingsDialog::OnColorPicker2Changed)
EVT_BUTTON(wxID_CANCEL, SettingsDialog::OnCancel)
EVT_CHECKBOX(Setting_NeighborCount_ID, SettingsDialog::OnCheckboxClicked)
EVT_SPINCTRL(Setting_RandomChance_ID, SettingsDialog::OnSpinCtrl3)
wxEND_EVENT_TABLE()

SettingsDialog::SettingsDialog(wxWindow* parent, wxString title, Settings* settingsWindow)
	: wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(200,300))
{
	m_settings = settingsWindow;
	dummySettings = new Settings();
	*dummySettings = *m_settings;

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	SetSizer(mainSizer);

	wxBoxSizer* settingSizer1 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* label1 = new wxStaticText(this, wxID_ANY, "Interval:");
	m_spinCtrl1 = new wxSpinCtrl(this, Setting_Interval_ID);
	m_spinCtrl1->SetRange(1, 1000);
	m_spinCtrl1->SetValue(m_settings->interval);
	settingSizer1->Add(label1, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	settingSizer1->Add(m_spinCtrl1, 0, wxALIGN_CENTER_VERTICAL);
	mainSizer->Add(settingSizer1, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* settingSizer2 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* label2 = new wxStaticText(this, wxID_ANY, "Grid Size:");
	m_spinCtrl2 = new wxSpinCtrl(this, Setting_GridSize_ID);
	m_spinCtrl2->SetRange(1, 100);
	m_spinCtrl2->SetValue(m_settings->gridSize);
	settingSizer2->Add(label2, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	settingSizer2->Add(m_spinCtrl2, 0, wxALIGN_CENTER_VERTICAL);
	mainSizer->Add(settingSizer2, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* settingSizer3 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* label3 = new wxStaticText(this, wxID_ANY, "Living Cells:");
	m_colorPicker1 = new wxColourPickerCtrl(this, Setting_LivingColour_ID);
	m_colorPicker1->SetColour(m_settings->getLivingColor());
	settingSizer3->Add(label3, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	settingSizer3->Add(m_colorPicker1, 0, wxALIGN_CENTER_VERTICAL);
	mainSizer->Add(settingSizer3, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* settingSizer4 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* label4 = new wxStaticText(this, wxID_ANY, "Dead Cells:");
	m_colorPicker2 = new wxColourPickerCtrl(this, Setting_DeadColour_ID);
	m_colorPicker2->SetColour(m_settings->getDeadColor());
	settingSizer4->Add(label4, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	settingSizer4->Add(m_colorPicker2, 0, wxALIGN_CENTER_VERTICAL);
	mainSizer->Add(settingSizer4, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* settingSizer5 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* label5 = new wxStaticText(this, wxID_ANY, "Show Neighbor Count:");
	m_checkbox1 = new wxCheckBox(this, Setting_NeighborCount_ID, "");
	m_checkbox1->SetValue(m_settings->showNeighborCount);
	settingSizer5->Add(label5, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	settingSizer5->Add(m_checkbox1, 0, wxALIGN_CENTER_VERTICAL);
	mainSizer->Add(settingSizer5, 0, wxEXPAND | wxALL, 5);

	wxBoxSizer* settingSizer6 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* label6 = new wxStaticText(this, wxID_ANY, "Random Chance:");
	m_spinCtrl3 = new wxSpinCtrl(this, Setting_RandomChance_ID);
	m_spinCtrl3->SetRange(1, 100);
	m_spinCtrl3->SetValue(m_settings->randomAmount);
	settingSizer6->Add(label6, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
	settingSizer6->Add(m_spinCtrl3, 0, wxALIGN_CENTER_VERTICAL);
	mainSizer->Add(settingSizer6, 0, wxEXPAND | wxALL, 5);

	wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
	mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxALL, 10);
}

SettingsDialog::~SettingsDialog()
{

}

void SettingsDialog::OnSpinCtrl1(wxSpinEvent& event)
{
	m_settings->interval = event.GetInt();
}

void SettingsDialog::OnSpinCtrl2(wxSpinEvent& event)
{
	m_settings->gridSize = event.GetInt();
}

void SettingsDialog::OnSpinCtrl3(wxSpinEvent& event)
{
	m_settings->randomAmount = event.GetInt();
}

void SettingsDialog::OnColorPicker1Changed(wxColourPickerEvent& event)
{
	m_settings->setLivingColor(event.GetColour());
}

void SettingsDialog::OnColorPicker2Changed(wxColourPickerEvent& event)
{
	m_settings->setDeadColor(event.GetColour());
}

void SettingsDialog::OnCancel(wxCommandEvent& event)
{
	*m_settings = *dummySettings;
	EndDialog(wxID_CANCEL);
}

void SettingsDialog::OnCheckboxClicked(wxCommandEvent& event)
{
	m_settings->showNeighborCount = m_checkbox1->GetValue();
	Refresh();
}