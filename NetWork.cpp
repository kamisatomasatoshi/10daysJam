#include "NetWork.h"


// GetAllFaculties�̎���
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

// GetIDFaculties�̎���
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

// Post���\�b�h�̎���
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

// �V�������\�b�h�̎���: �S�ẴX�R�A���擾
pplx::task<void> NetWork::GetAllScores(const std::wstring& url) {
    return pplx::create_task([=] {
        // HTTP�N���C�A���g�̍쐬��GET���N�G�X�g�̑��M
        http_client client(url);
        return client.request(methods::GET);
        })
        .then([](http_response response) {
            // �X�e�[�^�X�R�[�h��OK�i200�j�̏ꍇ�AJSON�𒊏o
            if (response.status_code() == status_codes::OK) {
                return response.extract_json();
            }
            return pplx::task_from_result(json::value()); // �G���[���̋��JSON��Ԃ�
            })
            .then([](json::value jsonResponse) {
                // JSON���z��`�����m�F
                if (jsonResponse.is_array()) {
                    std::vector<std::pair<std::wstring, int>> playerScores;

                    // JSON�z����p�[�X���āA�e�v���C���[�̖��O�ƃX�R�A���擾
                    for (auto& player : jsonResponse.as_array()) {
                        std::wstring name = player[U("name")].as_string();
                        int score = player[U("score")].as_integer();
                        playerScores.push_back({ name, score });
                    }

                    // �X�R�A���Ƀ\�[�g�i�~���j
                    std::sort(playerScores.begin(), playerScores.end(),
                        [](const std::pair<std::wstring, int>& a, const std::pair<std::wstring, int>& b) {
                            return a.second > b.second;
                        });

                    // �����L���O��\��
                    printf("Ranking:\n");
                    for (size_t i = 0; i < playerScores.size(); ++i) {
                        // wstring����C����`���̃��C�h������ɕϊ�
                        std::wstring name = playerScores[i].first;
                        wprintf(L"%d. %ls : %d\n", (int)(i + 1), name.c_str(), playerScores[i].second);
                    }
                }
                else {
                    std::wcerr << L"Error: Invalid JSON format." << std::endl;
                }
                });
}

// Login���\�b�h�̎���
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