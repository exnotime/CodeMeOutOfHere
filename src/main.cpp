#include <angelscript.h>
#include <stdio.h>
#include <string>
#include "script/ScriptEngine.h"

int main() {
	g_ScriptEngine.Init();
	ScriptModule s = g_ScriptEngine.CompileScriptToModule("test.as");
	g_ScriptEngine.ExecuteModule(s, "void main()");
	system("Pause");
	return 0;
}