#!/usr/bin/env python3

import os
from datetime import datetime


def get_files_sorted_by_mtime(directory):
    files_with_time = []

    for root, _, files in os.walk(directory):
        for file_name in files:
            file_path = os.path.join(root, file_name)
            modified_time = os.path.getmtime(file_path)
            files_with_time.append((modified_time, file_path))

    files_with_time.sort(key=lambda item: item[1])
    return files_with_time


def main():
    target_directory = os.path.expanduser("~/my_project")

    if not os.path.exists(target_directory):
        print(f"Каталог не найден: {target_directory}")
        return

    for modified_time, file_path in get_files_sorted_by_mtime(target_directory):
        formatted_time = datetime.fromtimestamp(modified_time).strftime("%Y-%m-%d %H:%M:%S")
        print(f"{formatted_time} {file_path}")


if __name__ == "__main__":
    main()
