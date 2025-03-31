#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Interface definition
class UbuntuImageFetcherInterface {
public:
    virtual ~UbuntuImageFetcherInterface() = default;
    virtual std::vector<std::string> getSupportedReleases() = 0;
    virtual std::string getCurrentLTSVersion() = 0;
    virtual std::string getSha256(const std::string& release) = 0;
};

// Derived class implementation
class UbuntuCloudImageFetcher : public UbuntuImageFetcherInterface {
private:
    json data;
    const std::string url = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";

    void fetchData() {
        /*auto response = cpr::Get(cpr::Url{url});
        if (response.status_code == 200) {
            data = json::parse(response.text);
        } else {
            throw std::runtime_error("Failed to fetch data from Ubuntu cloud image API.");
        }*/
    }

public:
    UbuntuCloudImageFetcher() {
        //fetchData();
    }

    std::vector<std::string> getSupportedReleases() override {
        std::vector<std::string> releases;
        for (auto& product : data["products"].items()) {
            releases.push_back(product.key());
        }
        return releases;
    }

    std::string getCurrentLTSVersion() override {
        for (auto& product : data["products"].items()) {
            if (product.key().find("lts") != std::string::npos) {
                return product.key();
            }
        }
        return "Unknown";
    }

    std::string getSha256(const std::string& release) override {
        if (data["products"].contains(release)) {
            for (const auto& item : data["products"][release]["versions"].items()) {
                for (const auto& arch : item.value()["items"].items()) {
                    if (arch.key() == "amd64") {
                        return arch.value()["sha256"]["disk1.img"];
                    }
                }
            }
        }
        return "Not Found";
    }
};

int main(int argc, char* argv[]) {
    UbuntuCloudImageFetcher fetcher;

    if (argc < 2) {
        std::cerr << "Usage: ./ubuntu_fetcher <option> [release]" << std::endl;
        return 1;
    }

    std::string option = argv[1];

    if (option == "--list") {
        for (const auto& release : fetcher.getSupportedReleases()) {
            std::cout << release << std::endl;
        }
    } else if (option == "--lts") {
        std::cout << "Current LTS: " << fetcher.getCurrentLTSVersion() << std::endl;
    } else if (option == "--sha256" && argc == 3) {
        std::string release = argv[2];
        std::cout << "SHA256: " << fetcher.getSha256(release) << std::endl;
    } else {
        std::cerr << "Invalid option." << std::endl;
    }

    return 0;
}
