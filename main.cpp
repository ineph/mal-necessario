#define UNICODE
#define TEXT
#define DEFAULT_BUTTON_WIDTH 100
#define DEFAULT_BUTTON_HEIGHT 50

//IDs de menu
#define MENU_FILE_OPEN 1
#define MENU_FILE_SAVE 2
#define MENU_EDIT_COPY 3
#define MENU_EDIT_PASTE 4
#define MENU_OPSTIONS_OPTION 5
#define MENU_EXIT 6

#include <Windows.h>
#include <windows.h>
#include <WinUser.h>


HWND Window;
HWND bCreateWall;

void AddMenus(HWND hWnd);

//evento de comando
void WMCommand(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
    if (lParam == (LPARAM)bCreateWall)
        MessageBox(Window, L"vc apertou bCreateWall", L"BOA!", MB_OK);
    else if (wParam)
        switch (wParam) {
            case 1: MessageBox(Window, L"vc clicou em abrir", L"ae", MB_OK);break;
            case 2: MessageBox(Window, L"vc clicou em salvar", L"ae", MB_OK);break;
            case 3: MessageBox(Window, L"vc clicou em copiar", L"ae", MB_OK);break;
            case 4: MessageBox(Window, L"vc clicou em colar", L"ae", MB_OK);break;
            case 5: MessageBox(Window, L"vc clicou em opção", L"ae", MB_OK);break;
            case 6: {
                MessageBox(Window, L"FLWS", L"EAE", MB_OK);
                PostQuitMessage(0);
            }
        }
        
}


//gerenciador de mensagem e quase tudo que ocorre pois é o loop principal
LRESULT CALLBACK WndowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY: PostQuitMessage(0); break;
        case WM_CREATE: AddMenus(hWnd); break;
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

void AddMenus(HWND hWnd){
    HMENU hMenu = CreateMenu();

    HMENU hFile = CreateMenu();
    HMENU hOptions = CreateMenu();
    HMENU hEdit = CreateMenu();

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFile, L"File");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hEdit, L"Edit");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hOptions, L"Options");
    AppendMenu(hMenu, MF_SEPARATOR, NULL, NULL);    
    AppendMenu(hMenu, MF_STRING, MENU_EXIT, L"Exit");

    AppendMenu(hFile, MF_STRING, MENU_FILE_OPEN, L"Open");
    AppendMenu(hFile, MF_STRING, MENU_FILE_SAVE, L"Save");
    AppendMenu(hEdit, MF_STRING, MENU_EDIT_COPY, L"Copy");
    AppendMenu(hEdit, MF_STRING, MENU_EDIT_PASTE, L"Paste");
    AppendMenu(hOptions, MF_STRING, MENU_OPSTIONS_OPTION, L"Option");
    
    SetMenu(hWnd, hMenu);
}
