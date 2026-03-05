#pragma once 

#include <Windows.h>
#include <ShObjIdl_core.h>
#include <string>

namespace maltech {

    namespace persistence {

        using namespace std::literals;

        class PersistenceManager {
        public:
            ~PersistenceManager() {
                CoTaskMemFree(startup_folder_path_);
                if (shell_link_ptr_) {
                    shell_link_ptr_->Release();
                }
                if (exe_link_ptr_) {
                    exe_link_ptr_->Release();
                }
            }

            void InstallStartupFolderPersistence();
            void RemoveStartupFolderPersistence();

        private:
            PWSTR startup_folder_path_{NULL};
            IShellLinkW* shell_link_ptr_{ NULL };
            IPersistFile* exe_link_ptr_{ NULL };
            std::wstring current_exe_path_;
            std::wstring startup_file_path_;

            void SetupStartupFolderPath();
            void SetupStartupFilePath();
            void SetupComObject();
            void SetupCurrentPath();
            void SaveLinkToStartupFolder();
            
        };

    }

}