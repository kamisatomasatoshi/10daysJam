#include "DxLib.h"
#include "MapChip.h"
#include "Player.h"
#include "NetWork.h"

// ウィンドウのタイトルに表示する文字列
const TCHAR TITLE[] = "落ちるんデス";

// ウィンドウ横幅
const int WIN_WIDTH = 456;

// ウィンドウ縦幅
const int WIN_HEIGHT = 640;

enum Scene
{
	Title,	// タイトル
	Game,	// ステージ
	Clear,	// クリア
	Over,	// オーバー
};

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {

	// 使用する文字コードを utf8 に設定
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);


	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	MapChip* mapChip = new MapChip();
	Player* player = new Player(128, 0, mapChip);
	int scene_ = Scene::Title;

	// ゲームループで使う変数の宣言


	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		switch (scene_)
		{
		case Title:
			if (keys[KEY_INPUT_RETURN] == true && oldkeys[KEY_INPUT_RETURN] == false) {
				scene_ = Game;
			}
			break;
		case Game:
			player->Update(WIN_HEIGHT);
			if (player->gualFlag == true)
			{
				scene_ = Clear;
			}
			if (player->playerFlag == false) {
				scene_ = Over;
			}
			break;
		case Clear:
			player->Reset();
			mapChip->Reset();
			if (keys[KEY_INPUT_SPACE] == true && oldkeys[KEY_INPUT_SPACE] == false) {
				scene_ = Game;
			}
			break;

		case Over:
			player->Reset();
			mapChip->Reset();
			if (keys[KEY_INPUT_SPACE] == true && oldkeys[KEY_INPUT_SPACE] == false) {
				scene_ = Game;
			}
			break;
		}

		// 描画処理
		if (scene_ == Game) {
			player->Draw();
			mapChip->Draw(player->scrollY);
			DrawFormatString(360, 48, GetColor(255, 255, 255), "%d", player->gualFlag);
		}
		else if (scene_ == Clear) {
			DrawFormatString(0, 0, GetColor(255, 255, 255), "ゲームクリア");
		}
		else if (scene_ == Over) {
			DrawFormatString(0, 0, GetColor(255, 255, 255), "ゲームオーバー");
		}

		DrawFormatString(0, 0, GetColor(255, 255, 255), "SceneNo%d", scene_);
		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	delete player;
	delete mapChip;
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
