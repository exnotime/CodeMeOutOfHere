#include "ScriptEngine.h"
#include "scriptstdstring/scriptstdstring.h"
#include "scriptarray/scriptarray.h"
#include "scriptbuilder/scriptbuilder.h"
#include "scripthelper/scripthelper.h"
#include <assert.h>

using namespace AngelScript;

void MessageCallback(const asSMessageInfo *msg, void *param) {
	const char *type = "ERR ";
	if (msg->type == asMSGTYPE_WARNING)
		type = "WARN";
	else if (msg->type == asMSGTYPE_INFORMATION)
		type = "INFO";
	printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

void Print(const std::string& msg) {
	printf("%s\n", msg.c_str());
}

ScriptEngine::ScriptEngine() {
}

ScriptEngine::~ScriptEngine() {
	m_Context->Release();
	m_Engine->ShutDownAndRelease();
}

ScriptEngine& ScriptEngine::GetInstance() {
	static ScriptEngine m_Instance;
	return m_Instance;
}

void ScriptEngine::Init() {
	m_Engine = asCreateScriptEngine();
	m_Engine->SetMessageCallback(asFUNCTION(MessageCallback), nullptr, asCALL_CDECL);
	RegisterStdString(m_Engine);
	RegisterScriptArray(m_Engine, true);
	m_Engine->RegisterGlobalFunction("void print(const string &in)", asFUNCTION(Print), asCALL_CDECL);
	m_Context = m_Engine->CreateContext();

	m_Engine->SetEngineProperty(asEP_MAX_STACK_SIZE, 64);
}

void ScriptEngine::CompileScript(const std::string& scriptname) {
	AngelScript::CScriptBuilder scriptBuilder;
	int r = 0;
	r = scriptBuilder.StartNewModule(m_Engine, scriptname.c_str());
	assert(r >= 0);
	r = scriptBuilder.AddSectionFromFile(scriptname.c_str());
	assert(r >= 0);
	r = scriptBuilder.BuildModule();
	assert(r >= 0);
	m_Scripts.push_back(scriptname);
	printf("Compiled script :%s\n", scriptname.c_str());
}

ScriptModule ScriptEngine::CompileScriptToModule(const std::string& scriptname) {
	AngelScript::CScriptBuilder scriptBuilder;
	int r = 0;
	r = scriptBuilder.StartNewModule(m_Engine, scriptname.c_str());
	assert(r >= 0);
	r = scriptBuilder.AddSectionFromFile( scriptname.c_str());
	assert(r >= 0);
	r = scriptBuilder.BuildModule();
	assert(r >= 0);
	m_Scripts.push_back(scriptname);
	printf("Compiled script :%s\n", scriptname.c_str());
	return m_Engine->GetModule(scriptname.c_str());
}

ScriptModule ScriptEngine::CompileStringToModule(const std::string& name, const std::string& script) {
	AngelScript::CScriptBuilder scriptBuilder;
	int r = 0;
	r = scriptBuilder.StartNewModule(m_Engine, name.c_str());
	assert(r >= 0);
	r = scriptBuilder.AddSectionFromMemory(name.c_str(), script.c_str());
	assert(r >= 0);
	r = scriptBuilder.BuildModule();
	assert(r >= 0);
	m_Scripts.push_back(name);
	printf("Compiled script :%s\n", name.c_str());
	return m_Engine->GetModule(name.c_str());
}

void ScriptEngine::RunScript(const std::string& scriptname, const std::string& entry) {
	AngelScript::asIScriptModule* module = m_Engine->GetModule(scriptname.c_str());
	AngelScript::asIScriptFunction* func = module->GetFunctionByDecl(entry.c_str());
	m_Context->Prepare(func);
	m_Context->Execute();
}

void ScriptEngine::RecompileScript(const std::string& scriptname) {
	m_Engine->DiscardModule(scriptname.c_str());
	AngelScript::CScriptBuilder scriptBuilder;
	int r = 0;
	r = scriptBuilder.StartNewModule(m_Engine, scriptname.c_str()); assert(r >= 0);
	r = scriptBuilder.AddSectionFromFile(scriptname.c_str()); assert(r >= 0);
	r = scriptBuilder.BuildModule(); assert(r >= 0);
}

void ScriptEngine::RecompileAllScripts() {
	for (auto& script : m_Scripts) {
		RecompileScript(script);
	}
}

void ScriptEngine::ExecuteString(const std::string& code) {
	AngelScript::ExecuteString(m_Engine, code.c_str(), nullptr, m_Context);
}

void ScriptEngine::ExecuteModule(ScriptModule module, const std::string& entry) {
	AngelScript::asIScriptFunction* func = module->GetFunctionByDecl(entry.c_str());
	m_Context->Prepare(func);
	m_Context->Execute();
}