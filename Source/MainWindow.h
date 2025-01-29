#pragma once
#include "Defines.h"
#include "Configs.h"
#include "CoursePanel.h"

class MainWindow : public wxFrame
{
private:
	Configs config;

	// Overall Sizers
	wxBoxSizer* mainBoxSizer = nullptr;
	wxBoxSizer* coursesSidebarSizer = nullptr;

	// Announcement Maker
	wxBoxSizer* rightPanelSizer = nullptr;
	wxTextCtrl* announcementInput = nullptr;
	wxTextCtrl* announcementOutput = nullptr;
	wxButton* copyButton = nullptr;

	int winWidth = 0, winHeight = 0;
	
	std::map<std::string, CourseInfo> coursemap;

	void InitAppFromConfig();
	void AddCourseSection(CourseInfo& course);
	void AddAnnouncementMaker();
	void ReadCoursesToButtons();

public:
	MainWindow();
	~MainWindow();

	void Event_EditingCourse(wxCommandEvent& event);
	void Event_CopyAnnouncement(wxCommandEvent& event);
	void Event_UpdateAnnouncement(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

