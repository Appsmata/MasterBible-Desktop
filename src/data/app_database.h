#ifndef APPDATABASE_H
#define APPDATABASE_H

#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QStandardItemModel>

#include "models/book.h"
#include "models/song.h"

// Application Database
class AppDatabase : public QObject
{
    Q_OBJECT

public:
    QSqlDatabase appDB;
    QString timeNow, dbPath;
    void checkDatabase();
    void checkPreferences();
    bool isDataLoaded();
    void connectionClose(QString connectionName);
    void connectionOpen(QString connectionName);
    void initDbOperations();

    int addBook(Book* book);
    int addSong(Song* song);

    QString sqlSafe(QString value);

    Song fetchSong(int songid);
    Song fetchSongDetails(int songid);
    Book fetchBook(int bookid);

    std::vector<Book> fetchBooks();
    std::vector<Song> fetchSongs();

    QString getValueOrDefault(QString key, QString defaultValue);
    void addValue(QString key, QString value);
    void updateValue(QString key, QString value);

    explicit AppDatabase();
    ~AppDatabase();

private:

};

#endif // APPDATABASE_H
