# ft_ls
School 21 (42) project. Implementation bash ls function.
- обрабатываем директории, символичесикие ссылки (readlink, readdir)


**как будем обходить папки** </br>
добавляем пришедшие папки/файлы из стандартного ввода в очередь (сортируем по приоритетности - сначала директории, потом файлы)
берем из начала директорию, обрабатываем ее и кладем ее содержимое в конец очереди...
## Readdir</br>
эта функция возвращает структуру struct dirent из нее нам нужно 2 поля - {d_name, d_type} </br>
## Парсинг стандартного ввода</br>
### что может прийти?</br>
### обработка ошибок
### сохранение в структуру 


# Первая версия
- чтение папок, которые подаются через stdin и вывод всех файлов просто в строчку
- продумать архитектуру

## Вывод 
### без флагов
1)  выводит названия папок и файлов через \t
2) не печатает скрытые файлы, начинающиеся с точки
3) файлы отсортированы по ascii
