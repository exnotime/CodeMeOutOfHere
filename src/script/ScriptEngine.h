#pragma once
#include <angelscript.h>
#include <string>
#include <vector>
#define g_ScriptEngine ScriptEngine::GetInstance()
typedef AngelScript::asIScriptModule* ScriptModule;
class ScriptEngine {
  public:
	~ScriptEngine();
	static ScriptEngine& GetInstance();
	void Init();
	void CompileScript(const std::string& scriptname);
	ScriptModule CompileScriptToModule(const std::string& scriptname);
	ScriptModule CompileStringToModule(const std::string& name, const std::string& script);
	void RunScript(const std::string& scriptname, const std::string& entry);
	AngelScript::asIScriptEngine* GetEngine() {
		return m_Engine;
	}
	void RecompileScript(const std::string& scriptname);
	void RecompileAllScripts();
	void ExecuteString(const std::string& code);
	void ExecuteModule(ScriptModule module, const std::string& entry);
  private:
	ScriptEngine();
	std::vector<std::string> m_Scripts;
	AngelScript::asIScriptEngine* m_Engine;
	AngelScript::asIScriptContext* m_Context;
};