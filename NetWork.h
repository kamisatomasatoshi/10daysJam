#pragma once
#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <iostream>

using namespace utility; // ������ϊ��Ȃǂ̈�ʓI�ȃ��[�e�B���e�B
using namespace web; // URI�̂悤�ȋ��ʂ̋@�\
using namespace web::http; // ���ʂ�HTTP�@�\
using namespace web::http::client; // HTTP �N���C�A���g�̋@�\
using namespace concurrency::streams; // �񓯊��X�g���[��




class NetWork {
public:
    // ���\�b�h�̐錾
    template <class T>


    pplx::task<T> GetAllFaculties(const std::wstring& url);

    pplx::task<void> GetAllScores(const std::wstring& url);

    pplx::task<void> GetIDFaculties(const std::wstring& baseUrl, const utility::string_t& id);

    pplx::task<void> Post(const std::wstring& url, const std::wstring& name, int score, const std::wstring& getAllScoresUrl);

    pplx::task<void> Login(const std::wstring& url, const std::wstring& name, const std::wstring& password);
};

//main.cpp�̎g����
//NetWork network;
//const std::wstring url = L"http://example.com/api/get_all_scores"; // �T�[�o�[��API URL

//try {
//    network.GetAllScores(url).wait();
//}
//catch (const std::exception& e) {
//    std::wcerr << L"Error: " << e.what() << std::endl;
//}