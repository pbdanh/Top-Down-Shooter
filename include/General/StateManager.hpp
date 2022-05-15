#pragma once

class GameScreen;

class StateManager
{
public:
	StateManager();
	~StateManager();

	enum class Screen
	{
		StartScreen,
		SettingScreen,
		GamePVP,
		EndScreen,
		AboutScreen
	};

	void switchScreen(Screen newScreen);

	GameScreen * currentScreen;
	GameScreen * nextScreen;
	int p1Score;
	int p2Score;

	int time;
	int map;
	int maxScore;
};

