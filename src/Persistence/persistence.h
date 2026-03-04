#pragma once 

#include <Windows.h>
#include <ShlObj.h>

namespace maltech {

    namespace persistence {

        class PersistenceManager {
        public:
            bool InstallStartupFolderPersistence();
            bool RemoveStartupFolderPersistence();

        private:
            PWSTR startup_folder_path_;

            void SetupStartupFolderPath();

        };

    }

}