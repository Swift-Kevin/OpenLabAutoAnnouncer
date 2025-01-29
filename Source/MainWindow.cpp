#include "MainWindow.h"

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_BUTTON(EVENT_EditCourseButton, MainWindow::Event_EditingCourse)
wxEND_EVENT_TABLE()

MainWindow::MainWindow() : wxFrame(nullptr, wxID_ANY, "Application", wxPoint(50, 50), wxSize(50, 50))
{
	InitAppFromConfig();

	mainBoxSizer = new wxBoxSizer(wxHORIZONTAL);
	mainBoxSizer->SetMinSize(wxSize(winWidth * 0.5f, winHeight));
	coursesSidebarSizer = new wxBoxSizer(wxVERTICAL);

	ReadCoursesToButtons();
	AddAnnouncementMaker();

	mainBoxSizer->Add(coursesSidebarSizer);
	this->SetSizerAndFit(mainBoxSizer);
	this->Layout();
}

MainWindow::~MainWindow()
{
}

void MainWindow::InitAppFromConfig()
{
	std::string winTitle = config.at("Project").at("title").as<std::string>();
	winWidth = config.at("Project").at("winWidth").as<int>();
	winHeight = config.at("Project").at("winHeight").as<int>();

	SetTitle(winTitle);
	SetSize(wxSize(winWidth, winHeight));
}

void MainWindow::AddCourseSection(CourseInfo& course)
{
	CoursePanel* coursePanel = new CoursePanel(this, course.title, EVENT_EditCourseButton, course.courseID);
	coursesSidebarSizer->Add(coursePanel, 0, wxEXPAND | wxALL, 2);
}

void MainWindow::AddAnnouncementMaker()
{
	rightPanelSizer = new wxBoxSizer(wxVERTICAL);
	
	// Input field for announcement message
	announcementInput = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(300, 50), wxTE_MULTILINE);
	rightPanelSizer->Add(new wxStaticText(this, wxID_ANY, "Enter Announcement:"), 0, wxLEFT | wxTOP, 5);
	rightPanelSizer->Add(announcementInput, 0, wxEXPAND | wxALL, 5);

	// Display generated announcement
	announcementOutput = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(300, 50), wxTE_READONLY | wxTE_MULTILINE);
	rightPanelSizer->Add(new wxStaticText(this, wxID_ANY, "Generated Announcement:"), 0, wxLEFT | wxTOP, 5);
	rightPanelSizer->Add(announcementOutput, 0, wxEXPAND | wxALL, 5);

	// Copy Button
	copyButton = new wxButton(this, wxID_ANY, "Copy to Clipboard");
	rightPanelSizer->Add(copyButton, 0, wxALIGN_CENTER | wxALL, 5);

	// Bind event
	copyButton->Bind(wxEVT_BUTTON, &MainWindow::Event_CopyAnnouncement, this);

	// Add right panel to main layout
	mainBoxSizer->Add(rightPanelSizer, 1, wxEXPAND | wxLEFT, 10);

	announcementInput->Bind(wxEVT_TEXT, &MainWindow::Event_UpdateAnnouncement, this, announcementInput->GetId());

}

void MainWindow::ReadCoursesToButtons()
{
	for (const auto& pItem : config)
	{
		if (pItem.second.contains("shorthand"))
		{
			CourseInfo course;
			ini::IniSection& section = config.at(pItem.first);
			course.title = section.at("title").as<std::string>();
			course.shorthand = section.at("shorthand").as<std::string>();
			course.message = section.at("message").as<std::string>();
			course.group = section.at("group").as<char>();
			course.courseCode = section.at("courseCode").as<std::string>();

			int courseID = Utils::CustomSTOI(course.courseCode.c_str(), course.courseCode.size());
			course.courseID = courseID;

			coursemap[course.courseCode] = course;
			AddCourseSection(course);
		}
	}
}

void MainWindow::Event_EditingCourse(wxCommandEvent& event)
{
}

void MainWindow::Event_CopyAnnouncement(wxCommandEvent& event)
{
	if (OpenClipboard(nullptr)) {
		EmptyClipboard();

		size_t strSize = strlen(announcementOutput->GetValue().c_str()) + 1;
		
		HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, strSize);
		if (hData) {
			char* pchData = (char*)GlobalLock(hData);
			strcpy_s(pchData, strSize, announcementOutput->GetValue().c_str());
			GlobalUnlock(hData);

			SetClipboardData(CF_TEXT, hData);
		}

		CloseClipboard();

	}
}

void MainWindow::Event_UpdateAnnouncement(wxCommandEvent& event)
{
	std::string selectedCourses;
	for (auto& [key, course] : coursemap)
	{
		if (course.isActive)
		{
			selectedCourses += "@" + course.shorthand + " ";
		}
	}

	std::string announcementText = selectedCourses + "\n# " + announcementInput->GetValue().ToStdString() +
		"\nNext open lab is at " + Utils::GetTimeFromOffset(4);

	announcementOutput->SetValue(announcementText);
}
