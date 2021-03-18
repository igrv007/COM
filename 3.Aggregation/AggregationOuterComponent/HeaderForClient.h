class ISum:public IUnknown
{
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int,int,int *)=0;
};
class ISubtract:public IUnknown
{
	public:
		virtual HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *)=0;
};
class IMultiplication:public IUnknown
{
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int,int,int *)=0;

};
class IDivision:public IUnknown
{
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int,int,int,int *)=0;
};

//CLSID of SumSubtract component {1802E75A-B4CE-4DFD-9F92-FD828F464B18}
const CLSID CLSID_SumSubtract={0x1802e75a, 0xb4ce, 0x4dfd, 0x9f, 0x92, 0xfd, 0x82, 0x8f, 0x46, 0x4b, 0x18};

//IID of ISum Interface {F7C4D07E-2F5B-4329-B340-7B8056A062C6}
const IID IID_ISum={0xf7c4d07e, 0x2f5b, 0x4329, 0xb3, 0x40, 0x7b, 0x80, 0x56, 0xa0, 0x62, 0xc6};

//IID of ISubtract interface {2055BD2B-478D-4C6D-9243-42CABB4D3003}
const IID IID_ISubtract={0x2055bd2b, 0x478d, 0x4c6d, 0x92, 0x43, 0x42, 0xca, 0xbb, 0x4d, 0x30, 0x3};


//CLSID of MultiplicationDivision Component {05EEFB73-1DBE-4CD5-949E-761AD693D15D}
const CLSID CLSID_MultiplicationDivision={0x5eefb73, 0x1dbe, 0x4cd5, 0x94, 0x9e, 0x76, 0x1a, 0xd6, 0x93, 0xd1, 0x5d};

//IID of IMultiplication Interface{85FF9B2F-A65E-42E8-84D1-79023E1D9321}
const IID IID_IMultiplication={0x85ff9b2f, 0xa65e, 0x42e8, 0x84, 0xd1, 0x79, 0x2, 0x3e, 0x1d, 0x93, 0x21};

//IID of IDivision interface{06D4469E-A5B2-448B-8D57-3BD34F9866F2}
const IID IID_IDivision={0x6d4469e, 0xa5b2, 0x448b, 0x8d, 0x57, 0x3b, 0xd3, 0x4f, 0x98, 0x66, 0xf2};


