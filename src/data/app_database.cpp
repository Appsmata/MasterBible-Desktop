#include <QFile>
#include <QDebug>
#include <QDateTime>

#include "app_database.h"
#include "../utils/db_utils.h"
#include "../utils/pref_utils.h"

AppDatabase::AppDatabase()
{
    timeNow = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    dbPath = "data/MasterBible.db";
}

// Add single quotes to values in a Query
QString AppDatabase::sqlSafe(QString value)
{
    return "'" + value + "'";
}

// Check if the database exists otherwise create it
void AppDatabase::checkDatabase()
{
    QFile file(dbPath);

    if (!file.exists())
    {
        QDir dir;
        if (!dir.exists("data")) dir.mkpath("data");

        file.open(QIODevice::ReadWrite);
        appDB = QSqlDatabase::addDatabase("QSQLITE");
        appDB.setDatabaseName(dbPath);

        if (!appDB.open()) {
            qDebug() << "database open failed.";
        }
        else
        {
            initDbOperations();
            qDebug() << "database is okay.";
        }
    }
    else
    {
        appDB = QSqlDatabase::addDatabase("QSQLITE");
        appDB.setDatabaseName(dbPath);
        if (!appDB.open()) {
            qDebug() << "database open failed.";
        }
        else
        {
            initDbOperations();
            qDebug() << "database is okay.";
        }
    }
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    appDB.close();
}

bool AppDatabase::isDataLoaded()
{
    bool isLoaded = false;

    //Count available books
    QString sqlSelect = "SELECT COUNT(*) FROM " + Tables::books() + ";";

    //Executing the query
    QSqlQuery selectQry(appDB);
    selectQry.prepare(sqlSelect);
    if (!selectQry.exec(sqlSelect)) {
        qDebug() << sqlSelect + " failed.\n" + selectQry.lastError().text();
    }
    else {
        qDebug() << sqlSelect + " succeded";
        if (selectQry.isSelect() && selectQry.first()) {
            int count = selectQry.value(0).toInt();
            if (count > 0) isLoaded = true;
        }
    }
    
    return isLoaded;
}

// Open a connection to the database
void AppDatabase::connectionOpen(QString connectionName)
{
    appDB = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    appDB.setDatabaseName(dbPath);
    if (!appDB.open()) {
        qDebug() << "database open failed.";
    }
}

// Close a connection to the database
void AppDatabase::connectionClose(QString connectionName)
{
    QSqlDatabase::removeDatabase(connectionName);
    appDB.close();
}

// Do initial database operations
void AppDatabase::initDbOperations()
{
    //Creating Books Table
    QSqlQuery qry1(appDB);
    if (!qry1.exec(DbQueries::createBooksTable())) {
        qDebug() << qry1.lastError().text();
    }

    if (!appDB.tables().contains(Tables::books())) {
        qDebug() << "Creating DB table: " + Tables::books() + " failed.";
    }

    //Creating History Table
    QSqlQuery qry2(appDB);
    if (!qry2.exec(DbQueries::createHistoryTable())) {
        qDebug() << qry2.lastError().text();
    }

    if (!appDB.tables().contains(Tables::history())) {
        qDebug() << "Creating DB table: " + Tables::history() + " failed.";
    }

    //Creating Search Table
    QSqlQuery qry3(appDB);
    if (!qry3.exec(DbQueries::createSearchTable())) {
        qDebug() << qry3.lastError().text();
    }

    if (!appDB.tables().contains(Tables::search())) {
        qDebug() << "Creating DB table: " + Tables::search() + " failed.";
    }

    //Creating English Verses Table
    QSqlQuery qry4(appDB);
    if (!qry4.exec(DbQueries::createEnglishVersesTable())) {
        qDebug() << qry4.lastError().text();
    }

    if (!appDB.tables().contains(Tables::verses_english())) {
        qDebug() << "Creating DB table: " + Tables::verses_english() + " failed.";
    }

    //Creating Swahili Verses Table
    QSqlQuery qry5(appDB);
    if (!qry5.exec(DbQueries::createSwahiliVersesTable())) {
        qDebug() << qry5.lastError().text();
    }

    if (!appDB.tables().contains(Tables::verses_swahili())) {
        qDebug() << "Creating DB table: " + Tables::verses_swahili() + " failed.";
    }

}

