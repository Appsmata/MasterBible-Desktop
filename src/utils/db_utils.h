#include <QtCore>

class DbUtils
{
public:
	//Generic string for Table creation
	static QString sqlCreate() { return "CREATE TABLE IF NOT EXISTS "; }
};

class Tables
{
public:
	static QString books()	{ return "as_books"; }
	static QString songs()	{ return "as_songs"; }
	static QString history()	{ return "as_history"; }
	static QString search()	{ return "as_search"; }
	static QString preferences()	{ return "as_preferences"; }
};

class Columns
{
public:
	static QString bookid() { return "bookid"; }
	static QString categoryid() { return "categoryid"; }
	static QString enabled() { return "enabled"; }
	static QString title() { return "title"; }
	static QString tags() { return "tags"; }
	static QString qcount() { return "qcount"; }
	static QString position() { return "position"; }
	static QString backpath() { return "backpath"; }
	static QString created() { return "created"; }
	static QString updated() { return "updated"; }

	static QString songid() { return "songid"; }
	static QString postid() { return "postid"; }
	static QString basetype() { return "basetype"; }
	static QString number() { return "number"; }
	static QString alias() { return "alias"; }
	static QString content() { return "content"; }
	static QString key() { return "key"; }
	static QString author() { return "author"; }
	static QString notes() { return "notes"; }
	static QString metawhat() { return "metawhat"; }
	static QString metawhen() { return "metawhen"; }
	static QString metawhere() { return "metawhere"; }
	static QString metawho() { return "metawho"; }
	static QString netthumbs() { return "netthumbs"; }
	static QString views() { return "views"; }
	static QString isfav() { return "isfav"; }
	static QString acount() { return "acount"; }
	static QString userid() { return "userid"; }

	static QString historyid() { return "historyid"; }
	static QString type() { return "type"; }
	static QString item() { return "item"; }
	static QString extra() { return "extra"; }
	static QString searchid() { return "searchid"; }
	static QString preferenceid() { return "preferenceid"; }
};

class DbQueries
{
public:
	//Sql String for Creating Books Table
	static QString createBooksTable()
	{
		return DbUtils::sqlCreate() + Tables::books() + " (" +
			Columns::bookid() + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, " +
			Columns::categoryid() + " INTEGER, " +
			Columns::enabled() + " INTEGER, " +
			Columns::title() + " VARCHAR(200), " +
			Columns::tags() + " VARCHAR(200), " +
			Columns::qcount() + " INTEGER, " +
			Columns::position() + " INTEGER, " +
			Columns::backpath() + " VARCHAR(20), " +
			Columns::created() + " VARCHAR(20), " +
			Columns::updated() + " VARCHAR(20)" +
		");";
	}

	//Sql String for Creating Songs Table
	static QString createSongsTable()
	{
		return DbUtils::sqlCreate() + Tables::songs() + " (" +
			Columns::songid() + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, " +
			Columns::postid() + " INTEGER, " +
			Columns::bookid() + " INTEGER, " +
			Columns::categoryid() + " INTEGER, " +
			Columns::basetype() + " VARCHAR(200), " +
			Columns::number() + " INTEGER, " +
			Columns::title() + " VARCHAR(200), " +
			Columns::alias() + " VARCHAR(200), " +
			Columns::content() + " VARCHAR(5000), " +
			Columns::tags() + " VARCHAR(200), " +
			Columns::key() + " VARCHAR(10), " +
			Columns::author() + " VARCHAR(100), " +
			Columns::notes() + " VARCHAR(1000), " +
			Columns::created() + " VARCHAR(20), " +
			Columns::updated() + " VARCHAR(20), " +
			Columns::metawhat() + " VARCHAR(10), " +
			Columns::metawhen() + " VARCHAR(10), " +
			Columns::metawhere() + " VARCHAR(10), " +
			Columns::metawho() + " VARCHAR(10), " +
			Columns::netthumbs() + " INTEGER, " +
			Columns::views() + " INTEGER, " +
			Columns::isfav() + " INTEGER, " +
			Columns::acount() + " INTEGER, " +
			Columns::userid() + " INTEGER" +
		");";
	}

	//Sql String for Creating History Table
	static QString createHistoryTable()
	{
		return DbUtils::sqlCreate() + Tables::history() + " (" +
			Columns::historyid() + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, " +
			Columns::type() + " INTEGER, " +
			Columns::item() + " INTEGER, " +
			Columns::title() + " VARCHAR(100), " +
			Columns::extra() + " VARCHAR(100), " +
			Columns::created() + " VARCHAR(20)" +
			");";
	}

	//Sql String for Creating Search Table
	static QString createSearchTable()
	{
		return DbUtils::sqlCreate() + Tables::search() + " (" +
			Columns::historyid() + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, " +
			Columns::type() + " INTEGER, " +
			Columns::item() + " INTEGER, " +
			Columns::title() + " VARCHAR(100), " +
			Columns::extra() + " VARCHAR(100), " +
			Columns::created() + " VARCHAR(20)" +
			");";
	}

	//Sql String for Creating Preference Table
	static QString createPreferenceTable()
	{
		return DbUtils::sqlCreate() + Tables::preferences() + " (" +
			Columns::historyid() + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, " +
			Columns::title() + " VARCHAR(500) UNIQUE, " +
			Columns::content() + " VARCHAR(2000), " +
			Columns::created() + " VARCHAR(20), " +
			Columns::updated() + " VARCHAR(20)" +
			");";
	}

};