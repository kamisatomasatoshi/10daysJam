#include "DxLib.h"
#include "MapChip.h"
#include "Player.h"
#include "Title.h"
//#include "NetWork.h"

// ウィンドウのタイトルに表示する文字列
const TCHAR TITLE[] = "落ちるんデス";

// ウィンドウ横幅
const int WIN_WIDTH = 456;

// ウィンドウ縦幅
const int WIN_HEIGHT = 640;

enum Scene
{

	Title_,	// タイトル
	Game_,	// ステージ
	Clear_,	// クリア
	Over_,	// オーバー

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
	Title* title = new Title();


	int count = 0;
	int countFalg = false;
	
	// パーティクルを管理するベクター
	std::vector<Particle> particles;

	// ゲームループで使う変数の宣言

	int scene_ = Scene::Title_;


	int texture_title = LoadGraph("Resource/title.png");
	int texture_background = LoadGraph("Resource/darkcave.png");
	int texture_clear = LoadGraph("Resource/clear.png");
	int texture_over = LoadGraph("Resource/over.png");

	// ゲームループで使う変数の宣言

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };


	bool siouflag = false;
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
		case Title_:
			//title->Update();
			if (keys[KEY_INPUT_SPACE] == true && oldkeys[KEY_INPUT_SPACE] == false) {
				scene_ = Game_;
			}

			siouflag = false;
			countFalg = false;
			count = 0;
			break;
		case Game_:
			player->Update(WIN_HEIGHT);
			if (player->gualFlag == true)
			{
				scene_ = Clear_;
			}

			if (player->playerFlag == false && siouflag == false) {
				auto newParticles = Particle::CreateParticles(player->x, player->y, 20);  // プレイヤーの足元に生成
				particles.insert(particles.end(), newParticles.begin(), newParticles.end());
				siouflag = true;
				countFalg = true;
			}

			if (countFalg)
			{
				count++;
			}
			if (count >= 40)
			{
				scene_ = Over_;			
			}
			break;
		case Clear_:
			player->Reset();
			mapChip->Reset();
			if (keys[KEY_INPUT_SPACE] == true && oldkeys[KEY_INPUT_SPACE] == false) {

				scene_ = Title_;


			}
			break;

		case Over_:
			player->Reset();
			mapChip->Reset();
			if (keys[KEY_INPUT_SPACE] == true && oldkeys[KEY_INPUT_SPACE] == false) {
				scene_ = Title_;
			}
			break;
		}




		// 描画処理
		if (scene_ == Title_)
		{
			DrawGraph(0, 0, texture_title , TRUE);
			//title->Draw();
		}
		else if (scene_ == Game_) {
			DrawGraph(0, 0, texture_background, TRUE);
			mapChip->Draw(player->scrollY);
			player->Draw();

			// パーティクルの更新と描画
			for (auto& particle : particles) {
				particle.Update();
				particle.Draw();
			}

			// パーティクルの寿命が尽きたものを削除
			particles.erase(
				std::remove_if(particles.begin(), particles.end(), [](const Particle& p) { return !p.IsAlive(); }),
				particles.end()
			);


			

		}
		else if (scene_ == Clear_) {
			DrawGraph(0, 0, texture_clear, TRUE);
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "ゲームクリア");
		}
		else if (scene_ == Over_) {
			DrawGraph(0, 0, texture_over, TRUE);
			//DrawFormatString(0, 0, GetColor(255, 255, 255), "ゲームオーバー");
		}

		//DrawFormatString(0, 0, GetColor(255, 255, 255), "SceneNo%d", scene_);
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
