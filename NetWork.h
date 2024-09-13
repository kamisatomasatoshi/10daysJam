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
    template <class T>


    pplx::task<T> GetAllFaculties(const std::wstring& url);

    pplx::task<void> GetAllScores(const std::wstring& url);

    pplx::task<void> GetIDFaculties(const std::wstring& baseUrl, const utility::string_t& id);

    pplx::task<void> Post(const std::wstring& url, const std::wstring& name, int score, const std::wstring& getAllScoresUrl);

    pplx::task<void> Login(const std::wstring& url, const std::wstring& name, const std::wstring& password);
};

//main.cppの使い方
//NetWork network;
//const std::wstring url = L"http://example.com/api/get_all_scores"; // サーバーのAPI URL

//try {
//    network.GetAllScores(url).wait();
//}
//catch (const std::exception& e) {
//    std::wcerr << L"Error: " << e.what() << std::endl;
//}