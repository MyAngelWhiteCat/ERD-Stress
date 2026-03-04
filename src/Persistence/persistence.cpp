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
            HRESULT hr = CoInitialize(NULL);
            if (!SUCCEEDED(hr)) {
                throw std::runtime_error("Can't initialize COM");
            }

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

        void PersistenceManager::SetupStartupFilePath() {
            startup_file_path_ = *startup_folder_path_ + L"MalwareVaccine.lnk";
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

            SetupCurrentPath();
            shell_link_ptr_->SetPath(current_exe_path_.data());
        }

        void PersistenceManager::SetupCurrentPath() {
            DWORD size = GetModuleFileNameW(
                NULL,
                current_exe_path_.data(),
                MAX_PATH
            );

            while (size == MAX_PATH) {
                current_exe_path_.resize(current_exe_path_.size() * 2);
                size = GetModuleFileNameW(
                    NULL,
                    current_exe_path_.data(),
                    current_exe_path_.size()
                );
            }

            if (size == 0) {
                throw std::runtime_error("Can't get current exe path");
            }

            current_exe_path_.resize(size);
        }

    }

}