#pragma once
#include "Defines.h"
#include "Configs.h"

class CoursePanel : public wxPanel
{
public:
    CoursePanel(wxWindow* parent, const std::string& courseTitle, int editID, int courseID)
        : wxPanel(parent, wxID_ANY)
    {
        wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
        sizer->AddSpacer(10);

        courseLabel = new wxStaticText(this, wxID_ANY, courseTitle);
        sizer->Add(courseLabel, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
        sizer->AddSpacer(10);

        editButton = new wxButton(this, editID, "...", wxDefaultPosition, wxSize(20, wxDefaultSize.y));
        sizer->Add(editButton, 0, wxALIGN_CENTER_VERTICAL);
        sizer->AddSpacer(10);

        checkBox = new wxCheckBox(this, wxID_ANY, "");
        sizer->Add(checkBox, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);

        sizer->AddSpacer(10);
        this->SetSizer(sizer);
    }

    wxCheckBox* GetCheckBox() { return checkBox; }
    wxString GetCourseName() const { return courseLabel->GetLabel(); }

private:
    wxCheckBox* checkBox;
    wxStaticText* courseLabel;
    wxButton* editButton;
};