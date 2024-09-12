#include "DxLib.h"
#include "MapChip.h"
#include "Player.h"
#include "NetWork.h"

// ウィンドウのタイトルに表示する文字列
const TCHAR TITLE[] = "落ちるんデス";

// ウィンドウ横幅
const int WIN_WIDTH = 600;

// ウィンドウ縦幅
const int WIN_HEIGHT = 800;

enum Scene
{
	Title,//タイトル
	Game,//ステージ
	Clear,
	Over,
	Ranking
};

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {

	NetWork network;
	const std::wstring postUrl = L"https://swgame-roan.vercel.app/all/scores";  // スコア送信用のAPI URL
	const std::wstring getAllScoresUrl = L"https://swgame-roan.vercel.app/all/scores";  // ランキング取得用のAPI URL

	

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
		case Scene::Title:
			if (keys[KEY_INPUT_RETURN] == 1) {
				scene_ = Scene::Game;
			}
			break;
		case Scene::Game:
			player->Update();
			break;

		case Scene::Clear:
		

			if (keys[KEY_INPUT_RETURN] == 1) {
				scene_ = Scene::Ranking;
			}
			break;

		case Scene::Over:
			

			if (keys[KEY_INPUT_RETURN] == 1) {
				scene_ = Scene::Ranking;
			}
			break;

		case Scene::Ranking:
		
			// RankingシーンでスコアをPOSTし、ランキングを取得して表示
		{
			static bool rankingRequested = false; // 1回だけリクエストするためのフラグ
			static std::vector<std::pair<std::wstring, int>> playerScores; // ランキングデータを保持
			static bool dataReceived = false; // データが受信されたかどうかを追跡

			if (!rankingRequested) {
				// ネットワークの初期化
				NetWork network;
				const std::wstring postUrl = L"http://example.com/api/post_score";  // スコア送信用のAPI URL
				const std::wstring getAllScoresUrl = L"http://example.com/api/get_all_scores";  // ランキング取得用のAPI URL
				std::wstring name = L"Player1";  // プレイヤー名（仮）
				int score;// = player->GetScore();  // プレイヤーのスコア

				// 非同期でスコアをPOSTし、その後ランキングを取得して描画
				try {
					network.Post(postUrl, name, score, getAllScoresUrl).then([&]() {
						// サーバーからランキングを取得して、結果を playerScores に格納
						network.GetAllScores(getAllScoresUrl).then([&](std::vector<std::pair<std::wstring, int>> scores) {
							playerScores = scores; // ランキングデータを保存
							dataReceived = true;   // データを受信したことを記録
							}).wait();
						}).wait();
				}
				catch (const std::exception& e) {
					std::wcerr << L"Error: " << e.what() << std::endl;
				}

				rankingRequested = true; // リクエストは1回だけ行う
			}

			// データが受信されたらランキングを表示
			if (dataReceived) {
				for (size_t i = 0; i < playerScores.size(); ++i) {
					// DXLibでランキングを描画
					DrawFormatString(100, 50 + i * 20, GetColor(255, 255, 255), "%d. %ls : %d", (int)(i + 1), playerScores[i].first.c_str(), playerScores[i].second);
				}
			}
		}

		if (keys[KEY_INPUT_RETURN] == 1) {
			scene_ = Scene::Title;
		}
		break;

			break;
		default:

			break;
		}

		// 描画処理
		DrawFormatString(0, 0, GetColor(255, 255, 255), "SceneNo%d", scene_);
		if (scene_ == Scene::Game) {
			player->Draw();
			mapChip->Draw();

		}

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
