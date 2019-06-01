#include <iostream>
#include <string>
#include <strstream>
#include <fstream>

using namespace std;
int listhead = -1;
const int rrn = 100;
struct book
{
	char isbn[6];
	char title[31];
	char name[31];
	char price[6];
	char year[5];
	char pages[6];
};


istream& operator >> (istream& in, book&b)
{
	cout << "isbn: "; in.getline(b.isbn, 6);
	cout << "title: "; in.getline(b.title, 31);
	cout << "Author: "; in.getline(b.name, 31);
	cout << "price: "; in.getline(b.price, 6);
	cout << "year: "; in.getline(b.year, 5);
	cout << "pages: "; in.getline(b.pages, 6);
	return in;
}


ostream & operator <<(ostream& os, book &b)
{
	os << b.isbn << endl;
	os << b.title << endl;
	os << b.name << endl;
	os << b.price << endl;
	os << b.year << endl;
	os << b.pages << endl;
	return os;
}

void readOnebook(fstream & stream, book & b)
{

	char buffer[rrn];
	istrstream strbuf(buffer);
	stream.read(buffer, rrn);
	strbuf.getline(b.isbn, 6, '|'); strbuf.getline(b.title, 31, '|');
	strbuf.getline(b.name, 31, '|'); strbuf.getline(b.price, 6, '|');
	strbuf.getline(b.year, 5, '|'); strbuf.getline(b.pages, 6, '|');
}

void addbook(fstream& stream, book &b)
{
	stream.seekg(0, ios::beg);
	stream.read((char*)&listhead, sizeof(int));
	if (listhead == -1) {			   // mfesh amakn fe el nos
		stream.seekp(0, ios::end);
		cin >> b;
		char buffer[rrn];
		strcpy_s(buffer, b.isbn);
		strcat_s(buffer, "|");
		strcat_s(buffer, b.title);
		strcat_s(buffer, "|");
		strcat_s(buffer, b.name);
		strcat_s(buffer, "|");
		strcat_s(buffer, b.price);
		strcat_s(buffer, "|");
		strcat_s(buffer, b.year);
		strcat_s(buffer, "|");
		strcat_s(buffer, b.pages);
		strcat_s(buffer, "|");
		int x = 99 - strlen(buffer);

		while (x--) {
			strcat_s(buffer, "#");
		}

		stream.write(buffer, rrn);
	}
	else {									 // fe amakn
		stream.seekp(rrn*listhead + 5, ios::beg); //hro7 3la el mkan last deleted record aktb 3leh 
		stream.read((char*)&listhead, sizeof(int));
		stream.seekg(-5, ios::cur);
		cin >> b;
		char buffer[rrn];
		strcpy_s(buffer, b.isbn);
		strcat_s(buffer, "|");
		strcat_s(buffer, b.title);
		strcat_s(buffer, "|");
		strcat_s(buffer, b.name);
		strcat_s(buffer, "|");
		strcat_s(buffer, b.price);
		strcat_s(buffer, "|");
		strcat_s(buffer, b.year);
		strcat_s(buffer, "|");
		strcat_s(buffer, b.pages);
		strcat_s(buffer, "|");
		int x = 99 - strlen(buffer);

		while (x--) {
			strcat_s(buffer, "#");
		}
		stream.write(buffer, rrn);
		stream.seekg(0, ios::beg);
		stream.write((char*)&listhead, sizeof(int)); // dlw2ty 3ayz a3'er el listhead b ele kan ablo 


	}
}

void Deletebook(fstream &stream, char a[6])
{
	book b;
	stream.seekg(0, ios::beg);
	stream.read((char*)&listhead, sizeof(int));
	while (!stream.eof())
	{
		readOnebook(stream, b);
		if (strcmp(b.isbn, a) == 0)
		{
			stream.seekg(-rrn, ios::cur);
			char x = '*';
			stream.write(&x, sizeof(char));
			stream.write((char*)&listhead, sizeof(int));
			listhead = stream.tellg() / rrn;
			stream.seekg(0, ios::beg);
			stream.write((char*)&listhead, sizeof(int));

			break;
		}
	}

}

