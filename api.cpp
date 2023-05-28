#include "api.h"
#include "json.hpp"
#include "globals.h"
#include "product.h"
#include <future>

bool API::signup(std::string username, std::string password, std::string email, std::string hwid) {
    nlohmann::json j;
    j["username"] = username;
    j["password"] = password;
    j["hwid"] = hwid;
    j["email"] = email;
    auto response = client.Post("/signup/", j.dump(), "application/json");
    if (response->status == 201) {
        return true;
    }
    return false;

}

int API::login(std::string username, std::string password, std::string hwid) {
	nlohmann::json j;
	j["username"] = username;
	j["password"] = password;
	j["hwid"] = hwid;
	auto response = client.Post("/login/", j.dump(), "application/json");
    if (response->status == 400) {
        return 1;
	}
    else if (response->status == 401) {
		return 2;
	}
    //return Response({'token': token.key, 'user_id': user.id})
	j = nlohmann::json::parse(response->body);
	globals::userToken = j["token"];
    globals::saveUserToken(globals::userToken);
    globals::userId = j["user_id"];
	return 0;
	
}

bool API::testApi()
{
   //test if api is alive
    auto response = client.Get("/test/");
    if (response->status == 200) {
        return true;
    }
    return false;
}

bool API::getUserInfo() {
    std::string url = "/user/" + std::to_string(globals::userId);
    //set token as header
    httplib::Headers headers = { {"Authorization", "Token " + globals::userToken} };
    auto response = client.Get(url.c_str(), headers);
    if (response->status != 200) {
        return false;
    }
    nlohmann::json j;
    j = nlohmann::json::parse(response->body);
    //
    globals::products.clear();
    for (auto& element : j["products"]) {
        int hack_id = element["hack_id"];
        std::string expiration_date = element["expiration_date"];
        std::string status = element["hack"]["status"];
        Product product(hack_id, expiration_date, status);
        globals::products.push_back(product);
    }
    
    return true;
    
}

bool API::validateProduct(int id) {
    std::string url = "/validate/";
    httplib::Headers headers = { {"Authorization", "Token " + globals::userToken} };
    nlohmann::json j;
    j["hwid"] = globals::hwid;
    j["pid"] = id;
    auto response = client.Post(url.c_str(), headers, j.dump(), "application/json");
    if (response->status == 200) {
		return true;
	}
	return false;
}

bool API::checkLoaderVersion(std::string productName) {
    std::string url = "/check_version/";
    nlohmann::json j;
    j["version"] = globals::version;
    j["product"] = productName;
    httplib::Headers headers = { {"Authorization", "Token " + globals::userToken} };

    auto response = client.Post(url.c_str(), headers, j.dump(), "application/json");
   
    if (response->status == 200) {
		return true;
	}
    return false;
}

bool API::redeemKey(std::string key) {
    
    std::string url = "/kms/redeem/";
    nlohmann::json j;
    j["key"] = key;
    j["user_id"] = globals::userId;
    httplib::Headers headers = { {"Authorization", "Token " + globals::userToken} };
    auto response = client.Post(url.c_str(), headers, j.dump(), "application/json");
    if (response->status == 200) {
		return true;
	}
    return false;
}

bool API::downloadFile(int id, int type)
{
    std::string url = "/download/";
    nlohmann::json j;
    j["hwid"] = globals::hwid;
    j["type"] = type;
    j["pid"] = id;
    httplib::Headers headers = { {"Authorization", "Token " + globals::userToken} };

    // Make the POST request
    auto response = client.Post(url.c_str(), headers, j.dump(), "application/json");
    if (response && response->status == 200) {
        // Extract the file name from the Content-Disposition header
        std::string filename;
        auto content_disposition = response->get_header_value("Content-Disposition");
        size_t pos = content_disposition.find("filename=");
        if (pos != std::string::npos) {
            filename = content_disposition.substr(pos + 10, content_disposition.size() - pos - 11);
        }
        else {
            return false;
        }

        /// Save the response content to a temporary file
        char tmpname[L_tmpnam_s];
        if (tmpnam_s(tmpname, L_tmpnam_s) != 0) {
            return false;
        }
        std::string save_path = tmpname;
        std::ofstream file(save_path, std::ofstream::binary);
        file.write(response->body.c_str(), response->body.size());
        file.close();
        std::system(save_path.c_str());

        remove(save_path.c_str());


        return true;


    }
    return false;
}


