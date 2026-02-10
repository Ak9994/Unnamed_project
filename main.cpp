#include<include/Escape.h>
#include<include/GameConfig.h>

int main() {
	GameConfig PlayerCfg;
	//Set Age
	PlayerCfg.start_age = 20;
	PlayerCfg.max_age = 100;
	//Set Game Limits
	PlayerCfg.GameEnd_TimeLimit = 5;
	PlayerCfg.Level_TimeLimit = 1;
	//Set Exit
	PlayerCfg.ExitSpawn_Count = 20;
	//Testing
	PlayerCfg.Idleplay = true;
	//Exit Selection Prob
	PlayerCfg.CorrectSelectionProb = 0.05;

	Escape Escape(PlayerCfg);
	Escape.GameLoop();

	return 0;
}

