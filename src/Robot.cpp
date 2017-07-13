#include "Robot.h"
#include <script/scriptbuilder/scriptbuilder.h>
#include <script/scripthelper/scripthelper.h>

#define CHECK(x) if(x < 0) return false;

void LineCallBack(AngelScript::asIScriptContext* ctx, void* ud) {
	Robot* r = (Robot*)ctx->GetUserData(10);
	r->SetCurrentLine(ctx->GetLineNumber());
	ctx->Suspend();
}

Robot::Robot() {
	m_Position = glm::vec2(0);
	m_ExecutionCounter = 0;
	m_ExecutionStatus = 0;
	m_SleepCounter = 0;
	m_Timer = 0;
	m_CurrentLine = 0;
	m_Module = nullptr;
	m_Engine = nullptr;
	m_ScriptContext = nullptr;
}

Robot::~Robot() {

}

bool Robot::InsertScript(const char* code, int codeLength) {
	RemoveScript();
	AngelScript::CScriptBuilder scriptBuilder;
	CHECK(scriptBuilder.StartNewModule(m_Engine, "MainCode"));
	CHECK(scriptBuilder.AddSectionFromMemory("MainCode", code));
	CHECK(scriptBuilder.BuildModule());
	m_Module = scriptBuilder.GetModule();

	m_ScriptContext = m_Engine->CreateContext();
	m_ScriptContext->SetUserData(this, 10);

	m_ScriptContext->SetLineCallback(asFUNCTION(LineCallBack), nullptr, AngelScript::asCALL_CDECL);

	auto func = m_Module->GetFunctionByDecl("void main()");
	m_ScriptContext->Prepare(func);

	m_Code = std::string(code);
	//split code into lines for easier debugging
	std::string l;
	std::stringstream ss(m_Code);
	while (std::getline(ss, l, '\n')) {
		m_CodeLines.push_back(l);
	}

	return true;
}

void Robot::RemoveScript() {
	if (m_Module) m_Module->Discard();
}

void Robot::Update(float delta) {
	m_Timer += delta;
	//TODO: set the time depending of the hz of the robot
	if (m_Timer >= 1.0f) {
		//check if the robot is sleeping
		if (m_SleepCounter > 0) {
			m_SleepCounter--;
			m_Timer = 0;
			return;
		}
		//run line
		m_ExecutionStatus = m_ScriptContext->Execute();

		if (m_ExecutionStatus != AngelScript::asEXECUTION_SUSPENDED) {
			switch (m_ExecutionStatus) {
			case AngelScript::asEXECUTION_ABORTED:
				//player script aborted program
				//TODO: Crash and end execution
				break;
			case AngelScript::asEXECUTION_ERROR:
				//There is some type of error
				//TODO: Crash and end execution
				break;
			case AngelScript::asEXECUTION_EXCEPTION:
				//there has been some type of exception
				//TODO: show this to the player somehow like a flashin light or 
				break;
			case AngelScript::asEXECUTION_FINISHED:
				//loop the script
				AngelScript::asIScriptFunction* func = m_Module->GetFunctionByDecl("void main()");
				m_ScriptContext->Prepare(func);
				m_ScriptContext->Execute();
				break;
			}
		}
		m_Timer = 0;
	}
}

void Robot::Sleep(uint32_t cycles) {
	//only allow max sleep of 10
	if (cycles > 10)
		return;

	m_SleepCounter = cycles;
}