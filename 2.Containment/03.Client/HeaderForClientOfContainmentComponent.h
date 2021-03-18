class ISum:public IUnknown
{
public:
    virtual HRESULT __stdcall SumOfTwoIntegers(int,int,int *)=0; //pure virtual

};

class ISubtract:public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *)=0;//pure virtual
};

class IMultiplication:public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int *)=0;//pure virtual
};

class IDivision:public IUnknown
{
public:
    virtual HRESULT __stdcall DivisionOfTwoIntegers(int,int,int *)=0;//pure virtual
};


//CLSID OF SumSubtract Component {B6FF1DB1-BDD8-4D3E-8338-4143F2CD378E}
const CLSID CLSID_SumSubtract = {0xb6ff1db1, 0xbdd8, 0x4d3e, 0x83, 0x38, 0x41, 0x43, 0xf2, 0xcd, 0x37, 0x8e};

//IID of ISum Interface {127AE258-56AB-4223-84B9-34FFDBC94748} 
const IID IID_ISum={0x127ae258, 0x56ab, 0x4223, 0x84, 0xb9, 0x34, 0xff, 0xdb, 0xc9, 0x47, 0x48};

//IID of ISubtract interface {2C95360E-AA2D-42F0-A726-9AFCC45C2FCD}
const IID IID_ISubtract={0x2c95360e, 0xaa2d, 0x42f0, 0xa7, 0x26, 0x9a, 0xfc, 0xc4, 0x5c, 0x2f, 0xcd};

//IID of IMultiplication Interface {3052AC97-1273-4F8D-9FBE-98746219CCFD}
const IID IID_IMultiplication={0x3052ac97, 0x1273, 0x4f8d, 0x9f, 0xbe, 0x98, 0x74, 0x62, 0x19, 0xcc, 0xfd};

//IID of IDivision Interface {DC39760F-79E6-47A5-AFDE-3595D6E05886}
const IID IID_IDivision ={0xdc39760f, 0x79e6, 0x47a5, 0xaf, 0xde, 0x35, 0x95, 0xd6, 0xe0, 0x58, 0x86};

