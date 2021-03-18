class IMultiplication:public IUnknown 
{
public:
	//IMultiplication specific method declarations
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int *)=0; //pure virtual	
};
class IDivision:public IUnknown
{
public:
	//IDivision specific method declarations
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int,int,int *)=0;//pure virtual	
};

//CLSID of MultiplicationDivision Component {552AC6EA-ED62-4FC8-A03B-C4D8F9CF64CA}
const CLSID CLSID_MultiplicationDivision ={0x552ac6ea, 0xed62, 0x4fc8, 0xa0, 0x3b, 0xc4, 0xd8, 0xf9, 0xcf, 0x64, 0xca};

//IID of IMultiplication Interface {3052AC97-1273-4F8D-9FBE-98746219CCFD}
const IID IID_IMultiplication={0x3052ac97, 0x1273, 0x4f8d, 0x9f, 0xbe, 0x98, 0x74, 0x62, 0x19, 0xcc, 0xfd};

//IID of IDivision Interface {DC39760F-79E6-47A5-AFDE-3595D6E05886}
const IID IID_IDivision ={0xdc39760f, 0x79e6, 0x47a5, 0xaf, 0xde, 0x35, 0x95, 0xd6, 0xe0, 0x58, 0x86};

