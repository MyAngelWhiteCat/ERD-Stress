#pragma once 

#include <Windows.h>

namespace maltech {

    namespace persistence {

        class PersistenceManager {
        public:
            ~PersistenceManager() {
                CoTaskMemFree(startup_folder_path_);
                if (shell_link_ptr_) {
                    shell_link_ptr_->Release();
                }
            }

            bool InstallStartupFolderPersistence();
            bool RemoveStartupFolderPersistence();

        private:
            PWSTR startup_folder_path_{NULL};
            IShellLinkW* shell_link_ptr_{ NULL };

            void SetupStartupFolderPath();
            void SetupComObject();

        };

    }

}