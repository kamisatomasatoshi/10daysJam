#pragma once
#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <iostream>

using namespace utility; // 文字列変換などの一般的なユーティリティ
using namespace web; // URIのような共通の機能
using namespace web::http; // 共通のHTTP機能
using namespace web::http::client; // HTTP クライアントの機能
using namespace concurrency::streams; // 非同期ストリーム




class NetWork {
public:
    // メソッドの宣言
    
    const std::wstring URL = L"https://swgame-roan.vercel.app/all/scores";  // スコア送信のURL

    //pplx::task<T> GetAllFaculties(const std::wstring& url);

    //pplx::task<void> GetAllScores(const std::wstring& url);

   // pplx::task<void> GetIDFaculties(const std::wstring& baseUrl, const utility::string_t& id);

    pplx::task<std::vector<std::pair<std::wstring, int>>> GetAllScores();

    pplx::task<void> Post(const std::wstring& name, int score);
    //pplx::task<int> Post(const std::wstring& name, int score);
    // スコアを表示する関数
    void DisplayScores(const std::vector<std::pair<std::wstring, int>>& playerScores);
    //pplx::task<void> Login(const std::wstring& url, const std::wstring& name, const std::wstring& password);
};

//main.cppの使い方
//NetWork network;
//const std::wstring url = L"http://example.com/api/get_all_scores"; // サーバーのAPI URL
//
//try {
//    network.GetAllScores(url).wait();
//}
//catch (const std::exception& e) {
//    std::wcerr << L"Error: " << e.what() << std::endl;
//}