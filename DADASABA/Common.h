﻿# pragma once
# include <Siv3D.hpp>

// シーンの名前
enum class State
{
	Title,
	Tutorial,
	Game,
	GameOver,
	ResultRanking,
};




// 共有するデータ
struct GameData
{
	// 直前のゲームのスコア
	Optional<int32> lastGameScore;

	// ハイスコア
	Array<int32> highScores = { 50, 40, 30, 20, 10 };
};

using App = SceneManager<State, GameData>;
