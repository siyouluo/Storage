#pragma once
#undef UNICODE
#include <string>
#include <vector>


class PathManager
{
public:
	PathManager(void) {};
	PathManager(const PathManager&) {};
	PathManager& operator=(const PathManager &) {};
public:
	~PathManager(void);

	static PathManager* getInstance();

	//判断是否符合目录规范,即以 \\ 或 /结尾
	bool isDirectory(const std::string& path);

	//
	bool isPathExist(const std::string& path);

	bool assertPathExist(const std::string& path);
	//由路径获取文件名
	std::string getFileName(const std::string& path);

	//由路径获取目录
	std::string getFileDirectory(const std::string& path);

	//将一条完整路径进行分割，获取每一级目录，层次依次加深
	//path：文件或文件夹路径
	std::vector<std::string> getDirectoryHierarchy(const std::string& path);

	//将传入的所有完整路径进行分割，获取每一级目录并合并重复目录，层次依次加深
	//paths：文件或文件夹路径
	std::vector<std::string> getDirectoryHierarchy(const std::vector<std::string>& paths);

	//由完整文件名获取不带后缀的文件名
	std::string getNameWithoutSuffix(const std::string& fileName);

	//由完整文件名获取后缀
	std::string getSuffix(const std::string& fileName);

	//由一条完整路径创建目录
	//path：文件或文件夹路径
	//return：成功创建路径的数量
	int createDirectory(const std::string& path);

	//由多条完整路径创建目录
	//paths：文件或文件夹路径
	//return：成功创建路径的数量
	int createDirectory(const std::vector<std::string>& paths);

	//删除文件，成功返回0，失败返回-1
	int removeFile(const std::string& fileName);

	//判断文件是否存在
	int isFileExist(const std::string& name);

	std::vector<std::string> getDirBinsSortedPath(std::string dirPath, std::string pattern="");
private:
	static	PathManager*	_pathManager;
};
