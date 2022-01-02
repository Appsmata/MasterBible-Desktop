#ifndef VERSE_H
#define VERSE_H

#include <QMetaType>

struct Verse {
	int verseid;
	QString title;
	QString content;
	QString highlight;
	QString notes;
};

Q_DECLARE_METATYPE(Verse)

#endif // VERSE_H
