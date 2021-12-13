#ifndef SONG_H
#define SONG_H

#include <QMetaType>

struct Song {
	int songid;
	int postid;
	int bookid;
	int categoryid;
	QString basetype;
	int number;
	QString title;
	QString alias;
	QString content;
	QString tags;
	QString key;
	QString author;
	QString notes;
	QString created;
	QString updated;
	QString metawhat;
	QString metawhen;
	QString metawhere;
	QString metawho;
	int netthumbs;
	int views;
	int isfav;
	int acount;
	int userid;
	QString book;
};

Q_DECLARE_METATYPE(Song)

#endif // SONG_H
