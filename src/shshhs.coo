#include <zip.h>
#include <iostream>
#include <fstream>

void extractFile(zip_t* archive, const char* filename) {
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(archive, filename, 0, &st);

    zip_file_t* zf = zip_fopen(archive, filename, 0);
    char* contents = new char[st.size];
    zip_fread(zf, contents, st.size);
    zip_fclose(zf);

    std::ofstream outFile(filename, std::ios::binary);
    outFile.write(contents, st.size);
    outFile.close();

    delete[] contents;
}

void extractAllFiles(const char* zipFilePath) {
    int err = 0;
    zip_t* archive = zip_open(zipFilePath, 0, &err);
    if (!archive) {
        std::cerr << "Failed to open ZIP archive: " << zipFilePath << std::endl;
        return;
    }

    zip_int64_t numFiles = zip_get_num_entries(archive, 0);
    for (zip_int64_t i = 0; i < numFiles; ++i) {
        const char* filename = zip_get_name(archive, i, 0);
        if (filename) {
            extractFile(archive, filename);
        }
    }

    zip_close(archive);
}

int main() {
    const char* zipFilePath = "example.zip";
    extractAllFiles(zipFilePath);
    std::cout << "All files extracted!" << std::endl;
    return 0;
}
