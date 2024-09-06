#include "NetWork.h"


// GetAllFacultiesの実装
template <class T>
pplx::task<T> NetWork::GetAllFaculties(const std::wstring& url) {
    return pplx::create_task([=] {
        http_client client(url);
        return client.request(methods::GET);
        })
        .then([](http_response response) {
            if (response.status_code() == status_codes::OK) {
                return response.extract_json();
            }
            });
}

// GetIDFacultiesの実装
pplx::task<void> NetWork::GetIDFaculties(const std::wstring& baseUrl, const utility::string_t& id) {
    return pplx::create_task([=] {
        http_client client(baseUrl + L"/" + id);
        return client.request(methods::GET);
        })
        .then([](http_response response) {
            if (response.status_code() == status_codes::OK) {
                auto body = response.extract_string();
                setlocale(LC_CTYPE, "ja_JP.UTF-8");
                std::wcout << body.get().c_str() << std::endl;
            }
            });
}

// Postメソッドの実装
pplx::task<int> NetWork::Post(const std::wstring& url, const std::wstring& name, int score) {
    return pplx::create_task([=] {
        json::value postData;
        postData[L"name"] = json::value::string(name);

        http_client client(url);
        return client.request(methods::POST, L"", postData.serialize(), L"application/json");
        })
        .then([](http_response response) {
            if (response.status_code() == status_codes::Created) {
                return response.extract_json();
            }
            })
            .then([](json::value json) {
                return json[L"rowCount"].as_integer();
                });
}

// 新しいメソッドの実装: 全てのスコアを取得
pplx::task<void> NetWork::GetAllScores(const std::wstring& url) {
    return pplx::create_task([=] {
        // HTTPクライアントの作成とGETリクエストの送信
        http_client client(url);
        return client.request(methods::GET);
        })
        .then([](http_response response) {
            // ステータスコードがOK（200）の場合、JSONを抽出
            if (response.status_code() == status_codes::OK) {
                return response.extract_json();
            }
            return pplx::task_from_result(json::value()); // エラー時の空のJSONを返す
            })
            .then([](json::value jsonResponse) {
                // JSONが配列形式か確認
                if (jsonResponse.is_array()) {
                    std::vector<std::pair<std::wstring, int>> playerScores;

                    // JSON配列をパースして、各プレイヤーの名前とスコアを取得
                    for (auto& player : jsonResponse.as_array()) {
                        std::wstring name = player[U("name")].as_string();
                        int score = player[U("score")].as_integer();
                        playerScores.push_back({ name, score });
                    }

                    // スコア順にソート（降順）
                    std::sort(playerScores.begin(), playerScores.end(),
                        [](const std::pair<std::wstring, int>& a, const std::pair<std::wstring, int>& b) {
                            return a.second > b.second;
                        });

                    // ランキングを表示
                    printf("Ranking:\n");
                    for (size_t i = 0; i < playerScores.size(); ++i) {
                        // wstringからC言語形式のワイド文字列に変換
                        std::wstring name = playerScores[i].first;
                        wprintf(L"%d. %ls : %d\n", (int)(i + 1), name.c_str(), playerScores[i].second);
                    }
                }
                else {
                    std::wcerr << L"Error: Invalid JSON format." << std::endl;
                }
                });
}

// Loginメソッドの実装
pplx::task<void> NetWork::Login(const std::wstring& url, const std::wstring& name, const std::wstring& password) {
    return pplx::create_task([=] {
        json::value postData;
        postData[L"name"] = json::value::string(name);
        postData[L"password"] = json::value::string(password);

        http_client client(url);
        return client.request(methods::POST, L"", postData.serialize(), L"application/json");
        })
        .then([](http_response response) {
            if (response.status_code() == status_codes::OK) {
                return response.extract_json();
            }
            return pplx::task_from_result(json::value());
            })
            .then([](json::value jsonResponse) {
                std::wcout << L"Response: " << jsonResponse.serialize() << std::endl;
                if (jsonResponse.has_field(L"login_status")) {
                    auto login_status = jsonResponse[L"login_status"].as_string();
                    if (login_status == L"success") {
                        std::wcout << L"Login successful!" << std::endl;
                    }
                    else {
                        std::wcout << L"Login failed: " << login_status << std::endl;
                    }
                }
                else {
                    std::wcout << L"Invalid response format." << std::endl;
                }
                });
}