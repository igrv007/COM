#include<windows.h>
#include"ContainmentInnerComponent.h"

//class declarations
 class CMultiplicationDivision:public IMultiplication,IDivision
 {
 private:
 	long m_cRef;
 public:
 	//constructor method declarations
 	CMultiplicationDivision(void);
 	//destructor method declarations
 	~CMultiplicationDivision(void);
 	//IUnknown specific method declarations(inherited)
 	HRESULT __stdcall QueryInterface(REFIID,void **);
 	ULONG __stdcall AddRef(void);
 	ULONG __stdcall Release(void);
 	//IMultiplication specific method declarations(inherited)
 	HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int*);
 	//IDivision specific method declarations(inherited)
 	HRESULT __stdcall DivisionOfTwoIntegers(int,int,int *);

 };
 class CMultiplicationDivisionClassFactory:public IClassFactory
 {
 private:
 	long m_cRef;
 public:
 	//constructor method declarations
 	CMultiplicationDivisionClassFactory(void);
 	//destructor method declarations
 	~CMultiplicationDivisionClassFactory(void);
 	//IUnknown specific method declarations(inherited)
 	HRESULT __stdcall QueryInterface(REFIID,void **);
 	ULONG __stdcall AddRef(void);
 	ULONG __stdcall Release(void);
 	//IClassFactory specific method declarations(inherited)
 	HRESULT __stdcall CreateInstance(IUnknown *,REFIID,void **);
 	HRESULT __stdcall LockServer(BOOL);
 };

//global variable declarations
 long glNumberOfActiveComponents=0; //number of active components
 long glNumberOfServerLocks     =0; //number of locks on this dll

 //DllMain
 BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID Reserved)
 {
 	//code
 	switch(dwReason)
 	{
 		case DLL_PROCESS_ATTACH:
            break;
        case DLL_PROCESS_DETACH:
            break;
 	}
 	return(TRUE);
 }

 //implementation of CMultiplicationDivision's Constructor Method
 CMultiplicationDivision::CMultiplicationDivision(void)
{
	//code
	m_cRef =1; //hardcoded initialization to anticipate possible failure of  QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);//increment global counter	
}

CMultiplicationDivision::~CMultiplicationDivision(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents);//decrement global counter
}

//Implementation of CMultiplicationDivision's IUnknown's methods
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid,void **ppv)
{
	//TCHAR str[256];
	//MessageBox(NULL,TEXT("Entering in InnerComponent CMultiplicationDivision's QueryInterface"),TEXT("SUCCESS"),MB_OK);
	//wsprintf(str, TEXT("RIID is: 0x%x\nIID_IUNK is 0x%x\nIID_IMUL is 0x%x\nIID_IDIV is 0x%x"), riid.Data1, IID_IUnknown.Data1, IID_IMultiplication.Data1, IID_IDivision.Data1);
	//MessageBox(NULL, str, TEXT("Debug"), MB_OK);
   //code
	if(riid == IID_IUnknown)
		*ppv=static_cast<IMultiplication *>(this);
	else if(riid == IID_IMultiplication)
		*ppv=static_cast<IMultiplication *>(this);
	else if(riid == IID_IDivision)
		*ppv=static_cast<IDivision *>(this);
	else
	{   
		
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	//MessageBox(NULL,TEXT("Exiting from InnerComponent CMultiplicationDivision's QueryInterface"),TEXT("SUCCESS"),MB_OK);
	return(S_OK);
}

ULONG CMultiplicationDivision::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CMultiplicationDivision::Release(void)
{
	//code
	InterlockedDecrement(&m_cRef);
	if(m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation Of IMultiplication's Methods
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1,int num2,int *pMultiplication)
{
	//code
	*pMultiplication=num1*num2;
	return(S_OK);
}
//Implementation of IDivision's methods
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2,int *pDivision)
{
  //code
	*pDivision=num1/num2;
	return(S_OK);
}

//implementation of CMultiplicationDivisionClassFactory's Constructor method
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	//code
	m_cRef=1; //hardcoded initialization to anticipate possible failure of QueryInterface

}

