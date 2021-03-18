class ISum:public IUnknown
{
	public:
		virtual HRESULT __stdcall SumOfTwoIntegers(int,int,int *)=0;//pure virtual

};
class ISubtract:public IUnknown
{
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *)=0;//pure vittual	
};

//CLSID of SumSubtract component {1802E75A-B4CE-4DFD-9F92-FD828F464B18}
const CLSID CLSID_SumSubtract={0x1802e75a, 0xb4ce, 0x4dfd, 0x9f, 0x92, 0xfd, 0x82, 0x8f, 0x46, 0x4b, 0x18};

//IID of ISum Interface {F7C4D07E-2F5B-4329-B340-7B8056A062C6}
const IID IID_ISum={0xf7c4d07e, 0x2f5b, 0x4329, 0xb3, 0x40, 0x7b, 0x80, 0x56, 0xa0, 0x62, 0xc6};

//IID of ISubtract interface {2055BD2B-478D-4C6D-9243-42CABB4D3003}
const IID IID_ISubtract={0x2055bd2b, 0x478d, 0x4c6d, 0x92, 0x43, 0x42, 0xca, 0xbb, 0x4d, 0x30, 0x3};

