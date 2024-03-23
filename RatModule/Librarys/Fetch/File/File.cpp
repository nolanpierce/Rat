#include "File.h"


/// <summary>
/// function that will search from the root directory to all others to find specific file
/// </summary>
/// <returns>file paths containing given file name</returns>
std::vector<std::string> File::all_paths() {
    
    std::vector<std::string> found_paths;

    std::filesystem::path root_path = std::filesystem::path("/").root_path();
    
    if (!std::filesystem::exists(root_path) || !std::filesystem::is_directory(root_path)) {
#ifdef _MSC_VER
        std::cerr << "Error: Path or directory does not exist " << root_path << std::endl;
#endif 
        return {};
    }

    for (const auto& entry : std::filesystem::recursive_directory_iterator(root_path)) {
        if (std::filesystem::is_regular_file(entry) && entry.path().filename() == this->file_name) {

            found_paths.push_back(entry.path().parent_path().string());
        }

    }

    if (found_paths.empty()) {
#ifdef _MSC_VER
        std::cerr << "Error: Failed to iterate through path " << root_path << std::endl;
#endif 
        return {};
    }

    return found_paths;
    
}

std::string File::path()
{
    //could do this differently but am lazy rn
    this->file_path = this->all_paths().at(1);
    if (this->file_path.empty()) {
#ifdef _MSC_VER
        std::cerr << "Error: "<< this->file_name << " cant be found" << std::endl;
#endif 
    }

    return file_path;
}

std::string File::name()
{
    return this->file_name;
}

std::vector<uint8_t> File::image() {

    std::ifstream file(this->file_path, std::ios::binary);
    if (!file) {
#ifdef _MSC_VER
        std::cerr << "Error: Unable to open file " << this->file_path << std::endl;
#endif 
        return{};
    }

    file.seekg(0, std::ios::end);
    std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> file_image(file_size);
    file.read(reinterpret_cast<char*>(file_image.data()), file_size);
    if (file_image.empty()) {
#ifdef _MSC_VER
        std::cerr << "Error: Failed to get image " << this->file_path << std::endl;
#endif 
        return{};
    }
    return file_image;
}
