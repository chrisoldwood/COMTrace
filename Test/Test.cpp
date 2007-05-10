#include "stdafx.h"
#include <iomanip>

#import "../COMTrace.tlb" raw_interfaces_only no_smart_pointers

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
//	typedef WCL::ComPtr<COMTraceLib::ICustomInterface> IInterfacePtr;
//	typedef WCL::ComPtr<COMTraceLib::IDualInterface> IInterfacePtr;
	typedef WCL::ComPtr<::IDispatch> IInterfacePtr;

	::CoInitialize(NULL);

	try
	{
//		IInterfacePtr pTracer(__uuidof(COMTraceLib::CustomTracer));
		IInterfacePtr pTracer(__uuidof(COMTraceLib::DualTracer));
//		IInterfacePtr pTracer(__uuidof(COMTraceLib::DispatchTracer));
		IInterfacePtr pTracer2(pTracer);
		IInterfacePtr pTracer3;

		pTracer3 = pTracer2;
		pTracer3 = IInterfacePtr();

		BSTR bstrIn  = ::SysAllocString(L"Hello World!");
		BSTR bstrOut = NULL;

		wchar_t* apszMethods[1] = { L"TestMethod" };
		DISPID   anMethodIDs[1];

		HRESULT hr = pTracer->GetIDsOfNames(IID_NULL, apszMethods, ARRAYSIZE(apszMethods), 0, anMethodIDs);

		if (SUCCEEDED(hr))
		{
			WCL::Variant vtInput(::SysAllocString(bstrIn));
			DISPPARAMS   oParams = {&vtInput, nullptr, 1, 0};
			WCL::Variant vtResult;
			EXCEPINFO    oExcepInfo = {0};
			UINT         uArgErr = 0;

			hr = pTracer->Invoke(anMethodIDs[0], IID_NULL, 0, DISPATCH_METHOD, &oParams, &vtResult, &oExcepInfo, &uArgErr);

			if (SUCCEEDED(hr))
			{
				bstrOut = ::SysAllocString(V_BSTR(&vtResult));
			}
		}

//		HRESULT hr = pTracer->TestMethod(bstrIn, &bstrOut);

		std::wcout << bstrIn  << std::endl;
		std::wcout << bstrOut << std::endl;
		std::wcout << "0x" << std::setw(8) << std::setfill(L'0') << std::hex << hr << " ";
		std::wcout << CStrCvt::FormatError(hr) << std::endl;

		pTracer.Release();
		pTracer2.Release();
		pTracer3.Release();

		::SysFreeString(bstrIn);
		::SysFreeString(bstrOut);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	::CoUninitialize();

	return 0;
}
