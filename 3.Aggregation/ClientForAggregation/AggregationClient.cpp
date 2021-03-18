#include<windows.h>
//#include<process.h>
//#include<Rpc.h>
#include"HeaderForClient.h"

//global function declarations
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//global variable declarations
ISum *pISum=NULL;
ISubtract *pISubtract =NULL;
IMultiplication *pIMultiplication =NULL;
IDivision *pIDivision =NULL;

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
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
		MessageBox(NULL,TEXT("COM Library can not be initialized."),TEXT("ERROR"),MB_OK);
	    exit(0);
	}

	//wndclassex initialization 
	wndclass.cbSize=sizeof(wndclass);
	wndclass.style=CS_HREDRAW | CS_VREDRAW;
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

    //REGISTER window class
    RegisterClassEx(&wndclass);

    //createWindow
    hwnd=CreateWindow(AppName,
    	              TEXT("Client of COM Dll Serever"),
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
    //msg loop
    while(GetMessage(&msg,NULL,0,0))
    {
    	TranslateMessage(&msg);
    	DispatchMessage(&msg);
    } 
   //COM Un-initialization
    CoUninitialize();
    return((int)msg.wParam);

}
//window procedure
LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	//function declarations
	void SafeInterfaceRelease(void);
	//variable declarations
	HRESULT hr;
	int iNum1,iNum2,iSum,iSubtraction,iMultiplication,iDivision;
	TCHAR str[255];
	//code
	switch(iMsg)
	{
		case WM_CREATE:
		     //TCHAR str1[256];
	         //wsprintf(str1, TEXT(" from client Passing CLSID_SumSubtract: 0x%s\nIID_ISum: 0x%s\n"), CLSID_SumSubtract->ToString("B"), IID_ISum->ToString("B"));
	      // MessageBox(NULL,TEXT("Client's WM_CREATE"), TEXT("Debug"), MB_OK);
		     hr=CoCreateInstance(CLSID_SumSubtract,NULL,CLSCTX_INPROC_SERVER,IID_ISum,(void **)&pISum);
        if(FAILED(hr))
        {
        	MessageBox(hwnd,TEXT("ISum interface can not be obtained"),TEXT("ERROR"),MB_OK);
        	DestroyWindow(hwnd);
        }
        //initialize arguments hardcoded
        iNum1=100;
        iNum2=50;
        //call of SumOfTwoIntergers of ISum to get the sum 
        pISum->SumOfTwoIntegers(iNum1,iNum2,&iSum);
        //display the result
        wsprintf(str,TEXT("Sum of %d and %d =%d"),iNum1,iNum2,iSum);
        MessageBox(hwnd,str,TEXT("Result"),MB_OK);

        //call QueryInterface() on ISum to get ISubtract's pointer
        hr=pISum->QueryInterface(IID_ISubtract,(void **)&pISubtract);
        if(FAILED(hr))
        {
        	MessageBox(hwnd,TEXT("ISubtract can not be obtained"),TEXT("ERROR"),MB_OK);
        	DestroyWindow(hwnd);
        }
        //as ISum is now not needed onwards ,Release it
        pISum->Release();
        pISum=NULL;  //make released interface NULL

        //again initialize arguments hardcoded
        iNum1=100;
        iNum2=75;

        pISubtract->SubtractionOfTwoIntegers(iNum1,iNum2,&iSubtraction);
        wsprintf(str,TEXT("Subtraction of %d and %d = %d"),iNum1,iNum2,iSubtraction);
        MessageBox(hwnd,str,TEXT("Result"),MB_OK);

        //call QueryInterface on ISubtract to get IMultiplication's pointer
        hr=pISubtract->QueryInterface(IID_IMultiplication,(void **)&pIMultiplication);
        if(FAILED(hr))
        {
            MessageBox(hwnd,TEXT("IMultiplication interface can not be obtained"),TEXT("ERROR"),MB_OK);
            DestroyWindow(hwnd);
        }
        //as ISubtract is now needed onwards,release it
        pISubtract->Release();
        pISubtract=NULL;

        //again initialize arguments hardcoded
        iNum1=5;
        iNum2=6;

        pIMultiplication->MultiplicationOfTwoIntegers(iNum1,iNum2,&iMultiplication);
        wsprintf(str,TEXT("Multiplication of %d and %d = %d "),iNum1,iNum2,iMultiplication);
        MessageBox(hwnd,str,TEXT("Result"),MB_OK);

        //call QueryInterface() on IMultiplication to get the IDivision pointer
        hr=pIMultiplication->QueryInterface(IID_IDivision,(void **)&pIDivision);
        if(FAILED(hr))
        {
        	MessageBox(hwnd,TEXT("IDivision interface can not be obtained"),TEXT("ERROR"),MB_OK);
        	DestroyWindow(hwnd);

        }
        //as IMultiplication is now needed onwards ,release it
        pIMultiplication->Release();
        pIMultiplication=NULL;

        iNum1=100;
        iNum2=10;

        pIDivision->DivisionOfTwoIntegers(iNum1,iNum2,&iDivision);

        wsprintf(str,TEXT("Division of %d and %d = %d"),iNum1,iNum2,iDivision);
        MessageBox(hwnd,str,TEXT("Result"),MB_OK);

        //finally release IDivision
        pIDivision->Release();
        pIDivision=NULL;

        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
          SafeInterfaceRelease();
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
	if(pIMultiplication)
	{
		pIMultiplication->Release();
		pIMultiplication=NULL;
	}
	if(pIDivision)
	{
		pIDivision->Release();
		pIDivision=NULL;
	}
}


