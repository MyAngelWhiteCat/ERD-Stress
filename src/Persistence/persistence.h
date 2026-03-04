#pragma once 

#include <Windows.h>

namespace maltech {

    namespace persistence {

        class PersistenceManager {
        public:
            ~PersistenceManager() {
                CoTaskMemFree(startup_folder_path_);
            }

            bool InstallStartupFolderPersistence();
            bool RemoveStartupFolderPersistence();

        private:
            PWSTR startup_folder_path_;

            void SetupStartupFolderPath();

        };

    }

}