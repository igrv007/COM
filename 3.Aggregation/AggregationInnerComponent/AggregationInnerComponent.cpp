#include<windows.h>
#include "AggregationInnerComponent.h"

//interface declaration (not to be included in .h file)
interface INoAggregationIUnknown 
{
	virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID , void **)=0;
	virtual ULONG __stdcall AddRef_NoAggregation(void)=0;
	virtual ULONG __stdcall Release_NoAggregation(void)=0;
};

//class declarations
class CMultiplicationDivision:public INoAggregationIUnknown,IMultiplication,IDivision
{
private:
	long m_cRef;
	IUnknown *m_pIUnknownOuter;
public:
	//condtructor method declarations
    CMultiplicationDivision(IUnknown *); //new
    //destructor method declarations
    ~CMultiplicationDivision(void);
    //Aggregation supported IUnknown specific method declaraions
    HRESULT __stdcall QueryInterface(REFIID,void **);
    ULONG __stdcall AddRef(void);
    ULONG __stdcall Release(void);

    //Aggregation INoAggregationIUnknown supported specific methods
    HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**);
    ULONG __stdcall AddRef_NoAggregation(void);
    ULONG __stdcall Release_NoAggregation(void);

    //IMultiplication specific method declarations
    HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int *);
   //IDivision specific method declarations
    HRESULT __stdcall DivisionOfTwoIntegers(int ,int, int *);

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
	//IUnknown specific method declaration
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall  AddRef(void);
	ULONG __stdcall   Release(void);

	//IClassFactory specific method declarations
	HRESULT __stdcall CreateInstance(IUnknown * ,REFIID, void **);
	HRESULT __stdcall LockServer (BOOL);
};
//global variable declarations 
long glNumberOfActiveComponents=0; //number of active compnents
long glNumberOfServerLocks =0;     //number of locks onthis dll

//DllMain
BOOL WINAPI DllMain(HINSTANCE hDll,DWORD dwReason ,LPVOID Reserved)
{
	//code
	switch(dwReason)
	{
		case DLL_PROCESS_ATTACH:
		break;
		case DLL_PROCESS_DETACH:
		break;

	}
	return (TRUE);
}
//Implementation of CMultiplicationDivision's Constructor method
CMultiplicationDivision::CMultiplicationDivision(IUnknown *pIUnknownOuter)
{
	//MessageBox(NULL,TEXT("Entering in constructor of inner CoClass "),TEXT("DEBUG"),MB_OK);
 //code
	m_cRef =1; 
	InterlockedIncrement(&glNumberOfActiveComponents); //increment global counter
	if(pIUnknownOuter != NULL)
		m_pIUnknownOuter = pIUnknownOuter;
	else
		m_pIUnknownOuter=reinterpret_cast<IUnknown *>(static_cast<INoAggregationIUnknown *>(this));
	//MessageBox(NULL,TEXT("Exiting from constructor of Inner CoClass "),TEXT("DEBUG"),MB_OK);
}
//implementation of CSumSubtract's destructor  method 
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global counter

}
//Implementation of CMultiplicationDivision's Aggregation supporting IUnknown's methods
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid,void **ppv)
{
	//code
	return(m_pIUnknownOuter->QueryInterface(riid,ppv));
}
ULONG CMultiplicationDivision::AddRef(void)
{
	//code
	return(m_pIUnknownOuter->AddRef());
}
ULONG CMultiplicationDivision::Release()
{
	return(m_pIUnknownOuter->Release());
}
//Implementation of CMultiplicationDivision's Aggregation NonSupporting IUnknown's methods
HRESULT CMultiplicationDivision::QueryInterface_NoAggregation(REFIID riid, void **ppv)
{
	//MessageBox(NULL,TEXT("Entering in QueryInterface_NoAggregation "),TEXT("DEBUG"),MB_OK);
	//code
	if(riid ==IID_IUnknown)
		*ppv=static_cast<INoAggregationIUnknown *>(this);
	else if(riid ==IID_IMultiplication)
		*ppv=static_cast<IMultiplication *> (this);
	else if(riid == IID_IDivision)
		*ppv=static_cast<IDivision *>(this);
	else
	{
		*ppv=NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	//MessageBox(NULL,TEXT("Exit from QueryInterface_NoAggregation"),TEXT("DEBUG"),MB_OK);
	return(S_OK);
}
ULONG CMultiplicationDivision::AddRef_NoAggregation(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}
ULONG CMultiplicationDivision::Release_NoAggregation(void)
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
//implementation of IMultiplication's methods
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1,int num2 ,int *pMultiplication)
{
	//code
	*pMultiplication =num1* num2;
	return(S_OK);
}
//implementation of IDivision's Mehtods
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1 ,int num2, int *pDivision)
{
	//code
	*pDivision=num1/num2;
	return(S_OK);
}
//implementation of CMultiplicationDivisionClassFactory's Constructor method 
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	//code
	m_cRef=1;//hardcoded initialiazation to anticipate failure of QueryInterface
}
//implementation of CMultiplicationDivisionClassFactory's Destructor method
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{
	//code
}
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid , void **ppv)
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
ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(S_OK);
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
//implementation of CMultiplicationDivisionClassFactory's IClassFactory's Mehtods
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
	//MessageBox(NULL,TEXT("Entering in Inner CreateInstance "),TEXT("DEBUG"),MB_OK);
	//variable declarations
	CMultiplicationDivision *pCMultiplicationDivision =NULL;
	HRESULT hr;
	//code
	if((pUnkOuter !=NULL) && (riid !=IID_IUnknown))
	     return(CLASS_E_NOAGGREGATION);
	 //CREAT the instance of component i.e ofCMultiplication class
	 pCMultiplicationDivision= new CMultiplicationDivision(pUnkOuter);
     if(pCMultiplicationDivision ==NULL)
     	return(E_OUTOFMEMORY);

     //GET the requested interface
     	hr=pCMultiplicationDivision->QueryInterface_NoAggregation(riid,ppv);
     	pCMultiplicationDivision->Release_NoAggregation();
     	//MessageBox(NULL,TEXT("Exiting from inner CreateInstance "),TEXT("DEBUG"),MB_OK);
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
//implementation of exported function from this dll
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid,REFIID riid,void **ppv)
{
	//variable declarations
	//MessageBox(NULL,TEXT("Entering in Inner DllGetClassObject "),TEXT("DEBUG"),MB_OK);
	CMultiplicationDivisionClassFactory *pCMultiplicationDivisionClassFactory =NULL;
	HRESULT hr;
	//code
	if(rclsid !=CLSID_MultiplicationDivision)
		return(CLASS_E_CLASSNOTAVAILABLE);
	//CREATE CLASS FACTORY
	pCMultiplicationDivisionClassFactory =new CMultiplicationDivisionClassFactory;
   if(pCMultiplicationDivisionClassFactory == NULL)
   	return(E_OUTOFMEMORY);
   hr=pCMultiplicationDivisionClassFactory->QueryInterface(riid,ppv);
   pCMultiplicationDivisionClassFactory->Release();
   //MessageBox(NULL,TEXT("Exit from Inner DllGetClassObject "),TEXT("DEBUG"),MB_OK);
   return(hr);
}
HRESULT __stdcall DllCanUnloadNow(void)
{
	//code
	if((glNumberOfActiveComponents== 0) &&(glNumberOfServerLocks ==0))
		return(S_OK);
	else
		return(S_FALSE);

}


