#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "state.h"
#include "input.h"
#include "world.h"

class EditorState : public State{
	public:
		EditorState();
		~EditorState();

		void update(float dt);
		void draw(core::gfx::Renderer&);
	private:
		void writeToDisk(std::string filename);
		void testLevel();

		bool saveFileMode=false;

		game::World world;
		game::Player player;
		glm::vec2 mouseInWorld;
		core::InputManager inputManager;
		core::gfx::Renderer* renderer=nullptr;
};

#endif
