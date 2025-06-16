#ifndef GAME_HPP
#define GAME_HPP

class Game {
   private:
	bool Keys[1024];
	unsigned int Width, Height;
	// constructor/destructor
   public:
	Game(unsigned int width, unsigned int height);
	~Game();
	// initialize game state (load all shaders/textures/levels)
	void Init();
	// game loop
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
};

#endif
