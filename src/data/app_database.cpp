#include <QFile>
#include <QDebug>
#include <QDateTime>

#include "app_database.h"
#include "../utils/db_utils.h"
#include "../utils/pref_utils.h"

AppDatabase::AppDatabase()
{
    timeNow = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    dbPath = "data/vSongBookApp.db";
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

    //Creating Songs Table
    QSqlQuery qry2(appDB);
    if (!qry2.exec(DbQueries::createSongsTable())) {
        qDebug() << qry2.lastError().text();
    }

    if (!appDB.tables().contains(Tables::songs())) {
        qDebug() << "Creating DB table: " + Tables::songs() + " failed.";
    }

    //Creating History Table
    QSqlQuery qry3(appDB);
    if (!qry3.exec(DbQueries::createHistoryTable())) {
        qDebug() << qry3.lastError().text();
    }

    if (!appDB.tables().contains(Tables::history())) {
        qDebug() << "Creating DB table: " + Tables::history() + " failed.";
    }

    //Creating Search Table
    QSqlQuery qry4(appDB);
    if (!qry4.exec(DbQueries::createSearchTable())) {
        qDebug() << qry4.lastError().text();
    }

    if (!appDB.tables().contains(Tables::search())) {
        qDebug() << "Creating DB table: " + Tables::search() + " failed.";
    }
}

void AppDatabase::checkPreferences()
{

}

