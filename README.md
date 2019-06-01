# File-Organization
File organization (fixed length records, delimited fields)
- Operations: - Delete book (given the ISBN),  useing the avail list technique for fixed length records, so that you can reuse the deleted records in new insertions. The list head is initially assigned ‐1, its data type is: short, and stored at the beginning of the file. 
- Add book,  checking first if there is a deleted record in the available list or not, if the list head is = ‐1, this means append the new record. 
- Update book (given the ISBN) 
- Print book (given the ISBN),  useing a sequential search. -
Print all books - 
Compact the file, remove the deleted records from the file, example - If the file looks like ( record1 record2 deletedrecord record3)  after compaction the file will look like ( record1 record2 record3) 