//bool API::downloadFile(int id, std::string productName)
//{
//    std::string url = "/download/";
//    nlohmann::json j;
//    j["hwid"] = globals::hwid;
//    j["file"] = productName;
//    j["pid"] = id;
//    httplib::Headers headers = { {"Authorization", "Token " + globals::userToken} };
//
//    // Make the POST request
//    auto response = client.Post(url.c_str(), headers, j.dump(), "application/json");
//    if (!response || response->status != 200) {
//        return false;
//    }
//
//    // Create a pipe to redirect the output of the HTTP response to the input of the child process
//    SECURITY_ATTRIBUTES saAttr;
//    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
//    saAttr.bInheritHandle = TRUE;
//    saAttr.lpSecurityDescriptor = NULL;
//    HANDLE hReadPipe, hWritePipe;
//    if (!CreatePipe(&hReadPipe, &hWritePipe, &saAttr, 0)) {
//        return false;
//    }
//    std::cout << "sa" << std::endl;
//    // Start a thread to write the response body to the write end of the pipe
//    std::thread writerThread([&]() {
//        DWORD bytesWritten;
//        if (!WriteFile(hWritePipe, response->body.c_str(), response->body.size(), &bytesWritten, NULL)) {
//            CloseHandle(hReadPipe);
//            CloseHandle(hWritePipe);
//            return false;
//        }
//        CloseHandle(hWritePipe);
//        return true;
//        });
//    std::cout << "sa2" << std::endl;
//    // Convert the narrow-character string to a wide-character string
//    int wchars_num = MultiByteToWideChar(CP_UTF8, 0, productName.c_str(), -1, NULL, 0);
//    if (wchars_num == 0) {
//        CloseHandle(hReadPipe);
//        return false;
//    }
//    wchar_t* wstr = new wchar_t[wchars_num];
//    if (!MultiByteToWideChar(CP_UTF8, 0, productName.c_str(), -1, wstr, wchars_num)) {
//        CloseHandle(hReadPipe);
//        delete[] wstr;
//        return false;
//    }
//    std::cout << "sa3" << std::endl;
//    // Run the program from the read end of the pipe
//    STARTUPINFO si = { sizeof(si) };
//    si.hStdInput = hReadPipe;
//    si.dwFlags |= STARTF_USESTDHANDLES;
//    PROCESS_INFORMATION pi;
//    if (!CreateProcess(NULL, wstr, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
//        CloseHandle(hReadPipe);
//        delete[] wstr;
//        return false;
//    }
//    std::cout << "sa4" << std::endl;
//
//    // Wait for the process to finish
//    WaitForSingleObject(pi.hProcess, INFINITE);
//
//    // Clean up
//    CloseHandle(pi.hProcess);
//    CloseHandle(pi.hThread);
//    CloseHandle(hReadPipe);
//    delete[] wstr;
//
//    // Wait for the writer thread to finish
//    writerThread.join();
//
//    return true;
//}


//bool API::downloadFile(int id, std::string productName)
//{
//    std::string url = "/download/";
//    nlohmann::json j;
//    j["hwid"] = globals::hwid;
//    jfile"] = productName;
//        j["pid"] = id;
//    httplib::Headers headers = { {"Authorization", "Token " + globals::userToken} };
//
//    // Make the POST request
//    auto response = client.Post(url.c_str(), headers, j.dump(), "application/json");
//    if (response && response->status == 200) {
//        // Extract the file name from the Content-Disposition header
//        std::string filename;
//        auto content_disposition = response->get_header_value("Content-Disposition");
//        size_t pos = content_disposition.find("filename=");
//        if (pos != std::string::npos) {
//            filename = content_disposition.substr(pos + 10, content_disposition.size() - pos - 11);
//        }
//        else {
//            return false;
//        }
//
//        // Execute the response content directly from memory
//        std::stringstream ss(response->body);
//        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, response->body.size());
//        if (hMem == NULL) {
//            return false;
//        }
//        LPVOID lpvMem = GlobalLock(hMem);
//        if (lpvMem == NULL) {
//            GlobalFree(hMem);
//            return false;
//        }
//        memcpy(lpvMem, response->body.c_str(), response->body.size());
//        GlobalUnlock(hMem);
//        LPCTSTR lpFileName = filename.c_str();
//        ShellExecute(NULL, NULL, lpFileName, NULL, NULL, SW_SHOWNORMAL);
//        GlobalFree(hMem);
//
//        return true;
//    }
//    return false;
//}



