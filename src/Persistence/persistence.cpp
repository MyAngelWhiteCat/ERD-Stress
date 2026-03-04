#include "persistence.h"

#include <Windows.h>
#include <ShlObj.h>

#include <iostream>
#include <stdexcept>


namespace maltech {

    namespace persistence {

        bool PersistenceManager::InstallStartupFolderPersistence() {
            PWSTR path;
            SHGetKnownFolderPath(FOLDERID_Startup, 0, NULL, &path);
            std::wcout << path << std::endl;
            CoTaskMemFree(path);
            return true;
        }

        bool PersistenceManager::RemoveStartupFolderPersistence() {
            return false;
        }

        void PersistenceManager::SetupStartupFolderPath() {
            HRESULT success = SHGetKnownFolderPath(FOLDERID_Startup, 0, NULL, &startup_folder_path_);
            if (success != S_OK) {
                throw std::runtime_error("Can't set setup startup folder");
            }
        }

    }

}