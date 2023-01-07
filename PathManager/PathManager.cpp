//C++ winƽ̨·��������:https://blog.csdn.net/fyyyr/article/details/79251650

#include "PathManager.h"
#include <windows.h>
#include <algorithm>
#include <stdio.h>
#include <io.h>
#include <dirent.h>

PathManager*	PathManager::_pathManager = nullptr;

PathManager::~PathManager(void)
{
	if (_pathManager)
	{
		delete (_pathManager);
		_pathManager = nullptr;
	}
}

PathManager* PathManager::getInstance()
{
	if (_pathManager == nullptr)
	{
		_pathManager = new	PathManager;
	}
	return	_pathManager;
}

bool PathManager::isDirectory(const std::string& path)
{
	int index = path.length() - 1;
	if (path.find_last_of('\\') != index && path.find_last_of('/') != index)
	{
		return	false;
	}

	return	true;
}


//����ļ�����ָ���ķ���Ȩ�ޣ���������0������ļ������ڣ�����û�з���ָ����Ȩ�ޣ��򷵻�-1��
//��ע��
//	��pathΪ�ļ�ʱ��_access�����ж��ļ��Ƿ���ڣ����ж��ļ��Ƿ������ modeֵָ����ģʽ���з��ʡ�
//	��pathΪĿ¼ʱ��_accessֻ�ж�ָ����Ŀ¼�Ƿ���ڣ���WindowsNT��Windows2000�У����е�Ŀ¼���ж�дȨ�ޡ�
//
//mode��ֵ�ͺ������±���ʾ��
//modeֵ		����ļ�
//00		ֻ����ļ��Ƿ����
//02		дȨ��
//04		��Ȩ��
//06		��дȨ��
bool PathManager::isPathExist(const std::string& path)
{
	if (isDirectory(path) == false) return false;
	return _access(path.c_str(), 0)==0;
}

bool PathManager::assertPathExist(const std::string& path)
{
	std::string dir = getFileDirectory(path);
	if (!isPathExist(dir))
	{
		//std::cout << dir << " dose not exist! try to create it!" << std::endl;
		int pathCount = createDirectory(dir);
		if (pathCount == 0) return false;
	}
	return true;
}

std::string PathManager::getFileName(const std::string& path)
{
	int indexP = path.find_last_of('\\');
	int indexN = path.find_last_of('/');
	return	path.substr((indexP > indexN ? indexP : indexN) + 1, path.length());
}

std::string PathManager::getFileDirectory(const std::string& path)
{
	int indexP = path.find_last_of('\\');
	int indexN = path.find_last_of('/');
	return	path.substr(0, (indexP > indexN ? indexP : indexN) + 1);
}

//��һ������·�����зָ��ȡÿһ��Ŀ¼��������μ�С
//·������Ϊ�ļ����ļ���·��
std::vector<std::string> getDirectoryHierarchyReverse(const std::string& path)
{
	std::vector<std::string>	directoryHierarchy;
	int index = path.find_last_of('\\');
	char separator = (index > 0) ? ('\\') : ('/');

	std::string directory = path;
	int indexF = path.find_first_of(separator);
	int indexL = path.find_last_of(separator);
	while (indexF < indexL)
	{
		directory = path.substr(0, directory.find_last_of(separator));
		directoryHierarchy.push_back(directory + separator);
		indexL = directory.find_last_of(separator);
	}

	return	directoryHierarchy;
}

std::vector<std::string> PathManager::getDirectoryHierarchy(const std::string& path)
{
	std::vector<std::string>	directoryHierarchy;
	directoryHierarchy = getDirectoryHierarchyReverse(path);
	reverse(directoryHierarchy.begin(), directoryHierarchy.end());

	return	directoryHierarchy;
}

std::vector<std::string> PathManager::getDirectoryHierarchy(const std::vector<std::string>& paths)
{
	std::vector<std::string>	directoryHierarchy;
	std::vector<std::string>	directorys;
	for (auto& path : paths)
	{
		directorys.clear();
		directorys = getDirectoryHierarchyReverse(path);
		directoryHierarchy.insert(directoryHierarchy.end(), directorys.begin(), directorys.end());
	}

	sort(directoryHierarchy.begin(), directoryHierarchy.end());
	directoryHierarchy.erase(unique(directoryHierarchy.begin(), directoryHierarchy.end()), directoryHierarchy.end());

	return	directoryHierarchy;
}

std::string PathManager::getNameWithoutSuffix(const std::string& fileName)
{
	int index = fileName.find_last_of('.');
	return	fileName.substr(0, index);
}

std::string PathManager::getSuffix(const std::string& fileName)
{
	int index = fileName.find_last_of('.');
	return	fileName.substr(index + 1, fileName.length());
}

int PathManager::createDirectory(const std::string& path)
{
	int pathCount = 0;
	auto directories = getDirectoryHierarchy(path);
	if (directories.size() > 0)
	{
		for (auto& directory : directories)
		{
			::CreateDirectory(directory.c_str(), NULL);
			pathCount++;
		}
	}

	return	pathCount;
}

int PathManager::createDirectory(const std::vector<std::string>& paths)
{
	int pathCount = 0;
	for (auto& path : paths)
	{
		pathCount += createDirectory(path);
	}
	return	pathCount;
}

int PathManager::removeFile(const std::string& fileName)
{
	return remove(fileName.c_str());
}


int PathManager::isFileExist(const std::string& name) 
{
	return _access(name.c_str(), 0);
}


static std::string static_pattern_str;

static int fileNameFilter(const struct dirent *cur)
{
	std::string str(cur->d_name);
	if (str.find(static_pattern_str.c_str()) != std::string::npos) {
		return 1;
	}
	return 0;
}

//��ȡ�ļ����������ļ�������ͨ��pattern�ַ������ļ������й���
std::vector<std::string> PathManager::getDirBinsSortedPath(std::string dirPath, std::string pattern)
{
	static_pattern_str = pattern;
	struct dirent **namelist;
	std::vector<std::string> ret;
	int n = scandir(dirPath.c_str(), &namelist, fileNameFilter, versionsort);//versionsort,alphasort
	if (n < 0) {
		return ret;
	}
	for (int i = 0; i < n; ++i) {
		std::string filePath(namelist[i]->d_name);
		ret.push_back(filePath);
		free(namelist[i]);
	};
	free(namelist);
	return ret;
}



