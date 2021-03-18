class ISum :public IUnknown 
{
	public :
	    //ISum specific method declarations
	    virtual HRESULT __stdcall SumOfTwoIntegers(int,int,int *)=0;//pure virtual

};
class ISubtract:public IUnknown
{
	public :
	      //ISubtract specific method declarations
	   virtual HRESULT __stdcall SubtractionOfTwoIntegers(int,int,int *)=0;//pure virtual

};

//CLSID of SumSutract Component  {B079B0A7-AC16-4166-8C0B-3B74EE0033CA}
const CLSID CLSID_SumSubtract={0xb079b0a7, 0xac16, 0x4166, 0x8c, 0xb, 0x3b, 0x74, 0xee, 0x0, 0x33, 0xca};

//IID of ISum Interface{62E82AF4-7986-4AE8-AFB3-8D922CDD683E}
const IID IID_ISum={0x62e82af4, 0x7986, 0x4ae8, 0xaf, 0xb3, 0x8d, 0x92, 0x2c, 0xdd, 0x68, 0x3e};

//IID of ISubtract Interface {E5FC2714-A707-4837-B3F6-D5CC8252AEAE}
const IID IID_ISubtract={0xe5fc2714, 0xa707, 0x4837, 0xb3, 0xf6, 0xd5, 0xcc, 0x82, 0x52, 0xae, 0xae};

