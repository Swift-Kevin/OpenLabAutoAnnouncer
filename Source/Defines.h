#pragma once
// Include Neccessary Libs
#include "wx/wx.h"
#include "wx/datectrl.h"
#include <vector>
#include <map>

// Mem Leak Detection Code
#if defined _MSC_VER && defined _DEBUG
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define ENABLE_LEAK_DETECTION() _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF)
#else
#define ENABLE_LEAK_DETECTION()
#endif

struct CourseInfo {
	std::string title = "";
	std::string shorthand = "";
	std::string message = "";
	char group = ' ';
	bool isActive = false;
	int courseID = 0;
	std::string courseCode = "";
};


/*
	WX Widgets Defines for ID's
*/

#define EVENT_EditCourseButton 10001
