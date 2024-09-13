#include "DxLib.h"
#include "Title.h"

Title::Title()
{
	x = 96;
	y = 63;
	vx = 10;
	vy = 10;
	LoadTexture();
}

Title::~Title()
{

}

void Title::Init()
{

}

void Title::Update()
{

}

void Title::Draw()
{
	DrawGraph(x, y, texture, TRUE);
}

void Title::Reset()
{

}

void Title::LoadTexture()
{
	texture = LoadGraph("Resource/dropDown.png");

	if (texture == -1) {
		printfDx("プレイヤーのテクスチャの読み込みに失敗しました。\n");
	};
}

void Title::UnloadTexture()
{
	DeleteGraph(texture);
}

