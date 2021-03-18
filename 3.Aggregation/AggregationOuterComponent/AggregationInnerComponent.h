class IMultiplication:public IUnknown
{
	public:
		//IMultiplication specific method declarations
		virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int *)=0;//pure virtual

};
class IDivision:public IUnknown
{
public:
	//IDivision specific methods declarations
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int,int,int *)=0;//pure virtual
};

//CLSID of MultiplicationDivision Component {05EEFB73-1DBE-4CD5-949E-761AD693D15D}
const CLSID CLSID_MultiplicationDivision={0x5eefb73, 0x1dbe, 0x4cd5, 0x94, 0x9e, 0x76, 0x1a, 0xd6, 0x93, 0xd1, 0x5d};

//IID of IMultiplication Interface{85FF9B2F-A65E-42E8-84D1-79023E1D9321}
const IID IID_IMultiplication={0x85ff9b2f, 0xa65e, 0x42e8, 0x84, 0xd1, 0x79, 0x2, 0x3e, 0x1d, 0x93, 0x21};

//IID of IDivision interface{06D4469E-A5B2-448B-8D57-3BD34F9866F2}
const IID IID_IDivision={0x6d4469e, 0xa5b2, 0x448b, 0x8d, 0x57, 0x3b, 0xd3, 0x4f, 0x98, 0x66, 0xf2};

