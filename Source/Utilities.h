#pragma once
#include <string>
#pragma warning(disable : 4996)
#include <chrono>

static enum SuffixType {
    Default,
    ShortTime = 't',
    LongTime = 'T',
    ShortDate = 'd',
    LongDate = 'D',
    ShortDateAndTime = 'f',
    LongDateAndTime = 'F',
    RelativeTime = 'R'
} suffix;

class Utils
{
private:

public:
    static void SetSuffixType(SuffixType option) 
    {
        suffix = option;
    }

	static std::string GetCurrTime()
	{
        return GetTimeFromOffset();
	}

    static std::string GetTimeFromOffset(int _hour = 0, int _min = 0, int _day = 0)
    {
        // Get the current time
        auto now = std::chrono::system_clock::now();
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm local_time = *std::localtime(&now_time_t); // Convert to local time

        local_time.tm_hour = _hour;
        local_time.tm_min = _min;
        local_time.tm_wday = _day;

        // Convert back to time_t (epoch time)
        std::time_t target_time_t = std::mktime(&local_time);
        auto target_epoch = static_cast<std::int64_t>(target_time_t);

        // Create the Discord timestamp
        std::string retVal = "<t:" + std::to_string(target_epoch) + ":" + (char)suffix + ">";

        return retVal;
    }
};