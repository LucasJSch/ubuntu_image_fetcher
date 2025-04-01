#include <vector>
#include <string>

namespace canonical {
// Interface definition
class UbuntuImageFetcherInterface {
    public:
        virtual ~UbuntuImageFetcherInterface() = default;
        virtual std::vector<std::string> getSupportedReleases() = 0;
        virtual std::string getCurrentLTSVersion() = 0;
        virtual std::string getSha256(const std::string& release) = 0;
};
} // namespace canonical