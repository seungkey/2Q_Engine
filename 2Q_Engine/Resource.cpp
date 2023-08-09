#include "pch.h"
#include "Resource.h"

#include "D2DRenderer.h"
#include "AnimationAsset.h"

#include <istream>
#include <fstream>

Resource::Resource()
{
}

Resource::~Resource()
{
}

void Resource::Initialize()
{
}

void Resource::LoadAnimation(wstring _animPath, D2DRenderer* _pRenderer)
{
    // ������ �������� ������ ������
    filesystem::path animPath(_animPath);
    assert(filesystem::exists(animPath) && filesystem::is_directory(animPath));
    
    // ���� �� ���� ��ȸ
    for (const auto& entry : filesystem::directory_iterator(_animPath))
    {
        const filesystem::path& filePath = entry.path();

        // ������ ���������� ������ ������
        assert(filesystem::is_regular_file(filePath) && filePath.has_extension());

        if (filePath.extension() == ".txt")
            LoadAnimInfoFromTextFile(filePath, _pRenderer);
    }
}

void Resource::LoadAnimInfoFromTextFile(filesystem::path _filePath, D2DRenderer* _pRenderer)
{
    std::ifstream file(_filePath);

    // ������ �� �� ������ ������
    assert(file.is_open());

    // ���� �ϳ��� �ϳ��� �ִϸ��̼� ������ �߰��ȴ�
    AnimationInfo* animInfo;

    std::string line;
    bool isFirstLine = true;

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        // ù ���� ���� ó��
        if (isFirstLine)
        {
            isFirstLine = false;
            std::wstring wstr;
            wstr.assign(line.begin(), line.end());

            // ��Ʈ�� Ű�� ��� ���� �Ǵ� �޾ƿ���
            AnimationAsset* animAsset = _pRenderer->CreateAnimationAsset(wstr);

            // ���ϸ����� ��¿� ���� �߰�
            ///animInfo = animAsset->AddAnimationInfo(filePath.stem().string());

            continue;
        }

        std::string  delimiter = ",";
        std::string  token;
        int pos = 0;
        int index = 0;

        while (true)
        {
            pos = (int)line.find(delimiter);
            token = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());

            float top, left, bottom, right;

            switch (index)
            {
                case 0:
                    top = stof(token);
                    break;
                case 1:
                    left = stof(token);
                    break;
                case 2:
                    bottom = stof(token);
                    break;
                case 3:
                    right = stof(token);
                    break;
            }

            // �� �� �� ������ ���� �߰�
            ///animInfo->AddFrameInfo(top, left, bottom, left);
            index++;

            // �� �̻� ���ڰ� �߰ߵ��� ������ ���� �ٷ� �Ѿ�� 
            if (pos == std::string::npos) break;
        }
    }
    file.close();

}


