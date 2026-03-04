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
            SetupComObject();
            std::wcout << startup_folder_path_ << std::endl;
            CoUninitialize();
            return true;
        }

        bool PersistenceManager::RemoveStartupFolderPersistence() {
            return false;
        }

        void PersistenceManager::SetupStartupFolderPath() {
            HRESULT hr = SHGetKnownFolderPath(FOLDERID_Startup, 0, NULL, &startup_folder_path_);
            if (!SUCCEEDED(hr)) {
                throw std::runtime_error("Can't set setup startup folder");
            }
        }

        void PersistenceManager::SetupComObject() {
            HRESULT hr = CoCreateInstance(
                CLSID_ShellLink,
                NULL,
                CLSCTX_INPROC_SERVER,
                IID_IShellLinkW,
                (LPVOID*)&shell_link_ptr_
            );
            if (!SUCCEEDED(hr)) {
                throw std::runtime_error("Can't set setup COM object");
            }
        }

    }

}