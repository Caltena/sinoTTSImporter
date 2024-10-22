#include <iostream>
#include <vector>
#include <fstream>
#include "miniz.h" // Include miniz header

std::vector<char> decompressZipToMemory(const std::string& zipFilename, const std::string& fileInZip) {
    // Open the ZIP archive
    mz_zip_archive zipArchive;
    memset(&zipArchive, 0, sizeof(zipArchive));

    if (!mz_zip_reader_init_file(&zipArchive, zipFilename.c_str(), 0)) {
        throw std::runtime_error("Failed to open ZIP file");
    }

    // Check if the file exists in the ZIP archive
    if (!mz_zip_reader_locate_file(&zipArchive, fileInZip.c_str(), nullptr, 0)) {
        mz_zip_reader_end(&zipArchive);
        throw std::runtime_error("File not found in ZIP archive");
    }

    // Get the file info
    mz_zip_archive_file_stat fileStat;
    if (!mz_zip_reader_file_stat(&zipArchive, 0, &fileStat)) {
        mz_zip_reader_end(&zipArchive);
        throw std::runtime_error("Failed to get file stat");
    }

    // Allocate buffer for the decompressed data
    std::vector<char> decompressedData(fileStat.m_uncompressed_size);

    // Read the file into the buffer
    if (!mz_zip_reader_extract_to_mem(&zipArchive, 0, decompressedData.data(), decompressedData.size(), 0)) {
        mz_zip_reader_end(&zipArchive);
        throw std::runtime_error("Failed to extract file");
    }

    // Clean up
    mz_zip_reader_end(&zipArchive);
    return decompressedData;
}

int main() {
    try {
        std::string zipFilename = "archive.zip"; // Replace with your ZIP file name
        std::string fileInZip = "file.txt"; // Replace with the file you want to extract

        std::vector<char> decompressedData = decompressZipToMemory(zipFilename, fileInZip);
        
        // Use the decompressed data (e.g., print it)
        std::cout.write(decompressedData.data(), decompressedData.size());
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
