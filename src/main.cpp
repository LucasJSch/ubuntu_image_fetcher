#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <chrono>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "ubuntu_cloud_image_fetcher.hpp"

using json = nlohmann::json;


int main(int argc, char* argv[]) {
    canonical::UbuntuCloudImageFetcher fetcher;

    if (argc < 2) {
        std::cerr << "Usage: ./ubuntu_image_fetcher <option> [release]" << std::endl;
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
