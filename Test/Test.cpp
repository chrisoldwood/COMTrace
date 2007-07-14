#include "stdafx.h"
#include <WCL/ComPtr.hpp>
#include <WCL/StrCvt.hpp>
#include <WCL/Variant.hpp>
#include <WCL/ComStr.hpp>
#include <WCL/AutoCom.hpp>
#include <iomanip>

#import "../COMTrace.tlb" raw_interfaces_only no_smart_pointers

void TestComPtr()
{
	try
	{
		typedef WCL::ComPtr<COMTraceLib::ICustomInterface> IInterfacePtr;

		IInterfacePtr pTracer1(__uuidof(COMTraceLib::CustomTracer));
		IInterfacePtr pTracer2(pTracer1);
		IInterfacePtr pTracer3;

		pTracer3 = pTracer2;

		pTracer1.Release();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void TestCustomInterface()
{
	try
	{
		typedef WCL::ComPtr<COMTraceLib::ICustomInterface> IInterfacePtr;

		WCL::ComStr bstrIn(L"Hello World!");
		WCL::ComStr bstrOut;

		IInterfacePtr pTracer(__uuidof(COMTraceLib::CustomTracer));
//		IInterfacePtr pTracer2(pTracer);
//		IInterfacePtr pTracer3;

//		pTracer3 = pTracer2;

		HRESULT hr = pTracer->TestMethod(bstrIn.Get(), AttachTo(bstrOut));
//		pTracer2->TestMethod(bstrIn, &bstrOut);
//		pTracer3->TestMethod(bstrIn, &bstrOut);

//		pTracer2.Release();
//		pTracer3.Release();

		if (SUCCEEDED(hr))
		{
			std::wcout << bstrIn.Get()  << std::endl;
			std::wcout << bstrOut.Get() << std::endl;
		}

		std::wcout << "0x" << std::setw(8) << std::setfill(L'0') << std::hex << hr << " ";
		std::wcout << CStrCvt::FormatError(hr) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void TestDualInterface()
{
	try
	{
		typedef WCL::ComPtr<COMTraceLib::IDualInterface> IInterfacePtr;

		const wchar_t* wstrIn(L"Hello World!");

		IInterfacePtr pTracer(__uuidof(COMTraceLib::DualTracer));

		wchar_t* apszMethods[1] = { L"TestMethod" };
		DISPID   anMethodIDs[1];

		HRESULT hr = pTracer->GetIDsOfNames(IID_NULL, apszMethods, ARRAYSIZE(apszMethods), 0, anMethodIDs);

		if (SUCCEEDED(hr))
		{
			WCL::ComStr  bstrIn(wstrIn);
			WCL::Variant vtInput(bstrIn);
			DISPPARAMS   oParams = {&vtInput, nullptr, 1, 0};
			WCL::Variant vtResult;
			EXCEPINFO    oExcepInfo = {0};
			UINT         uArgErr = 0;

			hr = pTracer->Invoke(anMethodIDs[0], IID_NULL, 0, DISPATCH_METHOD, &oParams, &vtResult, &oExcepInfo, &uArgErr);

			if (SUCCEEDED(hr))
			{
				std::wcout << wstrIn            << std::endl;
				std::wcout << V_BSTR(&vtResult) << std::endl;
			}
		}

		std::wcout << "0x" << std::setw(8) << std::setfill(L'0') << std::hex << hr << " ";
		std::wcout << CStrCvt::FormatError(hr) << std::endl;

		WCL::ComStr bstrIn(wstrIn);
		WCL::ComStr bstrOut;

		hr = pTracer->TestMethod(bstrIn.Get(), AttachTo(bstrOut));

		if (SUCCEEDED(hr))
		{
			std::wcout << bstrIn.Get()  << std::endl;
			std::wcout << bstrOut.Get() << std::endl;
		}

		std::wcout << "0x" << std::setw(8) << std::setfill(L'0') << std::hex << hr << " ";
		std::wcout << CStrCvt::FormatError(hr) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void TestDispatchInterface()
{
	try
	{
		typedef WCL::ComPtr<::IDispatch> IInterfacePtr;

		const wchar_t* wstrIn(L"Hello World!");

		IInterfacePtr pTracer(__uuidof(COMTraceLib::DispatchTracer));

		wchar_t* apszMethods[1] = { L"TestMethod" };
		DISPID   anMethodIDs[1];

		HRESULT hr = pTracer->GetIDsOfNames(IID_NULL, apszMethods, ARRAYSIZE(apszMethods), 0, anMethodIDs);

		if (SUCCEEDED(hr))
		{
			WCL::ComStr  bstrIn(wstrIn);
			WCL::Variant vtInput(bstrIn);
			DISPPARAMS   oParams = {&vtInput, nullptr, 1, 0};
			WCL::Variant vtResult;
			EXCEPINFO    oExcepInfo = {0};
			UINT         uArgErr = 0;

			hr = pTracer->Invoke(anMethodIDs[0], IID_NULL, 0, DISPATCH_METHOD, &oParams, &vtResult, &oExcepInfo, &uArgErr);

			if (SUCCEEDED(hr))
			{
				std::wcout << wstrIn            << std::endl;
				std::wcout << V_BSTR(&vtResult) << std::endl;
			}
		}

		std::wcout << "0x" << std::setw(8) << std::setfill(L'0') << std::hex << hr << " ";
		std::wcout << CStrCvt::FormatError(hr) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void TestErrorInfo()
{
	try
	{
		typedef WCL::ComPtr<COMTraceLib::ICustomInterface> IInterfacePtr;
		typedef WCL::ComPtr<ISupportErrorInfo> ISupportErrorInfoPtr;
		typedef WCL::ComPtr<IErrorInfo> IErrorInfoPtr;

		IInterfacePtr pTracer;

		pTracer.CreateInstance(__uuidof(COMTraceLib::CustomTracer));

		HRESULT hr = pTracer->TestMethod(nullptr, nullptr);

		if (FAILED(hr))
		{
			ISupportErrorInfoPtr pSupportErrorInfo(pTracer);

			HRESULT hr = pSupportErrorInfo->InterfaceSupportsErrorInfo(__uuidof(COMTraceLib::ICustomInterface));

			if (hr == S_OK)
			{
				IErrorInfoPtr pErrorInfo;

				hr = ::GetErrorInfo(0, AttachTo(pErrorInfo));

				if (hr == S_OK)
				{
					WCL::ComStr bstrSource;
					WCL::ComStr bstrDescription;

					pErrorInfo->GetSource(AttachTo(bstrSource));
					pErrorInfo->GetDescription(AttachTo(bstrDescription));

					std::wcout << bstrSource.Get()      << std::endl;
					std::wcout << bstrDescription.Get() << std::endl;
				}
			}
		}

		std::wcout << "0x" << std::setw(8) << std::setfill(L'0') << std::hex << hr << " ";
		std::wcout << CStrCvt::FormatError(hr) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

int _tmain(int /*argc*/, _TCHAR* /*argv*/[])
{
	WCL::AutoCom oCom(COINIT_APARTMENTTHREADED);
//	WCL::AutoCom oCom(COINIT_MULTITHREADED);

	TestComPtr();

	TestCustomInterface();

	std::wcout << std::endl;

	TestDualInterface();

	std::wcout << std::endl;

	TestDispatchInterface();

	std::wcout << std::endl;

	TestErrorInfo();

	return EXIT_SUCCESS;
}
