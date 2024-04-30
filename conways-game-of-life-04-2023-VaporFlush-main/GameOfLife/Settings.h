#ifndef SETTINGS_H
#define SETTINGS_H

#include <wx/wx.h>
#include<fstream>

struct Settings {
    unsigned int livingRed = 128;
    unsigned int livingGreen = 128;
    unsigned int livingBlue = 128;
    unsigned int livingAlpha = 255;
    unsigned int deadRed = 255;
    unsigned int deadGreen = 255;
    unsigned int deadBlue = 255;
    unsigned int deadAlpha = 255;

    int gridSize = 15;
    int interval = 50;
    int randomAmount = 55;
    
    bool showNeighborCount = false;
    bool isDoughnutMode = false;

    wxColor getLivingColor() const {
        return wxColor(livingRed, livingGreen, livingBlue, livingAlpha);
    }

    wxColor getDeadColor() const {
        return wxColor(deadRed, deadGreen, deadBlue, deadAlpha);
    }

    void setLivingColor(const wxColor& color) {
        livingRed = color.Red();
        livingGreen = color.Green();
        livingBlue = color.Blue();
        livingAlpha = color.Alpha();
    }

    void setDeadColor(const wxColor& color) {
        deadRed = color.Red();
        deadGreen = color.Green();
        deadBlue = color.Blue();
        deadAlpha = color.Alpha();
    }

    void LoadData()
    {
        std::ifstream file("settings.bin", std::ios::binary | std::ios::in);
        file.read((char*)this, sizeof(Settings));
        file.close();
    }

    void SaveData()
    {
        std::ofstream file("settings.bin", std::ios::out | std::ios::binary);
        file.write((char*)this, sizeof(Settings));
        file.close();
    }
};

#endif // SETTINGS_H
