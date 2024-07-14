#include "GeneratorUI.h"
#include <Windows.h>

using namespace SequenceGenerator;

[STAThread]
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew GeneratorUI);
    return 0;
}


/*int main() {
    int* arr;

    int n = getSequenceLenght("Rand_10_1.txt");
    arr = new int[n];
    getSequence(arr, "Rand_10_1.txt");

    for (int i = 0; i < 10; i++) {
        cout << arr[i];
    }

}*/