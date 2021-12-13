#include <QMovie>
#include <QDebug>
#include <QtCore>
#include <QtNetwork>
#include <QJsonDocument>
#include <QTextCodec>
#include <QLibraryInfo>
#include <QMessageBox>
#include <QLocale>
#include <QObject>

#include "services/task.h"
#include "utils/api_utils.h"
#include "data/models/list_item.h"
#include "data/delegates/book_delegate.h"

#include "book_select.h"
#include "ui_book_select.h"

QString networkResult;
//const int iterations = 20;
QVector<int> vector;
QMovie* mMovie;
AppDatabase* appDb;
std::vector<QString> selecteds, catids, titles, tags, contents, songnos;

BookSelect::BookSelect(QWidget* parent) :
	QDialog(parent),
	ui(new Ui::BookSelect)
{
	ui->setupUi(this);

	appDb = new AppDatabase();
	mMovie = new QMovie(":/images/loading.gif");
	ui->LblProgress->setMovie(mMovie);
	mMovie->start();
	loadBooks();
}

void BookSelect::loadBooks()
{
	ui->LblDetails->setText("Be patient as we load books from online for you...");
	showProgress(true);
	qnam = new QNetworkAccessManager();
	QObject::connect(qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onBooksResult(QNetworkReply*)));
	request.setUrl(QUrl(ApiUtils::baseUrl() + ApiUtils::booksSelect()));

	////AsBase::WriteLogs("Online", "Fetching books from online", "Url: " + ApiUtils::BaseUrl() + ApiUtils::BooksSelect() + " ", "");
	qnam->get(request);
}

void BookSelect::onBooksResult(QNetworkReply* reply)
{
	showProgress(false);
	if (reply->error()) {
		networkResult = (QString)reply->errorString();
		ui->TxtSearch->hide();
		ui->LstBooks->hide();
		ui->BtnProceed->hide();
		ui->BtnCancel->hide();
		ui->LblProgress->hide();
		ui->LblDetails->show();

		//AsBase::WriteLogs("Online", "Failed to fetch books from online", "Reason: " + networkResult, "");
		ui->LblDetails->setText("Failed to fetch books from online.\nReason: " + networkResult);
		return;
	}
	else
	{
		networkResult = (QString)reply->readAll();
		QJsonDocument jsonResponse = QJsonDocument::fromJson(networkResult.toUtf8());
		QJsonObject jsonObject = jsonResponse.object();
		QJsonArray jsonArray = jsonObject["data"].toArray();

		bookModel = new QStandardItemModel();

		int count = 1;
		foreach(const QJsonValue & value, jsonArray)
		{
			QJsonObject obj = value.toObject();
			QString title = obj["title"].toString();
			QString code = obj["backpath"].toString();
			QString songs = obj["qcount"].toString();

			QStandardItem* bookItem = new QStandardItem;
			ListItem book;

			book.image = "res/images/check.png";
			book.title = QString::number(count) + ". " + title;
			book.content = songs + " " + code + " songs";
			catids.push_back(obj["categoryid"].toString());
			titles.push_back(title);
			tags.push_back(obj["backpath"].toString());
			contents.push_back(obj["contents"].toString());
			songnos.push_back(songs);

			bookItem->setData(QVariant::fromValue(book), Qt::UserRole + 1);
			bookModel->appendRow(bookItem);
			count++;
		}

		BookSelect::createListView();

		QMessageBox::warning(this, "Just a Minute ...",
			tr("Take time to select a songbook at a time so as to setup your vSongBook Collection.\n\nOnce done that, proceed to the next stage")
		);
		//ui->LblDetails->setText("Take time to select a songbook at a time so as to setup your vSongBook Collection");
		ui->TxtSearch->setText(QString::number(count) + " books");
	}
}

void BookSelect::showProgress(bool show)
{
	if (show)
	{
		ui->TxtSearch->hide();
		ui->LstBooks->hide();
		ui->BtnProceed->hide();
		ui->BtnCancel->hide();
		ui->LblProgress->show();
		ui->LblDetails->show();
	}
	else
	{
		ui->TxtSearch->show();
		ui->LstBooks->show();
		ui->BtnProceed->show();
		ui->BtnCancel->show();
		ui->LblProgress->hide();
		ui->LblDetails->hide();
	}
}

void BookSelect::createListView()
{
    BookDelegate* bookDelegate = new BookDelegate(this);
    //ui->LstBooks->setItemDelegate(bookDelegate);
	ui->LstBooks->setModel(bookModel);
	ui->LstBooks->setViewMode(QListView::ListMode);
	ui->LstBooks->setDragEnabled(true);
	ui->LstBooks->setSelectionMode(QAbstractItemView::MultiSelection);
	ui->LstBooks->setSpacing(1);
	ui->LstBooks->setStyleSheet("* { background-color: #D3D3D3; }");
}

