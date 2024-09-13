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
		printfDx("�v���C���[�̃e�N�X�`���̓ǂݍ��݂Ɏ��s���܂����B\n");
	};
}

void Title::UnloadTexture()
{
	DeleteGraph(texture);
}

