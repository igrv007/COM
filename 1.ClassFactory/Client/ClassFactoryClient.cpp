#include<windows.h>
#include"ClassFactoryServer.h"

//global function declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//global variable declarations
ISum *pISum =NULL;
ISubtract *pISubtract =NULL;
ISum *pISumAgain =NULL;
IUnknown *pIUnknownFromISum = NULL;
IUnknown *pIUnknownFromISubtract =NULL;

//WinMain
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{
	//variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[]=TEXT("ComClient");
	HRESULT hr;

	//code
	//COM initialization

	hr=CoInitialize(NULL);
	if(FAILED(hr))
	{
		MessageBox(NULL,TEXT("COM Library can not be Initiated.\nExiting."),TEXT("ERROR"),MB_OK);
	    exit(0);
	}

	//wndclassex initialization
	wndclass.cbSize=sizeof(wndclass);
	wndclass.style=CS_HREDRAW| CS_VREDRAW ;
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.lpfnWndProc=WndProc;
	wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.hInstance=hInstance;
    wndclass.lpszClassName=AppName;
    wndclass.lpszMenuName=NULL;
    wndclass.hIconSm=LoadIcon(NULL,IDI_APPLICATION);

    //register class
    RegisterClassEx(&wndclass);

    //create window
    hwnd=CreateWindow(AppName,
    	              TEXT("Client of COM Dll Server"),
    	              WS_OVERLAPPEDWINDOW,
    	              CW_USEDEFAULT,
    	              CW_USEDEFAULT,
    	              CW_USEDEFAULT,
    	              CW_USEDEFAULT,
    	              NULL,
    	              NULL,
    	              hInstance,
    	              NULL);
    ShowWindow(hwnd,nCmdShow);
    UpdateWindow(hwnd);

    //message loop
    while(GetMessage(&msg,NULL,0,0))
    {
    	TranslateMessage(&msg);
    	DispatchMessage(&msg);
    }

    //COM uninitialization
    CoUninitialize();
    return((int)msg.wParam);

}

//window call back
LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	//function declarations
	void SafeInterfaceRelease(void);
	//variable declarations
	HRESULT hr;
	int iNum1,iNum2,iSum,iSubtract;
	TCHAR str[255];

	//code
	switch(iMsg)
	{

		case WM_CREATE:
		hr=CoCreateInstance(CLSID_SumSubtract,NULL,CLSCTX_INPROC_SERVER,IID_ISum,(void **)&pISum);
		if(FAILED(hr))
		{
			MessageBox(hwnd,TEXT("ISum Interface can Not be Obtained"),TEXT("ERROR"),MB_OK);
			DestroyWindow(hwnd);

		}
		//initialize arguments hardcoded
		iNum1=100;
		iNum2=100;
		//call SumOfTwoIntegers() of ISum
		pISum->SumOfTwoIntegers(iNum1,iNum2,&iSum);
		//display result
		wsprintf(str,TEXT("SUM OF %d and %d is:%d"),iNum1,iNum2,iSum);
        MessageBox(hwnd,str,TEXT("RESULT"),MB_OK);

        //call QueryInterface() on ISum to get ISubtract's pointer
        hr=pISum->QueryInterface(IID_ISubtract,(void**)&pISubtract);
        if(FAILED(hr))
        {
        	MessageBox(hwnd,TEXT("ISubtract interface can not be obtained"),TEXT("ERROR"),MB_OK);
        	DestroyWindow(hwnd);
        }
        //as ISumis not  needed ,release it
        pISum->Release();
        pISum=NULL;//make release interface NULL

        //again initialize arguments hardcoded
        iNum1=100;
        iNum2=50;
        //call SubtractionOfTwoIntegers of ISubtract
        pISubtract-> SubtractionOfTwoIntegers(iNum1,iNum2,&iSubtract);
        pISubtract->Release();
        pISubtract=NULL;//make released interface NULL

        //display the result
        wsprintf(str,TEXT("Subtraction of %d and %d is: %d"),iNum1,iNum2,iSubtract);
        MessageBox(hwnd,str,TEXT("Result"),MB_OK);

        //exit the application
         DestroyWindow(hwnd);
         break;

         case WM_DESTROY:
         PostQuitMessage(0);
         break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}
void SafeInterfaceRelease(void)
{
	//code
	if(pISum)
	{
		pISum->Release();
		pISum=NULL;
	}
	if(pISubtract)
	{
		pISubtract->Release();
		pISubtract=NULL;
	}
}






































































