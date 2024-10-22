#include <iostream>
#include <fstream>
#include <vector>
#include <zlib.h>

std::vector<char> decompressFile(const std::string& filename) {
    // Open the compressed file
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file");
    }

    // Read the compressed data into a buffer
    std::vector<char> compressedData((std::istreambuf_iterator<char>(file)), {});
    file.close();

    // Prepare a buffer for the decompressed data
    std::vector<char> decompressedData(compressedData.size() * 2); // Allocate more space initially

    // Decompress the data
    z_stream strm = {};
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    if (inflateInit(&strm) != Z_OK) {
        throw std::runtime_error("inflateInit failed");
    }

    strm.avail_in = compressedData.size();
    strm.next_in = reinterpret_cast<Bytef*>(compressedData.data());
    strm.avail_out = decompressedData.size();
    strm.next_out = reinterpret_cast<Bytef*>(decompressedData.data());

    int result = inflate(&strm, Z_NO_FLUSH);
    if (result != Z_STREAM_END) {
        inflateEnd(&strm);
        throw std::runtime_error("inflate failed");
    }

    // Resize the decompressed data to the actual size
    decompressedData.resize(decompressedData.size() - strm.avail_out);

    inflateEnd(&strm);
    return decompressedData;
}

int main() {
    try {
        std::string filename = "file.gz"; // Replace with your compressed file
        std::vector<char> decompressedData = decompressFile(filename);
        
        // Use the decompressed data (e.g., print it)
        std::cout.write(decompressedData.data(), decompressedData.size());
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
