#include "NetWork.h"
#include <DxLib.h>


// GetAllFaculties�̎���
//template <class T>
//pplx::task<T> NetWork::GetAllFaculties(const std::wstring& url) {
//    return pplx::create_task([=] {
//        http_client client(url);
//        return client.request(methods::GET);
//        })
//        .then([](http_response response) {
//            if (response.status_code() == status_codes::OK) {
//                return response.extract_json();
//            }
//            });
//}

// GetIDFaculties�̎���
//pplx::task<void> NetWork::GetIDFaculties(const std::wstring& baseUrl, const utility::string_t& id) {
//    return pplx::create_task([=] {
//        http_client client(baseUrl + L"/" + id);
//        return client.request(methods::GET);
//        })
//        .then([](http_response response) {
//            if (response.status_code() == status_codes::OK) {
//                auto body = response.extract_string();
//                setlocale(LC_CTYPE, "ja_JP.UTF-8");
//                std::wcout << body.get().c_str() << std::endl;
//            }
//            });
//}

// Post���\�b�h�̎���
pplx::task<void> NetWork::Post( const std::wstring& name, int score) {
    return pplx::create_task([=] {
        json::value postData;
        postData[L"name"] = json::value::string(name);
        postData[L"score"] = json::value::number(score);  // �X�R�A��JSON�ɒǉ�

        http_client client(URL);
        return client.request(methods::POST, L"", postData.serialize(), L"application/json");
        })
        .then([=](http_response response) -> pplx::task<void> {
            if (response.status_code() == status_codes::Created || response.status_code() == status_codes::OK) {
                return response.extract_json().then([=](json::value json) {
                    if (json.has_field(L"rowCount")) {
                        std::wcout << L"Post successful, rowCount: " << json[L"rowCount"].as_integer() << std::endl;
                    }
                    else {
                        std::wcerr << L"Post failed: Invalid response." << std::endl;
                    }
                    return pplx::task_from_result();  // ��̃^�X�N��Ԃ�
                    });
            }
            else {
                std::wcerr << L"Post failed: HTTP error " << response.status_code() << std::endl;
                return pplx::task_from_result();  // �G���[���̋�̃^�X�N��Ԃ�
            }
            });
}

//pplx::task<int> NetWork::Post(const std::wstring& name, int score) {
//    return pplx::create_task([=] {
//        json::value postData;
//        postData[L"score"] = json::value::number(score);
//        postData[L"name"]  = json::value::string(name);
//
//        http_client client(URL);
//        return client.request(methods::POST, L"", postData.serialize(), L"application/json");
//        })
//        .then([](http_response response) {
//            if (response.status_code() == status_codes::OK) {
//                return response.extract_json();
//            }
//            else {
//                throw std::runtime_error("Received non-OK HTTP status code");
//            }
//            })
//            .then([](json::value json) { return json[L"status_code"].as_integer(); });
//}

// �V�������\�b�h�̎���: �S�ẴX�R�A���擾
//pplx::task<void> NetWork::GetAllScores(const std::wstring& url) {
//    return pplx::create_task([=] {
//        http_client client(url);
//        return client.request(methods::GET);
//        })
//        .then([](http_response response) {
//            if (response.status_code() == status_codes::OK) {
//                return response.extract_json();
//            }
//            return pplx::task_from_result(json::value());  // �G���[���̋��JSON��Ԃ�
//            })
//            .then([](json::value jsonResponse) {
//                if (jsonResponse.is_array()) {
//                    std::vector<std::pair<std::wstring, int>> playerScores;
//                    for (auto& player : jsonResponse.as_array()) {
//                        std::wstring name = player[U("name")].as_string();
//                        int score = player[U("score")].as_integer();
//                        playerScores.push_back({ name, score });
//                    }
//
//                    // �X�R�A���Ƀ\�[�g�i�~���j
//                    std::sort(playerScores.begin(), playerScores.end(),
//                        [](const std::pair<std::wstring, int>& a, const std::pair<std::wstring, int>& b) {
//                            return a.second > b.second;
//                        });
//
//                    // �����L���O�\����DXLib�ōs��
//                    for (size_t i = 0; i < playerScores.size(); ++i) {
//                        // wstring����C����`���̃��C�h������ɕϊ����ADXLib�ŕ`��
//                        std::wstring name = playerScores[i].first;
//                        DrawFormatString(100, 50 + i * 20, GetColor(255, 255, 255), "%d. %ls : %d", (int)(i + 1), name.c_str(), playerScores[i].second);
//                    }
//                }
//                else {
//                    std::wcerr << L"Error: Invalid JSON format." << std::endl;
//                }
//                });
//}


