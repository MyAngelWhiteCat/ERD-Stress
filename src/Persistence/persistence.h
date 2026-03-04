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

            bool InstallStartupFolderPersistence();
            bool RemoveStartupFolderPersistence();

        private:
            PWSTR startup_folder_path_{NULL};
            IShellLinkW* shell_link_ptr_{ NULL };
            IPersistFile* exe_link_ptr_{ NULL };
            std::wstring current_exe_path_{MAX_PATH, '\0'};

            void SetupStartupFolderPath();
            void SetupComObject();
            void SetupCurrentPath();
            void SaveLinkToStartupFolder();
            
        };

    }

}