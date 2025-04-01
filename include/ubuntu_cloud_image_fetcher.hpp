#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <chrono>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include "ubuntu_image_fetcher_interface.hpp"

namespace canonical {

class UbuntuCloudImageFetcher : public UbuntuImageFetcherInterface {
private:
    nlohmann::json data;
    const std::string URL = "https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json";

    // Fetch data from the URL and parse it into JSON
    void fetchData();

public:
    // Constructor
    UbuntuCloudImageFetcher();
    
    std::vector<std::string> getSupportedReleases() override;

    // Gets the latest LTS version available.
    std::string getCurrentLTSVersion() override;

    // Assuming that the SHA256 wanted is of the latest version of the release.
    // For amd64 it's not necessary, since there's only one version.
    // For other architectures, we need to find the latest version.
    std::string getSha256(const std::string& release) override;
};

} // namespace canonical