pplx::task<std::vector<std::pair<std::wstring, int>>> NetWork::GetAllScores() {
    return pplx::create_task([=] {
        http_client client(URL);
        return client.request(methods::GET);
        })
        .then([](http_response response) -> pplx::task<json::value> {
            if (response.status_code() == status_codes::OK) {
                return response.extract_json();
            }
            return pplx::task_from_result(json::value());  // �G���[���͋��JSON��Ԃ�
            })
            .then([](json::value jsonResponse) -> std::vector<std::pair<std::wstring, int>> {
                std::vector<std::pair<std::wstring, int>> playerScores;

                if (jsonResponse.is_array()) {
                    for (auto& player : jsonResponse.as_array()) {
                        std::wstring name = player[U("name")].as_string();
                        int score = player[U("score")].as_integer();
                        playerScores.push_back({ name, score });
                    }
                }
                return playerScores;  // �X�R�A���X�g��Ԃ�
                });
}


// �X�R�A���X�g��\������֐�
void NetWork::DisplayScores(const std::vector<std::pair<std::wstring, int>>& playerScores) {
    // �X�R�A���Ƀ\�[�g�i�~���j
    std::vector<std::pair<std::wstring, int>> sortedScores = playerScores;
    std::sort(sortedScores.begin(), sortedScores.end(),
        [](const std::pair<std::wstring, int>& a, const std::pair<std::wstring, int>& b) {
            return a.second > b.second;
        });

    // �X�R�A��\��
    for (size_t i = 0; i < sortedScores.size(); ++i) {
        //std::wcout << (i + 1) << L". " << sortedScores[i].first << L" : " << sortedScores[i].second << std::endl;
        DrawFormatString(100, 300 + i * 20, GetColor(255, 255, 255), "%d. %ls : %d", (int)(i + 1), sortedScores[i].first.c_str(), sortedScores[i].second);
    }
    //�܂��́ADXLib���g���ĕ`�悷��ꍇ
       // DrawFormatString(100, 300 + i * 20, GetColor(255, 255, 255), L"%d. %ls : %d", (int)(i + 1), sortedScores[i].first.c_str(), sortedScores[i].second);
}


// Login���\�b�h�̎���
//pplx::task<void> NetWork::Login(const std::wstring& url, const std::wstring& name, const std::wstring& password) {
//    return pplx::create_task([=] {
//        json::value postData;
//        postData[L"name"] = json::value::string(name);
//        postData[L"password"] = json::value::string(password);
//
//        http_client client(url);
//        return client.request(methods::POST, L"", postData.serialize(), L"application/json");
//        })
//        .then([](http_response response) {
//            if (response.status_code() == status_codes::OK) {
//                return response.extract_json();
//            }
//            return pplx::task_from_result(json::value());
//            })
//            .then([](json::value jsonResponse) {
//                std::wcout << L"Response: " << jsonResponse.serialize() << std::endl;
//                if (jsonResponse.has_field(L"login_status")) {
//                    auto login_status = jsonResponse[L"login_status"].as_string();
//                    if (login_status == L"success") {
//                        std::wcout << L"Login successful!" << std::endl;
//                    }
//                    else {
//                        std::wcout << L"Login failed: " << login_status << std::endl;
//                    }
//                }
//                else {
//                    std::wcout << L"Invalid response format." << std::endl;
//                }
//                });
//}