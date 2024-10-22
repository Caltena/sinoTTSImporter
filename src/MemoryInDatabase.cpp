#include <iostream>
#include <fstream>
#include <vector>
#include <sqlite3.h>

// Function to read a file into a memory buffer
std::vector<char> readFileToMemory(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file");
    }
    return std::vector<char>((std::istreambuf_iterator<char>(file)), {});
}

// Function to store binary data in SQLite
void storeDataInDatabase(const std::string& dbFilename, const std::string& tableName, const std::vector<char>& data) {
    sqlite3* db;
    sqlite3_open(dbFilename.c_str(), &db);

    // Create table if it doesn't exist
    std::string createTableSQL = "CREATE TABLE IF NOT EXISTS " + tableName + " (id INTEGER PRIMARY KEY, data BLOB);";
    sqlite3_exec(db, createTableSQL.c_str(), nullptr, nullptr, nullptr);

    // Prepare SQL statement
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO " + tableName + " (data) VALUES (?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    // Bind the data
    sqlite3_bind_blob(stmt, 1, data.data(), data.size(), SQLITE_STATIC);

    // Execute the statement
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

// Function to retrieve binary data from SQLite
std::vector<char> retrieveDataFromDatabase(const std::string& dbFilename, const std::string& tableName, int id) {
    sqlite3* db;
    sqlite3_open(dbFilename.c_str(), &db);

    // Prepare SQL statement
    sqlite3_stmt* stmt;
    const char* sql = ("SELECT data FROM " + tableName + " WHERE id = ?;").c_str();
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    // Bind the ID
    sqlite3_bind_int(stmt, 1, id);

    // Execute and retrieve the data
    std::vector<char> data;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const void* blob = sqlite3_column_blob(stmt, 0);
        int size = sqlite3_column_bytes(stmt, 0);
        data.assign(static_cast<const char*>(blob), static_cast<const char*>(blob) + size);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return data;
}

int main() {
    try {
        std::string dbFilename = "example.db"; // Database file name
        std::string tableName = "MyTable";      // Table name
        std::string fileToStore = "example.txt"; // File to read

        // Read file into memory
        std::vector<char> fileData = readFileToMemory(fileToStore);

        // Store the data in the database
        storeDataInDatabase(dbFilename, tableName, fileData);
        std::cout << "Data stored successfully." << std::endl;

        // Retrieve data back from the database
        std::vector<char> retrievedData = retrieveDataFromDatabase(dbFilename, tableName, 1);
        std::cout << "Retrieved " << retrievedData.size() << " bytes of data." << std::endl;

        // Optionally, write the retrieved data back to a file
        std::ofstream outFile("retrieved_example.txt", std::ios::binary);
        outFile.write(retrievedData.data(), retrievedData.size());
        outFile.close();
        std::cout << "Data written to retrieved_example.txt." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
