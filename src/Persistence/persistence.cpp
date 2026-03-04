#include "persistence.h"

#include <Windows.h>
#include <ShlObj.h>
#include <objbase.h>

#include <iostream>
#include <stdexcept>


namespace maltech {

    namespace persistence {

        bool PersistenceManager::InstallStartupFolderPersistence() {
            if (!startup_folder_path_) {
                SetupStartupFolderPath();
            }
            CoInitialize(NULL);
            IShellLinkW* pShellLink{ NULL };
            HRESULT hr = CoCreateInstance(
                CLSID_ShellLink,
                NULL,
                CLSCTX_INPROC_SERVER,
                IID_IShellLinkW,
                (LPVOID*)&pShellLink
            );
            std::wcout << startup_folder_path_ << std::endl;
            CoUninitialize();
            return true;
        }

        bool PersistenceManager::RemoveStartupFolderPersistence() {
            return false;
        }

        void PersistenceManager::SetupStartupFolderPath() {
            HRESULT hr = SHGetKnownFolderPath(FOLDERID_Startup, 0, NULL, &startup_folder_path_);
            if (hr != S_OK) {
                throw std::runtime_error("Can't set setup startup folder");
            }
        }

    }

}