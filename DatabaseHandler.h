#ifndef DATABASE_HANDLER_H
#define DATABASE_HANDLER_H

#include <sqlite3.h>
#include <string>
#include <vector>

struct Credential {
    std::string appName;
    std::string username;
    std::string password;
};

class DatabaseHandler {
    sqlite3* db;
public:
    DatabaseHandler(const std::string& dbName) {
        if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
            throw std::runtime_error("Failed to open database.");
        }
        const char* createTableQuery = 
            "CREATE TABLE IF NOT EXISTS credentials ("
            "appName TEXT PRIMARY KEY, username TEXT, password TEXT);";
        sqlite3_exec(db, createTableQuery, nullptr, nullptr, nullptr);
    }

    ~DatabaseHandler() {
        sqlite3_close(db);
    }

    void addCredential(const std::string& appName, const std::string& username, const std::string& password) {
        const char* insertQuery = 
            "INSERT OR REPLACE INTO credentials (appName, username, password) VALUES (?, ?, ?);";
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, insertQuery, -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, appName.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, password.c_str(), -1, SQLITE_STATIC);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    void removeCredential(const std::string& appName) {
        const char* deleteQuery = "DELETE FROM credentials WHERE appName = ?;";
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, deleteQuery, -1, &stmt, nullptr);
        sqlite3_bind_text(stmt, 1, appName.c_str(), -1, SQLITE_STATIC);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    std::vector<Credential> listCredentials() {
        std::vector<Credential> credentials;
        const char* selectQuery = "SELECT appName, username, password FROM credentials;";
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, selectQuery, -1, &stmt, nullptr);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Credential cred;
            cred.appName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            cred.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            cred.password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            credentials.push_back(cred);
        }
        sqlite3_finalize(stmt);
        return credentials;
    }
};

#endif // DATABASE_HANDLER_H

