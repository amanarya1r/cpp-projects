#include <iostream>
#include <windows.h>

std::wstring tetromino[7]; 
// wide string type define in c++ stl, it's used to represent strings of wide characters(wchar_t), which are typically used to handle
// international and unicode text. This is especially useful for languages and environments that require more than the standard 8-bit character set.
int nFieldHeight = 18;
int nFieldWidth = 12;
unsigned char* Field = nullptr; // pointer given address of zero

int nScreenWidth = 80; // Console Screen size x <-- columns
int nScreenHeight = 30; // Console Screen size y <-- rows


int Rotate(int px, int py, int r) {
    switch (r % 4) {
    case 0: return py * 4 + px; // 0 degrees
    case 1: return 12 + py - (px * 4); // 90 degrees
    case 2: return 15 - (py * 4) - px; // 180 degrees
    case 3: return 3 - py + (px * 4); // 270 degrees
    }
    return 0;
}

// command line as a screen buffer



int main()
{
    // Create assets
    tetromino[0].append(L"...."); // L"string": the L prefix before the string literal indicated that it's a wide string literal.
    // std::wcout: used to output wide strings to the console
    tetromino[0].append(L"....");
    tetromino[0].append(L"....");
    tetromino[0].append(L"....");
    // 4 elements wide by 4 wide deep
    // '.' is used for empty space and any other symbol for part of the shape
    Field = new unsigned char[nFieldWidth * nFieldHeight]; //located in heap
    for (int x = 0; x < nFieldWidth; x++) {  // Widening the boundary
        for (int y = 0; y < nFieldHeight; y++) {
            Field[y * nFieldWidth + x] == (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0; //ternary operator is used
            // 9 is used to represent border
        }
    }

    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight]; // screen is a pointer
    for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    // game loops are the most important part of the game engine
    bool bGameOver = false;

    while (!bGameOver) {
        // Draw Field
        for (int x = 0; x < nFieldWidth; x++) {
            for (int y = 0; y < nFieldHeight; y++) {
                screen[(y + 2) * nScreenWidth + (x + 2)] = L" ███████=║"[Field[y * nFieldWidth + x]]; //settings output depending on he character of string arrays
                // ║ used for border
            }
        }
    }



    // Display Frame
    WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
            
    
    return 0;
}

class MyClass {
    public:
        void doSomething() {
            // Implementation
        }
    };
    