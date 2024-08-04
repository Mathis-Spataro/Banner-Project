#ifndef SETTINGSDAO_H
#define SETTINGSDAO_H
#include <algorithm>
#include <filesystem>

struct GraphicsSettings {
    bool raytracing = false;
    float fov = (2 * 3.14) / 5;
    float near = 1.0f;
    float far = 100.0f;
};

// Developper internal settings
struct ProgramSettings {
    ProgramSettings() {
        // init assets_dir
        // dev, until path finder class
        const std::filesystem::path path = PROGRAM_ROOT_DIR;
        std::string pathStr = path.string();
        std::replace(pathStr.begin(), pathStr.end(), '\\', '/');
        rootDir = pathStr;
    }
    std::string rootDir;
};

class SettingsDao { // Singleton
public :
    // --- -- Constructors -- --- //
    SettingsDao(const SettingsDao&) = delete;
    void operator=(const SettingsDao&) = delete;
    static std::shared_ptr<SettingsDao> getPtr() {
        static std::shared_ptr<SettingsDao> instance(new SettingsDao);
        return instance;
    }

    // --- -- Accessors -- --- //
    [[nodiscard]] const GraphicsSettings& graphicsSettings() const { return _graphicsSettings; }
    GraphicsSettings& graphicsSettings() { return _graphicsSettings; }
    [[nodiscard]] const ProgramSettings& programSettings() const { return _programSettings; }
    ProgramSettings& programSettings() { return _programSettings; }

protected:
    SettingsDao() : _graphicsSettings(), _programSettings() {}

    // ---- ---- Data ---- ---- //
    GraphicsSettings _graphicsSettings;
    ProgramSettings _programSettings;

}; // SettingsDao


#endif //SETTINGSDAO_H
