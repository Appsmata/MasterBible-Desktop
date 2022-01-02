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
	static QString history()	{ return "as_history"; }
	static QString search()	{ return "as_search"; }
	static QString verses_english()	{ return "as_verses_english"; }
	static QString verses_swahili()	{ return "as_verses_swahili"; }
};

class Columns
{
public:
	static QString bookid() { return "bookid"; }
	static QString testament() { return "testament"; }
	static QString code() { return "code"; }
	static QString title() { return "title"; }
	static QString chapters() { return "chapters"; }
	static QString swahili() { return "swahili"; }

	static QString verseid() { return "verseid"; }
	static QString content() { return "content"; }
	static QString highlight() { return "highlight"; }
	static QString notes() { return "notes"; }

	static QString historyid() { return "historyid"; }
	static QString type() { return "type"; }
	static QString item() { return "item"; }
	static QString extra() { return "extra"; }
	static QString searchid() { return "searchid"; }
	static QString created() { return "created"; }
};

class DbQueries
{
public:
	//Sql String for Creating Books Table
	static QString createBooksTable()
	{
		return DbUtils::sqlCreate() + Tables::books() + " (" +
			Columns::bookid() + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, " +
			Columns::testament() + " INTEGER, " +
			Columns::code() + " VARCHAR(10), " +
			Columns::title() + " VARCHAR(100), " +
			Columns::chapters() + " VARCHAR(200), " +
			Columns::swahili() + " VARCHAR(100)" +
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

	//Sql String for Creating English Verses Table
	static QString createEnglishVersesTable()
	{
		return DbUtils::sqlCreate() + Tables::verses_english() + " (" +
			Columns::verseid() + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, " +
			Columns::title() + " VARCHAR(50), " +
			Columns::content() + " VARCHAR(2000), " +
			Columns::highlight() + " VARCHAR(50), " +
			Columns::notes() + " VARCHAR(1000)" +
			");";
	}

	//Sql String for Creating Swahili Verses Table
	static QString createSwahiliVersesTable()
	{
		return DbUtils::sqlCreate() + Tables::verses_swahili() + " (" +
			Columns::verseid() + " INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, " +
			Columns::title() + " VARCHAR(50), " +
			Columns::content() + " VARCHAR(2000), " +
			Columns::highlight() + " VARCHAR(50), " +
			Columns::notes() + " VARCHAR(1000)" +
			");";
	}
};