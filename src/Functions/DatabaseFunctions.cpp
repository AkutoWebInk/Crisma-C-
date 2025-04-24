#include <sqlite3.h>
#include <iostream>
#include <vector>
#include "DatabaseFunctions.h"


int openDatabase(const char* dbName, sqlite3** db){
    
    int OpenConnection = sqlite3_open(dbName, db);
    
    if (OpenConnection ==SQLITE_OK){
        std::cout << "\nDatabase connection successfully initialized.\n"<<std::endl;
    } else{
        std::cerr<< "\nError initializing database connection: \n"<<sqlite3_errmsg(*db)<<std::endl;
    }
    return OpenConnection;
}

void closeDatabase(sqlite3* db){
    if (db!=nullptr){

        int closeResult = sqlite3_close(db);
        
        if (closeResult == SQLITE_OK){
            std::cout<< "\nDatabase connection successfully terminated. " <<std::endl;
        } else{
            std::cerr << "\nError terminating Database connection: \n" <<sqlite3_errmsg(db);
        }
    }
}

void executeQuery(sqlite3* db, const char* Query){
    char* SQLerror = 0;
    if (sqlite3_exec(db, Query, 0,0, &SQLerror) != SQLITE_OK){
        std::cerr<< "\nDev. note: error running executeQuery( ): \n" <<SQLerror<<std::endl;
        sqlite3_free(SQLerror);
        sqlite3_close(db);
    }else{
        std::cout<< "Dev. note: executeQuery( ) ran successfully." << std::endl;
    }
}

int readRow(void* Data, int columns, char** columnValues, char** columnNames){
    //std::cout<< "Dev. note: read() ran successfully. \n" <<std::endl;
    for(int i=0; i<columns; i++){
        std::cout << columnValues[i] << " ";
    }
    std::cout<< std::endl;
    return 0;
}

void readTable(sqlite3* db, const char* tableName){
    std::string table = tableName;     //Converts to an std::string (C++ string)
    std::string query = "SELECT * FROM " +  table +";";     //Concat the full query
    
    const char* SQLquery = query.c_str();     //Turns the query into a full string 
    char* SQLerror;
    
    if(sqlite3_exec(db, SQLquery, readRow, 0, &SQLerror) != SQLITE_OK){
        std::cerr << "\nDev. note: error running sqlite3_exec( ) inside readTable( ). " << std::endl;
        sqlite3_free(SQLerror);
        sqlite3_close(db);
    }
}

