#include<windows.h>
#include"ClassFactoryServer.h"

//class declarations
class CSumSubtract:public ISum,ISubtract
{
private:
	long m_cRef;
public:
	//constructor method declarations
	CSumSubtract(void);
	//destructor method declarations
	~CSumSubtract(void);
	//IUnknown specific method declaratios (inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	//ISum specific method declarations(inhterited)
	HRESULT __stdcall SumOfTwoIntegers(int,int,int*);
	//ISubtract specific method declarations(inherited)
	HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *);

};
class CSumSubtractClassFactory:public IClassFactory
{
private: 
	long m_cRef;
public: 
	//constructor method declarations
	CSumSubtractClassFactory(void);
	//destructor method declarations
	~CSumSubtractClassFactory(void);
	//IUnknown specific method declarations(inherited)
	HRESULT __stdcall QueryInterface(REFIID,void **);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	//IClassFactory specific method declarations (inherited)
	HRESULT __stdcall CreateInstance(IUnknown*,REFIID,void **);
	HRESULT __stdcall LockServer(BOOL);

};


//global variable declarations 
long glNumberOfActiveComponents=0; //number of Active componenets
long glNumberOfServerLocks=0;      //number of locks on this dll
 
//DLL main
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
 return (TRUE);
}

//Implemantation of CSumSubtract's Constuctor Method
CSumSubtract::CSumSubtract(void)
{
	//code 
	m_cRef=1; //hardcoded initialization to anticipate possible failure
	InterlockedIncrement(&glNumberOfActiveComponents);//increment global counter

}
CSumSubtract::~CSumSubtract(void)
{
	//code 
	InterlockedIncrement(&glNumberOfActiveComponents);//decrement global counter

}

//implementationof CSumSubtract's IUnknown's methods

HRESULT  CSumSubtract::QueryInterface(REFIID riid,void **ppv)
{
	//code
	if(riid == IID_IUnknown)
       *ppv=static_cast<ISum *>(this);
    else if(riid==IID_ISum)
    	*ppv=static_cast<ISum *>(this);
    else if(riid == IID_ISubtract)
    	*ppv=static_cast<ISubtract *>(this);
    else
    {
    	*ppv=NULL;
    	return(E_NOINTERFACE);
    }
    reinterpret_cast<IUnknown *>(*ppv)->AddRef();
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
    if(m_cRef == 0)
    {
    	delete(this);
    	return(0);
    }
    return(m_cRef);
}

//Implementation of ISum'sMethods
 HRESULT CSumSubtract::SumOfTwoIntegers(int num1,int num2,int *pSum)
 {
 	//code
 	*pSum=num1+num2;
 	return(S_OK);
 }

//Implementation of ISubtract's methods
  HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1,int num2,int *pSubtract)
  {
  	//code
  	*pSubtract=num1-num2;
  	return(S_OK);
  }

//Implementation of CSumSubtractClassFactory's Constructor methods
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{

	//code
	m_cRef=1;//hardcoded initialization to anticipate possible failureof QueryInterface()

}
 

 //Implementation Of CSumSubtractClassFactory's Destructor method
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	//code

}

//implementatoin of CSumSubtractClassFactory's IClassFactory's IUknown's Methods
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid,void **ppv)
{
	//code
	if(riid == IID_IUnknown)
		*ppv=static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
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
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
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
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter,REFIID riid,void **ppv)
{
	//variable declarations
	CSumSubtract *pCSumSubtract=NULL;
	HRESULT hr;

	//code
	if(pUnkOuter !=NULL)
		return (CLASS_E_NOAGGREGATION);
	//create the instance of component i.e .of CSumSubtract class
	pCSumSubtract=new CSumSubtract;
	if(pCSumSubtract ==NULL)
		return (E_OUTOFMEMORY);

	//get the requested interface
	hr=pCSumSubtract->QueryInterface(riid,ppv);
    pCSumSubtract->Release(); //anticipate possible failure ofQueryInterface()
    return(hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	//code
	if(fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedIncrement(&glNumberOfServerLocks);
	return(S_OK);
}

//implementation of Exported functions from this dll
HRESULT __stdcall DllGetClassObject(REFCLSID rclsid,REFIID riid,void **ppv) 
{
	//variable declaraions
	CSumSubtractClassFactory *pCSumSubtractClassFactory=NULL;
	HRESULT hr;

	//code
	if(rclsid != CLSID_SumSubtract)
		return (CLASS_E_CLASSNOTAVAILABLE);
     
    //create class factory
    pCSumSubtractClassFactory=new CSumSubtractClassFactory;
    if(pCSumSubtractClassFactory == NULL)
    	return(E_OUTOFMEMORY);
    hr=pCSumSubtractClassFactory->QueryInterface(riid,ppv);
    pCSumSubtractClassFactory->Release();//anticipate possibla failure of Queryinterface
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



