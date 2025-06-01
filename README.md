# HelloArch

Кроссплатформенный C++-проект, демонстрирующий:
- Под Windows: в консоль каждую секунду выводится `Hello from <архитектура>`.
- Под Linux (Raspberry Pi): то же самое + мигание встроенным ACT-LED.

## Ссылка на репозиторий

Репозиторий доступен по адресу:  
[GitHub: HelloArch](https://github.com/ElyorKHodjimetov/HelloArch.git)

---

## Структура репозитория

```text
HelloArch/
├── CMakeLists.txt       # скрипт сборки CMake
├── HelloArch.cpp        # исходник с функцией main()
└── .gitignore           # правила игнорирования файлов и папок
```

### Коротко о файлах

- `HelloArch.cpp` — основной исходник, где определяется архитектура и (для Raspberry Pi) управление ACT-LED.  
- `CMakeLists.txt` — конфигурация CMake (сборка без зависимости от IDE).  
- `.gitignore` — исключает из репозитория артефакты сборки (папки `build/`, `CMakeCache.txt`, `.exe`, `.obj` и др.).

---

## Требования

- **Windows**:
  - Visual Studio 2022 (или любая версия, поддерживающая CMake).  
  - CMake ≥ 3.5, установлен в PATH (в VS 2022 CMake уже встроен).  
  - Проект настроен для стандарта C++17.

- **Linux / Raspberry Pi (Debian/Ubuntu)**:
  - `g++` / `clang++` (пакет `build-essential`).  
  - `cmake` (пакет `cmake`).  
  - Для управления ACT-LED требуются права `root` (или соответствующие udev-правила).

Под Raspberry Pi (Raspbian OS):
```bash
sudo apt update
sudo apt install -y build-essential cmake
```

---

## Сборка и запуск

### Windows (Visual Studio 2022)

1. **Клонируйте репозиторий**:
   ```powershell
   cd D:\путь\до\папки
   git clone https://github.com/ElyorKHodjimetov/HelloArch.git
   cd HelloArch
   ```

2. **Откройте папку как CMake-проект**:
   - В Visual Studio: **File → Open → Folder…** → выберите `D:\путь\до\HelloArch`.
   - Visual Studio автоматически обнаружит `CMakeLists.txt`.

3. **Выберите конфигурацию**:
   - Сверху в списке выберите `x64-Release` (или `x64-Debug`).

4. **Соберите проект**:
   - Нажмите **Build → Build All** или зелёную кнопку «Build».

5. **Запустите**:
   - Исполняемый файл `HelloArch.exe` будет в папке `HelloArch\x64\Release\`.
   - Запустите:
     ```powershell
     cd HelloArch\x64\Release
     .\HelloArch.exe
     ```
   - В консоли будет:
     ```
     Hello from x86_64 (Windows)
     Hello from x86_64 (Windows)
     …
     ```

---

### Windows (через встроенный терминал CMake)

**Примечание:** при генерации с генератором Visual Studio переменная `CMAKE_BUILD_TYPE` игнорируется. Конфигурацию (Release или Debug) нужно указывать при сборке через параметр `--config`, а не в `cmake ..`.

1. **Перейдите в корень проекта**:
   ```powershell
   cd D:\путь\до\HelloArch
   ```

2. **Создайте папку `build` и зайдите в неё**:
   ```powershell
   mkdir build
   cd build
   ```

3. **Сгенерируйте файлы сборки (Release)**:
   ```powershell
   cmake ..
   ```
   Visual Studio найдёт генератор и создаст `.sln` и прочие файлы.

4. **Соберите (Release)**:
   ```powershell
   cmake --build . --config Release
   ```
   — в `build\Release\HelloArch.exe` будет бинарник.

5. **Запустите**:
   ```powershell
   cd Release
   .\HelloArch.exe
   ```
   — вывод аналогичен предыдущему (`Hello from x86_64 (Windows)`).

*Если нужна Debug-версия, выполните `cmake --build . --config Debug`, тогда бинарник окажется в `build\Debug\HelloArch.exe`.*

---

### Linux / Raspberry Pi

1. **Клонируйте репозиторий**:
   ```bash
   cd ~
   git clone https://github.com/ElyorKHodjimetov/HelloArch.git
   cd HelloArch
   ```

2. **Установите зависимости**:
   ```bash
   sudo apt update
   sudo apt install -y build-essential cmake
   ```

3. **Создайте папку `build` и перейдите в неё**:
   ```bash
   mkdir build
   cd build
   ```

4. **Сгенерируйте сборку через CMake (Release)**:
   ```bash
   cmake .. -DCMAKE_BUILD_TYPE=Release
   ```
   Вывод:
   ```
   -- Configuring for Linux (Raspberry Pi)
   -- Generating done
   -- Build files have been written to: /home/pi/HelloArch/build
   ```

5. **Соберите**:
   ```bash
   make
   ```
   — появится исполняемый файл `HelloArch` в папке `build`.

6. **Запустите (с правами `sudo`, чтобы управлять ACT-LED)**:
   ```bash
   sudo ./HelloArch
   ```
   — в консоли:
   ```
   Hello from armv7l (Linux)
   Hello from armv7l (Linux)
   …
   ```
   — и ACT-LED будет мигать.

7. **Верните ACT-LED в стандартный режим (после остановки)**:
   ```bash
   echo mmc0 | sudo tee /sys/class/leds/ACT/trigger
   ```

---

## Структура после сборки

```text
HelloArch/
├── .gitignore
├── CMakeLists.txt
├── HelloArch.cpp
└── build/                   # создаётся при сборке, в репо отсутствует
    ├── CMakeFiles/
    ├── Release/
    │   └── HelloArch.exe    # Windows-бинарник
    └── HelloArch            # Linux-бинарник
```

---

## Автор

**Элёр**

---

## Лицензия

Проект распространяется под лицензией MIT.  
Полный текст лицензии см. в файле [LICENSE](./LICENSE).