//implementation of CMultiplicationDivisionClassFactory'd Destructor method
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
  //code
}
//implementation of CMultiplicationDivisionClassFactory's IClassFactory's IUnknown's methods
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid,void **ppv)
{
	//MessageBox(NULL,TEXT("Entering in InnerComponent CMultiplicationDivisionClassFactory's QueryInterface"),TEXT("SUCCESS"),MB_OK);
	/*TCHAR str[256];
	wsprintf(str, TEXT("Received CLSID: %ld\nriid: %ld\n"), rclsid, riid);
	MessageBox(NULL, str, TEXT("Debug"), MB_OK);*/
	if(riid == IID_IUnknown)
		*ppv=static_cast<IClassFactory *>(this);
	else if(riid == IID_IClassFactory)
		*ppv=static_cast<IClassFactory *>(this);
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	//MessageBox(NULL,TEXT("Exiting from InnerComponent CMultiplicationDivisionClassFactory's QueryInterface"),TEXT("SUCCESS"),MB_OK);
	return(S_OK);
}
ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	///code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);

}
ULONG CMultiplicationDivisionClassFactory::Release(void)
{
	//code
	InterlockedDecrement(&m_cRef);
	if(m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);

}
//Implementation of CMultiplicationDivisionClassFactory's IClassFactory's methods
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
	//MessageBox(NULL,TEXT("Entering in InnerComponent CMultiplicationDivisionClassFactory's CreateInstance"),TEXT("SUCCESS"),MB_OK);

	//TCHAR str[256];
	//wsprintf(str, TEXT("innercomponent Create instance received riid of IID_IMultiplication: 0x%x\n"), riid.Data1);
	//MessageBox(NULL, str, TEXT("Debug"), MB_OK);
	//variable declarations
	CMultiplicationDivision *pCMultiplicationDivision =NULL;
	HRESULT hr;
	//code
	if(pUnkOuter !=NULL)
		return(CLASS_E_NOAGGREGATION);
	//create the instance of components i.e CMultiplicationDivision class
	pCMultiplicationDivision =new CMultiplicationDivision;

	if(pCMultiplicationDivision ==NULL)
		return(E_OUTOFMEMORY);
	//get the requested interface
	hr=pCMultiplicationDivision->QueryInterface(riid,ppv);
	pCMultiplicationDivision->Release(); //anticipate possible failure of QueryInterface
	//MessageBox(NULL,TEXT("Exiting from InnerComponent CMultiplicationDivisionClassFactory's CreateInstance"),TEXT("SUCCESS"),MB_OK);
	return(hr);
}

HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
{
	//code
	if(fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}

//implementation of Exported functions frmo this Dll
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid,REFIID riid,void ** ppv)
{
	//MessageBox(NULL,TEXT("Entering in InnerComponent DllGetClassObject"),TEXT("SUCCESS"),MB_OK);

	/*TCHAR str[256];
	wsprintf(str, TEXT("Received CLSID: %ld\nriid: %ld\n"), rclsid, riid);
	MessageBox(NULL, str, TEXT("Debug"), MB_OK);*/

	//variable declarations
	CMultiplicationDivisionClassFactory *pCMultiplicationDivisionClassFactory =NULL;
	HRESULT hr;
   
   ///code
	if(rclsid !=CLSID_MultiplicationDivision)
		return(CLASS_E_CLASSNOTAVAILABLE);
	//create class factory
	pCMultiplicationDivisionClassFactory =new CMultiplicationDivisionClassFactory;
    if(pCMultiplicationDivisionClassFactory ==NULL)
    	return(E_OUTOFMEMORY);
    hr=pCMultiplicationDivisionClassFactory->QueryInterface(riid,ppv);
    pCMultiplicationDivisionClassFactory->Release();  //anticipate possible failure to QueryInterface
    //MessageBox(NULL,TEXT("Exiting from InnerComponent DllGetClassObject"),TEXT("SUCCESS"),MB_OK);
    return(hr);
}
HRESULT __stdcall DllCanUnloadNow(void)
{
	//code
	if((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
         return(S_OK);
     else
     	return(S_FALSE);
}






























