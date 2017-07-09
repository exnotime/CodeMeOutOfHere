#pragma once
#include <angelscript.h>
#include <glm/glm.hpp>
class Robot {
public:
	Robot();
	~Robot();
	bool InsertScript(const char* code, int codeLength);
	void RemoveScript();
	void Update(float delta);
	void Sleep(uint32_t cycles);

	void Move(const glm::vec2& v) { m_Position += v; }
	glm::vec2 GetPos() { return m_Position; }

	AngelScript::asIScriptContext* GetContext() { return m_ScriptContext; }
	void SetEngine(AngelScript::asIScriptEngine* e) { m_Engine = e; }
private:
	glm::vec2 m_Position;
	uint32_t m_ExecutionCounter;
	uint32_t m_SleepCounter;
	float m_Timer;
	int m_ExecutionStatus;
	AngelScript::asIScriptContext* m_ScriptContext; //frontend
	AngelScript::asIScriptEngine* m_Engine; //backend
	AngelScript::asIScriptModule* m_Module; //code

};
