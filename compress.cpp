#include <iostream>
#include <vector>
#include <zlib.h>

/*
sudo apt install zlib1g

*/

bool compressToMemoryStream(const std::vector<unsigned char>& input, std::vector<unsigned char>& output) {
    uLongf compressedSize = compressBound(input.size());
    output.resize(compressedSize);

    int result = compress(output.data(), &compressedSize, input.data(), input.size());
    if (result != Z_OK) {
        std::cerr << "Compression failed with error: " << result << std::endl;
        return false;
    }

    output.resize(compressedSize); // Resize to actual compressed size
    return true;
}

int main() {
    // Beispielinhalt, den wir komprimieren möchten
    std::vector<unsigned char> data = { /* ... deine Daten hier ... */ };

    std::vector<unsigned char> compressedData;
    if (compressToMemoryStream(data, compressedData)) {
        std::cout << "Compressed size: " << compressedData.size() << " bytes" << std::endl;
    } else {
        std::cerr << "Compression failed." << std::endl;
    }

    return 0;
}
