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

	//�ж��Ƿ����Ŀ¼�淶,���� \\ �� /��β
	bool isDirectory(const std::string& path);

	//
	bool isPathExist(const std::string& path);

	bool assertPathExist(const std::string& path);
	//��·����ȡ�ļ���
	std::string getFileName(const std::string& path);

	//��·����ȡĿ¼
	std::string getFileDirectory(const std::string& path);

	//��һ������·�����зָ��ȡÿһ��Ŀ¼��������μ���
	//path���ļ����ļ���·��
	std::vector<std::string> getDirectoryHierarchy(const std::string& path);

	//���������������·�����зָ��ȡÿһ��Ŀ¼���ϲ��ظ�Ŀ¼��������μ���
	//paths���ļ����ļ���·��
	std::vector<std::string> getDirectoryHierarchy(const std::vector<std::string>& paths);

	//�������ļ�����ȡ������׺���ļ���
	std::string getNameWithoutSuffix(const std::string& fileName);

	//�������ļ�����ȡ��׺
	std::string getSuffix(const std::string& fileName);

	//��һ������·������Ŀ¼
	//path���ļ����ļ���·��
	//return���ɹ�����·��������
	int createDirectory(const std::string& path);

	//�ɶ�������·������Ŀ¼
	//paths���ļ����ļ���·��
	//return���ɹ�����·��������
	int createDirectory(const std::vector<std::string>& paths);

	//ɾ���ļ����ɹ�����0��ʧ�ܷ���-1
	int removeFile(const std::string& fileName);

	//�ж��ļ��Ƿ����
	int isFileExist(const std::string& name);

	std::vector<std::string> getDirBinsSortedPath(std::string dirPath, std::string pattern="");
private:
	static	PathManager*	_pathManager;
};
