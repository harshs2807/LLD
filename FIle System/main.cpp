#include <bits/stdc++.h>
using namespace std;

class File
{
	private:
		string fileName;
        string content;
        int fileSize;

	public:
		File(const string &name): fileName(name), fileSize(0) {}

        string getName() const
        {
            return fileName;
        }

        int getSize() const
        {
            return fileSize;
        }

        string getContent() const
        {
            return content;
        }

        void setContent(const string &fileContent)
        {
            content = fileContent;
            fileSize = content.length();
        }
};

class Directory
{
	private:
	    string directoryName;
	    vector<File> files;
	    vector<Directory> subdirectories;

	public:
		Directory(const string &name): directoryName(name) {}

        string getName() const
        {
            return directoryName;
        }

        void addFile(const File &file)
        {
            files.push_back(file);
        }

        void deleteFile(const string &fileName)
        {
            for (auto it = files.begin(); it != files.end(); ++it)
            {
                if (it->getName() == fileName)
                {
                    files.erase(it);
                    break;
                }
            }
        }

        void listFiles() const
        {
            cout << "Files in directory \"" << directoryName << "\":\n";
            for (const auto &file: files)
            {
                cout << "- " << file.getName() << " (" << file.getSize() << " bytes)\n";
            }
        }

        vector<File> &getFiles()
        {
            return files;
        }
};

class FileSystem
{
	private:
		Directory rootDirectory;

	public:
		FileSystem(): rootDirectory("root") {}

        void createFile(const string &fileName)
        {
            File newFile(fileName);
            rootDirectory.addFile(newFile);
            cout << "File \"" << fileName << "\" created.\n";
        }

        void deleteFile(const string &fileName)
        {
            rootDirectory.deleteFile(fileName);
            cout << "File \"" << fileName << "\" deleted.\n";
        }

        void readFile(const string &fileName)
        {
            for (auto &file: rootDirectory.getFiles())
            {
                if (file.getName() == fileName)
                {
                    cout << "Content of file \"" << fileName << "\":\n";
                    cout << file.getContent() << "\n";
                    return;
                }
            }

            cout << "File \"" << fileName << "\" not found.\n";
        }

        void writeFile(const string &fileName, const string &content)
        {
            for (auto &file: rootDirectory.getFiles())
            {
                if (file.getName() == fileName)
                {
                    file.setContent(content);
                    cout << "Content written to file \"" << fileName << "\".\n";
                    return;
                }
            }

            cout << "File \"" << fileName << "\" not found.\n";
        }
};

int main()
{
	FileSystem fileSystem;

	fileSystem.createFile("file1.txt");
	fileSystem.createFile("file2.txt");
	fileSystem.createFile("file3.txt");

	fileSystem.writeFile("file1.txt", "This is the content of file 1");
	fileSystem.writeFile("file2.txt", "This is the content of file 2");
	fileSystem.writeFile("file3.txt", "This is the content of file 3");

	fileSystem.readFile("file1.txt");
	fileSystem.readFile("file2.txt");
	fileSystem.readFile("file3.txt");

	fileSystem.deleteFile("file2.txt");

	fileSystem.readFile("file2.txt");

	return 0;
}