void addItem(sqlite3*db, Item& item){
    char* SQLerror=0;
    sqlite3_stmt * STMTquery;
    // ID is passed as null  since SQL handles INT AUTOINCREMENT values.
    std::string itemName = item.getName();
    std::string itemReference = item.getReference();
    std::string itemCode = item.getCode();
    std::string itemLine = item.getLine();
    double itemCapacity = item.getCapacity();
    int itemQuantity = item.getQuantity();
    std::string itemImagePath = item.getImagePath();

    const char* query = "INSERT INTO item(id, name, reference, code, line, capacity, quantity, imagepath) VALUES(?,?,?,?,?,?,?,?);";
    if(sqlite3_prepare_v2(db, query, -1, &STMTquery, NULL) == SQLITE_OK){
        sqlite3_bind_null(STMTquery, 1); // Null in the first "?" since it's the item ID that SQL will autoincrement.
        sqlite3_bind_text(STMTquery, 2, itemName.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(STMTquery, 3, itemReference.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(STMTquery, 4, itemCode.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(STMTquery, 5, itemLine.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_double(STMTquery, 6, itemCapacity);
        sqlite3_bind_int(STMTquery, 7, itemQuantity);
        sqlite3_bind_text(STMTquery, 8, itemImagePath.c_str(),-1, SQLITE_TRANSIENT);
        if(sqlite3_step(STMTquery) == SQLITE_DONE){
            std::cout<< "\nNew item added succesfully." <<std::endl;
        }else{
            std::cerr<< "\nFailed to add item. \nError:" + std::string(SQLerror) <<std::endl;
        }
    }
    sqlite3_finalize(STMTquery);
}

void deleteItem(sqlite3*db, int id, const char* itemName){
    char* SQLerror = 0;
    sqlite3_stmt* STMTquery;
    const char* query = "DELETE FROM item WHERE id = ? AND name = ?;";
    if(sqlite3_prepare_v2(db, query, -1, &STMTquery, NULL)==SQLITE_OK){
        sqlite3_bind_int(STMTquery, 1, id);
        sqlite3_bind_text(STMTquery, 2, itemName, -1, SQLITE_TRANSIENT);
        if(sqlite3_step(STMTquery)==SQLITE_DONE){
            std::cout<< std::string(itemName)+ " successfully removed from database.\n" <<std::endl;
        }else{ std::cerr<<"\n Error removing: "+ std::string(itemName);}
    }
    sqlite3_finalize(STMTquery);
}

void searchItem(sqlite3*db, const char* input, std::vector<Item>& vector){
    // Clears the old search before anything else:
    vector.clear(); //clear the vector
    vector.shrink_to_fit();//releases its memory

    char* SQLerror; //SQl error handler.
    sqlite3_stmt* STMTquery; // SQL will insert the prepared statement here.
    
    // Pre-prepare user input to be inserted into SQL function.
    std::string search = input;
    search  = "%"+search+"%"; 

    /* SQL base query: the user input will be searched in NAME, REFERENCE, CODE and LINE for a broader search.
    if you can remember that the item has an "A" somewhere but not exactly sure in which identifier, just type "A" and the program
    will return the items countaning "A" in these fields: */
    const char* query = "SELECT * FROM item WHERE name LIKE ? OR code LIKE ? OR line LIKE ? OR reference LIKE ? ";
    
    // Prepares the user input ("search" variable) to be inserted into every "?" and stores (by pointer) the full query into STMTquery.
    if(sqlite3_prepare_v2(db, query, -1, &STMTquery, NULL) == SQLITE_OK){
        //Just a loop so i dont have to write sqlite3_bind_text for every "?"
        for(int i=1; i<=4; i++){
            sqlite3_bind_text(STMTquery, i, search.c_str(), -1, SQLITE_TRANSIENT);
        }
        // Every time sqlite3_steps runs the prepared query it will return a value informing if theres another row bellow, while it's true keep reading.
        // While sqlite3_steps(STMTquery) keeps returning that there's another row (==SQLITE_ROW), filter the info and creates a new Item object.
        while (sqlite3_step(STMTquery) == SQLITE_ROW){
            // Filter item info:
            int itemId = sqlite3_column_int(STMTquery, 0); 
            const char* itemName  = (const char*)sqlite3_column_text(STMTquery, 1);
            const char* itemRef = (const char*) sqlite3_column_text(STMTquery, 2);
            const char* itemCode = (const char*) sqlite3_column_text(STMTquery, 3);
            const char* itemLine = (const char*) sqlite3_column_text(STMTquery, 4);
            double itemCap = sqlite3_column_double(STMTquery, 5);
            int itemQtt = sqlite3_column_int(STMTquery, 6);
            const char* itemImagePath = (const char*) sqlite3_column_text(STMTquery, 7);
           
            // Creates the item object to be added to the list of items returned by the search:
            Item itemResponse(itemId,
            std::string(itemName),
            std::string(itemRef),
            std::string(itemCode),
            std::string(itemLine),
            itemCap, itemQtt,
            std::string(itemImagePath));
            vector.push_back(itemResponse);
            std::cout << std::string(itemName)+ " " +std::string(itemRef)+ " " +std::string(itemCode)<<+ " " +std::string(itemLine)<<+ " " +std::string(itemImagePath) <<std::endl;
        }
    }
    // Releases the pointer (SQL has a function for it, dont use CPP standard)
    sqlite3_finalize(STMTquery);
}

void updateName(sqlite3*db, int id, const char* itemName, const char* newName){
    char* SQLerror=0;
    sqlite3_stmt* STMTquery;
    const char* query = "UPDATE item SET name = ? WHERE id = ? and name = ?;";
    if(sqlite3_prepare_v2(db, query, -1, &STMTquery, NULL)==SQLITE_OK){
        sqlite3_bind_text(STMTquery, 1, newName, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(STMTquery, 2, id);
        sqlite3_bind_text(STMTquery, 3, itemName, -1, SQLITE_TRANSIENT);
        if(sqlite3_step(STMTquery)==SQLITE_DONE){
            std::cout<< itemName << " name updated to: " <<newName<<std::endl;
        }else{
            std::cerr<< "Error updating name line: "+ std::string(SQLerror)<<std::endl;
        }
        sqlite3_finalize(STMTquery);
    }
}

void updateReference(sqlite3*db, int id, const char* itemName, const char* newReference){
    char* SQLerror=0;
    sqlite3_stmt* STMTquery;
    const char* query = "UPDATE item SET reference = ? WHERE id = ? and name = ?;";
    if(sqlite3_prepare_v2(db, query, -1, &STMTquery, NULL)==SQLITE_OK){
        sqlite3_bind_text(STMTquery, 1, newReference, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(STMTquery, 2, id);
        sqlite3_bind_text(STMTquery, 3, itemName, -1, SQLITE_TRANSIENT);
        if(sqlite3_step(STMTquery)==SQLITE_DONE){
            std::cout<< itemName << " reference updated to: " <<newReference<<std::endl;
        }else{
            std::cerr<< "Error updating item reference: "+ std::string(SQLerror)<<std::endl;
        }
        sqlite3_finalize(STMTquery);
    }
}

void updateCode(sqlite3*db, int id, const char* itemName, const char* newCode){
    char* SQLerror=0;
    sqlite3_stmt* STMTquery;
    const char* query = "UPDATE item SET code = ? WHERE id = ? and name = ?;";
    if(sqlite3_prepare_v2(db, query, -1, &STMTquery, NULL)==SQLITE_OK){
        sqlite3_bind_text(STMTquery, 1, newCode, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(STMTquery, 2, id);
        sqlite3_bind_text(STMTquery, 3, itemName, -1, SQLITE_TRANSIENT);
        if(sqlite3_step(STMTquery)==SQLITE_DONE){
            std::cout<< itemName << " code updated to: " <<newCode<<std::endl;
        }else{
            std::cerr<< "Error updating item code: "+ std::string(SQLerror)<<std::endl;
        }
        sqlite3_finalize(STMTquery);
    }
}

void updateLine(sqlite3*db, int id, const char* itemName, const char* newLine){
    char* SQLerror=0;
    sqlite3_stmt* STMTquery;
    const char* query = "UPDATE item SET line = ? WHERE id = ? and name = ?;";
    if(sqlite3_prepare_v2(db, query, -1, &STMTquery, NULL)==SQLITE_OK){
        sqlite3_bind_text(STMTquery, 1, newLine, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(STMTquery, 2, id);
        sqlite3_bind_text(STMTquery, 3, itemName, -1, SQLITE_TRANSIENT);
        if(sqlite3_step(STMTquery)==SQLITE_DONE){
            std::cout<< itemName << " line updated to: " <<newLine<<std::endl;
        }else{
            std::cerr<< "Error updating item line: "+ std::string(SQLerror)<<std::endl;
        }
        sqlite3_finalize(STMTquery);
    }
}

void updateCapacity(sqlite3*db, int id, const char* itemName, double newCapacity){
    char* SQLerror=0;
    sqlite3_stmt* STMTquery;
    const char* query = "UPDATE item SET capacity = ? WHERE id = ? and name = ?;";
    if(sqlite3_prepare_v2(db, query, -1, &STMTquery, NULL)==SQLITE_OK){
        sqlite3_bind_double(STMTquery, 1, newCapacity);
        sqlite3_bind_int(STMTquery, 2, id);
        sqlite3_bind_text(STMTquery, 3, itemName, -1, SQLITE_TRANSIENT);
        if(sqlite3_step(STMTquery)==SQLITE_DONE){
            std::cout<< itemName << " capacity updated to: " <<newCapacity<<std::endl;
        }else{
            std::cerr<< "Error updating item capacity: "+ std::string(SQLerror)<<std::endl;
        }
        sqlite3_finalize(STMTquery);
    }
}

void updateQuantity(sqlite3*db, int id, const char* itemName, int quantity){

    char* SQLerror = 0;
    sqlite3_stmt* STMTquery;
    const char* query = "UPDATE item SET quantity = quantity + ? WHERE id = ? AND name = ?;";

    if(sqlite3_prepare_v2(db,query, -1, &STMTquery, NULL)==SQLITE_OK){
        sqlite3_bind_int(STMTquery,1, quantity);
        sqlite3_bind_int(STMTquery,2, id);
        sqlite3_bind_text(STMTquery, 3, itemName,-1,SQLITE_TRANSIENT);
        if(sqlite3_step(STMTquery)==SQLITE_DONE){
            std::cout<< itemName << " quantity updated to: " << quantity<<std::endl;
        }else{
            std::cerr<< "Error updating item quantity: "+ std::string(SQLerror)<<std::endl;
        }
    }
    sqlite3_finalize(STMTquery);
}

void updateImagePath(sqlite3*db, int id, const char* itemName, const char* newPath){
    char* SQLerror=0;
    sqlite3_stmt* STMTquery;
    const char* query = "UPDATE item SET imagepath = ? WHERE id = ? and name = ?;";
    if(sqlite3_prepare_v2(db, query, -1, &STMTquery, NULL)==SQLITE_OK){
        sqlite3_bind_text(STMTquery, 1, newPath, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(STMTquery, 2, id);
        sqlite3_bind_text(STMTquery, 3, itemName, -1, SQLITE_TRANSIENT);
        if(sqlite3_step(STMTquery)==SQLITE_DONE){
            std::cout<< itemName << " image updated to: " <<newPath<<std::endl;
        }else{
            std::cerr<< "Error updating item image path line: "+ std::string(SQLerror)<<std::endl;
        }
        sqlite3_finalize(STMTquery);
    }
}
