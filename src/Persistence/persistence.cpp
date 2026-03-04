#include "persistence.h"

#include <Windows.h>
#include <ShlObj.h>

#include <iostream>
#include <stdexcept>


namespace maltech {

    namespace persistence {

        bool PersistenceManager::InstallStartupFolderPersistence() {
            if (!startup_folder_path_) {
                SetupStartupFolderPath();
            }
            std::wcout << startup_folder_path_ << std::endl;
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