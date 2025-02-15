# Computer Club Management System

## Описание

Эта программа представляет собой прототип системы для управления компьютерным клубом. Она отслеживает события (приход/уход клиентов, занятие/освобождение столов, ожидание в очереди), рассчитывает выручку за день и время занятости каждого стола.

## Стек технологий

*   C++ (стандарт до C++20 включительно)
*   STL (Standard Template Library)

## Требования

*   Компилятор g++ или clang
*   Операционная система: Linux, macOS, Windows (с MinGW/Cygwin)

## Структура проекта

Проект состоит из следующих файлов:

*   `main.cpp`: Основной файл с функцией `main`, отвечающей за чтение входных данных, создание объекта `ComputerClub` и вызов необходимых методов.
*   `computer_club.h`: Заголовочный файл класса `ComputerClub`, который инкапсулирует всю логику управления компьютерным клубом.
*   `computer_club.cpp`: Исходный файл класса `ComputerClub` с реализацией методов обработки событий, генерации событий конца дня и вывода статистики.
*   `time_utils.h`: Заголовочный файл, содержащий структуры и функции для работы со временем (парсинг, форматирование, сравнение, вычисление разницы).
*   `time_utils.cpp`: Исходный файл с реализацией функций для работы со временем.
*   `README.md`: Этот файл с описанием проекта и инструкциями по сборке и запуску.

## Сборка

### Linux/macOS

```bash
g++ -std=c++11 main.cpp time_utils.cpp computer_club.cpp -o task
```

Windows (с MinGW)
```bash
g++ -std=c++11 main.cpp time_utils.cpp computer_club.cpp -o task.exe
```

## Запуск
```bash
./task <input_file>
```
## или
```
task.exe <input_file>
```
