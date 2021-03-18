#include<windows.h>
#include"AggregationInnerComponent.h"
#include"AggregationOuterComponent.h"

class CSumSubtract:public ISum,ISubtract
{
private:
	long m_cRef;
	IUnknown *m_pIUnknownInner;
	IMultiplication *m_pIMultiplication;
	IDivision *m_pIDivision;
public:
	//constructor method declarations
	CSumSubtract(void);
	//destructor method declarations
	~CSumSubtract(void);

	//IUnknown specific method declarations
	HRESULT __stdcall QueryInterface(REFIID,void **ppv);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//ISum specific method declarations
	HRESULT __stdcall SumOfTwoIntegers(int,int,int *);
	//ISubtract specific method declarations
	HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *);
	//custom method for inner component cretion
	HRESULT __stdcall InitializeInnerComponent(void);
};
class CSumSubtractClassFactory:public IClassFactory
{
private:
	long m_cRef;
public:
	//constructor method declarations
	CSumSubtractClassFactory(void);
	//destrctor method declartions
	~CSumSubtractClassFactory(void);
	//IUnknown specific method declarations
	HRESULT __stdcall QueryInterface(REFIID ,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//IClassFactory specific method declarations
	HRESULT __stdcall CreateInstance(IUnknown * ,REFIID ,void **);
	HRESULT __stdcall LockServer(BOOL);
};

//global variable declarations
long glNumberOfActiveComponents=0; 
long glNumberOfServerLocks=0;

//DllMain
BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason,LPVOID Reserved)
{
	//code
	switch(dwReason)
	{
		case  DLL_PROCESS_ATTACH:
		break;
		case  DLL_PROCESS_DETACH:
		break;
	}
	return(TRUE);
}
///implementation of CSumSubtract's Constructor method
CSumSubtract::CSumSubtract(void)
{
	//code
	//initialize private member
	m_pIUnknownInner=NULL;
	m_pIMultiplication=NULL;
	m_pIDivision=NULL;
	m_cRef=1;//hardcoded initiaiize to anticipate possible failure of QueryInterface
	InterlockedIncrement(&glNumberOfActiveComponents);
}
//implementation of CSumSubtract's destructor method
CSumSubtract::~CSumSubtract(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents);
	if(m_pIMultiplication)
	{
		m_pIMultiplication->Release();
	    m_pIMultiplication=NULL;
	}
	if(m_pIDivision)
	{
		m_pIDivision->Release();
		m_pIDivision=NULL;
	}
	if(m_pIUnknownInner)
	{
		m_pIUnknownInner->Release();
		m_pIUnknownInner=NULL;
	}

}

//implementation of CSumSubtract's IUnknown's methods
HRESULT CSumSubtract::QueryInterface(REFIID riid,void **ppv)
{
 //MessageBox(NULL,TEXT("Entering in CSumSubtract QueryInterface "),TEXT("DEBUG"),MB_OK);
	//code
	if(riid ==IID_IUnknown)
		*ppv=static_cast<ISum *>(this);
	else if(riid == IID_ISum)
		*ppv=static_cast<ISum *>(this);
	else if(riid == IID_ISubtract)
		*ppv=static_cast<ISubtract *>(this);
	else if(riid == IID_IMultiplication)
		return(m_pIUnknownInner->QueryInterface(riid,ppv));
	else if(riid ==IID_IDivision)
		return(m_pIUnknownInner->QueryInterface(riid,ppv));
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	//MessageBox(NULL,TEXT("Exting from CSumSubtract QueryInterface"),TEXT("DEBUG"),MB_OK);
	return(S_OK);
}
ULONG CSumSubtract::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSumSubtract::Release(void)
{
	//code
	InterlockedDecrement(&m_cRef);
	if(m_cRef ==0 )
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}
//implementation of ISum's methods
HRESULT CSumSubtract::SumOfTwoIntegers(int num1,int num2,int *pSum)
{
	//code
	*pSum=num1+num2;
	return(S_OK);
}
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1 ,int num2,int *pSubtract)
{
	*pSubtract=num1-num2;
	return(S_OK);
}

