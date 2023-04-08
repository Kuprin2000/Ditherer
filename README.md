# Ditherer
Программа для многопоточного дизеринга изображения, то есть конвертации полноцветного изображения в формат с ограниченным количеством цветов, на C++. Для параллельных вычислений используется OpenMP, а для создания графического интерфейса связка GLFW + ImGui.

Интерфейс программы
![Alt text](docs/Interface.PNG?raw=true "Интерфейс программы")

Пользователь может выбрать метод дизеринга и палитру, в которую будет конвертировано изображение. Также можно указать, между сколькими потоками будет распределена задача.

На данный момент реализован только дизеринг методом Джарвиса-Джужиса-Нинке и следующие палитры:
1) Black and white
2) Black, gray and white
3) Two bits grayscale 
4) Four bits grayscale
5) Black, red green, blue and white
6) BK 0011 palette 1
7) BK 0011 palette 2
8) BK 0011 palette 3
9) BK 0011 palette 6
10) BK 0011 palette 7
11) BK 0011 palette 8
12) BK 0011 palette 9
13) BK 0011 palette 10
14) BK 0011 palette 11
15) BK 0011 palette 12
16) EGA 16 colors
17) VGA 256 colors

Более подробное описание программы приведено в файле docs/theory.pdf

# Примеры работы программы
Исходное изображение
![Alt text](docs/example.PNG?raw=true "Интерфейс программы")

Черно-белая палитра
![Alt text](docs/black_white.PNG?raw=true "Интерфейс программы")

Палитра с черным, серым и белым цветами
![Alt text](docs/black_gray_white.PNG?raw=true "Интерфейс программы")

Палитра с 16 оттенками серого
![Alt text](docs/four_bit_grayscale.PNG?raw=true "Интерфейс программы")

Палитра стандарта EGA, 16 цветов
![Alt text](docs/ega.PNG?raw=true "Интерфейс программы")

Палитра стандарта VGA, 256 цветов
![Alt text](docs/vga.PNG?raw=true "Интерфейс программы")