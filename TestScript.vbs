Option Explicit

Dim obj
Set obj = CreateObject("COMTrace.DualTracer")
'Set obj = CreateObject("COMTrace.DispatchTracer")

Dim strIn, strOut
strIn = "Hello World!"
strOut = obj.TestMethod(strIn)

WScript.Echo strIn
WScript.Echo strOut
