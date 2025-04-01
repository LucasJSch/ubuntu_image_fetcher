#include "ubuntu_cloud_image_fetcher.hpp"
#include "year_month.hpp"

using json = nlohmann::json;

namespace canonical {

UbuntuCloudImageFetcher::UbuntuCloudImageFetcher() {
    fetchData();
}
    
void UbuntuCloudImageFetcher::fetchData() {
    auto response = cpr::Get(cpr::Url{URL});
    if (response.status_code == 200) {
        data = json::parse(response.text);
    } else {
        throw std::runtime_error("Failed to fetch data from Ubuntu cloud API.");
    }
}

std::vector<std::string> UbuntuCloudImageFetcher::getSupportedReleases() {
    std::vector<std::string> releases;
    for (auto& product : data["products"].items()) {
        if (product.value()["supported"])
        {
            releases.push_back(product.key());
        }
    }
    return releases;
}

std::string UbuntuCloudImageFetcher::getCurrentLTSVersion() {
    auto supported_releases = getSupportedReleases();
    YearMonth latest_ym = {0, 0};
    for (auto& release : supported_releases) {
        auto release_title = data["products"][release]["release_title"].get<std::string>();
        auto version = data["products"][release]["version"].get<std::string>();
        if (release_title.find("LTS") != std::string::npos) {
            YearMonth ym = parseYearMonth(version);
            if (latest_ym < ym) {
                latest_ym = ym;
            }
        }
    }
    if (latest_ym.year == 0) {
        return "No LTS version found";
    }
    return latest_ym.toStringShort();
}

std::string UbuntuCloudImageFetcher::getSha256(const std::string& release) {
    auto items = data["products"][release]["versions"].items();
    auto last_item = items.begin();

    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it.key().find_first_not_of("0123456789.") != std::string::npos) {
            continue;  // Skip non-numeric keys
        }
        last_item = it;
    }

    return last_item.value()["items"]["disk1.img"]["sha256"];
}
    

} // namespace canonical