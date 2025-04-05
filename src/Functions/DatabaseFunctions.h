#pragma once
#include <sqlite3.h>
#include <Item.h>
#include <vector>

int openDatabase(const char* dbName, sqlite3** db);

void closeDatabase(sqlite3* db);

void executeQuery(sqlite3* db, const char* Query);

int readRow(void* Data, int columns, char** columnValues, char** columnNames);

void readTable(sqlite3* db, const char* tableName);

void searchItem(sqlite3*db, const char* input, std::vector<Item>& vector);

void addItem(sqlite3*db, Item& item);

void deleteItem(sqlite3*db, int id, const char* name);

void updateQuantity(sqlite3*db, int id, const char* itemName, int quantity);

void updateReference(sqlite3*db, int id, const char* itemName, const char* newReference);

void updateCode(sqlite3*db, int id, const char* itemName, const char* newCode);

void updateCapacity(sqlite3*db, int id, const char* itemName, double newCapacity);

void updateLine(sqlite3*db, int id, const char* itemName, const char* newLine);

void updateName(sqlite3*db, int id, const char* itemName, const char* newName);

void updateImagePath(sqlite3*db, int id, const char* itemName, const char* newPath);