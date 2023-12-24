#pragma once
#include <vector>
#include "Book.h"
#include <qwidget.h>
#include <qvector.h>

class Rack : public QWidget
{
private:
	Q_OBJECT
	QVector<QVector<Book*>> shelf;
	bool IsSameBook(QDragEnterEvent*);
	void AddBook(int, int);
	bool CorrectBook(QDragEnterEvent*);
	int lastBook;
	int delBook = 0;
	QVector<bool> isFullShelf;

public:
	bool IsFull;
	int TakenBook;
	int widthShelf = 0;
	int CountShelf;
	QVector<int> offset;


	Rack(int countShelf, QWidget* table, QWidget* parent = nullptr) : CountShelf(countShelf), QWidget(parent)
	{
		setAcceptDrops(true);
		setObjectName("Rack");
		shelf = QVector<QVector<Book*>>();
		for (size_t i = 0; i < countShelf; i++)
		{
			shelf.append(QVector<Book*>());
			offset.append(0);
			isFullShelf.append(false);
		}
		IsFull = false;
		lastBook = 0;
		connect(table, SIGNAL(calculatedThickness(int)), this, SLOT(applyThickness(int)));
		connect(table, SIGNAL(removeFromRack(int)), this, SLOT(DelBook(int)));
		connect(this, SIGNAL(deleteBook(int)), table, SLOT(DeleteBook(int)));
	}

protected:
	void paintEvent(QPaintEvent*) override;

	void dragEnterEvent(QDragEnterEvent*);

	void dropEvent(QDropEvent* e);

private slots:
	void applyThickness(int);
	void DelBook(int);

signals:
	void deleteBook(int);
};

