import os

root_path = os.path.abspath(os.path.join(__file__, '../'))
ignore_path = {os.path.abspath(os.path.join(root_path, '.idea')),
               os.path.abspath(os.path.join(root_path, '.git')),
               os.path.abspath(os.path.join(root_path, 'cmake-build-debug')),
               os.path.abspath(os.path.join(root_path, 'template'))}

cpp_template_path = os.path.abspath(os.path.join(root_path, r'template\tool\template.cpp'))
cpp_template = None


def countLines(path):
    assert os.path.exists(path)
    try:
        file = open(file=path, encoding='utf-8')
        texts = file.readlines()

        total_lines, valid_lines = 0, 0
        for line in texts:
            if not cpp_template.__contains__(line):
                valid_lines += 1
            total_lines += 1
        return total_lines, valid_lines
    except Exception as e:
        print(e)
        print(path)
    finally:
        return total_lines, valid_lines


def countFiles(root_path):
    assert os.path.exists(root_path)
    total_files, total_lines, valid_lines = 0, 0, 0
    item_list = os.listdir(root_path)
    if len(item_list) == 0:
        return total_files, total_lines, valid_lines
    for item in item_list:
        next_path = os.path.abspath(os.path.join(root_path, item))
        if os.path.isfile(next_path):
            if item[-4::] == '.cpp' or item[-3::] == '.py':
                total_files += 1
                ret1, ret2 = countLines(next_path)
                total_lines += ret1
                valid_lines += ret2
        else:
            if not ignore_path.__contains__(next_path):
                ret1, ret2, ret3 = countFiles(next_path)
                total_files += ret1
                total_lines += ret2
                valid_lines += ret3

    return total_files, total_lines, valid_lines


if __name__ == '__main__':
    print(root_path)
    print(cpp_template_path)
    cpp_template_file = open(cpp_template_path, 'r', encoding='utf-8')
    cpp_template = set(cpp_template_file.readlines())

    total_files, total_lines, valid_lines = countFiles(root_path)
    print(f'total files: {total_files}')
    print(f'total lines: {total_lines}')
    print(f'valid lines: {valid_lines}')
