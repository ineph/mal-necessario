#define UNICODE
#define TEXT
#define DEFAULT_BUTTON_WIDTH 100
#define DEFAULT_BUTTON_HEIGHT 100
#include <Windows.h>
#include <windows.h>
#include <WinUser.h>

HWND Window;
HWND bCreateWall;
//evento de comando
void WMCommand(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
    if (lParam == (LPARAM)bCreateWall)
        MessageBox(Window, L"vc apertou bCreateWall", L"BOA!", MB_OK);
    // else if (wParam == ID_FILE_EXIT) PostQuitMessage(0);
}


//gerenciador de mensagem e quase tudo que ocorre pois é o loop principal
LRESULT CALLBACK WndowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY: PostQuitMessage(0); break;
        case WM_CREATE: {
            HMENU hMenu = CreateMenu();
            HMENU hFile = CreateMenu();
            HMENU hOptions = CreateMenu();

            AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFile, L"File");
            AppendMenu(hMenu, MF_POPUP, NULL, L"Edit");
            AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hOptions, L"Options");

            AppendMenu(hFile, MF_STRING, NULL, L"Exit");
            AppendMenu(hFile, MF_STRING, NULL, L"1");
            AppendMenu(hFile, MF_STRING, NULL, L"2");
            SetMenu(hWnd, hMenu);
        } break;
        case WM_COMMAND: WMCommand(hWnd, msg, wParam, lParam); break;
    }
    return (DefWindowProc(hWnd, msg, wParam, lParam));
}

//main
int WINAPI WinMain(
HINSTANCE hInstance,
HINSTANCE hPrevious,
LPSTR IpCmdString,
int CmdShow){

    const wchar_t CLASS_NAME[] = L"ME";
    WNDCLASS wc = {};
    MSG      msg;

    // as variaveis aqui declaradas seguem o padrao do livro (pagina 6)
    //p n alocar mais bytes de memoria alem do tamanho do WNCLASS
    wc.cbClsExtra    = 0;
    //n precisa de mais memoria pra janela instanciada
    wc.cbWndExtra    = 0;
    //define cor de fundo da janela
    // wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    // define o cursors
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    // define o ícone da janela
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    // instancia do WinMain
    wc.hInstance     = hInstance;
    // manuseia as msgs do sistema
    wc.lpfnWndProc   = WndowProc;
    // nome da janela ("ME" de MAP EDITOR)
    wc.lpszClassName = CLASS_NAME;
    // controlador do menu para essa instancia de janela
    wc.lpszMenuName  = NULL;
    // estrutura do estilo da janela
    wc.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    
    if (!RegisterClass(&wc)){
        MessageBox (NULL, L"Erro: Impossivel registrar classe", L"ERRO!", MB_OK);
        return(0);
    }

    Window = CreateWindowEx(
        0,
        L"ME",
        L"Map Editor",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, 0, 640, 480,
        NULL, NULL,
        hInstance, NULL);
    
    bCreateWall = CreateWindow(
        L"BUTTON",
        L"Create Wall",
        WS_CHILD | WS_VISIBLE,
        0, 100,
        DEFAULT_BUTTON_WIDTH,
        DEFAULT_BUTTON_HEIGHT,
        Window,
        NULL,
        hInstance,
        NULL);

    if (Window == NULL){
        MessageBox(NULL, L"Erro: Falha ao criar janela", L"ERRO!", MB_OK);
        return (0);
    }

    while (1){

        if (PeekMessage (&msg, NULL, 0 , 0, PM_REMOVE)){

            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } 
    }
    
    return (1);
}