//Adding a Book to the DB
int AppDatabase::addBook(Book* book)
{
    QString sqlInsert = "INSERT INTO " + Tables::books() + " (" + 
        Columns::categoryid() + ", " + 
        Columns::enabled() + ", " +
        Columns::title() + ", " + 
        Columns::tags() + ", " + 
        Columns::qcount() + ", " + 
        Columns::position() + ", " +
        Columns::backpath() + ", " + 
        Columns::created() + ", " + 
        Columns::updated() + 
    ")";
    sqlInsert.append("VALUES(" +
        sqlSafe(QString::number(book->categoryid)) + ", " +
        sqlSafe(QString::number(book->enabled)) + ", " +
        sqlSafe(book->title) + ", " +
        sqlSafe(book->tags) + ", " +
        sqlSafe(QString::number(book->qcount)) + ", " +
        sqlSafe(QString::number(book->position)) + ", " +
        sqlSafe(book->content) + ", " +
        sqlSafe(book->backpath) + ", " +
        sqlSafe(timeNow) + ", " +
        sqlSafe(timeNow) +
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
    QString sqlSelect = "SELECT * FROM " + Tables::books() + " WHERE " + Columns::enabled() + "=1 AND " + Columns::songid() + "=" + bookid + ";";

    //Executing the query
    QSqlQuery selectQry(appDB);
    if (!selectQry.exec(sqlSelect)) {
        qDebug() << sqlSelect + " failed.\n" + selectQry.lastError().text();
    }

    while (selectQry.next()) {
        Book book;
        book.bookid = selectQry.value(0).toInt();
        book.categoryid = selectQry.value(1).toInt();
        book.enabled = selectQry.value(2).toInt();
        book.title = selectQry.value(3).toString();
        book.tags = selectQry.value(4).toString();
        book.qcount = selectQry.value(5).toInt();
        book.position = selectQry.value(6).toInt();
        book.backpath = selectQry.value(7).toString();
        book.created = selectQry.value(8).toString();
        book.updated = selectQry.value(9).toString();
    }
    return book;
}

std::vector<Book> AppDatabase::fetchBooks()
{
    std::vector<Book> books;

    //Sql String for selecting Books from the DB
    QString sqlSelect = "SELECT * FROM " + Tables::books() + " WHERE " + Columns::enabled() + "=1;";

    //Executing the query
    QSqlQuery selectQry(appDB);
    if (!selectQry.exec(sqlSelect)) {
        qDebug() << sqlSelect + " failed.\n" + selectQry.lastError().text();
    }

    while (selectQry.next()) {
        Book book;
        book.bookid = selectQry.value(0).toInt();
        book.categoryid = selectQry.value(1).toInt();
        book.enabled = selectQry.value(2).toInt();
        book.title = selectQry.value(3).toString();
        book.tags = selectQry.value(4).toString();
        book.qcount = selectQry.value(5).toInt();
        book.position = selectQry.value(6).toInt();
        book.backpath = selectQry.value(7).toString();
        book.created = selectQry.value(8).toString();
        book.updated = selectQry.value(9).toString();

        books.push_back(book);
    }
    return books;
}

// Save a new song in the database
int AppDatabase::addSong(Song* song)
{
    //Sql String for Adding a Song to the DB
    QString sqlInsert = "INSERT INTO " + Tables::songs() + " (" +
        Columns::postid() + ", " +
        Columns::bookid() + ", " +
        Columns::categoryid() + ", " +
        Columns::basetype() + ", " +
        Columns::number() + ", " +
        Columns::title() + ", " +
        Columns::alias() + ", " +
        Columns::content() + ", " +
        Columns::tags() + ", " +
        Columns::key() + ", " +
        Columns::author() + ", " +
        Columns::notes() + ", " +
        Columns::created() + ", " +
        Columns::updated() + ", " +
        Columns::metawhat() + ", " +
        Columns::metawhen() + ", " +
        Columns::metawhere() + ", " +
        Columns::metawho() + ", " +
        Columns::netthumbs() + ", " +
        Columns::views() + ", " +
        Columns::isfav() + ", " +
        Columns::acount() + ", " +
        Columns::userid() +
    ")";
    sqlInsert.append("VALUES(" +
        sqlSafe(QString::number(song->songid)) + ", " +
        sqlSafe(QString::number(song->postid)) + ", " +
        sqlSafe(QString::number(song->bookid)) + ", " +
        sqlSafe(QString::number(song->categoryid)) + ", " +
        sqlSafe(song->basetype) + ", " +
        sqlSafe(QString::number(song->number)) + ", " +
        sqlSafe(song->title) + ", " +
        sqlSafe(song->alias) + ", " +
        sqlSafe(song->content) + ", " +
        sqlSafe(song->tags) + ", " +
        sqlSafe(song->key) + ", " +
        sqlSafe(song->author) + ", " +
        sqlSafe(song->notes) + ", " +
        sqlSafe(timeNow) + ", " +
        sqlSafe(timeNow) + ", " +
        sqlSafe(song->metawhat) + ", " +
        sqlSafe(song->metawhen) + ", " +
        sqlSafe(song->metawhere) + ", " +
        sqlSafe(song->metawho) + ", " +
        sqlSafe(QString::number(song->netthumbs)) + ", " +
        sqlSafe(QString::number(song->views)) + ", " +
        sqlSafe(QString::number(song->isfav)) + ", " +
        sqlSafe(QString::number(song->acount)) + ", " +
        sqlSafe(QString::number(song->userid)) +
        ");");

    //Executing the query
    QSqlQuery insertQry(appDB);
    if (!insertQry.exec(sqlInsert)) {
        qDebug() << sqlInsert + " failed.\n" + insertQry.lastError().text();
    }
    return insertQry.lastInsertId().toInt();
}

Song AppDatabase::fetchSong(int songid)
{
    Song song;

    //Sql String for selecting Songs from the DB

    QString sqlSelect = "SELECT " + 
        Tables::songs() + "." + Columns::songid() + ", " +
        Tables::songs() + "." + Columns::postid() + ", " +
        Tables::songs() + "." + Columns::categoryid() + ", " +
        Tables::songs() + "." + Columns::number() + ", " +
        Tables::songs() + "." + Columns::title() + ", " +
        Tables::songs() + "." + Columns::alias() + ", " +
        Tables::songs() + "." + Columns::content() + ", " +
        Tables::songs() + "." + Columns::tags() + ", " +
        Tables::songs() + "." + Columns::key() + ", " +
        Tables::songs() + "." + Columns::author() + ", " +
        Tables::books() + "." + Columns::title() +
        " FROM " + Tables::songs();
    sqlSelect.append(" INNER JOIN " + Tables::books() + " ON " + Tables::songs() + "." + Columns::categoryid() + "=" + Tables::books() + "." + Columns::categoryid());
    sqlSelect.append(" WHERE " + Columns::songid() + "=" + QString::number(songid) + ";");
    qDebug() << sqlSelect;

    //Executing the query
    QSqlQuery selectQry(appDB);
    if (!selectQry.exec(sqlSelect)) {
        qDebug() << sqlSelect + " failed.\n" + selectQry.lastError().text();
    }

    while (selectQry.next()) {
        song.songid = selectQry.value(0).toInt();
        song.postid = selectQry.value(1).toInt();
        song.categoryid = selectQry.value(2).toInt();
        song.number = selectQry.value(3).toInt();
        song.title = selectQry.value(4).toString();
        song.alias = selectQry.value(5).toString();
        song.content = selectQry.value(6).toString();
        song.tags = selectQry.value(7).toString();
        song.key = selectQry.value(8).toString();
        song.author = selectQry.value(9).toString();
        song.book = selectQry.value(10).toString();
    }
    return song;
}

Song AppDatabase::fetchSongDetails(int songid)
{
    Song song;

    //Sql String for selecting Songs from the DB

    QString sqlSelect = "SELECT * FROM " + Tables::songs();
    sqlSelect.append(" INNER JOIN " + Tables::books() + " ON " + Tables::songs() + "." + Columns::categoryid() + "=" + Tables::books() + "." + Columns::categoryid());
    sqlSelect.append(" WHERE " + Columns::songid() + "=" + QString::number(songid) + ";");
    qDebug() << sqlSelect;

    //Executing the query
    QSqlQuery selectQry(appDB);
    if (!selectQry.exec(sqlSelect)) {
        qDebug() << sqlSelect + " failed.\n" + selectQry.lastError().text();
    }

    while (selectQry.next()) {
        song.songid = selectQry.value(0).toInt();
        song.postid = selectQry.value(1).toInt();
        song.bookid = selectQry.value(2).toInt();
        song.categoryid = selectQry.value(3).toInt();
        song.basetype = selectQry.value(4).toString();
        song.number = selectQry.value(5).toInt();
        song.title = selectQry.value(6).toString();
        song.alias = selectQry.value(7).toString();
        song.content = selectQry.value(8).toString();
        song.tags = selectQry.value(9).toString();
        song.key = selectQry.value(10).toString();
        song.author = selectQry.value(11).toString();
        song.notes = selectQry.value(12).toString();
        song.created = selectQry.value(13).toString();
        song.updated = selectQry.value(14).toString();
        song.metawhat = selectQry.value(15).toString();
        song.metawhen = selectQry.value(16).toString();
        song.metawhere = selectQry.value(17).toString();
        song.metawho = selectQry.value(18).toString();
        song.netthumbs = selectQry.value(19).toInt();
        song.views = selectQry.value(20).toInt();
        song.isfav = selectQry.value(21).toInt();
        song.acount = selectQry.value(22).toInt();
        song.userid = selectQry.value(23).toInt();
    }
    return song;
}

// Get the list of all songs in the database
std::vector<Song> AppDatabase::fetchSongs()
{
    std::vector<Song> songs;

    //Sql String for selecting Songs from the DB
    QString sqlSelect = "SELECT * FROM " + Tables::songs() + ";";

    //Executing the query
    QSqlQuery selectQry(appDB);
    if (!selectQry.exec(sqlSelect)) {
        qDebug() << sqlSelect + " failed.\n" + selectQry.lastError().text();
    }

    while (selectQry.next()) {
        Song song;
        song.songid = selectQry.value(0).toInt();
        song.postid = selectQry.value(1).toInt();
        song.bookid = selectQry.value(2).toInt();
        song.categoryid = selectQry.value(3).toInt();
        song.basetype = selectQry.value(4).toString();
        song.number = selectQry.value(5).toInt();
        song.title = selectQry.value(6).toString();
        song.alias = selectQry.value(7).toString();
        song.content = selectQry.value(8).toString();
        song.tags = selectQry.value(9).toString();
        song.key = selectQry.value(10).toString();
        song.author = selectQry.value(11).toString();
        song.notes = selectQry.value(12).toString();
        song.created = selectQry.value(13).toString();
        song.updated = selectQry.value(14).toString();
        song.metawhat = selectQry.value(15).toString();
        song.metawhen = selectQry.value(16).toString();
        song.metawhere = selectQry.value(17).toString();
        song.metawho = selectQry.value(18).toString();
        song.netthumbs = selectQry.value(19).toInt();
        song.views = selectQry.value(20).toInt();
        song.isfav = selectQry.value(21).toInt();
        song.acount = selectQry.value(22).toInt();
        song.userid = selectQry.value(23).toInt();

        songs.push_back(song);
    }
    return songs;
}

// Get the Value of a preference if it exists on the database otherwise get the default value
QString AppDatabase::getValueOrDefault(QString key, QString defaultValue)
{
    QString value;
    QString sqlSelect = "SELECT " + Columns::content() + " FROM " + Tables::preferences() + " WHERE " + Columns::title() + "=" + sqlSafe(key) + ";";
    
    QSqlQuery selectQry(appDB);
    selectQry.prepare(sqlSelect);
    if (!selectQry.exec(sqlSelect)) 
    {
        addValue(key, defaultValue);
        value = defaultValue;
    }
    else {
        if (selectQry.isSelect() && selectQry.first()) {
            value = selectQry.value(0).toString();
            if (value.size() == 0)
            {
                updateValue(key, defaultValue);
                value = defaultValue;
            }
        }
    }

    return value;
}

// Save the value of  preference for the first time in the database
void AppDatabase::addValue(QString key, QString value) 
{
    QString sqlInsert = "INSERT INTO " + Tables::preferences() + " (" +
        Columns::title() + ", " +
        Columns::content() + ", " +
        Columns::created() +
        ")";
    sqlInsert.append("VALUES(" +
        sqlSafe(key) + ", " +
        sqlSafe(value) + ", " +
        sqlSafe(timeNow) +
        ");");

    //Executing the query
    QSqlQuery insertQry(appDB);
    if (!insertQry.exec(sqlInsert)) {
        qDebug() << sqlInsert + " failed.\n" + insertQry.lastError().text();
    }
}

// Update the value of a preference
void AppDatabase::updateValue(QString key, QString value) 
{
    QString sqlUpdate = "UPDATE " + Tables::preferences() + " SET " +
        Columns::content() + "=" + sqlSafe(value) + ", " +
        Columns::updated() + "=" + sqlSafe(timeNow) +
        " WHERE " + Columns::title() + "=" + sqlSafe(key) +
        ";";

    //Executing the query
    QSqlQuery updateQry(appDB);
    if (!updateQry.exec(sqlUpdate)) {
        qDebug() << sqlUpdate + " failed.\n" + updateQry.lastError().text();
        addValue(key, value);
    }
}

AppDatabase::~AppDatabase()
{

}
