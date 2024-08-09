#include <iostream>
#include <conio.h> 
#include <Windows.h>

#include "code.hpp"

Cleaning clean;
Aesthetic aesthetic;

int main()
{
    code.IntializeWindowFormat(57, 21);
    code.displayLogo();

    code.print("Press any key to renew your OS.");
    _getch();

    console.Clear();
    code.displayLogo();
    
    SetConsoleTitle("lunatic.os | can take some minutes.");

    code.print("Lunatic started the process, be patient.");
    console.Spacing(true);

    optimizer.DisableUnnecessaryFeatures(); // Disable most of useless settings
    code.print("Disabling unnecessary features..");
    console.Spacing(true);
    Sleep(1000);

    optimizer.optimizeWindowsStartMenu();
    code.print("Managing Windows Start Menu..");
    console.Spacing(true);
    Sleep(1000);

    optimizer.DisableTaskbarElements(); // Disable useless taskbar things like Cortana, etc..
    code.print("Disabling taskbar elements..");
    console.Spacing(true);
    Sleep(1000);

    optimizer.disableIPv6(); // Disable IPV6 since nobody use that
    code.print("Managing network..");
    console.Spacing(true);
    Sleep(1000);

    optimizer.configureBootSettings(); // Optimizer msconfig settings
    code.print("Managing boot settings..");
    console.Spacing(true);
    

    clean.uninstallMicrosoftApps(); // uninstall all useless apps
    code.print("Uninstalled useless application(s)..");
    console.Spacing(true);
    Sleep(1000);

    clean.cleanFiles(); // removing temp, journals, logs folders
    code.print("Managing useless file(s)..");
    console.Spacing(true);
    Sleep(1000);

    code.print("Changing aesthetic..");

    aesthetic.setCursorToBlack(); // Modern black cursor from https://vsthemes.org
    aesthetic.setBackground(); // classic flat background

    optimizer.RestartExplorer(); // to apply all 

    console.Spacing(true);
    Sleep(1000);

    SetConsoleTitle("lunatic.os");

    code.print("Lunatic finished his job.");
    console.Spacing(false);
    code.print("NOTE: We recommend to restart your PC.");

    Sleep(-1);
}

