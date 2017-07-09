#pragma once
#include <angelscript.h>
#include "Robot.h"

using namespace AngelScript;

namespace RobotCommon {

	void MessageCallback(const asSMessageInfo *msg, void *param) {
		const char *type = "ERR ";
		if (msg->type == asMSGTYPE_WARNING)
			type = "WARN";
		else if (msg->type == asMSGTYPE_INFORMATION)
			type = "INFO";
		printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
	}

	enum Direction {
		UP, DOWN, LEFT, RIGHT
	};

	void MoveRobot(int direction) {
		auto ctx = asGetActiveContext();
		Robot* r = (Robot*)ctx->GetUserData(10);
		switch (direction) {
		case UP:
			r->Move(glm::vec2(0, -1));
		case DOWN:
			r->Move(glm::vec2(0, 1));
		case LEFT:
			r->Move(glm::vec2(-1, 0));
		case RIGHT:
			r->Move(glm::vec2(1, 0));
		}
	}

	void SleepRobot(int cycles) {
		Robot* r = (Robot*)asGetActiveContext()->GetUserData(10);
		r->Sleep(cycles);
	}

	void LoadCommonInterface(asIScriptEngine* e) {
		e->RegisterEnum("Direction");
		e->RegisterEnumValue("Direction", "UP", UP);
		e->RegisterEnumValue("Direction", "DOWN", DOWN);
		e->RegisterEnumValue("Direction", "LEFT", LEFT);
		e->RegisterEnumValue("Direction", "RIGHT", RIGHT);

		e->RegisterGlobalFunction("void Move(int direction)", asFUNCTION(MoveRobot), asCALL_CDECL);
		e->RegisterGlobalFunction("void Sleep(int cycles)", asFUNCTION(SleepRobot), asCALL_CDECL);
	}
};

namespace MoverRobot {

	void LoadInterface(asIScriptEngine* e) {
		RobotCommon::LoadCommonInterface(e);
	}

	static void CreateEngine(Robot* r) {
		//create script engine
		asIScriptEngine* e = asCreateScriptEngine();
		e->SetMessageCallback(asFUNCTION(RobotCommon::MessageCallback), nullptr, asCALL_CDECL);
		//load interface
		LoadInterface(e);
		//set this robots engine to mover type
		r->SetEngine(e);
	}
}