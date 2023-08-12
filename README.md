# Задание:
## Реализовать класс динамических строк `String`

1. Написан на C++11 без использования сторонних библиотек. Не использует в своей основе 
какую-либо другую реализацию динамических строк, контейнеров или умных указателей STL.
Можно использовать стандартную библиотеку C.

2. Класс не шаблонный. Поддерживает строки произвольного размера, используя базовые 
операции работы с динамическим хипом (функции `malloc()/free()` или операторы `new/delete`)
для манипуляции последовательностями символов типа `char`.

3. Интерфейс класса:
- Есть конструктор копирования.
- Есть оператор присваивания.
- Поддерживается move-сематника.
- Есть оператор `+=`.
- Есть внешний оператор сложения двух строк.
- Операции поддерживаются не только для параметров типа `String`, но и для традиционных С-строк, оканчивающихся нулем.

Нет необходимости использовать какие-то изощренные методы оптимизации (типа SSO, COW и многопоточной поддержки).

Написать пример с использованием этого класса строк и какого-либо контейнера STL. 
Программа должна принимать список строк, затем выдавать его в порядке, обратном
лексикографическому без учета регистра. Поддержки кодировки ASCII будет достаточно.

Программа-пример работает из командной строки.

# Вывод программы-примера:
![Вывод программы-примера (См. файл example_output.jpg)](/example_output.jpg)