#pragma once
class Title
{
public:
	Title();	// �R���X�g���N�^
	~Title();	// �f�X�g���N�^

	void Init();	// ������
	void Update();	// �X�V
	void Draw();	// �`��
	void Reset();	// ���Z�b�g

private:
	int x, y;
	int vx, vy;
	int texture;

	float time;

	void LoadTexture();
	void UnloadTexture();

};

