#include "MapChip.h"

// �R���X�g���N�^�Ń}�b�v�f�[�^�����������A�e�N�X�`����ǂݍ���
MapChip::MapChip() {

	// �e�N�X�`����ǂݍ���
	LoadTextures();

	// �`��p�̏����l�ݒ�
	MapDrawPointX = 0;
	MapDrawPointY = 0;
}

// �f�X�g���N�^�Ńe�N�X�`�����������
MapChip::~MapChip() {
	UnloadTextures();
}

void MapChip::SetMapNo(int MapNo_)
{
	if (MapNo < 0 || MapNo >= MAP_NUM) {
		printfDx("�G���[: �s���ȃ}�b�v�ԍ� %d ���w�肳��܂����B\n", MapNo);
		return;
	}
	MapNo = MapNo_;
}

// �e�N�X�`����ǂݍ���
void MapChip::LoadTextures() {
	emptyTexture = LoadGraph("Resource/emptyTexture.png"); // ��̃e�N�X�`���i0�̒l�ɑΉ��j
	blockTexture = LoadGraph("Resource/Block01.png"); // �u���b�N�̃e�N�X�`���i1�̒l�ɑΉ��j
	goalTexture = LoadGraph("Resource/blockTexture.png"); // �u���b�N�̃e�N�X�`���i1�̒l�ɑΉ��j

	// �e�N�X�`���ǂݍ��ݎ��s�`�F�b�N
	if (blockTexture == -1 || emptyTexture == -1) {
		printfDx("�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂����B\n");
	}
}

// �e�N�X�`�����������
void MapChip::UnloadTextures() {
	DeleteGraph(blockTexture);
	DeleteGraph(emptyTexture);
	DeleteGraph(goalTexture);
}

// �}�b�v�`�b�v�̕`��
void MapChip::Draw(int ScrollY) {
	if (MapNo < 0 || MapNo >= MAP_NUM) {
		printfDx("�G���[: �����ȃ}�b�v�ԍ� %d ���w�肳��Ă��܂��B\n", MapNo);
		return;
	}

	int j, i;

	// �`�悷��}�b�v�`�b�v�̐����Z�b�g
	DrawMapChipNumX = 100;
	DrawMapChipNumY = 1000;

	// ��ʍ���ɕ`�悷��}�b�v���W���Z�b�g
	MapDrawPointX = 0;
	MapDrawPointY = 0;

	// �}�b�v��`��
	for (i = 0; i < DrawMapChipNumY; i++) {
		for (j = 0; j < DrawMapChipNumX; j++) {
			if ((j + MapDrawPointX < 0) || (i + MapDrawPointY < 0) ||
				(j + MapDrawPointX >= MapData[MapNo].Width) || (i + MapDrawPointY >= MapData[MapNo].Height)) {
				continue;
			}

			// �}�b�v�f�[�^��0���������e�N�X�`����`��
			if (MapData[MapNo].Data[i + MapDrawPointY][j + MapDrawPointX] == 0) {
				DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE - ScrollY, emptyTexture, TRUE);
			}
			// �}�b�v�f�[�^��1��������u���b�N�e�N�X�`����`��
			else if (MapData[MapNo].Data[i + MapDrawPointY][j + MapDrawPointX] == 1) {
				DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE - ScrollY, blockTexture, TRUE);
			}
			// �}�b�v�f�[�^��1��������u���b�N�e�N�X�`����`��
			else if (MapData[MapNo].Data[i + MapDrawPointY][j + MapDrawPointX] == 2) {
				DrawGraph(j * CHIP_SIZE, i * CHIP_SIZE - ScrollY, goalTexture, TRUE);
			}
		}
	}
}

// �w��ʒu�̓����蔻��
bool MapChip::IsHit(int x, int y) {
	int mapX = x / CHIP_SIZE;
	int mapY = y / CHIP_SIZE;

	// �͈͊O�𓖂���Ƃ���
	if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
		return true;
	}

	// �}�b�v�f�[�^��1�Ȃ瓖���蔻��
	return MapData[MapNo].Data[mapY][mapX] == 1;
}

bool MapChip::IsGual(int x, int y) {
	int mapX = x / CHIP_SIZE;
	int mapY = y / CHIP_SIZE;

	// �͈͊O�𓖂���Ƃ���
	if (mapX < 0 || mapX >= MAP_WIDTH || mapY < 0 || mapY >= MAP_HEIGHT) {
		return true;
	}

	// �}�b�v�f�[�^��2�Ȃ瓖���蔻��
	return MapData[MapNo].Data[mapY][mapX] == 2;
}