void AppDatabase::checkPreferences()
{

}

//Adding a Book to the DB
int AppDatabase::addBook(Book* book)
{
    QString sqlInsert = "INSERT INTO " + Tables::books() + " (" +
        Columns::testament() + ", " + 
        Columns::code() + ", " +
        Columns::title() + ", " + 
        Columns::chapters() + ", " + 
        Columns::swahili() + 
    ")";
    sqlInsert.append("VALUES(" +
        sqlSafe(QString::number(book->testament)) + ", " +
        sqlSafe(book->code) + ", " +
        sqlSafe(book->title) + ", " +
        sqlSafe(QString::number(book->chapters)) + ", " +
        sqlSafe(book->swahili) + ", " +
    ");");

    //Executing the query
    QSqlQuery insertQry(appDB);
    if (!insertQry.exec(sqlInsert)) {
        qDebug() << sqlInsert + " failed.\n" + insertQry.lastError().text();
    }
    return insertQry.lastInsertId().toInt();
}

Book AppDatabase::fetchBook(int bookid)
{
    Book book;

    //Sql String for selecting Books from the DB
    QString sqlSelect = "SELECT * FROM " + Tables::books() + " WHERE " + Columns::bookid() + "=" + bookid + ";";

    //Executing the query
    QSqlQuery selectQry(appDB);
    if (!selectQry.exec(sqlSelect)) {
        qDebug() << sqlSelect + " failed.\n" + selectQry.lastError().text();
    }

    while (selectQry.next()) {
        Book book;
        book.bookid = selectQry.value(0).toInt();
        book.testament = selectQry.value(1).toInt();
        book.code = selectQry.value(2).toString();
        book.title = selectQry.value(3).toString();
        book.chapters = selectQry.value(4).toInt();
        book.swahili = selectQry.value(5).toString();
    }
    return book;
}

std::vector<Book> AppDatabase::fetchBooks()
{
    std::vector<Book> books;

    //Sql String for selecting Books from the DB
    QString sqlSelect = "SELECT * FROM " + Tables::books() + ";";

    //Executing the query
    QSqlQuery selectQry(appDB);
    if (!selectQry.exec(sqlSelect)) {
        qDebug() << sqlSelect + " failed.\n" + selectQry.lastError().text();
    }

    while (selectQry.next()) {
        Book book;
        book.bookid = selectQry.value(0).toInt();
        book.testament = selectQry.value(1).toInt();
        book.code = selectQry.value(2).toString();
        book.title = selectQry.value(3).toString();
        book.chapters = selectQry.value(4).toInt();
        book.swahili = selectQry.value(5).toString();

        books.push_back(book);
    }
    return books;
}

// Save a new verse in the database
int AppDatabase::addVerse(Verse* verse, int language)
{
    //Sql String for Adding a Verse to the DB
    QString sqlInsert = "INSERT INTO " + (language ? Tables::verses_english() : Tables::verses_swahili()) +
        " (" +
        Columns::title() + ", " +
        Columns::content() + ", " +
        Columns::highlight() + ", " +
        Columns::notes() +
    ")";
    sqlInsert.append("VALUES(" +
        sqlSafe(verse->title) + ", " +
        sqlSafe(verse->content) + ", " +
        sqlSafe(verse->highlight) + ", " +
        sqlSafe(verse->notes) +
        ");");

    //Executing the query
    QSqlQuery insertQry(appDB);
    if (!insertQry.exec(sqlInsert)) {
        qDebug() << sqlInsert + " failed.\n" + insertQry.lastError().text();
    }
    return insertQry.lastInsertId().toInt();
}

AppDatabase::~AppDatabase()
{

}