void printAllBooks(fstream & stream, book& b)
{
	stream.seekg(0, ios::beg);
	stream.read((char*)&listhead, sizeof(int));


	do {

		readOnebook(stream, b);
		if (stream.eof()) break;
		if (b.isbn[0] != '*') {
			cout << "ISBN: " << b.isbn << endl;
			cout << "Title: " << b.title << endl;
			cout << "Author: " << b.name << endl;
			cout << "Year: " << b.year << endl;
			cout << "Price: " << b.price << endl;
			cout << "Pages: " << b.pages << endl << endl;
		}

	} while (!stream.eof());


	stream.clear(); //to be able to read again.

}

bool getBook(fstream & stream, book& b, string isbn)
{
	stream.seekg(4, ios::beg);
	while (!stream.eof()) {


		char buffer[100];
		stream.read(buffer, 100);
		istrstream strbuf(buffer);
		strbuf.getline(b.isbn, 6, '|'); strbuf.getline(b.title, 31, '|');
		strbuf.getline(b.name, 31, '|'); strbuf.getline(b.price, 6, '|');
		strbuf.getline(b.year, 5, '|'); strbuf.getline(b.pages, 6, '|');
		if (b.isbn == isbn) {
			cout << b;
			return 1;
		}

	}
	cout << "not found" << endl;
	stream.seekg(0, ios::beg);
	return 0;


}
void update(fstream  & stream, book & b, char a[6]) {
	stream.seekg(4, ios::beg);

	readOnebook(stream, b);
	do {
		if (strcmp(b.isbn, a) == 0) {
			Deletebook(stream, a);
			addbook(stream, b);
			break;
		}
		readOnebook(stream, b);
	} while (!stream.eof());


}
void compactfile(fstream &stream, book &b)
{
	char* newbuffer = new char[1200];


	char buffer[101];

	buffer[100] = '\0';



	stream.seekg(4, ios::beg);
	listhead = -1;


	while (true) {
		readOnebook(stream, b);

		if (b.isbn[0] != '*') {
			stream.seekg(-100, ios::cur);
			stream.read(buffer, rrn);
			strcpy_s(newbuffer, 1200, buffer);
			strcat_s(newbuffer, 1200, "#");
			break;
		}
	}
	readOnebook(stream, b);
	while (!stream.eof()) {
		if (b.isbn[0] != '*') {
			stream.seekg(-100, ios::cur);
			stream.read(buffer, rrn);
			strcat_s(newbuffer, 1200, buffer);
			strcat_s(newbuffer, 1200, "#");


		}
		readOnebook(stream, b);
	}
	int x = strlen(newbuffer);
	stream.close();
	fstream f("save.txt", ios::trunc | ios::out);
	f.write((char*)&listhead, sizeof(int));
	f.write(newbuffer, x);
	f.close();
	delete newbuffer;



}


int main()
{
	int choice;
	fstream file;
	book b;
	file.open("save.txt", ios::in | ios::out);
	//	file.write((char*)&listhead, sizeof(int));
start:
	cout << "choose what you want to do : \n 1-Add a new book \n 2-get a book by tile \n 3-delete the record of a book \n 4-update a book \n 5-print all books \n 0-exit" << endl;
	cin >> choice;
	if (choice == 1) {
		cout << "enter the number of books you want to add:";
		int numOFbooks;
		cin >> numOFbooks;
		cin.ignore();

		while (numOFbooks--) {
			addbook(file, b);
		}
		goto start;
	}

	else if (choice == 2)
	{
		cout << "enter the isbn of the book you want to find:";
		string x;
		cin.ignore();
		getline(cin, x);
		getBook(file, b, x);
		goto start;
	}

	else if (choice == 3) {
		char a[6];
		cout << "enter the isbn of the book you want to delete :";
		cin >> a;
		cin.ignore();
		Deletebook(file, a);
		goto start;
	}

	else if (choice == 4) {
		char x[6];
		cin >> x;
		cin.ignore();
		update(file, b, x);
		goto start;
	}

	else if (choice == 5) {
		printAllBooks(file, b);
		goto start;
	}

	else if (choice == 0) {
		compactfile(file, b);
		exit;
	}
}