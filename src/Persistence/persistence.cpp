#include "persistence.h"

#include <Windows.h>
#include <ShlObj.h>

#include <iostream>


namespace maltech {

    namespace persistence {

        bool PersistenceManager::InstallStartupFolderPersistence() {
            PWSTR path;
            SHGetKnownFolderPath(FOLDERID_Startup, 0, NULL, &path);
            std::wcout << *path << std::endl;
            CoTaskMemFree(path);
        }

        bool PersistenceManager::RemoveStartupFolderPersistence() {
            return false;
        }

    }

}