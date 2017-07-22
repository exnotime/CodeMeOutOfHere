#pragma once
#include <angelscript.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
class Robot {
public:
	Robot();
	~Robot();
	bool InsertScript(const char* code, int codeLength);
	void RemoveScript();
	void Update(float delta);
	void Sleep(uint32_t cycles);
	void RunLine();

	//getters
	glm::vec2 GetPos() { return m_Position; }
	AngelScript::asIScriptContext* GetContext() { return m_ScriptContext; }
	std::string& GetCurrentLine() { return m_CodeLines[m_CurrentLine]; }
	uint32_t GetCurrentLineIndex() { return m_CurrentLine; }
	std::vector<std::string>& GetCode() { return m_CodeLines; }
	double GetInvHz() { return m_InvHz; }

	//setters, movers and togglers
	void Move(const glm::vec2& v) { m_Position += v; }
	void SetEngine(AngelScript::asIScriptEngine* e) { m_Engine = e; }
	void SetCurrentLine(uint32_t l) { m_CurrentLine = l; }
	void TogglePause() { m_Paused = !m_Paused; }
	void SetHz(double hz) { m_InvHz = 1.0 / hz; }


private:
	glm::vec2 m_Position;
	uint32_t m_ExecutionCounter;
	uint32_t m_SleepCounter;
	double m_Timer;
	double m_InvHz;
	bool m_Paused;
	int m_ExecutionStatus;
	AngelScript::asIScriptContext* m_ScriptContext; //frontend
	AngelScript::asIScriptEngine* m_Engine; //backend
	AngelScript::asIScriptModule* m_Module; //code

	std::string m_Code;
	std::vector<std::string> m_CodeLines;
	uint32_t m_CurrentLine;
};
