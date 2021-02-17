
#define UNICODE
#define TEXT
#define DEFAULT_BUTTON_WIDTH 100
#define DEFAULT_BUTTON_HEIGHT 100
#include <Windows.h>
#include <WinUser.h>


HWND Window;

LRESULT CALLBACK WndowProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY: PostQuitMessage(0); break;
    }
    return (DefWindowProc(hWnd, msg, wParam, lParam));
}

int WINAPI WinMain (
HINSTANCE hInstance,
HINSTANCE hPrevious,
LPSTR IpCmdString,
int CmdShow){

    const wchar_t CLASS_NAME[] = L"Map Editor";
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

    Window = CreateWindowEx(0, L"Map Editor", L"Map Editor", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        0, 0, 640, 480, NULL, NULL, hInstance, NULL);

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