HRESULT CSumSubtract::InitializeInnerComponent(void)
{
	//MessageBox(NULL,TEXT("Entering in InitializeInnerComponent "),TEXT("DEBUG"),MB_OK);
	//variable declarations
	HRESULT hr;
	//code
	hr=CoCreateInstance(CLSID_MultiplicationDivision,
		reinterpret_cast<IUnknown *>(this),
		CLSCTX_INPROC_SERVER,
		IID_IUnknown,
		(void**)&m_pIUnknownInner);
	if(FAILED(hr))
	{
		MessageBox(NULL,TEXT("failed to get IUnknownInner\n"),TEXT("ERROR"),MB_OK);
		return(E_FAIL);
	}
	hr=m_pIUnknownInner->QueryInterface(IID_IMultiplication,(void**)&m_pIMultiplication);

	if(FAILED(hr))
	{
		MessageBox(NULL,TEXT("IMultiplication interface can not be obtained"),TEXT("ERROR"),MB_OK);
		m_pIUnknownInner->Release();
		m_pIUnknownInner=NULL;
		return(E_FAIL);
	}
	//MessageBox(NULL,TEXT("Exting from InitializeInnerComponent "),TEXT("DEBUG"),MB_OK);
	return(S_OK);
}
//implementation of CSumSubtractClassFactory'Cunstructor method
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	//code
	m_cRef=1;

}

CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	//code
}
HRESULT  CSumSubtractClassFactory::QueryInterface(REFIID riid,void **ppv)
{
	//code
	if(riid ==IID_IUnknown)
		*ppv=static_cast<IClassFactory *>(this);
	else if(riid ==IID_IClassFactory)
		*ppv=static_cast<IClassFactory *>(this);
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}
ULONG CSumSubtractClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CSumSubtractClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if(m_cRef == 0)
     {
     	delete(this);
     	return(0);

     }
     return(m_cRef);
}
//implimentation ofCSumSubtractClassFactory's IClassFactory's Methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
	//MessageBox(NULL,TEXT("Entering in Outer CreateInstance "),TEXT("DEBUG"),MB_OK);

	//variable declartions
	CSumSubtract *pCSumSubtract=NULL;
	HRESULT hr;
	//code
	if(pUnkOuter !=NULL)
		return(CLASS_E_NOAGGREGATION);
	//create the instance of component i.e. CSumSubtract class
	pCSumSubtract= new CSumSubtract;
	if (pCSumSubtract ==NULL)
		return(E_OUTOFMEMORY);
	//initialie the inner component
	hr=pCSumSubtract->InitializeInnerComponent();
	if(FAILED(hr))
	{
		MessageBox(NULL,TEXT("Failed to initialize inner component"),TEXT("ERROR"),MB_OK);
		pCSumSubtract->Release();
		return(hr);
	}
	//get the requested interface
	hr=pCSumSubtract->QueryInterface(riid,ppv);
	pCSumSubtract->Release();
	//MessageBox(NULL,TEXT("Exting from  Outer CreateInstance "),TEXT("DEBUG"),MB_OK);
    return(hr);
	
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	//code
	if(fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid,REFIID riid,void **ppv)
{
	//variable declarations
	//MessageBox(NULL,TEXT("Entering in Outer DllGetClassObject "),TEXT("DEBUG"),MB_OK);
	CSumSubtractClassFactory *pCSumSubtractClassfactory =NULL;
	HRESULT hr;
	if(rclsid !=CLSID_SumSubtract)
		return(CLASS_E_CLASSNOTAVAILABLE);
	//create class factory
	pCSumSubtractClassfactory =new CSumSubtractClassFactory;
	if(pCSumSubtractClassfactory ==NULL)
		return(E_OUTOFMEMORY);
	hr=pCSumSubtractClassfactory->QueryInterface(riid,ppv);
	pCSumSubtractClassfactory->Release();
	//MessageBox(NULL,TEXT("Exting from  Outer DllGetClassObject "),TEXT("DEBUG"),MB_OK);
    return(hr);
}
HRESULT __stdcall DllCanUnloadNow(void)
{
	//code
	if((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks ==0))
		return(S_OK);
	else
		return(S_FALSE);
}



