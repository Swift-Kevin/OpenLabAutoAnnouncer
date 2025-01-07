#include <iostream>
#include <string>
#include "Configs.h"
#include "Utilities.h"

int main()
{
    std::cout << "Open Lab Auto Announcement Maker\n====================\n\n";

    Configs config;

    // Output the result
    Utils::SetSuffixType(SuffixType::LongDateAndTime);

    std::cout << Utils::GetCurrentTime() << std::endl;
}
