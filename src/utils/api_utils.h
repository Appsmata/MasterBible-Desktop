#include <QtCore>

class ApiUtils
{
public:
	static QString baseUrl() { return "http://sing.appsmata.com/"; }

	static QString booksSelect() { return "as-client/book-select.php"; }

	static QString postsSelect() { return "as-client/posts-select.php"; }

};