void BookSelect::on_BtnProceed_clicked()
{
	selecteds.clear();
	QModelIndexList list = ui->LstBooks->selectionModel()->selectedIndexes();

	foreach(const QModelIndex & index, list)
	{
		int book = index.row();
		selecteds.push_back(catids[book]);
	}

	if (selecteds.size() > 0)
	{
		QString selectedones;
		QMessageBox msgBox;

		msgBox.setWindowTitle("Just a minute ...");
		QIcon icon;
		icon.addFile(QStringLiteral(":/images/appicon"), QSize(), QIcon::Normal, QIcon::Off);
		msgBox.setWindowIcon(icon);

		msgBox.setIcon(QMessageBox::Warning);
		msgBox.setText("Done with selecting?");
		for (int i = 0; i < selecteds.size(); i++)
		{
			int bid = selecteds[i].toInt() - 1;
			selectedones = selectedones + QString::number(i + 1) + ". " + titles[bid] + " - " + tags[bid] + " (" +
				songnos[bid] + " songs).\n";
		}
		msgBox.setInformativeText(selectedones);
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::No);

		int ret = msgBox.exec();
		switch (ret) {
		case QMessageBox::Yes:
			loadSongs();
			break;
		default:
			// should never be reached
			break;
		}
	}
	else
		QMessageBox::warning(this, "Just a Minute ...",
			tr("Oops! This is so heart breaking. You haven't selected a book, you expect things to be okay. You got to select at least one book. \n\n By the way we can always bring you back here to select afresh. But for now select at least one")
		);
}

void BookSelect::loadSongs()
{
	ui->LblDetails->setText("Loading songs from online ...\n Thanks for you patience");
	setStyleSheet("* { background-color: #000000; color: #FFFFFF; }");
	showProgress(true);

	appDb->connectionOpen("NewBooks");
	QString books = selecteds[0];
	int bid = books.toInt() - 1;

	Book* book = new Book();
	book->title = titles[bid];
	book->categoryid = catids[bid].toInt();
	book->tags = tags[bid];
	book->content = contents[bid];
	book->qcount = songnos[bid].toInt();
	book->enabled = 1;
	appDb->addBook(book);

	if (selecteds.size() > 1)
	{
		for (int i = 1; i < selecteds.size(); i++)
		{
			books = books + "," + selecteds[i];
			int bid = selecteds[i].toInt() - 1;
			Book* book = new Book();
			book->title = titles[bid];
			book->categoryid = catids[bid].toInt();
			book->tags = tags[bid];
			book->content = contents[bid];
			book->qcount = songnos[bid].toInt();
			book->enabled = 1;
			appDb->addBook(book);
		}
	}

	appDb->connectionClose("NewBooks");

	qnam = new QNetworkAccessManager();
	QObject::connect(qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onSongsResult(QNetworkReply*)));
	request.setUrl(QUrl(ApiUtils::baseUrl() + ApiUtils::postsSelect() + "?books=" + books));
	//AsBase::WriteLogs("Online", "Fetching songs from online for books: " + books, "Url: " + baseUrl + AsUtils::PostsSelect() + "?books=" + books + " ", "");
	qnam->get(request);
}

QString insertSongs()
{
	QJsonDocument jsonResponse = QJsonDocument::fromJson(networkResult.toUtf8());
	QJsonObject jsonObject = jsonResponse.object();
	QJsonArray jsonArray = jsonObject["data"].toArray();

	appDb->connectionOpen("NewSongs");

	foreach(const QJsonValue & value, jsonArray)
	{
		QJsonObject obj = value.toObject();
		Song* song = new Song();

		song->bookid = obj["categoryid"].toInt();
		song->categoryid = obj["categoryid"].toInt();
		song->number = obj["number"].toInt();
		song->postid = obj["postid"].toInt();
		song->title = obj["title"].toString();
		song->alias = obj["alias"].toString();
		song->content = obj["content"].toString();
		song->author = obj["who"].toString();

		song->title = song->title.replace("\n", "\\n");
		song->title = song->title.replace("'", "''");

		song->content = song->content.replace("\n", "\\n");
		song->content = song->content.replace("'", "''");

		int newSong = appDb->addSong(song);
	}
	appDb->connectionClose("NewSongs");
	return "Task Finished";
}

void BookSelect::onSongsResult(QNetworkReply* reply)
{
	if (reply->error()) {
		showProgress(false);
		networkResult = (QString)reply->errorString();
		ui->TxtSearch->hide();
		ui->LstBooks->hide();
		ui->BtnProceed->hide();
		ui->BtnCancel->hide();
		ui->LblProgress->hide();
		ui->LblDetails->show();

		//AsBase::WriteLogs("Online", "Failed to fetch songs from online", "Reason: " + networkResult, "");
		ui->LblDetails->setText("Failed to fetch songs from online.\nReason: " + networkResult);
		return;
	}
	else
	{
		networkResult = (QString)reply->readAll();

		Task::await([]() {
			return insertSongs();
			});

		showProgress(false);

		this->close();
	}
}

void BookSelect::on_BtnCancel_clicked()
{
	this->close();
}

BookSelect::~BookSelect()
{
	delete qnam;
	delete ui;
}
