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

        };

    }

}