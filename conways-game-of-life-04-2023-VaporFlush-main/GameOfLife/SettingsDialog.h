#include "wx/wx.h"
#include <wx/spinctrl.h>
#include <wx/clrpicker.h>
#include "Settings.h"

class SettingsDialog : public wxDialog
{
public:
    SettingsDialog(wxWindow* parent, wxString title, Settings* settingsWindow);
    ~SettingsDialog();

private:
    // Event table declaration
    wxDECLARE_EVENT_TABLE();

    // Settings object pointer
    Settings* m_settings;
    Settings* dummySettings;

    // Spin controls
    wxSpinCtrl* m_spinCtrl1;
    wxSpinCtrl* m_spinCtrl2;
    wxSpinCtrl* m_spinCtrl3;

    // Color picker controls
    wxColourPickerCtrl* m_colorPicker1;
    wxColourPickerCtrl* m_colorPicker2;

    // NeighborCount control
    wxCheckBox* m_checkbox1;
    void OnCheckboxClicked(wxCommandEvent& event);

    // Event handlers for spin controls
    void OnSpinCtrl1(wxSpinEvent& event);
    void OnSpinCtrl2(wxSpinEvent& event);
    void OnSpinCtrl3(wxSpinEvent& event);

    // Event handlers for color picker controls
    void OnColorPicker1Changed(wxColourPickerEvent& event);
    void OnColorPicker2Changed(wxColourPickerEvent& event);

    void OnCancel(wxCommandEvent& event);

    // Button sizer
    wxSizer* m_buttonSizer;
};
