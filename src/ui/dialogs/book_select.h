#ifndef BOOK_SELECT_H
#define BOOK_SELECT_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QModelIndex>
#include <QStandardItemModel>

#include "data/app_database.h"

class QStandardItemModel;

namespace Ui {
    class BookSelect;
}

class BookSelect : public QDialog
{
    Q_OBJECT

public:
    explicit BookSelect(QWidget *parent = nullptr);
    ~BookSelect();

private slots:
    void onBooksResult(QNetworkReply* reply);
    void onSongsResult(QNetworkReply* reply);
    void createListView();
    void loadBooks();
    void loadSongs();
    void showProgress(bool show);

    void on_BtnProceed_clicked();
    void on_BtnCancel_clicked();

private:
    Ui::BookSelect* ui;
    QNetworkAccessManager* qnam;
    QNetworkRequest request;
    QStandardItemModel* bookModel;

};

#endif // BOOK_SELECT_H
