==================================ОПИСАНИЕ_ЗАДАНИЯ=============================
Написать программу на любом языке, которая считает количество строк в заданном файле. Имя файла задается в командной строке. Считать, что строки разделяются `\n`. Кол-во строк вывести в stdout. Результирующая программа будет аналогична вызову `wc -l /path/to/file`. Исходный код выложить на github и прислать ссылку.
Будет плюсом, если напишите на Go.
Код выкладывайте в свой репозиторий на github.
Если есть опыт в разработке на Go, то вместо теста можно дать ссылку на код.
Выполненные задания присылайте d.isaev@corp.mail.ru с темой "go 2017" до 10.08 15:00


==================================ОПИСАНИЕ_РЕШЕНИЯ=============================

Дерево каталога 

./wc_alias/
├── Makefile
├── README.txt
├── simple_line_count.c
├── test_files
│   ├── 1.txt
│   ├── A20.xml
│   └── test.txt
├── test_scripts
│   ├── show_performance.sh
│   └── show_results.sh
└── wc_alias.c

1.	Компиляция.
	В ./wc_alias выполнить команды
		$ make clean && make

2.	Запуск.
	В ./wc_alias выполнить команды
	$ make clean && make
	$ ./simple_line_count <filename> // simple_line_count - для подсчета 
		количества строк используется просто целочисленная переменная 
		long unsigned int (8 bytes)

	$ ./wc_alias <filename>  // wc_alias - для подсчета количества строк
		используется массив char * в динамической памяти.

3.	Сравнение результатов.
	Чтобы сравнить результаты нужно выполнить следующие команды:
	$ cd ./wc_alias/test_scripts
	$ show_results.sh <text_file_name> // данный скрипт запускает
		wc, simple_line_count и wc_alias

4.	Примеры текстовых файлов.
	В каталоге test_files находятся примеры текстовых файлов
