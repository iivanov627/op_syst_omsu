#!/usr/bin/env python3

import os


def count_files(directory):
    total_files = 0

    for _, _, files in os.walk(directory):
        total_files += len(files)

    return total_files


def main():
    target_directory = os.path.expanduser("~/my_project/lab1")

    if not os.path.exists(target_directory):
        print(f"Каталог не найден: {target_directory}")
        return

    files_count = count_files(target_directory)
    print(f"Найдено {files_count} файлов.")


if __name__ == "__main__":
    main()
